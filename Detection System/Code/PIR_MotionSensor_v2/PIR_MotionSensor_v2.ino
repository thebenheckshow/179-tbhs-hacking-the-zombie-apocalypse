//https://www.google.com/search?q=make+pir+arduino&oq=make+pir+arduino&aqs=chrome..69i57.6267j0j4&sourceid=chrome&es_sm=93&ie=UTF-8// Uses a PIR sensor to detect movement, buzzes a buzzer
// more info here: http://blog.makezine.com/projects/pir-sensor-arduino-alarm/
// email me, John Park, at jp@jpixl.net
// based upon:
// PIR sensor tester by Limor Fried of Adafruit
// tone code by michael@thegrebs.com

 
int ledPin = 13;                // choose the pin for the LEDhttp://www.kosagi.com/w/index.php?title=Novena_Main_Page#Firmware
int armedLed = 4; 
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pinSpeaker = 10;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)
int transistorPin = 12;    // connected to the base of the transistor
int oneShot = 1;

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(pinSpeaker, OUTPUT);  // declare piezo as output
  pinMode(transistorPin, OUTPUT);  // set  the transistor pin as output:
  Serial.begin(9600);
  delay(2000);
  while (digitalRead(inputPin) == HIGH) {
    delay(1);
  }
  delay(3000);
}

void loop(){
  
  if (oneShot != 0) {
          digitalWrite(armedLed, HIGH);  // turn LED ON
    }else {
      digitalWrite(armedLed, LOW);  // turn LED ON\ff
    }
    
  val = digitalRead(inputPin);  // read input value
    
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (oneShot == 1) {
          digitalWrite(transistorPin, HIGH);
          delay(100);
          digitalWrite(transistorPin, LOW);
          oneShot = 0;
    }
    playTone(300, 160);

    delay(150);

    
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
      digitalWrite(ledPin, LOW); // turn LED OFF
      playTone(0, 0);
      delay(300);    
      if (pirState == HIGH){
      // we have just turned off
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
// duration in mSecs, frequency in hertz
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}
