//double Kp = 131.9, Ki = 19.411, Kd = 71.701;
//PID myPID(&inputLevel,&outputValve, &SP_WATER, Kp, Ki, Kd, DIRECT);


void setPIDMode(short int state){
  //0 is MANUAL, non-0 is AUTOMATIC
  myPID.SetMode(state);
}

void setPIDSetPoint(){
  myPID.SetOutputLimits(0,90);
}

void pidCompute(){
  myPID.Compute();
  //tambahan diki boleh dihapus
  //delay(1000);
}

void pidSampleTime(int ms){
  myPID.SetSampleTime(ms);
}
