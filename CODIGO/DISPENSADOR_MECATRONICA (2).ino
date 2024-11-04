#include <Wire.h>              
#include <LiquidCrystal_I2C.h>  

// Crear un objeto LCD. Cambia "0x27" si es necesario.
LiquidCrystal_I2C lcd(0x27, 16, 2);  

int boton1=7;
int boton2=6;
int boton3=5;
int l1=LOW;
int l2=LOW;
int l3=LOW;
int porcen=0;
int motor1=2;
int motor2=3;
int tamvas;
int infra1=11;
int infra2=12;
int infra3=13;
float rcrm=1.5;
float rcrg=2.25;
void setup() {
  lcd.begin(16,2);              
  lcd.backlight();          
  lcd.setCursor(0, 0);      
  lcd.print("Iniciando..."); 
  delay(2000);  // Espera 2 segundos antes de comenzar
  pinMode(boton1,INPUT);
  pinMode(boton2,INPUT);
  pinMode(boton3,INPUT);
  pinMode(infra1,INPUT);
  pinMode(infra2,INPUT);
  pinMode(infra3,INPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
}

void loop() {
  l1=digitalRead(boton1);  
  l2=digitalRead(boton2);
  l3=digitalRead(boton3);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(porcen); 
  lcd.print("% del liquido A");
  if(porcen<0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Claudio weon, no hay negativos");
  }
  if(l1==HIGH){
    porcen=porcen+5;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(porcen); 
    lcd.print("% del liquido A");
  }
  else if(l2==HIGH){
    porcen=porcen-5;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(porcen); 
    lcd.print("% del liquido A");
  }
  else if(l3==HIGH){
    
    int tiempoa=20*porcen;
    int tiempob=2000-tiempoa;
    int sensor1=digitalRead(infra1);
    int sensor2=digitalRead(infra2);
    int sensor3=digitalRead(infra3);
    float rela=vaso(sensor1,sensor2,sensor3);
    tiempoa=rela*tiempoa;
    tiempob=rela*tiempob;
    digitalWrite(motor1,HIGH);
    delay(tiempoa);
    digitalWrite(motor1,LOW);
    digitalWrite(motor2,HIGH);
    delay(tiempob);
    digitalWrite(motor2,LOW);
    
    
   
    
  }
  delay(200);
}
float vaso(int sensor1,int sensor2,int sensor3){
  float rela=0;
  if(sensor1==LOW && sensor2==LOW && sensor3==LOW){
    rela=rcrg;
  }
  else if(sensor1==LOW && sensor2==LOW && sensor3==HIGH){
    rela=rcrm;
  }
  else if(sensor1==LOW && sensor2==HIGH && sensor3==HIGH){
    rela=1;
  }
  else if(sensor1==HIGH && sensor2==HIGH && sensor3==HIGH){
    rela=0;
  }
  return rela;
}