//SMOOTHING, IF DONT USE THIS, COMMENT ALL SMOOTHING IN MAIN CODE

const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;              // the index of the current reading
int total = 0.0;                  // the running total
int average = 0.0;   


void initSmoothing(){
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

float smoothing(float valueNow){
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = valueNow;
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;
  
  return average;
  delay(1);
}

int readings2[numReadings];
int readIndex2 = 0;              // the index of the current reading
float total2 = 0.0;                  // the running total
int average2 = 0.0;   


void initSmoothing2(){
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings2[thisReading] = 0;
  }
}

float smoothing2(float valueNow){
  // subtract the last reading:
  total2 = total2 - readings2[readIndex2];
  // read from the sensor:
  readings2[readIndex2] = valueNow;
  // add the reading to the total:
  total2 = total2 + readings2[readIndex2];
  // advance to the next position in the array:
  readIndex2 = readIndex2 + 1;

  // if we're at the end of the array...
  if (readIndex2 >= numReadings) {
    // ...wrap around to the beginning:
    readIndex2 = 0;
  }
  // calculate the average:
  average2 = total2 / numReadings;
  
  return average2;
  delay(1);
}
