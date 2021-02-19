#define pinSom 3
#define pinRele 12
#define pinAcop 2
#define tempoEntrePalmas 150 //milisegundos
#define tempoMaximoEntrePalmas 500 //milisegundos

int contaPalmas = 0;
unsigned long tempoEspera = 0;
unsigned long tempoEsperaEntrePalmas = 0;

void executarAcao();
void setup() {
	Serial.begin(9600);

	pinMode(pinSom, INPUT);
	pinMode(pinRele, OUTPUT);
	pinMode(pinAcop, OUTPUT);

	digitalWrite(pinRele, LOW);
	digitalWrite(pinAcop, LOW);

	Serial.println("Setup Concluído");
}

void loop() {
	static int sensorSomAnt;
	int sensorSom = digitalRead(pinSom);

	if ((sensorSom == HIGH) && (sensorSomAnt == LOW)) {
		Serial.print("detectou");

		if ((millis() - tempoEspera) > tempoEntrePalmas) {
		tempoEspera = millis();
		tempoEsperaEntrePalmas = millis();
		contaPalmas++;
		}
	}
	sensorSomAnt = sensorSom;

	if ( (contaPalmas != 0) && ((millis() - tempoEsperaEntrePalmas) > tempoMaximoEntrePalmas) ) {
		executarAcao();
		contaPalmas = 0;
		tempoEsperaEntrePalmas = millis();
	}
}

void executarAcao() {
	switch (contaPalmas) {
		case 3:
		digitalWrite(pinAcop, HIGH);
		delay(200);
		digitalWrite(pinAcop, LOW);
		Serial.println("Duas Palmas, trocando modo do pisca");
		break;
		case 2:
		digitalWrite(pinRele, !digitalRead(pinRele));
		Serial.println("Tres Palmas, trocando estado do rele");
		break;
		default:
		Serial.print("A quantidade de palmas foi de:");
		Serial.println(contaPalmas);
	}
}
