void hc12() {

  if((millis()-telemetria_millisInicial) > 1000){
    noInterrupts();
    transmitir = (String(averageC) + "," + String(VEL) + "," + String(RPM));
    HC12.println(transmitir);
    telemetria_millisInicial = millis();
    interrupts();
  }
}
