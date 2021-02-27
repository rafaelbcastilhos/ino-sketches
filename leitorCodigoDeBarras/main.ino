#include <hidboot.h>
#include <usbhub.h>
#include <SPI.h>
#include "Leitor.h"

String codigoLido="";
bool leituraRealizada = false;

void setup() {
	Serial.begin(9600);
	Serial.println("Iniciando USB Host Shield");

	if (Usb.Init() == -1) {
		Serial.println("Algo deu errado :( ");
		Serial.println("Confira o Sketch");
	}
	delay( 200 );

	Serial.println("Iniciando Leitor de Código de Barras");
	HidKeyboard.SetReportParser(0, &Prs);

	Serial.println("Setup concluído");
}

void loop() {
	Usb.Task();
	if(leituraRealizada){
		Serial.print("Código lido: ");
		Serial.println(codigoLido);

		leituraRealizada = false;
		codigoLido = "";
	}
}