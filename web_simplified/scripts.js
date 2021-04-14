const antares = require('antares-http');
const express = require('express')
const app = express()
const port = process.env.PORT || 3000;

antares.setAccessKey('6e6b74ca7ead77f7:09437f0a4cc56904');

app.get('/', function(req, res) {
    antares.get('Cekapurumiot', 'CekapurumSensor')
        .then(function(response) {
            console.log(response.content);
            res.json(response.content);
        });
});

app.listen(port);