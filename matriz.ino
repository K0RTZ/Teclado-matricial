#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>

Servo miServo;
LiquidCrystal lcd(48,49,50,51,52,53);

const byte filas = 4;
const byte columnas = 3;
char teclas[filas][columnas] = {
   {'1','2','3'},
   {'4','5','6'},
   {'7','8','9'},
   {'*','0','#'}};
   
byte pin_filas[filas] = { 8, 7, 6, 5 };
byte pin_columna[columnas] = { 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(teclas), pin_filas, pin_columna, filas, columnas);

byte led = 29;

int rojo = A13;
int verde = A14;  //led rgb
int azul = A15;

byte d1 = 22;
byte d2 = 23;
byte d3 = 24;
byte d4 = 25;      //display de 7 segmentos
byte d5 = 26;
byte d6 = 27;
byte d7 = 28;

int buzzer = 9;
byte estadoBuzzer = 20;

float distancia=0;
float tiempo=0;      //sensor ultrasonico
byte trig = 10;
byte echo = 11; 

byte pinServo = 36;
byte posicion1 = 180;  //servomotor
byte posicion2 = 0;

byte pulso = 12;       //pines para controlar el CD4017
byte reset = 13;

unsigned long antesMillis = 0;
unsigned long actualMillis = 0;
unsigned long antesMillis2 = 0;
unsigned long actualMillis2 = 0;
long intervalo = 0;
const long intervalo2 = 500;

void setup() {
   Serial.begin(9600);
   lcd.begin(16,2);
   
   miServo.attach(pinServo);
   miServo.write(posicion2);   //inicia el servo a 0 grados
   
   pinMode(led,OUTPUT);       //pin 29 como salida
   pinMode(buzzer,OUTPUT);    //pin 9 como salida
   
   pinMode(rojo,OUTPUT);
   pinMode(verde,OUTPUT);    //pines analogicos A13,A14,A15 como salida
   pinMode(azul,OUTPUT);
   
   pinMode(d1,OUTPUT);
   pinMode(d2,OUTPUT);
   pinMode(d3,OUTPUT);
   pinMode(d4,OUTPUT);
   pinMode(d5,OUTPUT);       //pines para el display como salida
   pinMode(d6,OUTPUT);
   pinMode(d7,OUTPUT);
   pinMode(44,OUTPUT);      //pines para controlar el puente H
   pinMode(46,OUTPUT);

   pinMode(trig,OUTPUT);    //pin 10 como salida
   pinMode(echo,INPUT);     //pin 11 como entrada

   pinMode(pulso,OUTPUT);   //pin 12 como salida
   pinMode(reset,OUTPUT);   //pin 13 como salida
}
void sensor(){
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  delayMicroseconds(10);
}

void uno(){  
  digitalWrite(d1,HIGH);
  digitalWrite(d2,LOW);
  digitalWrite(d3,LOW);
  digitalWrite(d4,HIGH);     //aparece el numero uno en el display
  digitalWrite(d5,HIGH);
  digitalWrite(d6,HIGH);
  digitalWrite(d7,HIGH);
    
  analogWrite(rojo,0);
  analogWrite(verde,255);   //led rgb de color verde
  analogWrite(azul,0);
    
  digitalWrite(led,HIGH);   //led enciende

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla 1");
  lcd.setCursor(0,1);
  lcd.print("Encender LED");
  lcd.print("         ");
}

void dos(){
  digitalWrite(d1,LOW);
  digitalWrite(d2,LOW);
  digitalWrite(d3,HIGH);
  digitalWrite(d4,LOW);      //aparece el numero dos en el display
  digitalWrite(d5,LOW);
  digitalWrite(d6,LOW);
  digitalWrite(d7,HIGH);
    
  analogWrite(rojo,0);
  analogWrite(verde,255);   //led rgb de color verde
  analogWrite(azul,0);
    
  digitalWrite(led,LOW);    //led apagado

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla 2");
  lcd.setCursor(0,1);
  lcd.print("Apagar LED");
  lcd.print("         ");
}

void tres(){
  digitalWrite(d1,LOW);
  digitalWrite(d2,LOW);
  digitalWrite(d3,LOW);
  digitalWrite(d4,LOW);     //aparece el numero tres en el display
  digitalWrite(d5,HIGH);
  digitalWrite(d6,LOW);
  digitalWrite(d7,HIGH);
    
  analogWrite(rojo,0);
  analogWrite(verde,255);   //led rgb en color verde
  analogWrite(azul,0);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla 3");
  lcd.setCursor(0,1);
  lcd.print("Sensor: ");
}

void cuatro(){
  digitalWrite(d1,HIGH);
  digitalWrite(d2,LOW);
  digitalWrite(d3,LOW);
  digitalWrite(d4,HIGH);    //aparece el numero cuatro en el display
  digitalWrite(d5,HIGH);
  digitalWrite(d6,LOW);
  digitalWrite(d7,LOW);
    
  analogWrite(rojo,0);
  analogWrite(verde,0);   //led rgb de color azul
  analogWrite(azul,255);
    
  analogWrite(buzzer,0);  //se apaga el buzzer

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla 4");
  lcd.setCursor(0,1);
  lcd.print("Apagar sensor");
  lcd.print("         ");
}

void cinco(){
  digitalWrite(d1,LOW);
  digitalWrite(d2,HIGH);
  digitalWrite(d3,LOW);
  digitalWrite(d4,LOW);   //aparece el numero cinco en el display
  digitalWrite(d5,HIGH);
  digitalWrite(d6,LOW);
  digitalWrite(d7,LOW);
    
  analogWrite(rojo,0);
  analogWrite(verde,0);   //led rgb de color azul
  analogWrite(azul,255);
    
  miServo.write(posicion1);  //servomotor a 180 grados

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla 5");
  lcd.setCursor(0,1);
  lcd.print("Servo a 180");
  lcd.print("         ");
}

void seis(){
  digitalWrite(d1,LOW);
  digitalWrite(d2,HIGH);
  digitalWrite(d3,LOW);
  digitalWrite(d4,LOW);    //aparece el numero seis en el display
  digitalWrite(d5,LOW);
  digitalWrite(d6,LOW);
  digitalWrite(d7,LOW);
    
  analogWrite(rojo,0);
  analogWrite(verde,0);   //led rgb de color azul
  analogWrite(azul,250);
    
  miServo.write(posicion2);  //servomotor a 0 grados 

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla 6");
  lcd.setCursor(0,1);
  lcd.print("Servo a 0");
  lcd.print("         ");
}

void siete(){
  digitalWrite(d1,LOW);
  digitalWrite(d2,LOW);
  digitalWrite(d3,LOW);
  digitalWrite(d4,HIGH);   //aparece el numero siete en el display
  digitalWrite(d5,HIGH);
  digitalWrite(d6,HIGH);
  digitalWrite(d7,HIGH);
    
  analogWrite(rojo,255);
  analogWrite(verde,0);   //led rgb de color rojo
  analogWrite(azul,0);
    
  digitalWrite(44,HIGH);  //gira el motor a un lado 
  digitalWrite(46,LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla 7");
  lcd.setCursor(0,1);
  lcd.print("1-Girar motor");
  lcd.print("         ");
}

void ocho(){
  digitalWrite(d1,LOW);
  digitalWrite(d2,LOW);
  digitalWrite(d3,LOW);
  digitalWrite(d4,LOW);   //aparece el numero ocho en el display
  digitalWrite(d5,LOW);
  digitalWrite(d6,LOW);
  digitalWrite(d7,LOW);
    
  analogWrite(rojo,255);
  analogWrite(verde,0);   //led rgb de color rojo
  analogWrite(azul,0);
    
  digitalWrite(44,LOW);   //gira el motor a el lado opuesto
  digitalWrite(46,HIGH);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla 8");
  lcd.setCursor(0,1);
  lcd.print("2-Girar motor");
  lcd.print("         ");
}

void nueve(){
  digitalWrite(d1,LOW);
  digitalWrite(d2,LOW);
  digitalWrite(d3,LOW);
  digitalWrite(d4,LOW);    //aparece el numero nueve en el display
  digitalWrite(d5,HIGH);
  digitalWrite(d6,LOW);
  digitalWrite(d7,LOW);
    
  analogWrite(rojo,255);
  analogWrite(verde,0);   //led rgb de color rojo
  analogWrite(azul,0);
    
  digitalWrite(44,LOW);   //apaga el motor
  digitalWrite(46,LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla 9");
  lcd.setCursor(0,1);
  lcd.print("Apagar motor");
  lcd.print("         ");
}

void asterisco(){
  digitalWrite(d1,HIGH);
  digitalWrite(d2,HIGH);
  digitalWrite(d3,HIGH);
  digitalWrite(d4,HIGH);   // aparece el simbolo - en el display
  digitalWrite(d5,HIGH);
  digitalWrite(d6,LOW);
  digitalWrite(d7,HIGH);
    
  analogWrite(rojo,255);
  analogWrite(verde,0);   //led rgb de color morado
  analogWrite(azul,255);

  digitalWrite(pulso,HIGH);   //manda un pulso al CD4017 para cambiar de led
  delay(10);
  digitalWrite(pulso,LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla *");
  lcd.setCursor(0,1);
  lcd.print("Siguiente LED");
  lcd.print("         ");
}

void cero(){
  digitalWrite(d1,LOW);
  digitalWrite(d2,LOW);
  digitalWrite(d3,LOW);
  digitalWrite(d4,LOW);   //aparece el numero cero en el display
  digitalWrite(d5,LOW);
  digitalWrite(d6,HIGH);
  digitalWrite(d7,LOW);
    
  analogWrite(rojo,255);
  analogWrite(verde,0);   //led rgb de color morado
  analogWrite(azul,255);

  digitalWrite(led,LOW);  //apaga el led si esta encendido

  analogWrite(buzzer,0);  //apaga el buzzer si esta sonando

  miServo.write(posicion2);  //servomotor a 0 grados

  digitalWrite(44,LOW);   //apaga el motor si esta girando
  digitalWrite(46,LOW);

  digitalWrite(reset,HIGH);  //manda una señal para volver al primer led del CD4017
  delay(10);
  digitalWrite(reset,LOW);

  lcd.clear();  
  lcd.setCursor(0,0);
  lcd.print("Tecla 0");
  lcd.setCursor(0,1);
  lcd.print("REINICIAR TODO");
  lcd.print("         ");
}

void gato(){
  digitalWrite(d1,LOW);
  digitalWrite(d2,HIGH);
  digitalWrite(d3,HIGH);
  digitalWrite(d4,LOW);   //aparece 3 lineas en reprecentacion a # en el display
  digitalWrite(d5,HIGH);
  digitalWrite(d6,LOW);
  digitalWrite(d7,HIGH);
  
  analogWrite(rojo,255);
  analogWrite(verde,0);   //led rgb de color morado 
  analogWrite(azul,255);

  digitalWrite(reset,HIGH);   //manda una señal para volver al primer led del CD4017
  delay(10);
  digitalWrite(reset,LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tecla #");
  lcd.setCursor(0,1);
  lcd.print("Reiniciar LEDs");
  lcd.print("         ");
}

void loop() {
   char tecla = keypad.getKey();
  
  if(tecla){
  switch(tecla){
    
    case '1':
    uno();
    Serial.println(tecla);
    break;
    
    case '2':
    dos();
    Serial.println(tecla);
    break;
    
    case '3':
    tres();

    while(tecla == '3'){  //entra en un while si se presiona la tecla 3
      sensor();
      tiempo = pulseIn(echo,HIGH);
      distancia = 0.01716 * tiempo;   // se calcula la distancia del sensor
      actualMillis = millis();
      actualMillis2 = millis();
      
      if(actualMillis2 - antesMillis2 >= intervalo2){   //manda el valor de la distancia al lcd cada medio segundo
        antesMillis2 = actualMillis2;
        Serial.println(distancia);
        lcd.setCursor(8,0);
        lcd.print(distancia);
        lcd.print("cm   ");
      }
      //dependiendo de la distancia el buzzer sonara más rapido o más lento
      //utilice if y millis para que no se ocuparan delays 
      if(distancia < 6){
        intervalo = 50;
        if(actualMillis - antesMillis >= intervalo){
          antesMillis = actualMillis;
        
          if(estadoBuzzer == 0){
          estadoBuzzer = 10;
          }else{
          estadoBuzzer = 0;
          } 
         }
        analogWrite(buzzer,estadoBuzzer);
      }
      if(distancia > 6 && distancia < 10){
        intervalo = 130;
        if(actualMillis - antesMillis >= intervalo){
          antesMillis = actualMillis;
        
          if(estadoBuzzer == 0){
          estadoBuzzer = 10;
          }else{
          estadoBuzzer = 0;
          } 
         }
        analogWrite(buzzer,estadoBuzzer);
      }
      if(distancia > 10 && distancia < 20){
        intervalo = 200;
        if(actualMillis - antesMillis >= intervalo){
          antesMillis = actualMillis;
        
          if(estadoBuzzer == 0){
          estadoBuzzer = 10;
          }else{
          estadoBuzzer = 0;
          } 
         }
        analogWrite(buzzer,estadoBuzzer);
      }
      if(distancia > 20 && distancia < 50){
        intervalo = 300;
        if(actualMillis - antesMillis >= intervalo){
          antesMillis = actualMillis;
        
          if(estadoBuzzer == 0){
          estadoBuzzer = 10;
          }else{
          estadoBuzzer = 0;
          } 
         }
        analogWrite(buzzer,estadoBuzzer);
      }
      if(distancia > 50 && distancia < 100){
        intervalo = 500;
        if(actualMillis - antesMillis >= intervalo){
          antesMillis = actualMillis;
        
          if(estadoBuzzer == 0){
          estadoBuzzer = 10;
          }else{
          estadoBuzzer = 0;
          } 
         }
        analogWrite(buzzer,estadoBuzzer);
      }
      if(distancia > 100){
        intervalo = 700;
        if(actualMillis - antesMillis >= intervalo){
          antesMillis = actualMillis;
        
          if(estadoBuzzer == 0){
          estadoBuzzer = 10;
          }else{
          estadoBuzzer = 0;
          } 
         }
        analogWrite(buzzer,estadoBuzzer);
      }
      
  
      char tecla1 = keypad.getKey();
      //para poder salir del while se debe presionar la tecla 4 o 0 
      //la variable tecla y tecla1 son diferentes pero funcionan igual
      if(tecla1){
        switch(tecla1){
          case '1':
          uno();
          break;

          case '2':
          dos();
          break;

          case '3':
          tres();
          break;
          
          case '4':
          tecla = '4';
          cuatro();
          break;

          case '5':
          cinco();
          break;

          case '6':
          seis();
          break;

          case '7':
          siete();
          break;

          case '8':
          ocho();
          break;

          case '9':
          nueve();
          break;

          case '*':
          asterisco();
          break;

          case '0':
          tecla = '0';
          cero();
          break;

          case '#':
          gato();
          break;
        }
      }
    }
    
    break;
    
    case '4':
    cuatro();
    Serial.println(tecla);
    break;

    case '5':
    cinco();
    Serial.println(tecla);
    break;

    case '6':
    seis();
    Serial.println(tecla);
    break;

    case '7':
    siete();
    Serial.println(tecla);
    break;

    case '8':
    ocho();
    Serial.println(tecla);
    break;

    case '9':
    nueve();
    Serial.println(tecla);
    break;

    case '*':
    asterisco();
    Serial.println(tecla);
    break;

    case '0':
    cero();
    Serial.println(tecla);
    break;

    case '#':
    gato();
    Serial.println(tecla);
    break;
  } 
  }
  
}
