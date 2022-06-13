/*

   Esta experiencia muestra el uso de la funcion analogRead() y

   analogWrite() para controlar la intensidad de un led co
   un potenciometro encendido y apagado con un led.

*/
 
#define LED_PIN 11
#define BUTTON_PIN 3
#define POTENTIOMETER_PIN A1

unsigned long debounceDuration = 50; // millis
unsigned long lastTimeButtonStateChanged = 0;

byte lastButtonState = HIGH;
bool LEDOn = false;
int aux = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}
void loop()
{
  unsigned long timeNow = millis();

  if (timeNow - lastTimeButtonStateChanged > debounceDuration) {
    byte buttonState = digitalRead(BUTTON_PIN);
    if (buttonState != lastButtonState) {
      lastTimeButtonStateChanged = timeNow;
      lastButtonState = buttonState;
      if (buttonState == HIGH) { // button has been released
        LEDOn = ! LEDOn;
      }
    }
  }
  
  if (LEDOn) {
    int potentiometerValue = analogRead(POTENTIOMETER_PIN);
    int brightness = map(potentiometerValue, 0, 1023, 0, 255);
    aux = 1;
    
    Serial.print("brightness: ");
    Serial.println(brightness);
    Serial.print("LED: ");
    Serial.println(aux);
    
    analogWrite(LED_PIN, brightness); 
  }
  else {
    aux = 0;
    Serial.print("LED: ");
    Serial.println(aux);
    
    digitalWrite(LED_PIN, LOW);
  }
}