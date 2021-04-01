const antares = require('antares-http');
const express = require('express')
const app = express()

antares.setAccessKey('6e6b74ca7ead77f7:09437f0a4cc56904');

app.use((req, res, next) => {
  res.header('Access-Control-Allow-Origin', '*');
  next();
});

app.get('/', function(req, res, next) {
	antares.get('Cekapurumiot', 'CekapurumSensor')
            .then(function(response) {
                console.log(response.content);
                res.json(response.content);
            });
});
app.listen(3000);