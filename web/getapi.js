function getData() {
    fetch('https://platform.antares.id:8443/~/antares-cse/antares-id/Cekapurumiot/CekapurumSensor/la', {mode:'cors'})
    .then(response => response.json())
    .then(data => {
        console.log(data)

        let temperatur = data.temperature
        let humidity = data.humidity
        let firesensor = data.fire_units
        let status = data.status
        
        document.getElementById("temperatur").innerHTML = temperatur
        document.getElementById("kelembapan").innerHTML = humidity
        document.getElementById("fire-sensor").innerHTML = firesensor  
        document.getElementById("status").innerHTML = status
    })
    .catch(err => {
        console.log(err)
    });
}