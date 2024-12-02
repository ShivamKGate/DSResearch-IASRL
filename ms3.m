% MATLAB Code for BLE Communication
clear; clc;

% Connect to the BLE device
deviceAddress = 'ECDA3B60DDAD';
try
    b = ble(deviceAddress);
    %disp("Connected to device: " + deviceAddress);
catch
    error("Failed to connect to device.");
end

% Set up characteristic object
try
    pDataCharacteristic = characteristic(b, '6E400001-B5A3-F393-E0A9-E50E24DCCA9E', '6E400003-B5A3-F393-E0A9-E50E24DCCA9E');
catch
    error("Failed to find characteristic.");
end

%disp("Receiving real-time data...");

% Loop to continuously read data
while true
    try
        rawData = char(read(pDataCharacteristic, 'latest'));

        % Only display if valid data is received
        if ~isempty(rawData)
            disp(rawData);  % Display as a comma-separated list
        end
    catch ME
        fprintf("Error reading data: %s\n", ME.message);
    end
    
    pause(0.01); % Small delay to control read frequency
end
