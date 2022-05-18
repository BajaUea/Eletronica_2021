void MPU() {
  if((millis() - mpu_millisInicial) > 250){
    // Comandos para iniciar transmissão de dados
    // MPU 1
    Wire.beginTransmission(MPU1);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU1, 14, true); // Solicita os dados ao sensor

    // Armazena o valor dos sensores nas variaveis correspondentes
    AccX1 = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AccY1 = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AccZ1 = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Temp1 = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyrX1 = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyrY1 = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyrZ1 = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    Wire.endTransmission(true);

   // MPU 2
    Wire.beginTransmission(MPU2);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU2, 14, true); // Solicita os dados ao sensor

    // Armazena o valor dos sensores nas variaveis correspondentes
    AccX2 = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AccY2 = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AccZ2 = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Temp2 = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyrX2 = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyrY2 = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyrZ2 = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    Wire.endTransmission(true);

    //Imprime na Serial os valores obtidos
    /* Alterar divisão conforme fundo de escala escolhido:
      Acelerômetro
      +/-2g = 16384
      +/-4g = 8192
      +/-8g = 4096
      +/-16g = 2048

      Giroscópio
      +/-250°/s = 131
      +/-500°/s = 65.6
      +/-1000°/s = 32.8
      +/-2000°/s = 16.4
    */

    Serial.print(AccX1*9.8 / 4096);
    Serial.print(" ");
    Serial.print(AccY1*9.8 / 4096);
    Serial.print(" ");
    Serial.println(AccZ1*9.8 / 4096);

    Serial.print(AccX2*9.8 / 4096);
    Serial.print(" ");
    Serial.print(AccY2*9.8 / 4096);
    Serial.print(" ");
    Serial.println(AccZ2*9.8 / 4096);
    
    Serial.println("===================================");

    //Serial.print(GyrX / 131);
    // Serial.print(" ");
    //Serial.print(GyrY / 131);
    //Serial.print(" ");
    //Serial.println(GyrZ / 131);
        
    mpu_millisInicial = millis();
  }
}
