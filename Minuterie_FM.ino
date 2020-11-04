/* Petite minute minuterie pour la chaudière de FM

=========> ATTENTION !!!!!!!!! <=========
System avec résistance PULLUP :
Cablage bouton entre la pin d'entrée (In) et le GND
*/

// Pin de sortie (out), Pin d'entrée (In)
const int nPinIn = 2;
const int nPinOut = 10; 

// Valeurs pour calculs
unsigned long calcOnTime, calcOffTime;
int pinState = 0, re = 0;
unsigned long nowTime;

// Déclaration des variables de temps
int sOn, mOn, hOn, sOff, mOff, hOff ;

void setup() {

  /* Choisi ton timing:
     sOx = secondes
     mOx = minutes
     hOx = heure

     xOn = relais activé
     xOff = relais désactivé
  */
  
  // Relais on 10 minutes (max ~50jours)
    sOn = 0;
    mOn = 10;
    hOn = 0;
  // Relais off 5 minutes (max ~50jours)
    sOff = 0;
    mOff = 5;
    hOff = 0;

    pinMode(nPinIn, INPUT_PULLUP);
    pinMode(nPinOut, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    // Conversion des temps donnés plus haut en secondes
    calcOnTime = (sOn + mOn *60 + hOn *3600) * 1000;
    calcOffTime = (sOff + mOff *60 + hOff *3600) * 1000;

}

void loop() {
  // On vérifie que le In est bien alimenté
  while (digitalRead(nPinIn) == 0){
      // On vérifie le "rising" edge(re) du bouton
      if (re == 0){
        nowTime = millis();
        pinState = 1;
        re = 1;
        digitalWrite(nPinOut,1);
        digitalWrite(LED_BUILTIN,1);      
      }
      else {
        //On lance les timers
        timer();
      }
      delay(100);
  }
  re = 0;
  digitalWrite(nPinOut,0);
  digitalWrite(LED_BUILTIN,0);
  delay(100);
}

void timer(){
  // timer on
    if (millis()- nowTime > calcOnTime && pinState == 1){
      nowTime = millis();
      pinState = 0;
      digitalWrite(nPinOut,0);
      digitalWrite(LED_BUILTIN,0);
    }
   // timer off
    else if (millis()- nowTime > calcOffTime && pinState == 0) {
      nowTime = millis();
      pinState = 1;
      digitalWrite(nPinOut,1);
      digitalWrite(LED_BUILTIN,1);
    }
}
