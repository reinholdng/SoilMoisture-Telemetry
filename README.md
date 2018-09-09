# SoilMoisture-Telemetry
Remote measurement of multiple soil variables like moisture and temperature to optimize irrigation

ToDo List (CentralStation):
- [x] Microcontroller communication via serial with Node-Red Server (Localhost PC)
- [x] Send request to NodeStation via SIM900
- [ ] Send request to NodeStation via LoRa RFM9x
- [ ] Detection of response (with sensors data) from NodeStation
- [ ] Parsing and plotting of data received from NodeStationdata 
- [ ] Implement Node-Red Server in Raspberry Pi
- [ ] Interface SIM900/LoRa RFM9x Modules with Raspberry Pi Server to avoid using a Microcontroller

ToDo List (NodeStation):
- [x] Detection of request from CentralStation
- [x] Parsing data from the request
- [x] Temperature measurement using DS18B20 sensor
- [x] Soil measurement using Watermark 200SS sensor
- [x] Automatic response using SIM900 Module
- [ ] Integrate temperature and soil moisture measures to the response
- [ ] Automatic response using LoRa RFM9x
- [ ] Automatic sensing and data sending without request from CentralStation
- [ ] Watermark 200ss and DS18B20 Calibration


