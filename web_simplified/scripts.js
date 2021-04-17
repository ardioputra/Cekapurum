const express = require('express');
const path = require("path");
const app = express();
const staticpath = path.join(__dirname, '../cekapurum/public');
const port = process.env.PORT || 80;

app.use(express.static(staticpath));

app.get('/', function(req, res) {
    res.sendFile(staticpath + '/index.html');
});

app.listen(port);