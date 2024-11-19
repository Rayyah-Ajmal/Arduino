int count;
int pin=2;
int pin_irq=0;
void setup() {
  Serial.begin(9600)
  attachInterrupt(digitalPinToInterrupt(2),buttonPressed1,RISING)
  //attachInterrupt(pin_irq,count,RISING);

}
void counter(){
  if 
  count++;
}
void loop() {

  
}
