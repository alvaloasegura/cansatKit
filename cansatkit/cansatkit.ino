#include <Adafruit_BMP085.h>
#include <basicMPU6050.h> 
#include "DHT12.h"

#include <SPI.h>
#include "printf.h"
#include "RF24.h"


// Create instance
Adafruit_BMP085 bmp;
basicMPU6050<> imu;
DHT12 DHT(&Wire);

const byte slaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(9, 10);  // using pin 9 for the CE pin, and pin 10 for the CSN pin

char payload[10] = "Hola ";
  
void setup() {

  pinMode(4, OUTPUT);
// MPU6050
  // Set registers - Always required
  imu.setup();
  // Initial calibration of gyro
  imu.setBias();

  DHT.begin();

  Serial.begin(115200);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }

  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}  // hold in infinite loop
  }
  radio.setPALevel(RF24_PA_MIN);  // RF24_PA_MAX is default.
  radio.setDataRate( RF24_250KBPS );
  radio.openWritingPipe(slaveAddress);

  radio.stopListening();  // put radio in TX mode

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



  delay(2000);

  if (DHT.read() == DHT12_OK) {
    data.humedad = DHT.getHumidity();
  }

  Serial.print("Temperature = ");
  data.temperatura = (int)(bmp.readTemperature()*10);
  
  data.altura = bmp.readAltitude(101500);

  // Update gyro calibration 
  imu.updateBias();
  //-- Scaled and calibrated output:
  data.acelX = imu.ax();
  data.acelY = imu.ay();
  data.acelZ = imu.az();
  data.gyX = imu.gx();
  data.gyY = imu.gy();
  data.gyZ = imu.gz();

  Serial.print(((float)data.temperatura)/10);
  Serial.println(" *C");

  Serial.print("Humedad: ");
  Serial.println(data.humedad);
  
  Serial.print("Altitude = ");
  Serial.print(data.altura);
  Serial.println(" meters");
  Serial.println("");

  // Accel
  Serial.println("Acel:");
  Serial.print( data.acelX ); Serial.print( " " );
  Serial.print( data.acelY ); Serial.print( " " );
  Serial.print( data.acelZ ); Serial.println( " " );
  // Gyro
  Serial.println("Gyr:");
  Serial.print( data.gyX ); Serial.print( " " );
  Serial.print( data.gyY ); Serial.print( " " );
  Serial.print( data.gyZ ); Serial.println( " " );



    
  // Serial.print("Pressure = ");
  // Serial.print(bmp.readPressure());
  // Serial.println(" Pa");

  //unsigned long start_timer = micros();                // start the timer
  bool report = radio.write((byte *)&data, sizeof(data));  // transmit & save the report

  // led blink
  digitalWrite(4, HIGH);
  delay(5);
  digitalWrite(4, LOW);
    







}
