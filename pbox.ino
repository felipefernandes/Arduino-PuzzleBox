#include <LiquidCrystal.h>
#include <Servo.h>

/* Inicializa as CONSTANTES */
const int Luz_Fundo = 7;
const int button = 13;              // variavel para o BTN
Servo servoTampa;                   // cria o servo object
LiquidCrystal lcd(12,11,5,4,3,2);   // cria o LiquidCrystal object

/* Inicializa as VARIAVEIS */
int btnStatus = 0; // variavel para o Status do BTN
int stageGame = 0;
byte heart[8] = { 0b00000, 0b01010, 0b11111, 0b11111, 0b01110, 0b00100, 0b00000, 0b00000 };



void setup() {    

  Serial.begin(9600);
  
  pinMode(button, INPUT);        // declara o button com uma entrada
  pinMode(Luz_Fundo, OUTPUT);
  
  servoTampa.attach(9);           // Define o pino 9 para o servo
  servoTampa.write(0);            // Vai pro angulo ZERO (posicao inicial)
  
  digitalWrite(Luz_Fundo, HIGH); 
 
  lcd.begin(16,2);
  lcd.createChar(1, heart); 
  
  /* 
    Inicio do Game: Mensagem de saudaçao  
  */  
  loadingHearts(0);               // faz o coracao piscar por 0.5 segundo (5 vezes)                                            
  mensagemLCD("Ola' mestre!", "", 2000);        
  stageGame++; //adiciona 1 para entrar na proxima fase 
  
  delay(200);
}



void loop() {
  
  int estado = digitalRead(button);   
  
  // if (canInterrupt()) {
  //   if (estado == LOW) { Serial.println("ON"); } else { Serial.println("OFF"); }
  // }    
  
  switch (stageGame) {
        
    case 1: 
      mensagemLCD("Voce e humano?", "", 4000);  
      actionAndCheckQuestion();  
      break;
      
    case 2:
      mensagemLCD("O ceu esta", "azul?", 4000);        
      actionAndCheckQuestion();  
      break;
    
    case 3:
      mensagemLCD("Quer conhecer", "o premio?", 4000);
      actionAndCheckQuestion();
      break;       
  }
  
  if (stageGame == 999) {
      mensagemLCD("BINGO!!!", "", 4000);
      servoTampa.write(90);                       // Servo vai para a posicao 90º
  }
  
  
}


void actionAndCheckQuestion() {

    mensagemLCD("Aperte e segure o botao", "se SIM...", 4000);      
    mensagemLCD("..ou nao faca", "nada, se NAO.", 4000);      
    checkNextStage();  // verifica o estado do botao se apertado, incrementa a var de Controle

}


void mensagemLCD(String msg1, String msg2, int tempo) {

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(msg1);
  
  if (msg2 != "") {  
    lcd.setCursor(0,1);
    lcd.print(msg2);
  }
  
  delay(tempo);

}


void checkNextStage() {

    btnStatus = digitalRead(button);
    
    Serial.println(btnStatus, DEC);  // mensagem para o monitor com o estado do botao
    
    if (btnStatus == LOW) {
      Serial.println("Proxima fase!");
      stageGame++;
      lcd.clear();                   // limpa a tela do LCD
    }  

}


void loadingHearts(int mode) {

    switch (mode) {
        case 0:
          for(int i = 0; i < 15; i++) {
            lcd.setCursor(15,0);
            lcd.write(1);
            delay(80);  
            lcd.setCursor(15,0);
            lcd.print(" ");
            delay(80);
          }   
          break;
        case 1:
          for(int i = 0; i < 15; i++) {
              lcd.setCursor(i,0);
              lcd.write(1);
              delay(80);  
              lcd.setCursor(i+1,0);
              lcd.print(" ");
              delay(80);
           }  
          break;
        default:
          // do nothing
          break;
    }

}

/*
 *  Funcão que checa se o botão já foi acionado para evitar
 *  o bounce.
 *
 *  Por Bruno P. Gonçalves 
 *  http://forum.arduino.cc/index.php?PHPSESSID=e8cf5dpt7nkp4jil41cp7edp64&topic=29133.0
*/

bool canInterrupt()
{
      static unsigned long last_interrupt_time = 0;
      unsigned long interrupt_time = millis();

      // Verifica se a ultima interrupção foi à 200 ms
      if(interrupt_time - last_interrupt_time > 400)
      {
            last_interrupt_time = interrupt_time;
            return true;
      }
      return false;
} 

