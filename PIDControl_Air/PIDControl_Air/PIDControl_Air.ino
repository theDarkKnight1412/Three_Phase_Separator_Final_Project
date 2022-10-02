#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <ESP32Servo.h>
#include <PID_v1.h>

//define setpoint each phase in CM
double SP_LEVEL = 10.0;

//define allowable working pressure
#define ALLOWABLE_PRESSURE_MAX 105000
#define ALLOWABLE_PRESSURE_MIN 100000

//define pressure at Top and Bottom, adjust based on condition
#define LEVEL_AT_BOTTOM 100520
#define LEVEL_AT_TOP 102165

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
Servo Valve1;
Servo Valve2;
//boolean servoState = 0;

double inputLevel, outputValve;

int interval = 2000;          // interval between sends
long lastSendTime = 0;    

//Tune PID PARAMETER HERE
//double Kp = 3.92 , Ki = 0.82,  Kd = 1.498;
//untuk minyak
double Kp = 15, Ki = 12, Kd = 3;

PID myPID(&inputLevel,&outputValve, &SP_LEVEL, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  // Start I2C communication with the Multiplexer
  Wire.begin();

  // Initialization Sensor, Sensor 1 =  Water, Sensor 2 = Mixed
  // Choose one or both
  initSensor1();
  initSensor2();
  
  // Initialization CV, Valve1 = MIXED, Valve2 = OIL
//  setUpValve(Valve1,CV_MIXED_PIN);
//  setUpValve(Valve2,CV_OIL_PIN);

  Valve1.attach(CV_OIL_PIN);
  Valve1.write(90);

//  Valve2.attach(CV_OIL_PIN);
//  Valve2.write(0);
  
  //SMOOTHING BLM DIPAKE YA GAIS
  initSmoothing();
  //initSmoothing2();
  
  //Init Manual Mode and Define Setpoint
  setPIDMode(0);
  setPIDSetPoint();
}

void loop() {
  //double lastValue;
  //Print values for sensor (cm), BMP0 = WATER , BMP2 = MIXED
//  Serial.print(smoothing(calculateBMP(bmp0, 0)));
//  Serial.print(";");
//  Serial.println(smoothing2(calculateBMP(bmp2, 2)));

    setPIDMode(1);
    inputLevel = convertToLevel(smoothing(calculateBMP(bmp2, 2)));
    
    Serial.print(";");  
//    if(millis() - lastSendTime > interval){
//       Serial.println(inputLevel);
//       lastSendTime =  millis();     
//    }
    Serial.print(inputLevel);
    Serial.print(";");
    Serial.println(SP_LEVEL);

    pidCompute();
    Valve1.write(outputValve);   
//   delay(5000);
}
