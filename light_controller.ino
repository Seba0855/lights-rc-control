/* 
  ----------------------------------------------------------
  Credits:

  https://github.com/sui77/rc-switch/
  https://github.com/LSatan/SmartRC-CC1101-Driver-Lib
  ----------------------------------------------------------
*/

/*
 * NODEMCU CONNECTION:
 * VCC      -> 3.3V
 * SI(MOSI) -> D7
 * SO(MISO) -> D6
 * CSN      -> D8
 * GND      -> G (GND)
 * SCK      -> D5
 * GD2      -> D2
 * GD0      -> D1
 */

 /*
  * ARDUINO NANO CONNECTION:
  * VCC       -> 3.3V
  * SI (MOSI) -> D11
  * SO (MISO) -> D12
  * CSN       -> D10
  * GND       -> GND
  * SCK       -> D13
  * GDO2      -> D2
  * GDO0      -> D6
  */
 
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <RCSwitch.h>

int pin; // pin on which receiver is connected.
bool terracePowered = false;
bool shedPowered = false;
int idTerrace = 1351; // setting the receiver id for terrace
int idShed = 1352;    // setting the receiver id for shed

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);

#ifdef ESP32
  pin = 4;  // for esp32! Receiver on GPIO pin 4.
#elif ESP8266
  pin = 4;  // for esp8266! Receiver on pin 4 = D2.
#else
  pin = 0;  // for Arduino! Receiver on interrupt 0 => that is pin #2
#endif

// PINOUT SETUP
#define terrace 7
#define shed 8
#define motionSensor 9

  //CC1101 Settings:
  ELECHOUSE_cc1101.Init();        // initializing the RC receiver!
  ELECHOUSE_cc1101.setMHZ(433.92); // setting the basic frequency (default = 433.92). The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ.


  mySwitch.enableReceive(pin);  // Choose the pin on which receiver is connected.

  ELECHOUSE_cc1101.SetRx();  // set Receive on
  pinMode(terrace, OUTPUT);
  pinMode(shed, OUTPUT);
  pinMode(motionSensor, INPUT);
  digitalWrite(terrace, HIGH);
  digitalWrite(shed, HIGH);
  Serial.print("Zaladowalo sie\n");
}

void lightsON(int getID, int ID, int getBitLength, int bitLength, bool active, int location) {
  if (getID == ID && getBitLength == bitLength && active == false) {
    Serial.print("Lights turned on\n");
    digitalWrite(location, LOW);
  }
}

void lightsOFF(int getID, int ID, int getBitLength, int bitLength, bool active, int location) {
  if (getID == ID && getBitLength == bitLength && active == true) {
    Serial.print("Lights turned off\n");
    digitalWrite(location, HIGH);
  }
}

void loop() {
  int getID = 0;
  int getBitLength = 0;

  if (digitalRead(motionSensor) == 1 && terracePowered == false && shedPowered == false) {
    digitalWrite(terrace, LOW);
    digitalWrite(shed, LOW);
  }

  if (digitalRead(motionSensor) == 0 && terracePowered == false && shedPowered == false) {
     digitalWrite(terrace, HIGH);
     digitalWrite(shed, HIGH);
  }
  
  if (mySwitch.available()) {

    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );
    getID = mySwitch.getReceivedValue();
    getBitLength = mySwitch.getReceivedBitlength();

    int currentIteration = 0;
    delay(5);
    if (terracePowered == false && currentIteration != 1 && getID == idTerrace) {
      lightsON(getID, idTerrace, getBitLength, 12, terracePowered, terrace);
      terracePowered = true;
      currentIteration = 1;
      delay(200);
    }

    if (terracePowered == true && currentIteration != 1 && getID == idTerrace) {
      lightsOFF(getID, idTerrace, getBitLength, 12, terracePowered, terrace);
      terracePowered = false;
      currentIteration = 1;
      delay(200);
    }
    currentIteration = 0;
    if (shedPowered == false && currentIteration != 1 && getID == idShed) {
      lightsON(getID, idShed, getBitLength, 12, shedPowered, shed);
      shedPowered = true;
      currentIteration = 1;
      delay(200);
    }

    if (shedPowered == true && currentIteration != 1 && getID == idShed) {
      lightsOFF(getID, idShed, getBitLength, 12, shedPowered, shed);
      shedPowered = false;
      currentIteration = 1;
      delay(200);
    }
    mySwitch.resetAvailable();
  }
  delay(200);
}
