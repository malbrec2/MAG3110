

#include "MAG3110.h"
#include <Arduino.h>
#include <Wire.h>


static const unsigned char MAG_MSB[] = {0x01, 0x03, 0x05};
static const unsigned char  MAG_LSB[] = {0x02, 0x04, 0x06};

MAG3110::MAG3110(byte addr) {
	address = addr;
}

void MAG3110::init() {
	Wire.begin();
	Wire.beginTransmission(address); // transmit to device 0x0E
	Wire.write(0x11);              // cntrl register2
	Wire.write(0x80);              // send 0x80, enable auto resets
	Wire.endTransmission();       // stop transmitting

	delay(15);

	Wire.beginTransmission(this->address); // transmit to device 0x0E
	Wire.write(0x10);              // cntrl register1
	Wire.write(1);                 // send 0x01, active mode
	Wire.endTransmission();       // stop transmitting
}

void MAG3110::read() {
	this->x = read_axis('x');
	this->y = read_axis('y');
	this->z = read_axis('z');
}

int MAG3110::read_axis(char axis) {
	int low, high;  //define the MSB and LSB
	int ax = axis - 'x';
  
	Wire.beginTransmission(address);	// transmit to device 0x0E
	Wire.write(MAG_MSB[ax]);		// MSB reg
	Wire.endTransmission();			// stop transmitting
 
	delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
	Wire.requestFrom(address, (uint8_t)1); // request 1 byte
	while(Wire.available())    // slave may send less than requested
	{ 
		high = Wire.read(); // receive the byte
	}
  
	delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
	Wire.beginTransmission(address);	// transmit to device 0x0E
	Wire.write(MAG_LSB[ax]);		// LSB reg
	Wire.endTransmission();			// stop transmitting
 
	delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  
	Wire.requestFrom(address, (uint8_t)1); // request 1 byte
	while(Wire.available())    // slave may send less than requested
	{
		low = Wire.read(); // receive the byte
	}
  
	return (low|(high << 8)); //concatenate the MSB and LSB
}
