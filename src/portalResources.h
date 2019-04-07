#ifndef WWW_CONTENT_H
#define WWW_CONTENT_H

struct wwwFile
{
    String name;
    unsigned int offset;
    unsigned int size;
};


const wwwFile wwwContent[]   = {
                                   {           "index.html",     0,   317},
                                   {             "main.css",   317,   427},
                                   {              "main.js",   744,   298}
                               };

uint8_t wwwContentData[] PROGMEM = {
                                      // [index.html]
                                      0x78, 0xda, 0xbd, 0x94, 0xc1, 0x6e, 0xc2, 0x30, 0x0c, 0x86, 0xef, 0x93, 0xf6, 0x0e, 0x51,
                                      0xa4, 0x29, 0x43, 0x9a, 0x28, 0xbb, 0xb2, 0xa6, 0x97, 0x71, 0xd8, 0x2e, 0x68, 0x12, 0x4f,
                                      0x10, 0x92, 0x40, 0xb2, 0xa6, 0x69, 0x14, 0xbb, 0x74, 0xbc, 0xfd, 0xd2, 0x52, 0x24, 0xe8,
                                      0xc4, 0x4e, 0x40, 0x2e, 0xa9, 0xe3, 0xdf, 0xf6, 0xff, 0x45, 0x6a, 0x72, 0x83, 0x95, 0x2b,
                                      0x1e, 0x1f, 0x48, 0x5a, 0xb9, 0xd1, 0x42, 0x15, 0x79, 0xd6, 0x6f, 0xc3, 0x11, 0xc8, 0x68,
                                      0x03, 0x12, 0x88, 0x92, 0xd3, 0x4a, 0x58, 0x3f, 0xfd, 0x06, 0x9a, 0x24, 0x87, 0xe3, 0xa3,
                                      0xc8, 0x59, 0x5f, 0x92, 0xa8, 0x1d, 0xa7, 0x80, 0x7b, 0xa7, 0xc1, 0x68, 0x8d, 0x94, 0xe0,
                                      0x3e, 0x68, 0x4e, 0x51, 0xff, 0x60, 0x26, 0x01, 0x28, 0x31, 0x51, 0x6f, 0x86, 0x26, 0x5d,
                                      0x7c, 0x2c, 0x56, 0x76, 0x47, 0xa4, 0x13, 0x00, 0x9c, 0xb5, 0x51, 0x84, 0xa0, 0x23, 0x1b,
                                      0x52, 0xe3, 0x74, 0xe7, 0xeb, 0x3c, 0xdb, 0xad, 0xa5, 0xc6, 0xb6, 0x8e, 0xe5, 0x49, 0x49,
                                      0x96, 0x6a, 0x2e, 0xb4, 0x88, 0x75, 0x3b, 0xae, 0x3f, 0x4d, 0x4b, 0x11, 0xd0, 0xd6, 0x9e,
                                      0x15, 0xab, 0xd5, 0xe7, 0x62, 0x3e, 0x6e, 0x34, 0x56, 0x5b, 0x1f, 0x1a, 0x64, 0x45, 0xde,
                                      0xef, 0xa4, 0x47, 0xe7, 0xb4, 0xb5, 0x0a, 0xcd, 0x9c, 0xbc, 0xce, 0x66, 0x4f, 0x94, 0xd4,
                                      0x5e, 0x1a, 0xe1, 0xb7, 0x9a, 0xb3, 0x26, 0x28, 0x81, 0xfa, 0xbd, 0xf6, 0x1b, 0xbb, 0x7d,
                                      0xa6, 0x00, 0x56, 0xd1, 0x17, 0x82, 0xc6, 0xc2, 0x74, 0x27, 0x5c, 0xa3, 0x27, 0x6f, 0x2c,
                                      0x2b, 0xfe, 0x18, 0xbf, 0x02, 0xc8, 0x57, 0x0a, 0xd3, 0xf5, 0xa8, 0x1b, 0xc2, 0x84, 0x61,
                                      0xc4, 0x7d, 0x80, 0x3e, 0x6a, 0x40, 0xb2, 0x14, 0x95, 0xbe, 0x02, 0xd1, 0x45, 0x24, 0x93,
                                      0x86, 0xf8, 0x34, 0xe3, 0x3e, 0x48, 0xd5, 0x62, 0xb9, 0xba, 0x25, 0x4d, 0xa5, 0x3c, 0xdc,
                                      0x94, 0x64, 0xdd, 0x20, 0x76, 0x20, 0xe7, 0x8a, 0x5e, 0x75, 0x48, 0x75, 0xd6, 0x9c, 0x95,
                                      0x25, 0x67, 0xd0, 0xac, 0x2b, 0x8b, 0x83, 0xb3, 0x49, 0xfa, 0xd1, 0xfa, 0x38, 0xcf, 0x0e,
                                      0xba, 0xf1, 0x8c, 0x7f, 0x2c, 0x1e, 0xbf, 0xd3, 0x73, 0xd5, 0xbd, 0x60, 0xbf, 0x33, 0x05,
                                      0x58, 0xa6,
                                      // [main.css]
                                      0x78, 0xda, 0x95, 0x53, 0xdb, 0x4e, 0x84, 0x30, 0x10, 0x7d, 0xdf, 0x64, 0xff, 0x61, 0x5e,
                                      0x4c, 0x74, 0x13, 0x14, 0x57, 0x63, 0x0c, 0x9b, 0x18, 0x7f, 0xa5, 0xd0, 0x01, 0xc6, 0x2d,
                                      0x6d, 0x53, 0x8a, 0x48, 0x8c, 0xff, 0x6e, 0xcb, 0xa5, 0xb0, 0x2e, 0xde, 0xf6, 0x89, 0x9d,
                                      0xcb, 0x39, 0x67, 0xce, 0x4c, 0xaf, 0x5b, 0xc3, 0xb4, 0x46, 0x03, 0xef, 0xdb, 0x0d, 0xb8,
                                      0x1f, 0xa7, 0x5a, 0x0b, 0xd6, 0x25, 0x90, 0x0b, 0x7c, 0x3b, 0x0c, 0x31, 0xff, 0x19, 0xe5,
                                      0x42, 0xb5, 0x09, 0x18, 0xd5, 0x82, 0xef, 0x98, 0x32, 0x4a, 0xda, 0xa8, 0x45, 0x2a, 0x4a,
                                      0x9b, 0x40, 0xaa, 0x04, 0x5f, 0x74, 0x24, 0x70, 0x0b, 0xb7, 0x71, 0x7c, 0x31, 0x86, 0x34,
                                      0xe3, 0x9c, 0x64, 0xe1, 0xa2, 0xb1, 0xf6, 0xc0, 0x1f, 0xdb, 0xcd, 0x76, 0x73, 0x3d, 0xb1,
                                      0x3f, 0xc1, 0x6e, 0x52, 0xf0, 0xa5, 0x77, 0xa8, 0x2b, 0x91, 0xf1, 0x59, 0x64, 0xca, 0xb2,
                                      0x63, 0x61, 0x54, 0x23, 0xb9, 0x57, 0xd4, 0x31, 0x91, 0x8a, 0x06, 0x47, 0x9e, 0x4c, 0x09,
                                      0x65, 0x12, 0x68, 0x4b, 0xb2, 0x53, 0xc8, 0xe2, 0x9b, 0x8d, 0x98, 0xa0, 0x42, 0x26, 0x90,
                                      0xa1, 0xb4, 0x68, 0x7e, 0xd4, 0xe4, 0x67, 0x5c, 0x21, 0xaa, 0x49, 0xbc, 0x86, 0xce, 0xde,
                                      0x12, 0x4e, 0x06, 0x33, 0x4b, 0x4a, 0xf6, 0xbe, 0x2c, 0x33, 0x7e, 0xac, 0x64, 0x69, 0x54,
                                      0xb0, 0x95, 0xa4, 0x20, 0x89, 0xd1, 0xc2, 0xdd, 0x5e, 0x58, 0xe4, 0xd4, 0x56, 0xf5, 0x17,
                                      0x79, 0x15, 0x33, 0x05, 0x39, 0x70, 0xd6, 0x58, 0x15, 0xd4, 0x65, 0x4c, 0x7b, 0xca, 0x49,
                                      0xe1, 0xcd, 0xee, 0x44, 0xa4, 0x56, 0xad, 0xf3, 0xa9, 0xb7, 0x03, 0x76, 0x37, 0xeb, 0x53,
                                      0xfa, 0x98, 0x32, 0xae, 0xcc, 0x45, 0xc6, 0xbf, 0x2d, 0x71, 0x5b, 0x26, 0xb0, 0x0f, 0xdb,
                                      0x3a, 0x0b, 0x2c, 0x3d, 0x34, 0x7e, 0xdf, 0x41, 0x10, 0x49, 0xdd, 0xd8, 0x6f, 0xe4, 0x08,
                                      0x5f, 0x59, 0x18, 0x44, 0xf9, 0x27, 0x39, 0xfb, 0x53, 0xf6, 0x87, 0xc0, 0xfe, 0xd2, 0xd4,
                                      0x96, 0xf2, 0x2e, 0xca, 0xdc, 0xbd, 0x39, 0x87, 0x16, 0x3e, 0x0d, 0x1a, 0xd2, 0xc6, 0xda,
                                      0xd9, 0x93, 0x35, 0x86, 0xef, 0x11, 0xfe, 0xbf, 0x03, 0x47, 0x98, 0x2b, 0x65, 0xd7, 0xef,
                                      0x71, 0x31, 0xf2, 0xa4, 0xae, 0x62, 0x14, 0xb4, 0x2d, 0x7d, 0x14, 0x98, 0xdb, 0xc3, 0x39,
                                      0x02, 0x47, 0xd4, 0xf5, 0xb1, 0x1b, 0x6f, 0x7a, 0x80, 0x60, 0x35, 0x71, 0x8c, 0xf6, 0x6b,
                                      0x84, 0xa5, 0xb2, 0x9a, 0xe4, 0x71, 0x2a, 0x7d, 0xae, 0x90, 0x13, 0x73, 0x13, 0x09, 0x60,
                                      0x92, 0xc3, 0x65, 0x45, 0x32, 0x0a, 0x7e, 0x3a, 0x3f, 0xae, 0x26, 0x8c, 0x01, 0x13, 0xde,
                                      0xc3, 0x83, 0x8b, 0x21, 0x3e, 0xc0, 0xc7, 0xef, 0x30, 0x8f, 0xa7, 0x30, 0xc3, 0x74, 0x23,
                                      0xca, 0x1d, 0x78, 0xcb, 0x3d, 0x4a, 0x9f, 0xeb, 0x1f, 0x43, 0xff, 0x9e, 0xe6, 0x8b, 0x9b,
                                      0x93, 0x83, 0x87, 0x73, 0xee, 0x7e, 0xa6, 0x4f, 0x15, 0xef, 0xce, 0xd6, 0xb9, 0xc7, 0xca,
                                      0x4f, 0xf9, 0x09, 0x7f, 0x08, 0x53, 0x1e,
                                      // [main.js]
                                      0x78, 0xda, 0x75, 0x91, 0x31, 0x6f, 0x83, 0x30, 0x10, 0x85, 0x77, 0x24, 0xfe, 0xc3, 0x29,
                                      0x8b, 0x8d, 0x1a, 0x81, 0xba, 0x55, 0x44, 0x9d, 0xd2, 0x2e, 0x1d, 0xda, 0x81, 0xa1, 0x43,
                                      0x94, 0xc1, 0x81, 0x83, 0xa2, 0x10, 0x3b, 0xb2, 0x0d, 0x51, 0x94, 0xe6, 0xbf, 0xf7, 0xb0,
                                      0x93, 0x16, 0x1a, 0xe2, 0xc1, 0xb2, 0xde, 0x9d, 0xbf, 0xf7, 0xec, 0xeb, 0x84, 0x86, 0x5c,
                                      0xc9, 0xb2, 0xae, 0xe0, 0x19, 0x4e, 0xe7, 0x45, 0x18, 0x74, 0x5e, 0x91, 0x98, 0xdb, 0x5a,
                                      0x49, 0x52, 0x25, 0x1e, 0xe0, 0x13, 0x37, 0x99, 0xca, 0xb7, 0x68, 0x39, 0x3b, 0x98, 0x34,
                                      0x49, 0x18, 0x3c, 0x40, 0xa3, 0x72, 0xd1, 0xb7, 0xc4, 0x5f, 0xca, 0x58, 0x29, 0x76, 0x48,
                                      0x1a, 0x4b, 0x9f, 0x1e, 0x13, 0x36, 0x87, 0x15, 0x13, 0xba, 0x68, 0x6b, 0xa9, 0xd8, 0x3a,
                                      0x22, 0xe6, 0x1f, 0x2f, 0x56, 0x52, 0xed, 0xb1, 0xc7, 0x96, 0xad, 0x74, 0x0a, 0x8f, 0xe0,
                                      0x14, 0x06, 0x40, 0x6b, 0xd0, 0x65, 0x50, 0x16, 0x9c, 0x2d, 0xbd, 0x00, 0xbd, 0x5b, 0x9f,
                                      0xe2, 0x45, 0x58, 0xe4, 0x51, 0x0f, 0x3c, 0xff, 0x87, 0xa2, 0xd6, 0x4a, 0x0f, 0xa9, 0x4e,
                                      0x18, 0xa2, 0x8d, 0x6a, 0x30, 0x6e, 0x54, 0xc5, 0xd9, 0xef, 0x63, 0xe0, 0xd5, 0xdd, 0xa2,
                                      0xbc, 0xbe, 0x7b, 0x0a, 0xbc, 0x43, 0x63, 0x44, 0x85, 0x23, 0xf4, 0x34, 0x36, 0x43, 0xdd,
                                      0xa1, 0x4e, 0x1d, 0x2e, 0x2e, 0x84, 0x15, 0x93, 0xbc, 0xbc, 0x51, 0x06, 0xef, 0x3d, 0x7f,
                                      0x2a, 0xe3, 0x60, 0x16, 0xee, 0x6e, 0xc1, 0xae, 0xdc, 0x30, 0xb8, 0x42, 0xa0, 0xdd, 0x93,
                                      0x21, 0x2e, 0xdd, 0x20, 0xf9, 0x16, 0x8f, 0x73, 0xe8, 0x44, 0xd3, 0x8e, 0x82, 0x52, 0x65,
                                      0x45, 0x95, 0x35, 0x79, 0xbb, 0xda, 0xe2, 0xd6, 0x75, 0x46, 0xf5, 0x14, 0x66, 0xf4, 0xdb,
                                      0x74, 0xa0, 0x7d, 0x06, 0xdf, 0xbe, 0xd7, 0x8b, 0x1e, 0xd9, 0x9b, 0x8f, 0xbc, 0x4d, 0xbb,
                                      0xd9, 0xd5, 0xf6, 0xe2, 0x7d, 0x77, 0x98, 0x6f, 0xd9, 0xc7, 0x7b, 0x6c, 0xac, 0xae, 0x65,
                                      0x55, 0x97, 0x47, 0xee, 0x03, 0x45, 0x17, 0xda, 0x0f, 0x9a, 0x68, 0xcd, 0x70
                                    };


#endif