const antares = require('antares-http');
const express = require('express');
const path = require("path");
const app = express();
const staticpath = path.join(__dirname, '../web_simplified/public');
const port = process.env.PORT || 3000;

console.log(staticpath);

antares.setAccessKey('6e6b74ca7ead77f7:09437f0a4cc56904');

app.use(express.static(staticpath));

app.use((req, res, next) => {
    res.header('Access-Control-Allow-Origin', '*');
    next();
});

app.get('/', function(req, res) {
    res.sendFile(staticpath + '/index.html');
});

app.get('/index.html', function(req, res) {
    res.sendFile('index.html');
});

app.get('/about.html', function(req, res) {
    res.sendFile('about.html');
});

app.get('/sensor.html', function(req, res) {
    res.sendFile('/sensor.html')
});

app.get('/data', function(req, res) {
    antares.get('Cekapurumiot', 'CekapurumSensor')
        .then(function(response) {
            console.log(response.content);
            res.json(response.content);
        });
});

app.listen(port);