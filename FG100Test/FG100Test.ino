int pumpPin = 9;  

void setup()
{
  pinMode(pumpPin, OUTPUT);   // sets the pin as output
}

void loop()
{
  for (int voltageIncrement = 1; voltageIncrement < 11; voltageIncrement++) {
    analogWrite(pumpPin, (255/10*voltageIncrement)); 
    delay(3000);
  }  
}
