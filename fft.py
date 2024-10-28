import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.fft import fft

# Load accelerometer data from CSV
data = pd.read_csv('vibration_data.csv')

# Extract the time and acceleration data
time = data['Time (ms)'].values
accel_x = data['Accel_X (m/s^2)'].values
accel_y = data['Accel_Y (m/s^2)'].values
accel_z = data['Accel_Z (m/s^2)'].values

# Calculate sampling frequency
sampling_interval = (time[-1] - time[0]) / len(time) / 1000  # Convert to seconds
sampling_rate = 1 / sampling_interval

# Perform FFT for X-axis
N = len(accel_x)
xf = np.fft.fftfreq(N, sampling_interval)[:N//2]
yf_x = fft(accel_x)
yf_x = 2.0 / N * np.abs(yf_x[0:N//2])

# Perform FFT for Y-axis
yf_y = fft(accel_y)
yf_y = 2.0 / N * np.abs(yf_y[0:N//2])

# Perform FFT for Z-axis
yf_z = fft(accel_z)
yf_z = 2.0 / N * np.abs(yf_z[0:N//2])

# Plot the FFT results in separate figures

# X-axis FFT plot
plt.figure()
plt.plot(xf, yf_x, color='r')  # Red for X-axis
plt.title('FFT of Accelerometer Data (X-Axis)')
plt.xlabel('Frequency (Hz)')
plt.ylabel('Amplitude')
plt.grid()
plt.show()

# Y-axis FFT plot
plt.figure()
plt.plot(xf, yf_y, color='g')  # Green for Y-axis
plt.title('FFT of Accelerometer Data (Y-Axis)')
plt.xlabel('Frequency (Hz)')
plt.ylabel('Amplitude')
plt.grid()
plt.show()

# Z-axis FFT plot
plt.figure()
plt.plot(xf, yf_z, color='b')  # Blue for Z-axis
plt.title('FFT of Accelerometer Data (Z-Axis)')
plt.xlabel('Frequency (Hz)')
plt.ylabel('Amplitude')
plt.grid()
plt.show()
