#include <LedControl.h>

#define CLK2 13
#define CS   12
#define DIN  11
#define pinSensor1 2
#define pinSensor2 3
#define buzzer A3
#define ANDAMENTO 0
#define QUEIMOU1 1
#define QUEIMOU2 2
#define VALIDA 3
#define intervaloLeitura 1000
#define frequencia 1600
#define tempo 10

LedControl lc = LedControl(DIN, CLK2, CS, 1);

void exibeVoltas();
void contagem();
void largada();
void queimada();

void myDelay(unsigned long pausa);

byte _largada = ANDAMENTO;
int voltaP1 = -1;
int voltaP2 = -1;
unsigned long tempoAntP1 = 0;
unsigned long tempoAntP2 = 0;
unsigned long tempoP1;
unsigned long tempoP2;
bool exibe = false;

void setup() {
    Serial.begin(9600);

    pinMode(pinSensor1, INPUT_PULLUP);
    pinMode(pinSensor2, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(pinSensor1), lerSensorP1, FALLING);
    attachInterrupt(digitalPinToInterrupt(pinSensor2), lerSensorP2, FALLING);

    lc.shutdown(0, false);
    lc.setIntensity(0, 5);
    lc.clearDisplay(0);

    lc.setDigit(0, 0, 0, false);
    lc.setDigit(0, 4, 0, false);

    Serial.println("Fim Setup");

    do {
        Serial.println("Simulando largada");
        delay(1000);

        contagem();

        if (_largada == ANDAMENTO) {
            largada();
            _largada = VALIDA;
        }

        if (_largada == QUEIMOU2) {
            Serial.print("Player 2 queimou a Largada !");
            queimada();
            _largada = ANDAMENTO;
        } else if (_largada == QUEIMOU1) {
            Serial.print("Player 1 queimou a Largada !");
            queimada();
            _largada = ANDAMENTO;
        }
    } while (_largada != VALIDA);
}

void loop() {
    if (exibe) {
        exibeVoltas();
        exibe = false;
    }
}

void lerSensorP1() {
    tempoP1 = millis();
    if (_largada == ANDAMENTO) {
        _largada = QUEIMOU1;
    } else if (_largada == VALIDA) {
        if (millis() - tempoAntP1 > intervaloLeitura) {
            voltaP1++;
            tempoAntP1 = tempoP1;
            exibe = true;
        } else
            tempoP1 = tempoAntP1;
    }
}

void lerSensorP2() {
    tempoP2 = millis();

    if (_largada == ANDAMENTO)
        _largada = QUEIMOU2;
    else if (_largada == VALIDA) {
        if (millis() - tempoAntP2 > intervaloLeitura) {
            voltaP2++;
            tempoAntP2 = tempoP2;
            exibe = true;
        } else
            tempoP2 = tempoAntP2;
    }
}

void exibeVoltas() {
    byte dig1P1, dig2P1, dig3P1, dig4P1;
    byte dig1P2, dig2P2, dig3P2, dig4P2;

    dig1P1 = dig1P2 = 0;
    if (voltaP2 >= 0) {
        dig1P2 = (voltaP2 / 1) % 10;
        dig2P2 = (voltaP2 / 10) % 10;
        dig3P2 = (voltaP2 / 100) % 10;
        dig4P2 = (voltaP2 / 1000) % 10;
    }

    if (voltaP1 >= 0) {
        dig1P1 = (voltaP1 / 1) % 10;
        dig2P1 = (voltaP1 / 10) % 10;
        dig3P1 = (voltaP1 / 100) % 10;
        dig4P1 = (voltaP1 / 1000) % 10;
    }

    lc.clearDisplay(0);

    lc.setDigit(0, 0, (byte)dig1P1, false);
    if (voltaP1 > 9) lc.setDigit(0, 1, (byte)dig2P1, false);
    if (voltaP1 > 99) lc.setDigit(0, 2, (byte)dig3P1, false);
    if (voltaP1 > 999) lc.setDigit(0, 3, (byte)dig4P1, false);

    lc.setDigit(0, 4, (byte)dig1P2, false);
    if (voltaP2 > 9) lc.setDigit(0, 5, (byte)dig2P2, false);
    if (voltaP2 > 99) lc.setDigit(0, 6, (byte)dig3P2, false);
    if (voltaP2 > 999) lc.setDigit(0, 7, (byte)dig4P2, false);
}

void contagem() {
    tone (buzzer, frequencia, 200);
    myDelay (800);
    tone (buzzer, frequencia, 200);
    myDelay (800);
    tone (buzzer, frequencia, 200);
    myDelay (800);
    tone (buzzer, frequencia, 200);
    myDelay (800);
    tone (buzzer, frequencia, 200);
    myDelay (800);
}

void largada() {
    myDelay(2000);
    tone (buzzer, frequencia, 1200);
}

void queimada() {
    for (int nota = 150; nota < 1800; nota ++) {
        tone(buzzer, nota, tempo);
        delay(1);
    }
    for (int nota = 1800; nota > 150; nota --) {
        tone(buzzer, nota, tempo);
        delay(1);
    }
}

void myDelay(unsigned long pausa) {
    unsigned long controleTempo = millis();
    while (millis() - controleTempo < pausa) {
        if (_largada == QUEIMOU1 || _largada == QUEIMOU2) 
            break;
    }
}
