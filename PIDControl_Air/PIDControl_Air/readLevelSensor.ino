int inputValue = 0;

// Select I2C BUS
void TCA9548A(uint8_t bus) {
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

int calculateBMP(Adafruit_BMP085 bmp, short int bus) {
  TCA9548A (bus);
  /*if(bmp.readPressure() < ALLOWABLE_PRESSURE_MAX && bmp.readPressure() > ALLOWABLE_PRESSURE_MIN){
    inputValue = bmp.readPressure();}*/  
  //inputValue = bmp.readPressure();
  return bmp.readPressure();
  //return inputValue;  
}

float convertToLevel(float inputPressure){
  float ketinggian = map(inputPressure, LEVEL_AT_BOTTOM, LEVEL_AT_TOP, 0 * 10, 18 * 10)/10.0;
  if(ketinggian <=0){
    ketinggian = 0;
  }
  return ketinggian;
}

void initSensor1(){
    // Init sensor on bus number based in input
  TCA9548A(0);
  if (!bmp0.begin(0x76)) {
    Serial.print("Could not find a valid BMP180 sensor on bus ");
    Serial.println(0);
    while (1);
  }
  Serial.println();
}

void initSensor2(){
//     Init sensor on bus number based in input
  TCA9548A(2);
  if (!bmp2.begin(0x76)) {
    Serial.print("Could not find a valid BMP180 sensor on bus ");
    Serial.println(2);
    while (1);
  }
  Serial.println();
}
