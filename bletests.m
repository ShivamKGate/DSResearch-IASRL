% Clear workspace
clear; clc;
% List all BLE devices
% blelist
% Connect to our Arduino Nano ESP32 using listed address
b = ble("ECDA3B60DDAD");
% Obtain UUIDs from ble device info and set up characteristic object
c = characteristic(b,"6E400001-B5A3-F393-E0A9-E50E24DCCA9E","6E400003-B5A3-F393-E0A9-E50E24DCCA9E");
% Read data and convert to char
mydata = read(c);
char(mydata)
% Process data
fprintf("Data received: \n");
while(1)
    dt = datetime;
    dt.Format = 'MMMM d, yyyy - HH:mm:ss';
    fprintf('%s \t', dt);
    disp(char(mydata(8:end-1)));
    pause(0.01);
end