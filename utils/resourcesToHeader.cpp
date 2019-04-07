#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <zlib.h>
#include <string>
#include <algorithm>

using namespace std;

// modified from https://stackoverflow.com/questions/4538586/how-to-compress-a-buffer-with-zlib
// to use deflateInit2 to output gzip instead.
void compress_memory(std::vector<uint8_t> in_data, std::vector<uint8_t> &buffer)
{
    const size_t BUFFER_SIZE = 8 * 1024;
    uint8_t temp_buffer[BUFFER_SIZE];

    z_stream strm;
    strm.zalloc = nullptr;
    strm.zfree = nullptr;
    strm.opaque = nullptr;
    strm.next_in = in_data.data();
    strm.avail_in = in_data.size();
    strm.next_out = temp_buffer;
    strm.avail_out = BUFFER_SIZE;

    // Use the gzip version of deflate.
    deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                 15 | 16,
                 8,
                 Z_DEFAULT_STRATEGY);

    while (strm.avail_in != 0)
    {
        int res = deflate(&strm, Z_NO_FLUSH);
        assert(res == Z_OK);
        if (strm.avail_out == 0)
        {
            buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFFER_SIZE);
            strm.next_out = temp_buffer;
            strm.avail_out = BUFFER_SIZE;
        }
    }

    int deflate_res = Z_OK;
    while (deflate_res == Z_OK)
    {
        if (strm.avail_out == 0)
        {
            buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFFER_SIZE);
            strm.next_out = temp_buffer;
            strm.avail_out = BUFFER_SIZE;
        }
        deflate_res = deflate(&strm, Z_FINISH);
    }

    assert(deflate_res == Z_STREAM_END);
    buffer.insert(buffer.end(), temp_buffer, temp_buffer + BUFFER_SIZE - strm.avail_out);
    deflateEnd(&strm);
}

int main (int argc, char *argv[])
{
    if (argc != 3) {
        cout << "Usage: resourcesToHeader <target directory> <output filename>" << endl;
        return (0);
    }

    // Change the working directory to the target.
    chdir(argv[1]);

    DIR *dp;
    struct dirent *ep;
    struct stat file_info{};
    std::stringstream headerContent;
    std::stringstream resources;
    std::stringstream contentData;
    std::stringstream contentLine;
    headerContent << "#ifndef WWW_CONTENT_H" << endl \
                << "#define WWW_CONTENT_H" << endl \
                << "" << endl \
                << "struct wwwFile" << endl \
                << "{" << endl \
                << "    String name;" << endl \
                << "    unsigned int offset;" << endl \
                << "    unsigned int size;" << endl \
                << "};" << endl\
                << "" << endl\
                << "\n";
    resources   << "const wwwFile wwwContent[]   = {";
    contentData << "uint8_t wwwContentData[] PROGMEM = {";
    dp = opendir (argv[1]);
    if (dp != nullptr)
    {
        int offset = 0;
        string delim = "";
        while ((ep = readdir (dp))) {
            stat(ep->d_name, &file_info);
            // Regular file, and not a directory.
            if (S_ISREG(file_info.st_mode)) {
                // read file
                ifstream fin(ep->d_name, ifstream::binary);
                cout << "Processing [" << ep->d_name << "]." << endl;
                vector<uint8_t> buffer (file_info.st_size,0);
                fin.read((char*)buffer.data(), buffer.size());
                vector<uint8_t> compressedBuffer;
                compress_memory(buffer,compressedBuffer);
                // this assumes file names that are less than 25 chars. Adjust as needed.
                resources << delim << endl << setw(36) << "{"
                        << setw(25) << string("\"") + ep->d_name + "\", "
                        << setw(5) << to_string(offset) << ", "
                        << setw(5) << to_string(compressedBuffer.size())
                        << "}";
                offset += compressedBuffer.size();
                contentData << delim << endl << setw(38) << " " << "// [" << ep->d_name << "]" << endl;
                delim = "";
                int columnCount = 0;
                for (auto it = compressedBuffer.begin(); it != compressedBuffer.end(); ++it) {
                    contentLine << delim << "0x" << hex << setfill('0') << setw(2) << (unsigned int) *it;
                    if (columnCount++ > 13) {
                        contentData << setw(126) << contentLine.str() << delim << endl;
                        std::stringstream().swap(contentLine);
                        delim = "";
                        columnCount = 0;
                    } else if (it == compressedBuffer.end() - 1) {
                        contentData << setw(38) << " " << contentLine.str();
                        std::stringstream().swap(contentLine);
                    } else {
                        delim = ", ";
                    }
                }
                delim = ", ";
                string compressedFile(ep->d_name);
#ifdef DEBUG
                compressedFile += ".gz";
                ofstream cprsout(compressedFile, ofstream::binary | ofstream::trunc );
                cprsout.write(reinterpret_cast<char*>(&compressedBuffer[0]), compressedBuffer.size() * sizeof(uint8_t));
#endif

            }
        }
        contentData << endl << setw(36) << " " << "};" << endl << endl;
        resources << endl << setw(33) << "};" << endl << endl;
        // write the stream to disk.
        ofstream fout(argv[2], ofstream::binary | ofstream::trunc );
        fout << headerContent.str() << resources.str() << contentData.str() << endl << "#endif";
        cout << "Done.";
        (void) closedir (dp);
    }
    else {
        perror("Couldn't open the directory");
    }
    return 0;
}