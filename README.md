# cansatKit
Cansat Kit &amp; Ground Station Arduino Code

libraries I used:

- [basicMPU6050](https://github.com/RCmags/basicMPU6050)

- [DHT12](https://github.com/RobTillaart/DHT12)

- [RF24](https://github.com/nRF24/RF24)

- [Adafruit BMP085/BMP180](https://github.com/adafruit/Adafruit-BMP085-Library)

Please use the provided library files. Or add the following code for I2C bus initialization, after ```I2C begin()``` (if you download the libraries with Arduino Library Manager):

```C
_wire->setClock(100000);
_wire->setWireTimeout(3000, true);
```
