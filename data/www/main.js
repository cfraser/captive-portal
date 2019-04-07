var config = {};
var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
connection.onopen = function() {
    connection.send('Connect ' + new Date());
};
connection.onerror = function(error) {
    console.log('WebSocket Error ', error);
};
connection.onmessage = function(e) {
    console.log('Server: ', e.data);
};
connection.onclose = function() {
    console.log('WebSocket connection closed');
};

function updateConfig(key, value) {
    config[key] = value;
    console.log("key: " + key + " | value: " + value);
}

function submitConfig() {
    connection.send(JSON.stringify(config));
}

function startOTA() {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "/toggleOTA");
    xhr.send("");
}
