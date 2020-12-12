#include "CTBot.h"

CTBot myBot;
CTBotReplyKeyboard myKbd;
bool isKeyboardActive;   

String ssid  = "wifiku"; 
String pass  = "12345678"; 
String token = "1444972137:AAGFePDZjegn--mF3SyuCq5TzayBxGFHEDE";

#define lampu_depan     16
#define lampu_belakang  4

void setup() {
	Serial.begin(115200);
	Serial.println("Starting TelegramBot...");
	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");

	myKbd.addButton("Lampu Depan Nyala");
	myKbd.addButton("Lampu Depan Mati");
  myKbd.addRow();
  myKbd.addButton("Lampu Belakang Nyala");
  myKbd.addButton("Lampu Belakang Mati");
	myKbd.enableResize();
	isKeyboardActive = true;
  pinMode(lampu_depan, OUTPUT);
  pinMode(lampu_belakang, OUTPUT);
}

void loop() {
	TBMessage msg;
	if (myBot.getNewMessage(msg)) {
		if (msg.messageType == CTBotMessageText) {
			if(msg.text.equalsIgnoreCase("/start")){
      myBot.sendMessage(msg.sender.id, "Selamat datang di Smarthome Supriyanti, S.Pd.SD. Gunakan untuk keperluan anda", myKbd);
			}else if(msg.text.equalsIgnoreCase("Lampu Depan Nyala")) {
        myBot.sendMessage(msg.sender.id, "Lampu Depan Telah Menyala", myKbd);
        digitalWrite(lampu_depan, HIGH);
			}
     else if(msg.text.equalsIgnoreCase("Lampu Depan Mati")) {
        myBot.sendMessage(msg.sender.id, "Lampu Depan Telah Mati", myKbd);
        digitalWrite(lampu_depan, LOW);
     }
     else if(msg.text.equalsIgnoreCase("Lampu Belakang Nyala")) {
        myBot.sendMessage(msg.sender.id, "Lampu Belakang Telah Menyala", myKbd);
         digitalWrite(lampu_belakang, HIGH);
     }
     else if(msg.text.equalsIgnoreCase("Lampu Belakang Mati")) {
        myBot.sendMessage(msg.sender.id, "Lampu Belakang Telah Mati", myKbd);
        digitalWrite(lampu_belakang, LOW);
     }
     else {
          myBot.sendMessage(msg.sender.id, "Mohon maaf, perintah tidak dikenali", myKbd);
     }     
	}
	}
	delay(100);
}
