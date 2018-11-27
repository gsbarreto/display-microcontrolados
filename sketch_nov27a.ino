//Programa: Teste de Display LCD 16 x 2
//Autor: FILIPEFLOP
 
//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
#include <string.h>

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define btn1 8
#define btn2 9

#define btnMais 7
#define btnMenos 6


int estado = 0; //0 - Proxima racao, 1 - Set racao   
char *str;
char *str2;
int horaConfigurada = 0;
int minutosConfigurados = 0;
int hora = 0;
int minutos = 0;
char buffer[20];
int flagEdit = 0; // 0 - Reset, 1 - Hora, 2 - Minutos

 
void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  pinMode(btn1, INPUT);
  pinMode(btn1, INPUT);  
  pinMode(btnMais, INPUT);
  pinMode(btnMenos, INPUT);      
}
 
void loop()
{
  if(digitalRead(btn1)){
    estado = 0;
    while(digitalRead(btn1));
  }

  if(digitalRead(btnMais)){
    if(flagEdit == 1){
      if(hora < 24){
        hora++;
      }
    }else if(flagEdit == 2){
      if(minutos < 60){
        minutos+=15;
      }
    }
    while(digitalRead(btnMais));
  }

  
  if(digitalRead(btnMenos)){
    if(flagEdit == 1){
      if(hora > 0){
        hora--;
      }
    }else if(flagEdit == 2){
      if(minutos > 0){
        minutos-=15;
      }
    }
    while(digitalRead(btnMenos));
  }


  if(digitalRead(btn2)){
    estado = 1;
  }
  
  if(estado == 0){
    //Limpa a tela
    lcd.clear();
    //Posiciona o cursor na coluna 3, linha 0;
    lcd.setCursor(0, 0);
    //Envia o texto entre aspas para o LCD
    lcd.print("Proxima Racao");
    lcd.setCursor(0, 1);
    lcd.setCursor(0, 1);
    if(hora < 10){
      lcd.print("0");
      lcd.setCursor(1, 1);
      lcd.print(itoa(horaConfigurada,buffer,10));
    }else{
      lcd.print(itoa(horaConfigurada,buffer,10));
    }
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(3, 1);
    if(minutos < 10){
      lcd.print("0");
      lcd.setCursor(4, 1);
      lcd.print(itoa(minutosConfigurados,buffer,10));
    }else{
      lcd.print(itoa(minutosConfigurados,buffer,10));
    }
    delay(100);
  }else{
    //Limpa a tela
    lcd.clear();
    //Posiciona o cursor na coluna 3, linha 0;
    lcd.setCursor(0, 0);
    //Envia o texto entre aspas para o LCD
    lcd.print("Config. Horario");
    //Mostra o horario
    lcd.setCursor(0, 1);
    if(hora < 10){
      lcd.print("0");
      lcd.setCursor(1, 1);
      lcd.print(itoa(hora,buffer,10));
    }else{
      lcd.print(itoa(hora,buffer,10));
    }
    lcd.setCursor(2, 1);
    lcd.print(":");
    lcd.setCursor(3, 1);
    if(minutos < 10){
      lcd.print("0");
      lcd.setCursor(4, 1);
      lcd.print(itoa(minutos,buffer,10));
    }else{
      lcd.print(itoa(minutos,buffer,10));
    }
    //Edita o horario
    if(digitalRead(btn2)){
      flagEdit++;
      while(digitalRead(btn2));
    }

    if(flagEdit == 3){
      horaConfigurada = hora;
      minutosConfigurados = minutos;
      flagEdit = 0;
      estado = 0;
    }
    
  }
  
}
