#define pinRPM 2
#define pinVEL 3

unsigned long millisInicial = 0; //tempo inicial 

volatile int pulsosRPM = 0; //contador de pulsos para RPM 
volatile int pulsosVEL = 0; //contador de pulsos para velocidade

unsigned int RPM = 0; //frequencia de rotacoes em RPM
unsigned int VEL = 0; //velocidade em km/h

void setup() 
{
  Serial.begin (9600);
  attachInterrupt (digitalPinToInterrupt(pinRPM), tacometro, RISING); //Interrupção para ler pulso do RPM
  attachInterrupt (digitalPinToInterrupt(pinVEL), veloc, RISING); //Interrupção para ler pulso da velocidade
}

void loop() 
{
  if((millis() - millisInicial) > 500)
  {
    noInterrupts();
    RPM = pulsosRPM*2*60;
    VEL = (pulsosVEL*2*3.14*0.5*3.6)/20;
    Serial.print ("RPM = ");
    Serial.print (RPM);
    Serial.print ("  VEL = ");
    Serial.println (VEL);
    pulsosRPM = 0;
    pulsosVEL = 0;
    millisInicial = millis();
    interrupts();
  }

}

void tacometro () 
{
  pulsosRPM++;
}

void veloc () 
{
  pulsosVEL++;
}
