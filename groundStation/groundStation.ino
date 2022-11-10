#include <SPI.h>
#include "printf.h"
#include "RF24.h"


// Create instance

const byte slaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(9, 10);  // using pin 9 for the CE pin, and pin 10 for the CSN pin

char dataReceived[10];
  
void setup() {

  pinMode(4, OUTPUT);

  Serial.begin(9600);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  } 
  Serial.println("Radio started");
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(1, slaveAddress);

  radio.startListening();  // put radio in RX mode

}

struct data_t {
int temperatura;
float altura;
uint8_t humedad; 
float acelX;
float acelY;
float acelZ;
float gyX;
float gyY;
float gyZ;
}
data;

void loop() {

    if ( radio.available() ) {
        // Serial.println("Received: ");
        radio.read( (byte *)&data, sizeof(data) );
        // Serial.println((float)data.temperatura/10);
        // Serial.println(data.altura);
        // Serial.println(data.humedad);
        // Serial.println(data.acelX);
        // Serial.println(data.acelY);
        // Serial.println(data.acelZ);
        // Serial.println(data.gyX);
        // Serial.println(data.gyY);
        // Serial.println(data.gyZ);
        // led blink
        digitalWrite(4, HIGH);
        delay(5);
        digitalWrite(4, LOW);
        // sen data to Serial Port
        Serial.write((uint8_t *) &data, sizeof data);
    }

}
