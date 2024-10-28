import serial
import time
import csv

ser = serial.Serial('COM4', 250000)  # Change COM port as needed
time.sleep(2)  # Wait for connection to establish

# Open a CSV file to log the data
with open('vibrationdata.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Time (ms)", "Accel_X (m/s^2)", "Accel_Y (m/s^2)", "Accel_Z (m/s^2)"])  # Header

    try:
        while True:
            line = ser.readline().decode('utf-8').strip()  # Read data from serial port
            if line:
                print(line)  # Print to terminal
                values = line.split(',')  # Split data by comma
                writer.writerow(values)  # Write row to CSV

    except KeyboardInterrupt:
        print("Logging stopped")

ser.close()
