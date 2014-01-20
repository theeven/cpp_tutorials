#ifndef REGISTER_H
#define REGISTER_H

enum {
	bit0 =  0x0001,
	bit1 =  0x0002,
	bit2 =  0x0004,
	bit3 =  0x0008,
	bit4 =  0x0010,
	bit5 =  0x0020,
	bit6 =  0x0040,
	bit7 =  0x0080,
	bit8 =  0x0100,
	bit9 =  0x0200,
	bit10 = 0x0400,
	bit11 = 0x0800,
	bit12 = 0x1000,
	bit13 = 0x2000,
	bit14 = 0x4000,
	bit15 = 0x8000
};

enum { highbits = bit8|bit9|bit10|bit11|bit12|bit13|bit14|bit15 };

class Register {
  public:
	bool ready() const
		{ return ctl_ & bit0; }
	bool interruptsEnabled() const
		{ return ctl_ & bit2; }
	void enableInterrupts()
		{ ctl_ |= bit2; }
	void disableInterrupts()
		{ ctl_ &= ~bit2; }
	unsigned read()
		{ return val_; }
	void write( unsigned value )
		{ val_ = value; }
  private:
	volatile unsigned ctl_; // data may change outside program control
	volatile unsigned val_; // ditto
};

#endif
