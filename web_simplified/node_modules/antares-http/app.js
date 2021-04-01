const antares = require('./index.js');

antares.setAccessKey('b4e89ce2436b9d90:202c7b14b849c084');

const data = {
  temp: Math.random() * Math.floor(34),
  hum: Math.random() * Math.floor(100),
}

// LATEST DATA
/*antares.get('weather-station', 'station1')*/
//.then(function(response) {
  //console.log(response);  
/*});*/

// SEND DATA
/*antares.send(data, 'weather-station', 'station1')*/
//.then(function(response) {
  //console.log(response);
/*});*/

// CREATE DEVICE
/*antares.createDevice('weather-station', 'nodejs-device')*/
//.then(function(response) {
  //console.log(response);
/*});*/

// GET ALL DEVICE
/*antares.getAllDevices('weather-station')*/
//.then(function(response) {
  //console.log(response);
/*});*/


// GET DEVICE ID
/*antares.getDeviceId('weather-station', 'station1')*/
//.then(function(response) {
  //console.log(response);
/*});*/

// SEND BY ID
/*antares.sendById(data, 'cnt-478686259')*/
//.then(function(response) {
  //console.log(response);
/*});*/

// GET ALL DATA
/*antares.getAll('weather-station', 'station1', 100)*/
//.then(function(response) {
  //console.log(response);
  //response.forEach(function(singleItem) {
    //console.log(singleItem.content)
  //});
/*});*/

// GET ALL DATA ID
/*antares.getAllId('weather-station', 'station1', 100)*/
//.then(function(response) {
  //console.log(response);
/*});*/

// GET SPECIFIC DATA
/*antares.getSpecific('weather-station',  'station1', 'cin_573563179')*/
//.then(function(response) {
  //console.log(response);
/*});*/


