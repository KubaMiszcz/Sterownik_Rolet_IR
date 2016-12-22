// 
// 
// 
#include <arduino.h>

//klasa motor
class Motor {
public: int BtnPIN;
public: int LED;
public: String Direction;
public: unsigned long IR_Code;
public: int DownPIN;
public: int UpPIN;
public: bool btnState, btnState_prev;

		Motor(int BtnPIN, int LED, String Direction, unsigned long IR_Code, int DownPIN, int UpPIN) {
			this->BtnPIN = BtnPIN;
			this->LED = LED;
			this->Direction = Direction;
			this->IR_Code = IR_Code;
			this->DownPIN = DownPIN;
			this->UpPIN = UpPIN;
			btnState = aktBtn_state();
			btnState_prev = btnState;
		}

		void ChangeDirection() {
			if (Direction == "up")Direction = "down";
			else if (Direction == "down")Direction = "up";
		}

		void Run(int Speed) {
			if (Direction == "up") {
				analogWrite(DownPIN, 0);
				analogWrite(UpPIN, Speed);
				digitalWrite(LED, HIGH);
				//Serial.println("up");
			}
			else if (Direction == "down") {
				analogWrite(DownPIN, Speed);
				analogWrite(UpPIN, 0);
				digitalWrite(LED, HIGH);
				//Serial.println("down");
			}
			if (Speed == 0)digitalWrite(LED, LOW);
		}
		bool aktBtn_state() {
			return !digitalRead(BtnPIN);
		}
		bool Btn_R_TRIG() {
			if (btnState_prev == 0 && btnState == 1) {
				return true;
				Serial.println("RtrigTrue");
			}
			else {
				return false;
				return false; Serial.println("RtrigFalse");
			}
		}
		bool Btn_F_TRIG() {
			if (btnState_prev == 1 && btnState == 0) {
				return true;
				Serial.println("FtrigTrue");
			}
			else {
				return false; Serial.println("FtrigFalse");
			}
		}
		bool Btn_IsON() {
			if (aktBtn_state()) {
				return true;
			}
			else
			{
				return false;
			}
		}
};


