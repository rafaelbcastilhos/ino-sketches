#define pinPIR 7

void setup() {
	pinMode(pinPIR, INPUT);
	Serial.begin(9600);
}

void loop() {
	bool valorPIR = digitalRead(pinPIR);

	if (valorPIR)
		Serial.println("Detectado");
	else
		Serial.println("----");
}
