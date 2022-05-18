void hc12() {

  if((millis()-telemetria_millisInicial) > 1000){
    noInterrupts();
    HC12.println(armazenar);
    telemetria_millisInicial = millis();
    interrupts();
  }
}
