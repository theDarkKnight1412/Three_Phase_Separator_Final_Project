void setUpValve(Servo numValve, int pin){
  numValve.attach(pin);
  
  //Close Valve for Safety Reason
  numValve.write(90);
}

void OpenValveShutdownPump(Servo numValve, int pin){
  //Shutdown Pump, KODING DISINI
  
  //Fully Opened CV?, Ganti angkanya lek ga sesuai
  //Pokok Control valve harus terbuka penuh
  numValve.write(0);
}
