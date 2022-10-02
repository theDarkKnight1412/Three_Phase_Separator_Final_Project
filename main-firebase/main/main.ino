#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <ESP32Servo.h>

//define setpoint each phase in CM
#define SP_WATER 10.0
#define SP_MIXED 10.0

//define allowable working pressure
#define ALLOWABLE_PRESSURE_MAX 105000
#define ALLOWABLE_PRESSURE_MIN 100000

//define pressure at Top and Bottom, adjust based on condition
#define LEVEL_AT_BOTTOM 100675
#define LEVEL_AT_TOP 102100
//102206
//define Control Valve Pin
//ini agak lupa pinnya kebalik atau ngga, dicek lagi kwkw
#define CV_MIXED_PIN 18
#define CV_OIL_PIN 25

/*  
BMP0 = Water, BMP2 = Mixed,
Choose one or both
*/

Adafruit_BMP085 bmp0; // I2C
Adafruit_BMP085 bmp2; // I2C

//Init servo valve 1 and 2
//Servo Valve1;
Servo Valve2;
short int servoState = 0;
float level = 0.0;
float pressure = 0.0;

int interval = 1000;          // interval between sends
long lastSendTime = 0;      

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  // Start I2C communication with the Multiplexer
  Wire.begin();

  // Initialization Sensor, Sensor 1 =  Water, Sensor 2 = Mixed
  // Choose one or both
  initSensor1();
  initSensor2();

  //Initialization to Firebase SDK
  
  
  // Initialization CV, Valve1 = WATER, Valve2 = MIXED
  //setUpValve(Valve1,CV_WATER_PIN);
  //setUpValve(Valve2,CV_MIXED_PIN);

  Valve2.attach(CV_OIL_PIN);
  Valve2.write(0);
  //SMOOTHING BLM DIPAKE YA GAIS
  initSmoothing();
  initSmoothing2();
  servoState = 0;
}

void loop() {
  //Print values for sensor (cm), BMP0 = WATER , BMP2 = MIXED
////
//  level = convertToLevel(smoothing(calculateBMP(bmp2, 2)));
//  Serial.print(level);
//  Serial.print(";");
//  Serial.println(servoState);

  Serial.print(smoothing(calculateBMP(bmp0, 0)));
  Serial.print(";");
  Serial.println(smoothing2(calculateBMP(bmp2, 2)));

  //Open Valve and Shutdown Pump, Parameter adjust based on Condition
//  if(level == SP_WATER){
//  Valve2.write(0);
//  servoState = 1;
//  }
//  delay(500);
}
