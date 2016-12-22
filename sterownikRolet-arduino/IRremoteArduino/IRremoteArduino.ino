/*
 Name:		IRremoteArduino.ino
 Created:	3/20/2016 12:05:08 AM
 Author:	KubaMiszcz
*/
/*
* Sketch modified by Enjoying Electronics: http://www.instructables.com/member/Enjoying+Electronics/
Code based off of:
* IRremote
* Version 0.1 July, 2009
* Copyright 2009 Ken Shirriff
* For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.html

* Special thanks to dablondeemu http://www.instructables.com/member/dablondeemu/
* and his instructable listed below, IR Remote Controlled Color Changing Cloud (Arduino)
* http://www.instructables.com/id/IR-Remote-Controlled-Color-Changing-Cloud-Arduino/


* Lets get started:

The IR sensor's pins are attached to Arduino as so:
Pin 1 to Vout (pin 11 on Arduino)
Pin 2 to GND
Pin 3 to Vcc (+5v from Arduino)

*/

/*******************CODE BEGINS HERE********************/
#include <IRremote.h>
#include "Received_IR_Code.cpp"
#include "Motor.cpp"

//DEFINICJE PINOW
					int IR_Input_PIN = 4;
		//silnik1 - lewy
					int motor1_BtnPIN = 8;
					int motor1_UpPIN = 5; //A-INA	PWM
					int motor1_DownPIN =6; //A-INB	PWM
					int motor1_LED = 12;
		//silnik2 - prawy
					int motor2_BtnPIN = 7;
					int motor2_UpPIN = 9; //A-INA	PWM
					int motor2_DownPIN = 10; //A-INB	PWM
					int motor2_LED = 13;
					
//ZMIENNE GLOBALNE
		unsigned long motor1_IRCode = 16195807;
		unsigned long motor2_IRCode = 16228447;

		int SpeedUpSlow = 255 * 0.95;	//128
		int SpeedUpFast = 255 * 1.0;	//255	
		int SpeedDownSlow = 255 * 0.5;	//64
		int SpeedDownFast = 255 * 0.8;	//128
		int SpeedUpWait_ms = 1500; //po tym czasie ma przyspieszyc

//ZMIENNE POMOCNICZE
		unsigned long Check_IR_Code = 0;
		unsigned long Check_IR_Code_Prev = Check_IR_Code;
		long int SpeedUpStart = 0;

//INSTANCJE
		Motor motor1 = Motor(motor1_BtnPIN, motor1_LED, "down", motor1_IRCode, motor1_DownPIN, motor1_UpPIN);
		Motor motor2 = Motor(motor2_BtnPIN, motor2_LED, "down", motor2_IRCode, motor2_DownPIN, motor2_UpPIN);

		Received_IR_Code received_IR_Code;
		IRrecv irrecv(IR_Input_PIN);
		decode_results results;

void setup()
{
	/*Serial.begin(9600);
	Serial.println("HEELOU!");*/
	
	// Start the receiver
	pinMode(IR_Input_PIN, INPUT);
	irrecv.enableIRIn(); 
	//silnik1
	pinMode(motor1_BtnPIN, INPUT_PULLUP);
	pinMode(motor1_LED, OUTPUT);
	pinMode(motor1_UpPIN, OUTPUT);
	pinMode(motor1_DownPIN, OUTPUT);
	//silnik2
	pinMode(motor2_BtnPIN, INPUT_PULLUP);
	pinMode(motor2_LED, OUTPUT);
	pinMode(motor2_UpPIN, OUTPUT);
	pinMode(motor2_DownPIN, OUTPUT);

}


void loop() {
	received_IR_Code.valuee = Read_IR_Code();
	motor1.btnState = motor1.aktBtn_state();
	motor2.btnState = motor2.aktBtn_state();

	String str = "kod: ";
	str += String(received_IR_Code.value_prev) + " ";
	str += String(received_IR_Code.valuee) + " ";
	str += motor1.Direction + " ";
	str += motor2.Direction;
	Serial.println(str);

	Silnik1();
	Silnik2();

	received_IR_Code.value_prev = received_IR_Code.valuee;
	motor1.btnState_prev = motor1.btnState;
	motor2.btnState_prev = motor2.btnState;

	

}


void Silnik1() {
	//OBLSUGA ZDARZEN
	//zalaczenie silnika
	if (received_IR_Code.R_TRIG(motor1.IR_Code) || motor1.Btn_R_TRIG()) {
		String str = "ksss: ";
		str += String(received_IR_Code.R_TRIG(motor1.IR_Code)) + " ";
		str += String(motor1.Btn_R_TRIG()) + " ";
		Serial.println(str);


		motor1.ChangeDirection();
		SpeedUpStart = millis() + SpeedUpWait_ms; //kiedy ma przyspieszyc
		if (motor1.Direction == "down") {
			motor1.Run(SpeedDownSlow);
			Serial.println("down");

		}
		if (motor1.Direction == "up") {
			motor1.Run(SpeedUpSlow);
			Serial.println("up");

		}
	}

	//zatrzymanie silnika po puszczeniu przycisku
	if (received_IR_Code.F_TRIG(motor1.IR_Code) || motor1.Btn_F_TRIG()) {
		motor1.Run(0);		Serial.println("stop");
	}

	//przyspieszenie po 3 sek od wcisniecia
	if (received_IR_Code.valuee == motor1.IR_Code || motor1.Btn_IsON()) {
		if (millis() >= SpeedUpStart) {
			if (motor1.Direction == "down") {
				motor1.Run(SpeedDownFast);
			}
			if (motor1.Direction == "up") {
				motor1.Run(SpeedUpFast);
			}
		}
	}
}//end loopOKKK()

void Silnik2() {
	//OBLSUGA ZDARZEN
	//zalaczenie silnika
	if (received_IR_Code.R_TRIG(motor2.IR_Code) || motor2.Btn_R_TRIG()) {
		String str = "ksss: ";
		str += String(received_IR_Code.R_TRIG(motor2.IR_Code)) + " ";
		str += String(motor2.Btn_R_TRIG()) + " ";
		Serial.println(str);


		motor2.ChangeDirection();
		SpeedUpStart = millis() + SpeedUpWait_ms; //kiedy ma przyspieszyc
		if (motor2.Direction == "down") {
			motor2.Run(SpeedDownSlow);
			Serial.println("down");

		}
		if (motor2.Direction == "up") {
			motor2.Run(SpeedUpSlow);
			Serial.println("up");

		}
	}

	//zatrzymanie silnika po puszczeniu przycisku
	if (received_IR_Code.F_TRIG(motor2.IR_Code) || motor2.Btn_F_TRIG()) {
		motor2.Run(0);		Serial.println("stop");
	}

	//przyspieszenie po 3 sek od wcisniecia
	if (received_IR_Code.valuee == motor2.IR_Code || motor2.Btn_IsON()) {
		if (millis() >= SpeedUpStart) {
			if (motor2.Direction == "down") {
				motor2.Run(SpeedDownFast);
			}
			if (motor2.Direction == "up") {
				motor2.Run(SpeedUpFast);
			}
		}
	}
}//end Silnik2

unsigned long Read_IR_Code() {
	_delay_ms(100);  //spowolnienie bo lapie zera miedzy odczytami ze niby puszczam przycisk
	if (irrecv.decode(&results))
	{
		//4294967295=kod ze przycisk jest trzymany, taki sam dla trzymania kazdego przycisku
		if (results.value != -1) {
			Check_IR_Code = results.value;
			Check_IR_Code_Prev = Check_IR_Code;
		}
		else {
			Check_IR_Code = Check_IR_Code_Prev;
		}
		irrecv.resume();   // Receive the next value
	}
	else {
		Check_IR_Code = 0;	
	}
	return Check_IR_Code;
}

