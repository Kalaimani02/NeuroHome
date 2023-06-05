# NeuroHome
This is a prototype project that uses Brainsense single channel EEG sensor to detect the person's brain wave behaviour and control simple appliances.

## Current features
1. Can display Attention and Meditation values of a person
2. Can send these data to an IoT cloud. In this project, Google Firebase is used
3. Currently limited to single appliance control
4. Ensures that receiver node receives all the data packets sent by the transmitter to the IoT cloud
5. Easy to use Firebase's realtime database is used

## How does it work ?
The EEG sensor will send the TGAM packets via bluetooth. The transmitter node is basically a NodeMCU equipped with HC-05 module to receive the TGAM packets from the sensor and **Brain_Firebase_Data_Send_v1.ino** will parse the TGAM packets and estimates the **Avg. Attention & Meditation** values and sends it to the Firebase's Realtime Database.

The receiver's are notified of new data by setting the NewInst variable to True whenever the Tx sends data to cloud. After every read by the receiver, this NewInst is set to False. This ensures that all the data sent to the cloud are read by the receiver, so that even instantaneuos changes are noted.

The receiver node is also a NodeMCU. After receiving the data, the receiver runs the below mentioned algorithm to control the appliance.

## Algorithm
The algorithm used is very simple, if the user focuses his attention value will increase, and if it exceeds a certain threshold, the appliance will toggle ON/OFF. 

**Note:** This is a short-term project and the processing is limited by the hardware. Hence only simple algorithm is used. Feel free to suggest new algorithms to improve :)

## Setup
<p align="center">
<img src="https://github.com/Kalaimani02/NeuroHome/assets/89019323/743b892e-e345-4295-ac7e-2d64f98d7706" width=85% height=85%>
<img src="https://github.com/Kalaimani02/NeuroHome/assets/89019323/a9c1e5e2-fc84-4b26-945c-8b0a84684ae4" width=84% height=84%>
</p>
<!-- ![image](https://github.com/Kalaimani02/NeuroHome/assets/89019323/743b892e-e345-4295-ac7e-2d64f98d7706)
![image](https://github.com/Kalaimani02/NeuroHome/assets/89019323/a9c1e5e2-fc84-4b26-945c-8b0a84684ae4) -->

## Software and Hardware requirements
1. Create a Realtime database in Firebase
2. Install support ESP8266 board in Arduino IDE
3. Install ESP8266WiFi, SoftwareSerial, FirebaseESP8266 Library
4. Configure bluetooth as Master-slave and Bind Tx HC05 to Sensor HC05
5. Two NodeMCU for TX and Rx

## Note
- The user need to wear the sensor such that the electrode is right above the left eye on the forehead. 
- Fill the Tx, Rx code with your own Database details and WiFi details
