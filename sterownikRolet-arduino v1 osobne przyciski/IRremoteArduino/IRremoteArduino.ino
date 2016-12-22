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

//####################WYPROWADZENIA
int IRpin = 3;
int UpLED = 5;
int DownLED = 2;
int silnik_w_lewo = 9; //A-INA
int silnik_w_prawo = 10; //A-INB

//###########################ZMIENNE PROGRAMOWE
double akcja = 0;
int speedUp = 255;
int speedDown = 128;
int licznik = 0;
String dir="brak przycisku";
String dirprev ;
double  akcjaprev ;
unsigned long aktualnyCzas = 0;
unsigned long aktualnyCzasPrev;

//##############################KODY PRZYCISKOW
int UpBtn = 1090515214;
int DownBtn = 1090488694;



IRrecv irrecv(IRpin);
decode_results results;

void setup()
{
	Serial.begin(9600);
	Serial.println("HEELOU!");
	irrecv.enableIRIn(); // Start the receiver
	pinMode(UpLED, OUTPUT);
	pinMode(DownLED, OUTPUT);
	pinMode(silnik_w_lewo, OUTPUT);
	pinMode(silnik_w_prawo, OUTPUT);
}

void loop()
{

	if (irrecv.decode(&results))
	{
		double temp = results.value; 
		//Serial.println("kod wcisnietego: " + String(results.value, DEC)); // Print the Serial 'results.value'
		Serial.println("kod wcisnietego: " + String(temp)); // Print the Serial 'results.value'
		if (temp != 4294967300.00) akcja = temp;
		irrecv.resume();   // Receive the next value
		licznik = 0;
	}
	else {
		licznik++;
		if (licznik > 2000) { 
			dir = "brak przycisku";
			akcja = 0;
		};
	}
	
	//pilot z wiezy double
	//gora	1090515200.00
	//dol	1090488700.00
	//stop	1090478500.00


	if (akcja == 1090515200.00 || akcja == 16187647.00) dir = "gora";
	if (akcja == 1090488700.00 || akcja == 16220287.00) dir = "dol";
	if (akcja == 1090478500.00 || akcja == 16236607.00) dir = "stop";
	if (akcja == 4294967300.00 || akcja == 4294967300.00) dir = "trzymam";

		
	if (dir == "gora") {
		digitalWrite(UpLED, HIGH);
		digitalWrite(DownLED, LOW);
		analogWrite(silnik_w_lewo, speedUp);
		analogWrite(silnik_w_prawo, 0);
	}

	else if (dir == "dol") {
		digitalWrite(UpLED, LOW);
		digitalWrite(DownLED, HIGH);
		analogWrite(silnik_w_lewo, 0);
		analogWrite(silnik_w_prawo, speedDown);
	}

	else if (dir == "stop") {
		digitalWrite(UpLED, LOW);
		digitalWrite(DownLED, LOW);
		analogWrite(silnik_w_lewo, 0);
		analogWrite(silnik_w_prawo, 0);
	}

	else if (dir == "trzymam") {
	}

	else if (dir == "brak przycisku") {
		digitalWrite(UpLED, LOW);
		digitalWrite(DownLED, LOW);
		analogWrite(silnik_w_lewo, 0);
		analogWrite(silnik_w_prawo, 0);
	}

	aktualnyCzas = millis()/1000;
	
	if (aktualnyCzas != aktualnyCzasPrev) {
		//Serial.println("sekunda "+String(aktualnyCzas));

	}

	if (aktualnyCzas == (60*60*11)) {
		digitalWrite(UpLED, HIGH);
		digitalWrite(DownLED, LOW);
		analogWrite(silnik_w_lewo, speedUp);
		analogWrite(silnik_w_prawo, 0);
		delay(4500);	//4800ms - podnoszenie rolety
		digitalWrite(UpLED, LOW);
		digitalWrite(DownLED, LOW);
		analogWrite(silnik_w_lewo, 0);
		analogWrite(silnik_w_prawo, 0);
	}



	aktualnyCzasPrev = aktualnyCzas;

	


	//akcja = 0;
	//piloty:
	//do wiezy:
	//1090515214: //gora
	//1090488694 : //dol
	//1090478494 :	//snooze
	//4294967295 -trzymany przycisk

	//pilot do zarowki:
	//	up - 16187647
	//	down -	16220287
	//	on-16236607
	//off - 16203967


}
