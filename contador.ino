#define pinBotao 3

int portas[8] = {10, 9, 6, 7, 8, 11, 12, 5};

int senhas[11][8] = {{0,0,0,0,0,0,0,0}, //Tudo apagado
  					{1,1,1,1,1,1,0,0}, //Digito 0
                    {0,1,1,0,0,0,0,0}, //Digito 1
                    {1,1,0,1,1,0,1,0}, //Digito 2
                    {1,1,1,1,0,0,1,0}, //Digito 3
                    {0,1,1,0,0,1,1,0}, //Digito 4
                    {1,0,1,1,0,1,1,0}, //Digito 5
                    {1,0,1,1,1,1,1,0}, //Digito 6
                    {1,1,1,0,0,0,0,0}, //Digito 7
                    {1,1,1,1,1,1,1,0}, //Digito 8
				    {1,1,1,1,0,1,1,0}}; //Digito 9;

int numero = 0;

boolean botaoAtu = false;
boolean botaoAnt = false;

void setup() {
    int i;
    pinMode(pinBotao, INPUT);
    
        for(i = 0; i < 8; i++){
            pinMode(portas[i], OUTPUT);
    }
}

void loop() {
    int i;
    botaoAtu = digitalRead(pinBotao);

    if (botaoAtu && !botaoAnt) {
        numero++;

        if (numero > 10) {
            numero = 0; 
        }
    }
    botaoAnt = botaoAtu;

	for(i = 0; i < 8; i++){
        digitalWrite(portas[i], senhas[numero][i]);
    }
}