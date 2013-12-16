#include <LiquidCrystal.h>
#include <Servo.h>

/* Inicializa as CONSTANTES */
const int Luz_Fundo = 7;
const int button = 10; //13;        // variavel para o BTN
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
  
  servoTampa.attach(2);         // Define o pino 2 para o servo
  servoTampa.write(0);           // Vai pro angulo ZERO (posicao inicial)
  
  digitalWrite(Luz_Fundo, HIGH); 
 
  lcd.begin(16,2);
  lcd.createChar(1, heart); 
  
  delay(200);
}



void loop() {
  
  int estado = digitalRead(button);
  
  Serial.println(estado, DEC);
  
  switch (stageGame) {
    
    case 0:
      loadingHearts(0);               // faz o coracao piscar por 0.5 segundo (5 vezes)                                            
      mensagemLCD("Ola' mestre!", "", 2000);        
      stageGame++; //adiciona 1 para entrar na proxima fase      
      break;
        
    case 1: 
      mensagemLCD("Voce e humano?", "", 4000);  
      actionAndCheckQuestion();  
      break;
      
    case 2:
      mensagemLCD("O ceu esta", "azul?", 4000);        
      actionAndCheckQuestion();  
      break;
  
    case 3:
      mensagemLCD("As plantas", "estao verdes?", 4000);      
      actionAndCheckQuestion(); 
      break; 
  
    case 4:
      mensagemLCD("Esta pisando", "no chão?", 4000);      
      actionAndCheckQuestion();    
      break;
    
    case 5:
      mensagemLCD("Quer conhecer", "o premio?", 4000);
      actionAndCheckQuestion();
      break;  
      
    case 6:
      mensagemLCD("BINGO!!!", "", 4000);
      servoTampa.write(60);                       // Servo vai para a posicao 60º
      break;   
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
    
    if (btnStatus == 1) {
      Serial.println("Proxima fase!");
      stageGame++;
      lcd.clear();                   // limpa a tela do LCD
    }  

}


void loadingHearts(int mode) {

    switch (mode) {
        case 1:
          for(int i = 0; i < 15; i++) {
            lcd.setCursor(15,0);
            lcd.write(1);
            delay(80);  
            lcd.setCursor(15,0);
            lcd.print(" ");
            delay(80);
          }   
          break;
        case :
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
    }

}
