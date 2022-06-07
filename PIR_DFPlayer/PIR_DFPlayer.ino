
#include "DFRobotDFPlayerMini.h"

//check pin2 ESP32
//https://cdn.shopify.com/s/files/1/0609/6011/2892/files/doc-esp32-pinout-reference-wroom-devkit.png

//referensi pin2 ESP32, yg dapat digunakan
//https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

 // GPIO36 (Input Only), label diboard GPIO36 => VP atau SP tergantung jenis board
#define PirPin 36

 //DFPlayer pakai POWER 5V !!!, sebaiknya tambahkan Logic Level Converter untuk Serial
DFRobotDFPlayerMini mp3;


//alarm1.mp3 durasinya 13 detik lebih dikit, buletin jadi 14 detik
//dan dalam milisecond => 14000
uint16_t mp3Duration = 14000;
uint16_t lastestPlayedMP3 = 0;

void setup() {
	pinMode(PirPin, INPUT);
	Serial.begin(115200); // Serial0 GPIO 3 RX0, GPIO 1 TX0 (atau USB)
	Serial2.begin(9600); // Serial2 GPIO 16 RX2, GPIO 17 TX2
	
	if (!mp3.begin(Serial2)) {  //Use softwareSerial to communicate with mp3.
		Serial.println(F("Unable to begin:"));
		Serial.println(F("1.Please recheck the connection!"));
		Serial.println(F("2.Please insert the SD card!"));
		while (true) {
			delay(0); // Code to compatible with ESP8266 watch dog.
		}
	}
	Serial.println(F("DFPlayer Mini online."));
	mp3.volume(25);  //Set volume value. From 0 to 30
	mp3.play(1); // inisial file... (agar file keload dalam cache dfplayer)
	
	delay(mp3Duration); // delay selama panjang mp3
	delay(1000);
	Serial.println("READY");
}

void loop() {
	Pir_Start();
	
	//sebaiknya PIR dikalibrasi dahulu, atur timer dan sensitivity paling kecil/paling besar dahulu
	//PIR sensitif terhadap RF, jauhkan dari ESP32, ESP32 ada RF (WiFi)
	//pastikan nilai 0, jika tidak ada gerakan. dan nilai 1 jika ada gerakan
	Serial.print("VALUE : ");
	Serial.println(digitalRead(PirPin));
	delay(100);
}



//------------------------------Pir Sensor Scan Start--------------------------//
void Pir_Start() {
	if (digitalRead(PirPin) == HIGH) { // jika ada gerakan

		// check mp3 sudah play atau belom
		// jika ada mp3 sudah play, maka tidak akan play lagi...
		if ((millis() - lastestPlayedMP3) >= mp3Duration) { // logic sederhana dengan mengambil waktu terakhir play mp3
			lastestPlayedMP3 = millis(); // set millis waktu ketika mp3 play
			mp3.play(1); // play file pertama
		}
	}
}