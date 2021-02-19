#define pinSensorA A0
#define pinSensorD 8

void setup() {
	pinMode(pinSensorD, INPUT);
	Serial.begin(9600);
}

void loop() {
	Serial.print("Digital:");

	if (digitalRead(pinSensorD))
		Serial.print("Sem chuva ");
	else
		Serial.print("Chovendo");

	Serial.print("Analogico:");
	Serial.print(analogRead(pinSensorA)); 
	Serial.print("  ");

	Serial.print("Atuador:");
	if (analogRead(pinSensorA) > 700)
		Serial.println("Toldo aberto");
	else
		Serial.println("Toldo fechado");
}
