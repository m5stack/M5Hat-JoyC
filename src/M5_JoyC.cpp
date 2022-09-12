#include "M5_JOYC.h"

bool M5_JOYC::begin(
	TwoWire * wire, 
	uint8_t sda,
	uint8_t scl,
	uint8_t addr
){
  	_wire = wire;
	_addr = addr;
  	_sda = sda;
	_scl = scl;
	_wire->setPins(_sda, _scl);
	_wire->begin();
	_wire->beginTransmission(_addr);
	uint8_t error = _wire->endTransmission();
    if(error == 0)
    {
    	return true;
    }else{
		return false;
	}
}

void M5_JOYC::writeBytes(
	uint8_t addr, 
	uint8_t reg, 
	uint8_t *buffer, 
	uint8_t length
){

	_wire->beginTransmission(addr); 
	_wire->write(reg);                         
	for(int i = 0; i < length; i++) {
		_wire->write(*(buffer+i)); 
	}
	_wire->endTransmission();
}

void M5_JOYC::readBytes(
	uint8_t addr, 
	uint8_t reg, 
	uint8_t *buffer, 
	uint8_t length
){
	uint8_t index= 0;
	_wire->beginTransmission(addr);
	_wire->write(reg);
	_wire->endTransmission();
	_wire->requestFrom(addr, length);
	for(int i = 0; i < length; i++) {
		buffer[index++] = _wire->read();
	}
}


void M5_JOYC::update(){
	uint8_t data[5];
	readBytes(_addr, 0x60, data, 5);
	x0 = data[0];
	y0 = data[1];
	x1 = data[2];
	y1 = data[3];
	btn0 = (data[4] & 0x10) > 0;
	btn1 = (data[4] & 0x01) > 0;

	uint8_t buf[8];
	readBytes(_addr, 0x70, buf, 8);
	angle0 = buf[0]<<8 | buf[1];
	angle1 = buf[2]<<8 | buf[3];
	distance0 = buf[4]<<8 | buf[5];
	distance1 = buf[6]<<8 | buf[7];
}

uint8_t M5_JOYC::getX(uint8_t pos){
	uint8_t x;
	uint8_t reg = 0x60 + pos*2;
	readBytes(_addr, reg, &x, 1);
	return x;
}

uint8_t M5_JOYC::getY(uint8_t pos){
	uint8_t y;
	uint8_t reg = 0x61 + pos*2;
	readBytes(_addr, reg, &y, 1);
	return y;
}

uint16_t M5_JOYC::getAngle(uint8_t pos){
	uint8_t data[2];
	uint8_t reg = 0x70 + pos*2;
	readBytes(_addr, reg, data, 2);
	return data[0]<<8 | data[1];
}

uint16_t M5_JOYC::getDistance(uint8_t pos){
	uint8_t data[2];
	uint8_t reg = 0x74 + pos*2;
	readBytes(_addr, reg, data, 1);
	return data[0]<<8 | data[1];
}

uint8_t M5_JOYC::getPress(uint8_t pos){
	uint8_t state;
	readBytes(_addr, 0x64, &state, 1);
	if(pos == 0 ) {
		return (state & 0x10) > 0;
	}else{
		return (state & 0x01) > 0;
	}
}

void M5_JOYC::setLEDColor(uint32_t colorHEX) {
	uint8_t color[3];
	//RED
	color[0] = (colorHEX >> 16) & 0xff;
	//GREEN
	color[1] = (colorHEX >> 8) & 0xff;
	//BLUE
	color[2] = colorHEX & 0xff;
	writeBytes(_addr, 0x20, color, 3);
}
