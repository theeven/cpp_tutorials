#ifndef VREGISTER_H
#define VREGISTER_H

#include "register.h"

//
//	Part 2:  A variety of approaches
//

//
//	Simple base class
//
class VRegister {
  public:
	VRegister( unsigned location )
		: r_( new (reinterpret_cast<void *>(location)) Register ) {}
	VRegister( void *location )
		: r_( new (location) Register ) {}
	virtual ~VRegister() = 0;
	virtual bool ready() const
		{ return r_->ready(); }
	virtual bool interruptsEnabled() const
		{ return r_->interruptsEnabled(); }
	virtual void enableInterrupts()
		{ r_->enableInterrupts(); }
	virtual void disableInterrupts()
		{ r_->disableInterrupts(); }
	virtual unsigned read()
		{ return r_->read(); }
	virtual void write( unsigned value )
		{ r_->write( value ); }
  private:
	VRegister( const VRegister & );
	VRegister &operator =( const VRegister & );
	Register *r_;
};

inline VRegister::~VRegister()
		{ r_->~Register(); }

//
//	The "default" concrete implementation of the register.
//
class StdRegister : public VRegister {
  public:
	StdRegister( unsigned location )
		: VRegister(location) {}
	StdRegister( void *location )
		: VRegister(location) {}
	~StdRegister()
		{}
};

//
//	A version that caches the last read or written value.
//
class CacheRegister : public VRegister {
  public:
	CacheRegister( unsigned location )
		: VRegister(location), lastread_(0), lastwrite_(0) {}
	CacheRegister( void *location )
		: VRegister(location), lastread_(0), lastwrite_(0) {}
	unsigned read()
		{ return lastread_ = VRegister::read(); }
	void write( unsigned value )
		{ VRegister::write( lastwrite_ = value ); }
	unsigned lastRead() const
		{ return lastread_; }
	unsigned lastWrite() const
		{ return lastwrite_; }
  private:
	unsigned lastread_;
	unsigned lastwrite_;
};

//
//	Interface class
//
//	For more flexibility, we're using an interface class at the
//	root of the hierarchy.
//
class VReg {
  public:
	VReg() {} // Q: Why do we have to declare this ctor?  Hint: it's private.
	virtual ~VReg() {}
	virtual bool ready() const = 0;
	virtual bool interruptsEnabled() const = 0;
	virtual void enableInterrupts() = 0;
	virtual void disableInterrupts() = 0;
	virtual unsigned read() = 0;
	virtual void write( unsigned value ) = 0;
  private:
	VReg( const VReg & );
	VReg &operator =( const VReg & );
};

//
//	An implementation of the interface.
//
class StdReg : public VReg {
  public:
	StdReg( unsigned location )
		: r_( new (reinterpret_cast<void *>(location)) Register ) {}
	StdReg( void *location )
		: r_( new (location) Register ) {}
	~StdReg()
		{ r_->~Register(); }
	bool ready() const
		{ return r_->ready(); }
	bool interruptsEnabled() const
		{ return r_->interruptsEnabled(); }
	void enableInterrupts()
		{ r_->enableInterrupts(); }
	void disableInterrupts()
		{ r_->disableInterrupts(); }
	unsigned read()
		{ return r_->read(); }
	void write( unsigned value )
		{ r_->write( value ); }
  private:
	Register *r_;
};

//
//	Application of the Decorator pattern to the hierarchy.
//
class RegDecorator : public VReg {
  public:
	RegDecorator( VReg *r )
		: sr_(r) {}
	~RegDecorator()
		{ delete sr_; }
	bool ready() const
		{ return sr_->ready(); }
	bool interruptsEnabled() const
		{ return sr_->interruptsEnabled(); }
	void enableInterrupts()
		{ sr_->enableInterrupts(); }
	void disableInterrupts()
		{ sr_->disableInterrupts(); }
	unsigned read()
		{ return sr_->read(); }
	void write( unsigned value )
		{ sr_->write( value ); }
  private:
	VReg *sr_;
};

//
//	A concrete decorator that adds chattiness to a register.
//
class BlabDecorator : public RegDecorator {
  public:
	BlabDecorator( VReg *r )
		: RegDecorator(r) {}
	unsigned read() {
		unsigned value = RegDecorator::read();
		std::cout << "read: " << value << ' ' << std::flush;
		return value;
	}
	void write( unsigned value ) {
		RegDecorator::write( value );
		std::cout << "wrote: " << value << ' ' << std::flush;
	}
};

//
//	A concrete decorator that adds a (signed) value to reads/writes.
//
class AugmentDecorator : public RegDecorator {
  public:
	AugmentDecorator( VReg *r, int amt )
		: RegDecorator(r), amt_(amt) {}
	unsigned read()
		{ return RegDecorator::read() + amt_; }
	void write( unsigned value )
		{ RegDecorator::write( value + amt_ ); }
  private:
	int amt_;
};

//
//	A caching decorator that adds caching to a register.
//
class CacheDecorator : public RegDecorator {
  public:
	CacheDecorator( VReg *r )
		: RegDecorator(r), lastread_(0), lastwrite_(0) {}
	unsigned read()
		{ return lastread_ = RegDecorator::read(); }
	void write( unsigned value )
		{ RegDecorator::write( lastwrite_ =  value ); }
	unsigned lastRead() const
		{ return lastread_; }
	unsigned lastWrite() const
		{ return lastwrite_; }
  private:
	unsigned lastread_;
	unsigned lastwrite_;
};


//
//	A non-virtual Monostate register.
//	Every object of this type will refer to the same register.
//
template <typename T, T *location>
class MonoReg {
  public:
	// MonoReg();
	// ~MonoReg();
	// MonoReg( const MonoReg & );
	// MonoReg &operator =( const MonoReg & );
	bool ready() const
		{ return r_->ready(); }
	bool interruptsEnabled() const
		{ return r_->interruptsEnabled(); }
	void enableInterrupts()
		{ r_->enableInterrupts(); }
	void disableInterrupts()
		{ r_->disableInterrupts(); }
	unsigned read()
		{ return r_->read(); }
	void write( unsigned value )
		{ r_->write( value ); }
  private:
	static Register *r_;
};

template <typename T, T *location>
Register *MonoReg<T,location>::r_ = new ((void *)location) Register;

#endif
