# Antares NodeJS
[![npm version](https://badge.fury.io/js/antares-http.svg)](https://badge.fury.io/js/antares-http)  

<img src="https://antares.id/assets/img/antaresnode.png" width="300">  

This is a NodeJS library to simplify the connection to Antares IoT Platform. For more information about the platform itself, please visit the [official site](https://antares.id).  

## Installation
Make sure you have NodeJS and npm installed.
```
npm install antares-http --save
```

### Usage Example
```js
var antares = require('antares-http');

var myData = {
  temperature: 30,
  humidity: 78
}

antares.setAccessKey('your-access-key-here');

antares.send(myData, 'your-project-name', 'your-device-name')
.then(function(response) {
  console.log(response);
});
```

### API Reference
* `setAccessKey(access-key)`  
Set the `access-key` parameter to your Antares access key.  

Functions below this line use `Promise` to return the response of each HTTP request, so you'll need to use a `.then` to retrieve the result. For example:
```js
antares.get('project1', 'device1')
.then(function(response) {
  console.log(response.content);
});
```
For more information about promises, please read more at [Mozilla Developer Guide](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Using_promises);

* `get(projectName, deviceName)`  
    Get the latest data from your Antares device.  
    return: latest data (json)  
* `getAll(projectName, deviceName, limit)`  
    Get a chunk of data from your Antares project, you can set the limitation by setting the `limit` parameter.  
    return: Chunk of data from your Antares device  

* `getAllId(projectName, deviceName, limit)`  
    Get a chunk of data IDs from your Antares project, you can set the limitation by setting the `limit` parameter.  
    return: Chunk of data IDs from your Antares device  

* `getSpecific(projectName, deviceName, data-id)`  
    Get specific data from your Antares device, the `data-id` parameter looks like this: `cin_81723819`.  
    return: Specific device data  

* `getDeviceId(projectName, deviceName)`  
    Get your Antares device ID.  
    return: antares device ID (i.e. `cnt-44637281`)  

* `send(data, projectName, deviceName)`  
    Send data to your Antares project. This can be a JavaScript object or other datatype (string/number).  
    return: POST response data from Antares  

* `sendById(data, device-id)`  
    Send data to your Antares device through Antares device ID which looks like `cnt-281727372`  
    return: POST response data from Antares  

* `createDevice(projectName, newDeviceName)`  
    Create an Antares device in your Project.  
    return: device creation response  

* `getDevices(projectName)`  
    Get all device names of Antares project  
    return: antares device names  
