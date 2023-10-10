/** Definição dos pinos **/
#define LED_VERDE 25
#define JOGADOR_01 26
#define JOGADOR_02 27

/** Variáveis para verificar o toque **/
int touchReset;
int touch1;
int touch2;

int statusJogo = 0; // Variavel de controle
int pontosJogador01 = 0; // Armazena pontos do jogador 01
int pontosJogador02 = 0; // Armazena pontos do jogador 02


unsigned long previousMilis = 0; // Variavel para armazenar o tempo do inicio da rodada

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Definindo os pinos como saida
  pinMode(LED_VERDE, OUTPUT);
  pinMode(JOGADOR_01, OUTPUT);
  pinMode(JOGADOR_02, OUTPUT);

  Serial.print("Jogo iniciando...");

}

void loop() {
  touchReset = touchRead(14); // Lendo se o pino de controle foi tocado

  if(touchReset <=20 && statusJogo == 0) { // Se o pino de controle foi tocado
    Serial.println("Apertou o verde!");

    // Apaga os LEDs que estiverem acesos
    digitalWrite(JOGADOR_01, LOW);
    digitalWrite(JOGADOR_02, LOW);

    for(int c = 0; c < 3; c++) { // Pisca o LED verde 3 vezes
      digitalWrite(LED_VERDE, HIGH);
      delay(500);
      digitalWrite(LED_VERDE, LOW);
      delay(500);
    }
    statusJogo = 1; // Status do jogo definido para 1
    digitalWrite(LED_VERDE, HIGH); // Ascende o LED verde
  }

  if(statusJogo == 1){ // Se o status do jogo é 1 (ou seja, o pino de
                       // controle foi tocado)
    unsigned long currentMillis = millis(); // Começa a contar o tempo
    previousMilis = currentMillis; // O tempo anterior pega o tempo de inicio

    Serial.println("Entrou no jogo!");
    
    while(1 > 0){ // Laço atico até um pino ser tocado

      // Ler os valores dos pinos do jogo
      touch1 = touchRead(12);
      touch2 = touchRead(13);

      if(touch1 <= 20) { // Se o pino do jogador 1 foi tocado

        digitalWrite(JOGADOR_01, HIGH); // Ascenda o LED do jogador 1

        // Imprimindo o tempo que o jogador 1 levou para apertar
        Serial.print("O jogador 1 apertou o botão com ");
        Serial.print(currentMillis - previousMilis);
        Serial.println(" ms");

        pontosJogador01 ++; // Incrementa a pontuação do jogador 1
        break; // Sai do laço

      }
      if(touch2 <= 20) { // Se o pino do jogador 2 foi tocado

        digitalWrite(JOGADOR_02, HIGH); // Ascenda o LED do jogador 2

        // Imprimindo o tempo que o jogador 2 levou para apertar
        Serial.print("O jogador 2 apertou o botão com ");
        Serial.print(currentMillis - previousMilis);
        Serial.println(" ms");
        
        pontosJogador02 ++; // Incrementa a pontuação do jogador 2
        break; // Sai do laço

      }
    }
    statusJogo = 0; // Zera o estado para aguardar o pino de controle

    Serial.println("Saiu da partida!");

    // Imprime o placar
    Serial.println("Placar:");
    Serial.print("Jogador 1 = ");
    Serial.print(pontosJogador01);
    Serial.println(" pontos.");
    
    Serial.print("Jogador 2 = ");
    Serial.print(pontosJogador02);
    Serial.println(" pontos.");
    
  }
  delay(100);

}
