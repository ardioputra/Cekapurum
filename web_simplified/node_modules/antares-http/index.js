/*
 *  LIBRARY description
 *  =================== 
 *  Antares HTTP for NodeJS
 *  This is a library to simplify the connection to Antares IoT Platform through NodeJS.
 *  There are a few methods for data transaction through HTTP, some of them are:
 *
 *  createDevice(projectName, new_device_name) - Create a new device on your Antares project
 *  getAllDevices(projectName) - Get all devices in your Antares project
 *  get(projectName, deviceName) - Get the latest data from your Antares device
 *  getAll(projectName, deviceName, limit) - Get chunk of data from your Antares device, including the contents
 *  getAllId(projectName, deviceName, limit) - Get chunk of data from your Antares device, but only the ID
 *  getSpecific(projectName, deviceName, instance) - Get specific data. the {instance} parameter must be cin_{identifier}
 *  send(data, projectName, deviceName)  - Send data into your Antares device
 *  getDeviceId(projectName, deviceName) - Get your device ID
 *  sendById(data, deviceId) - Send data into your Antares device through ID (cnt-{identifier})
 * */

const https = require('https');
const request = require('request');
let _antaresAccessKey = '';

exports.testFunction = function() {
  console.log('This is a message from the module.', _antaresAccessKey);
}

exports.get = function(projectName, deviceName) {
  // Initiate HTTP request
  return new Promise(function(resolve, reject) {
    const options = {
      url: `https://platform.antares.id:8443/~/antares-cse/antares-id/${projectName}/${deviceName}/la`,
      headers: {
        'X-M2M-Origin': _antaresAccessKey, // The access key 
        'Content-Type': 'application/json;ty=4',
        'Accept': 'application/json'
      }
    };

    function callback(error, response, body) {
      if(!error) {
        const data = JSON.parse(body)['m2m:cin'];

        let content = '';
        try {
          content = JSON.parse(data.con);
        }
        catch {
          content = data.con;
        }

        const finalData = {
          resource_identifier: data.ri,
          parent_id: data.pi,
          created_time: data.ct,
          last_modified_time: data.lt,
          content: content,
        }
        
        resolve(finalData);
      }
    }
    request(options, callback);
  });
}

exports.getSpecific = function(projectName, deviceName, instance) {
  // Initiate HTTP request
  return new Promise(function(resolve, reject) {
    const options = {
      url: `https://platform.antares.id:8443/~/antares-cse/antares-id/${projectName}/${deviceName}/${instance}`,
      headers: {
        'X-M2M-Origin': _antaresAccessKey, // The access key 
        'Content-Type': 'application/json;ty=4',
        'Accept': 'application/json'
      }
    };

    function callback(error, response, body) {
      if(!error) {
        const data = JSON.parse(body)['m2m:cin'];

        let content = '';
        try {
          content = JSON.parse(data.con);
        }
        catch {
          content = data.con;
        }

        const finalData = {
          resource_identifier: data.ri,
          parent_id: data.pi,
          created_time: data.ct,
          last_modified_time: data.lt,
          content: content,
        }
        
        resolve(finalData);
      }
    }
    request(options, callback);
  });
}


exports.getAll = function(projectName, deviceName, limit) {
  // Initiate HTTP request
  return new Promise(function(resolve, reject) {
    const options = {
      url: `https://platform.antares.id:8443/~/antares-cse/antares-id/${projectName}/${deviceName}?fu=1&ty=4&drt=1&lim=${limit}`,
      headers: {
        'X-M2M-Origin': _antaresAccessKey, // The access key 
        'Content-Type': 'application/json',
        'Accept': 'application/json'
      }
    };

    function callback(error, response, body) {
      if(!error) {
        // console.log('success');
        // console.log(body);
        const data = JSON.parse(body)['m2m:uril'];
        finalDataArray = [];

        let dataCounter = 0;
        data.forEach(function(individualUrl) {
          const optionsInd = {
            url: `https://platform.antares.id:8443/~${individualUrl}`,
            headers: {
              'X-M2M-Origin': _antaresAccessKey, // The access key 
              'Content-Type': 'application/json',
              'Accept': 'application/json'
            }
          };

          function callbackInd(errorInd, responseInd, bodyInd) {
            dataCounter++;
            // console.log('Data counter: ', dataCounter);
            // console.log(bodyInd);
            
            let parsedIndData = '';
            parsedIndData = JSON.parse(bodyInd)['m2m:cin'];
            
            let contentInd = '';
            try {
              contentInd = JSON.parse(parsedIndData.con);
            }
            catch {
              contentInd = parsedIndData.con;
            }
            
            finalIndData = {
              resource_name: parsedIndData.rn,
              resource_identifier: parsedIndData.ri,
              parent_id: parsedIndData.pi,
              created_time: parsedIndData.ct,
              last_modified_time: parsedIndData.lt,
              content: contentInd,
            }

            finalDataArray.push(finalIndData);

            if(dataCounter >= limit) {
              resolve(finalDataArray);
            }
          }
          request(optionsInd, callbackInd);
        });
      }
    }
    request(options, callback);
  });
}

exports.getAllId = function(projectName, deviceName, limit) {
  // Initiate HTTP request
  return new Promise(function(resolve, reject) {
    const options = {
      url: `https://platform.antares.id:8443/~/antares-cse/antares-id/${projectName}/${deviceName}?fu=1&ty=4&drt=1&lim=${limit}`,
      headers: {
        'X-M2M-Origin': _antaresAccessKey, // The access key 
        'Content-Type': 'application/json',
        'Accept': 'application/json'
      }
    };

    function callback(error, response, body) {
      if(!error) {
        // console.log('success');
        // console.log(body);
        const data = JSON.parse(body)['m2m:uril'];
        let newData = [];

        data.forEach(function(singleData) {
          const formedUrl = singleData.split('/');
          newData.push(formedUrl[5]);
        });
        
        resolve(newData);
      }
    }
    request(options, callback);
  });
}

exports.getDeviceId = function(projectName, deviceName) {
  return new Promise(function(resolve, reject) {
    const options = {
      url: `https://platform.antares.id:8443/~/antares-cse/antares-id/${projectName}/${deviceName}`,
      headers: {
        'X-M2M-Origin': _antaresAccessKey, // The access key 
        'Content-Type': 'application/json',
        'Accept': 'application/json'
      }
    };

    function callback(error, response, body) {
      if(!error) {
        // console.log('success');
        // console.log(body);
        const data = JSON.parse(response.body)['m2m:cnt']['ri'];
        const deviceId = data.split('/')[2]
        resolve(deviceId);
      }
    }
    request(options, callback);
  });
}

exports.getAllDevices = function(projectName) {
  // Initiate HTTP request
  return new Promise(function(resolve, reject) {
    const options = {
      url: `https://platform.antares.id:8443/~/antares-cse/antares-id/${projectName}?fu=1&ty=3`,
      headers: {
        'X-M2M-Origin': _antaresAccessKey, // The access key 
        'Content-Type': 'application/json',
        'Accept': 'application/json'
      }
    };

    function callback(error, response, body) {
      if(!error) {
        // console.log('success');
        // console.log(body);
        const data = JSON.parse(body)['m2m:uril'];
        const finalDeviceArray = [];

        data.forEach(function(deviceInd) {
          const splitUrl = deviceInd.split('/');
          // console.log(splitUrl);
          //const finalIndData = {
          //  url: deviceInd,
          //  projectName: splitUrl[3],
          //  deviceName: splitUrl[4],
          //}
          finalDeviceArray.push(splitUrl[4]); // Push device name
        });

        resolve(finalDeviceArray);
      }
    }
    request(options, callback);
  });
}

exports.send = function(data, projectName, deviceName) {
  // Initiate HTTP request
  let dataParsed = '';

  if(typeof data === 'object') {
    dataParsed = JSON.stringify(data);
  }
  else {
    dataParsed = data;
  }

  console.log(dataParsed);
  
  const dataTemplate = {
    'm2m:cin': {
      'con' : dataParsed,
    }
  };

  return new Promise(function(resolve, reject) {
    const options = {
      method: 'POST',
      url: `https://platform.antares.id:8443/~/antares-cse/antares-id/${projectName}/${deviceName}`,
      headers: {
        'X-M2M-Origin': _antaresAccessKey, // The access key 
        'Content-Type': 'application/json;ty=4',
        'Accept': 'application/json'
      },
      body: JSON.stringify(dataTemplate)
    };

    function callback(error, response, body) {
      if(!error) {
        const data = JSON.parse(body)['m2m:cin'];

        let content = '';
        try {
          content = JSON.parse(data.con);
        }
        catch {
          content = data.con;
        }

        const finalData = {
          resource_identifier: data.ri,
          parent_id: data.pi,
          created_time: data.ct,
          last_modified_time: data.lt,
          content: content,
        }
        
        resolve(finalData);
      }
    }
    request(options, callback);
  });
}

exports.sendById = function(data, deviceId) {
  // Initiate HTTP request
  let dataParsed = '';

  if(typeof data === 'object') {
    dataParsed = JSON.stringify(data);
  }
  else {
    dataParsed = data;
  }

  //console.log(dataParsed);
  
  const dataTemplate = {
    'm2m:cin': {
      'con' : dataParsed,
    }
  };

  return new Promise(function(resolve, reject) {
    const options = {
      method: 'POST',
      url: `https://platform.antares.id:8443/~/antares-cse/${deviceId}`,
      headers: {
        'X-M2M-Origin': _antaresAccessKey, // The access key 
        'Content-Type': 'application/json;ty=4',
        'Accept': 'application/json'
      },
      body: JSON.stringify(dataTemplate)
    };

    function callback(error, response, body) {
      if(!error) {
        const data = JSON.parse(body)['m2m:cin'];

        let content = '';
        try {
          content = JSON.parse(data.con);
        }
        catch {
          content = data.con;
        }

        const finalData = {
          resource_identifier: data.ri,
          parent_id: data.pi,
          created_time: data.ct,
          last_modified_time: data.lt,
          content: content,
        }
        
        resolve(finalData);
      }
    }
    request(options, callback);
  });
}

exports.createDevice = function(projectName, deviceName) {
  // Initiate HTTP request
  let dataParsed = '';
  console.log(dataParsed);
  
  const dataTemplate = {
    'm2m:cnt': {
      'rn' : deviceName,
    }
  };

  return new Promise(function(resolve, reject) {
    const options = {
      method: 'POST',
      url: `https://platform.antares.id:8443/~/antares-cse/antares-id/${projectName}`,
      headers: {
        'X-M2M-Origin': _antaresAccessKey, // The access key 
        'Content-Type': 'application/json;ty=3',
        'Accept': 'application/json'
      },
      body: JSON.stringify(dataTemplate)
    };

    function callback(error, response, body) {
      if(!error) {
        const data = JSON.parse(body)['m2m:cnt'];

        const finalData = {
          resource_name: data.rn,
          resource_identifier: data.ri,
          parent_id: data.pi,
          created_time: data.ct,
          last_modified_time: data.lt,
          acpi: data.acpi,
          et: data.et,
          oldest_data: data.ol,
          latest_data: data.la,
        }

        resolve(finalData);
      }
    }
    request(options, callback);
  });
}

exports.setAccessKey = function(accessKey) {
  _antaresAccessKey = accessKey;
}
