/******************************************************************************
MAG3110.h
MAG3110 Library Header File
Michael Albrecht @ AT&T Foundry
Original Creation Date: June 3, 2014

This file prototypes the MMA8452Q class, implemented in SFE_MMA8452Q.cpp. In
addition, it defines every register in the MMA8452Q.

Development environment specifics:
	IDE: Arduino 1.0.5
	Hardware Platform: Arduino Uno

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#ifndef MAG3110_h
#define MAG3110_h

#include <Arduino.h>


////////////////////////////////
// MMA8452Q Misc Declarations //
////////////////////////////////

////////////////////////////////
// MMA8452Q Class Declaration //
////////////////////////////////
class MAG3110
{
public:	
    MAG3110(byte addr = 0x0E); // Constructor
	
	void init();
    void read();
	
    int x, y, z;
	float cx, cy, cz;
private:
	uint8_t address;
    int read_axis(char axis);
};

#endif
