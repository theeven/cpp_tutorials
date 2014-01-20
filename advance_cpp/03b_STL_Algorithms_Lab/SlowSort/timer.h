#ifndef TIMER_H
#define TIMER_H

#ifdef MSVC
  #define STD_CLOCK_T  clock_t
  #define STD_CLOCK    clock
  #define STD_DIFFTIME difftime  
#else
  #define STD_CLOCK_T  std::clock_t
  #define STD_CLOCK    std::clock
  #define STD_DIFFTIME std::difftime  
#endif 

//
//	Use the Timer class for rough estimates of execution time.
//	Example:
//
//	Timer t; // create, init timer
//	// do something...
//	cout << t << endl; // see how long it took to do something
//

class Timer {
  public:
    Timer()
    	: start_(STD_CLOCK()) {}
    operator double() const 
    	{ return (STD_CLOCK() - start_) / static_cast<double>(CLOCKS_PER_SEC); }
    void reset()
    	{ start_ = STD_CLOCK(); }
  private:
    STD_CLOCK_T start_;
};

#endif
