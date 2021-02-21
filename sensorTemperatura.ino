#include <dht.h>

#define pinSensor 7
#define intervalo 2000

unsigned long delayIntervalo;
dht sensorDHT;

void setup(){
    Serial.begin(9600);
    Serial.println("Status,\tTempo(uS),\tUmidade(%),\tTemperatura(C)");
}

void loop(){
    if ((millis() - delayIntervalo) > intervalo) {
        unsigned long start = micros();
        int chk = sensorDHT.read22(pinSensor);
        unsigned long stop = micros();
        switch (chk){
            case DHTLIB_OK:
                Serial.print("OK,\t");
                break;
            case DHTLIB_ERROR_CHECKSUM:
                Serial.print("Checksum error,\t");
                break;
            case DHTLIB_ERROR_TIMEOUT:
                Serial.print("Time out error,\t");
                break;
            case DHTLIB_ERROR_CONNECT:
                Serial.print("Connect error,\t");
                break;
            case DHTLIB_ERROR_ACK_L:
                Serial.print("Ack Low error,\t");
                break;
            case DHTLIB_ERROR_ACK_H:
                Serial.print("Ack High error,\t");
                break;
            default:
                Serial.print("Unknown error,\t");
                break;
            }
        Serial.print(stop - start);
        Serial.print(", \t\t");
        Serial.print(sensorDHT.humidity, 1);
        Serial.print(",\t\t");
        Serial.println(sensorDHT.temperature, 1);

        delayIntervalo = millis();
    };
}
