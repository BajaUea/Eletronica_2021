void sd()
{
  if((millis() - sd_millisInicial) > 1000){

    armazenar += (String(VEL) + "," + String(AccX1*9.8/4096) + "," + String(AccY1*9.8/4096) + "," + String(AccZ1*9.8/4096)+ "," + String(GyrX1/131) + "," + String(GyrY1/131) + "," + String(GyrZ1/131) + "," + String(AccX2*9.8/4096)+ "," + String(AccY2*9.8/4096) + "," + String(AccZ2*9.8/4096) + "," + String(GyrX2/131) + "," + String(GyrY2/131)+ "," + String(GyrZ2/131) + "," + String(temp_obj) + "," + String(temp_amb) + "," + String() + "," + String()); 

    // escreve se o arquivo for valido
    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // escreve se o arquivo for valido
    if (dataFile) {
     dataFile.println(armazenar);
     dataFile.close();
   }
    // if the file isn't open, pop up an error:
    else {
    Serial.println("error opening datalog.txt");
    }

    sd_millisInicial = millis();
  }
}
