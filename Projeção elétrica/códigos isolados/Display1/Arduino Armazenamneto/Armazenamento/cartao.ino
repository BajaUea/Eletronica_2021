void cartao(){
  if((millis - sd_millisInicial) > 1000){
    //String ACE_MPU1 = "";
    //String GIRO_MPU1 = "";
    //String ACE_MPU2 = "";
    //String GIRO_MPU2 = "";
    //String StringVEL = "";

    //ACE_MPU1 += (String(AccX1*9.8/4096) + "," + String(AccY1*9.8/4096) + "," + String(AccZ1*9.8/4096) + ",");
    //GIRO_MPU1 += (String(GyrX1/131) + "," + String(GyrY1/131) + "," + String(GyrZ1/131) + ",");

    //ACE_MPU2 += (String(AccX2*9.8/4096) + "," + String(AccY2*9.8/4096) + "," + String(AccZ2*9.8/4096) + ",");
    //GIRO_MPU2 += (String(GyrX2/131) + "," + String(GyrY2/131) + "," + String(GyrZ2/131) + ",");

    //StringVEL += (String(StringVEL) + ",");


    dataFile = SD.open("datalog.txt", FILE_WRITE);

  // Escreve se o arquivo for valido
    if (dataFile) {
      //dataFile.print(ACE_MPU1);
      //dataFile.print(GIRO_MPU1);
      //dataFile.print(ACE_MPU2);
      //dataFile.print(GIRO_MPU2);
      //dataFile.print(StringVEL);
      dataFile.print(longitude);
      dataFile.print(",");
      dataFile.println(latitude);
      dataFile.close();
    }
  // Se o arquivo não abrir mostra msg de erro:
    else {
      Serial.println("error opening datalog.txt");
    }
    sd_millisInicial = millis();
  }
}
