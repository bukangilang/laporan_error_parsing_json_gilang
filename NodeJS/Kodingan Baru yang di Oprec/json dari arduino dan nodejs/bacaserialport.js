const express = require('express');
const app = express();
const { SerialPort } = require('serialport')
const { ReadlineParser } = require('@serialport/parser-readline')
const portexpress = 3000;

// Create a port
const port = new SerialPort({
    path: 'COM5',
    baudRate: 9600,
})

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

app.get('/', function (req, res) {
    return res.send('Perintah sedang berlangsung');
})

app.get('/:action', function (req, res) {
    var action = req.params.action || req.param('action');
    if (action == 'running') {
        port.write("{\"bacadata\":\"running\"");
        return res.send('Lampu menyala bergantian!');
    }
    if (action == 'flipflop') {
        port.write("{\"bacadata\":\"flipflop\"");
        return res.send('Lampu menyala flip flop!');
    }
    if (action == 'modeoff') {
        port.write("{\"bacadata\":\"off\"");
        return res.send("Lampu LED mati!");
    }
    return res.send('Action: ' + action);
});

port.on('open', () => {
    console.log('Serial port terbuka');
  
    const command = { command: 'matikan' };
    const jsonString = JSON.stringify(command);
  
    port.write(jsonString, (err) => {
      if (err) {
        return console.log('Error:', err.message);
      }
      console.log('Data JSON terkirim ke Arduino');
    });
  });
  
  parser.on('data', (data) => {
    try {
      const response = JSON.parse(data);
      console.log('Balasan dari Arduino:', response);
    } catch (err) {
      console.log('Error parsing JSON:', err.message);
    }
  });


// const lineStream = port.pipe(new ReadlineParser())

// lineStream.on('data', function (data) {
//     try {
//         const jsonObj = JSON.parse(data.trim());
//         console.log(jsonObj.sensor1);
//     } catch (error) {
//         console.error('Error parsing JSON:', error);
//     }
//      console.log('Data:', data)
// })

app.listen(portexpress, () => {
    console.log(`${port}`)
})