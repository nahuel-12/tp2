#include <Keypad.h> 
#include <LiquidCrystal_I2C.h>
#define ledR 13
#define ledV 12
#define test 1
#define reset 2
#define conf 3
LiquidCrystal_I2C lcd(0x27,20,4);  0x27 for a 16 chars and 2 line display
char contrasena[]="2C2022";  
char codigo[6];            
char tecla;
int cont=0;          
boolean verif=true;
#define fila 4 
#define colu  4 

char matriz[fila][colu] =  
{
  {'1','4','7','A'},
  {'2','5','8','B'},
  {'3','6','9','C'},
  {'*','0','#','D'}
};

byte pinesf[fila] = {7, 6, 5, 4}; 
byte pinesc[colu] = {11,10, 9,8}; 

Keypad teclado = Keypad(makeKeymap(matriz), pinesf, pinesc, fila, colu); 

void setup()
{ 
 // Serial.begin(9600); 
  lcd.init();
  lcd.backlight();
  inicial();
  
  pinMode(ledR,OUTPUT);
  pinMode(ledV,OUTPUT);
  pinMode(test,INPUT_PULLUP);
  pinMode(reset,INPUT_PULLUP);
  pinMode(conf,INPUT_PULLUP);
}

void loop()
{
    lee_teclado();
    if(cont==6)          
    {
      verifica();
    }
  if (digitalRead(reset)==LOW){
    resetea();
  }
   if (digitalRead(test)==LOW){
    verifica();
  }
    if (digitalRead(conf)==LOW){
    configurar();
  }
}
void lee_teclado(){
  tecla = teclado.getKey();
  if (tecla != NO_KEY)         
  {
    codigo[cont]=tecla;          
   
    lcd.setCursor(10+cont,0);
    lcd.print(codigo[cont]);
    cont=cont+1;              
  }
  
}
void resetea(){
  cont=0;
  inicial();
}
void configurar(){
  cont=0;
  lcd.setCursor(0,1);
  lcd.print("Modo config");
  while (cont<6){
      lee_teclado();
  }
    for (int i=0;i<6;i++){
      contrasena[i]=codigo[i];
    }
  inicial();
}

void inicial(){
   lcd.setCursor(0,0);
  lcd.print("Password:       ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}

void verifica(){
  for (int i=0;i<6;i++)
      {
        if (codigo[i]!= contrasena[i])
        {
          verif=false;
          break;
        }
     }
      if(verif==true)
      {
      
      cod_ok();
      }
      else
      {
     
      cod_bad();
      }
      cont=0;  
      verif=true;
}
void cod_ok(){
   lcd.setCursor(0,1);
  lcd.print("Password OK");
  for( int i=0; i<5;i++){
    digitalWrite(ledV,!digitalRead(ledV));
    delay(1000);
  }
   inicial();
}

void cod_bad(){
   lcd.setCursor(0,1);
  lcd.print("Password Fail");
  for( int i=0; i<5;i++){
    digitalWrite(ledR,!digitalRead(ledR));
    delay(1000);
  }
  inicial();
}
