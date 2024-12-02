#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>

BLEServer *pServer = NULL;
BLEService *pService;
BLECharacteristic *pDataCharacteristic;
bool deviceConnected = false;
Adafruit_MPU6050 mpu;

// UUIDs
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_DATA "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// Initialize last sample time
uint32_t lastSampleTime = 0;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) override {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) override {
    deviceConnected = false;
  }
};

void setup() {
  Serial.begin(115200);

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Initialize BLE
  BLEDevice::init("Vibration_Device");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create BLE Service and Data Characteristic
  pService = pServer->createService(SERVICE_UUID);
  pDataCharacteristic = pService->createCharacteristic(
                          CHARACTERISTIC_UUID_DATA,
                          BLECharacteristic::PROPERTY_NOTIFY
                        );

  // Add descriptor for notifications
  pDataCharacteristic->addDescriptor(new BLE2902());
  
  // Start the service and begin advertising
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Waiting for a client connection to notify...");
}

void loop() {
  if (deviceConnected) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Calculate time difference in microseconds
    uint32_t currentSampleTime = micros();
    uint32_t timeDiffUs = (lastSampleTime == 0) ? 0 : currentSampleTime - lastSampleTime;
    lastSampleTime = currentSampleTime;

    // Convert time difference to milliseconds
    uint32_t timeDiffMs = timeDiffUs / 1000;

    // Prepare the data packet as a comma-separated string without a newline character
    char packet[32];
    snprintf(packet, sizeof(packet), "%lu,%.4f,%.4f,%.4f", timeDiffMs, a.acceleration.x, a.acceleration.y, a.acceleration.z);

    // Send the data packet over BLE
    pDataCharacteristic->setValue((uint8_t*)packet, strlen(packet));
    pDataCharacteristic->notify();
    
    // No delay for maximum sampling rate
  }
}
