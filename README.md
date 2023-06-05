# NeuroHome
This is a prototype project that uses Brainsense single channel EEG sensor to detect the person's brain wave behaviour and control simple appliances.

# Current features
1. Can display Attention and Meditation values of a person
2. Can send these data to an IoT cloud. In this project, Google Firebase is used
3. Currently limited to single appliance control
4. Ensures that receiver node receives all the data packets sent by the transmitter to the IoT cloud
5. Easy to use Firebase's realtime database is used

# How does it work ?
The user will wear the EEG sensor such that the electrode is right above the left eye on the forehead. The EEG sensor will send the TGAM packets via bluetooth.
The transmitter node is basically a NodeMCU equipped with HC-05 module to receive the TGAM packets from the sensor and **Brain_Firebase_Data_Send_v1.ino** will parse the TGAM packets and estimates the **Avg. Attention & Meditation** values and sends it to the Firebase's Realtime Database.

The receiver's are notified of new data by setting the NewInst variable to True whenever the Tx sends data to cloud. After every read by the receiver, this NewInst is set to False. This ensures that all the data sent to the cloud are read by the receiver, so that even instantaneuos changes are noted.

The receiver node is also a NodeMCU. After receiving the data, the receiver runs the below mentioned algorithm to control the appliance.

# Algorithm
      The algorithm used is very simple, if the user focuses his attention value will increase, and if it exceeds a certain threshold, the appliance will toggle ON/OFF. 
**Note:** This is a short-term project and the processing is limited by the hardware. Hence only simple algorithm is used. Feel free to suggest new algorithms to improve :)

# Usage 
The user need to wear the EEG headset and need to focus to turn the appliance ON or OFF.

# Demo
