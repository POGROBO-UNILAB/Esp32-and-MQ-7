// C++ code
#include <MQUnifiedsensor.h>
#define Board "ESP32"
#define Voltage_Resolution 3.3
#define Pin 34
#define Type "MQ-7"
#define ADC_Bit_Resolution 12
#define RatioMQ7CleanAir 27.5
MQUnifiedsensor MQ7(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin,
Type);
void setup() {
Serial.begin(9600);
MQ7.setRegressionMethod(1);
MQ7.setA(99.042);
MQ7.setB(-1.518);
Serial.println("Calibrating... Please wait in clean air.");
MQ7.update();
float r0 = MQ7.calibrate(RatioMQ7CleanAir);
MQ7.setR0(r0);
if (isinf(r0)) {
Serial.println("Error: Infinite R0 (Open circuit). Check wiring.");
while (1);
}
if (r0 == 0) {
Serial.println("Error: Zero R0 (Short circuit). Check wiring.");
while (1);
}
Serial.println("Calibration complete.");
MQ7.serialDebug(true);
}
void loop() {
MQ7.update();
MQ7.readSensor();
MQ7.serialDebug();
delay(500);
}
