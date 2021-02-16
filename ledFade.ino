#define pinBotao 2
int pinLed[9] = {13, 12, 11, 10, 9, 8, 7, 6, 5};

void setup(){
    pinMode(pinBotao, INPUT);

    for(int i = 0; i <= 8; i++)
        pinMode(pinLed[i], OUTPUT);
}

void loop(){
    int numeroLed = 0;

	for(numeroLed = 0; numeroLed <= 8; numeroLed++){
        digitalWrite(pinLed[numeroLed], HIGH);
        delay(50);
    }
	for(numeroLed = 9; numeroLed > 0; numeroLed--){
        digitalWrite(pinLed[numeroLed], LOW);
        delay(100);
    }
}