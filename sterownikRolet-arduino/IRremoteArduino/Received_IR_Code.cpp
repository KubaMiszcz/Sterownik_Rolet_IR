// 
// 
// 

#include <arduino.h>
class Received_IR_Code {
public: unsigned long valuee;
public: unsigned long value_prev;
		Received_IR_Code() {
			valuee = 0;
			value_prev = 0;
		}
		bool R_TRIG(unsigned long Checked_IR_Code) {
			if (value_prev == 0 && valuee == Checked_IR_Code) {
				return true;
			}
			else return false;
		}
		bool F_TRIG(unsigned long Checked_IR_Code) {
			if (value_prev == Checked_IR_Code && valuee == 0) {
				return true;
			}
			else return false;
		}
};


