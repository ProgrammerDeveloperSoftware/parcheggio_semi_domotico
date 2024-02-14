  #include <LiquidCrystal_I2C.h>                          //includo la libreria del display con l'interfaccia I2C                          
#include <Servo.h>                                        //includo la libreria del servomotore

LiquidCrystal_I2C lcd(0x27,16,2);                         //inizio la comunicazione con il display a 16 colonne e 2 righe utilizzando un altro parametro che sarebbe 0x27 per l'interfaccia
Servo servo1;                                             //dichiaro la varibile servo1 
Servo servo2;                                             //dichiaro la varibile servo2
int sensoreentrata=13;                                    //pongo il sensoreentrata al pin 13 
int sensoreuscita=12;                                     //pongo il sensoreuscita al pin 12
int sensore1=11;                                          //pongo il sensore1 al pin 11
int sensore2=10;                                          //pongo il sensore2 al pin 10
int sensore3=9;                                           //ongo il sensore3 al pin 9
int led1=8;                                               //pongo il led1 al pin 8
int led2=7;                                               //pongo il led2 al pin 7
int led3=6;                                               //pongo il led3 al pin 6
int led4=2;                                               //pongo il led4 al pin 2                                       
int statosensoreentrata=HIGH;                             //pongo lo statosensoreentrata basso (perchè questo sensore quando non rileva niente ha lo stato alto, mentre rileva qualcosa ha lo stato basso)
int statosensoreuscita=HIGH;                              //pongo lo statosensoreuscita basso(non trova niente se è HIGH)
int statosensore1=HIGH;                                   //pongo lo statosensore1 basso
int statosensore2=HIGH;                                   //pongo lo statosensore2 basso
int statosensore3=HIGH;                                   //pongo lo statosensore3 basso
int a=0;                                                  //dichiaro la variabile per il counter dei ingressi
int b=0;                                                  //dichiaro la variabile per il counter per le uscite
int fotoresistenza=A3;                                    //pongo la fotoresistenza al pin A0 (pin anologico)
int val;                                                  //attribuisco questa variabile per i valori letti dalla fotoresistanza
int rele=5;                                               //pin dove è collegato il relè

void setup(){

Serial.begin(9600);                                       //inizializzo la comunicazione col monitor seriale
lcd.begin(16,2);                                          //inizializzo la comunicazione del display a 16 colonne e 2 righe
lcd.init();                                               //inizializzo la comunicazione
lcd.backlight();                                          //attivo la retro illuminazione
pinMode(led1,OUTPUT);                                     //pongo il led1 come OUTPUT
pinMode(led2,OUTPUT);                                     //pongo il led2 come OUTPUT
pinMode(led3,OUTPUT);                                     //pongo il led3 come OUTPUT
pinMode(led4,OUTPUT);                                     //pongo il led4 come OUTPUT
pinMode(sensoreentrata,INPUT);                            //pongo il sensoreentrata come INPUT
pinMode(sensoreuscita,INPUT);                             //pongo il sensoreuscita come INPUT
pinMode(sensore1,INPUT);                                  //pongo il sensore1 come INPUT
pinMode(sensore2,INPUT);                                  //pongo il sensore2 come INPUT
pinMode(sensore3,INPUT);                                  //pongo il sensore3 come INPUT
pinMode(rele,OUTPUT);                                     //pongo il relè come OUTPUT
servo1.attach(4);                                         //pongo il servo1 al pin 4
servo2.attach(3);                                         //pongo il servo2 al pin 3
  lcd.setCursor(3,0);                                     //pongo il cursore alla terza colonna, alla prima riga
  lcd.print("benvenuto");                                 //scrivo nel display la scritta "benvenuto"
  lcd.setCursor(4,1);                                     //pongo il cursore alla quarta colonna, alla seconda riga
  lcd.print("signore");                                   //scrivo nel display la scritta "signore"
  servo1.write(0);                                        //pongo il servo1 a 0 gradi
  servo2.write(0);                                        //pongo il servo2 a 0 gradi
  delay(5000);                                            //pausa di 5 secondi
  lcd.clear();                                            //pulisco il display
  lcd.setCursor(0,0);                                     //pongo il cursore all'inizio 
  lcd.print("ingressi= ");                                //scrivo nel display la parola "ingressi"
  lcd.setCursor(10,0);                                    //pongo il cursore alla decima colonna 
  lcd.print(a);                                           //stampo i valori della variabile per il counter degli ingressi
  lcd.setCursor(0,1);                                     //pongo il cursore alla prima colonna, prima riga
  lcd.print("posti pieni= ");                             //scrivo nel display la parola "posti pieni"
  lcd.setCursor(13,1);                                    //pongo il cursore alla tredicesima colonna, prima riga
  lcd.print(b);                                           //stampo i valori della variabile per il counter delle uscite
}

void loop(){

val=analogRead(fotoresistenza);                           //leggo i valori forniti dalla fotoresistenza e attribuito quei valori alla variabile "val"
Serial.println(val);                                      //stampo nel monitor seriale i valori della fotoresistenza
delay(500);                                               //pauda di mezzo secondo (500 ms)

if(val<500){                                             //se i valori sono maggiori o uguali rispetto alla soglia impostata
  digitalWrite(rele,HIGH);                                //pongo il relè alto
}

else{                                                     //altrimenti
  digitalWrite(rele,LOW);                                 //pongo il relè basso
}

statosensoreentrata=digitalRead(sensoreentrata);          //attribuisco la lettura digitale del sensoreentrata allo statosensoreentrata
if(statosensoreentrata==LOW){                             //se lo statosensoreentrata è alta
  a=a+1;                                                  //il counter dei ingressi viene incrementa di 1 
  b=b+1;                                                  //il counter per i posti pieni
  lcd.setCursor(0,0);                                     //pongo il cursore all'inizio del display
  lcd.print("ingressi= ");                                //scrivo nel display la parola "ingressi"
  lcd.setCursor(10,0);                                    //pongo il cursore alla decima colonna, prima riga
  lcd.print(a);                                           //stampo i valori del counter dei ingressi
  lcd.setCursor(0,1);                                     //pongo il cursore alla prima colonna, prima riga
  lcd.print("posti pieni= ");                             //scrivo nel display la parola "posti pieni"
  lcd.setCursor(13,1);                                    //pongo il cursore alla tredicesima colonna 
  lcd.print(b);                                           //stampo i valori della variabile per il counter dei posti pieni
  servo1.write(90);                                       //pongo il servo1 a 90 gradi
  delay(3000);                                            //pausa di 3 secondi
  servo1.write(0);                                        //pongo il servo1 a 0 gradi
  Serial.println("qualcuno è entrato");                   //scrivo nel monitor seriale la scritta "qualcuno è entrato"
  delay(1000);                                            //pausa di un secondo
}

else{                                                     //altrimenti
  servo1.write(0);                                        //pongo il servo a 0 gradi
}

statosensoreuscita=digitalRead(sensoreuscita);            //attribuisco la lettura digitale del sensoreuscita allo statosensoreuscita
if(statosensoreuscita==LOW){                              //se lo statosensoreuscita è alta
  b=b-1;                                                  //decrementa il counter per i posti pieni(qualcuno è uscito)
  a=a-1;                                                  //decrementa il counter della variabile dei ingressi
  lcd.setCursor(0,1);                                     //pongo il cursore all'nizione del display alla prima colonna e prima riga
  lcd.print("posti pieni= ");                             //scrivo nel display la parola "posti pieni"
  lcd.setCursor(13,1);                                    //pongo il cursore alla tredicesima colonna, prima riga
  lcd.print(b);                                           //stampo i valori della variabile per il counter dei posti pieni
  lcd.setCursor(10,0);                                    //pongo il cursore alla decima colonna, prima riga
  lcd.print(a);                                           //stampo i valori della variabile per il counter deli ingressi
  Serial.println(b);                                      //scrivo nel monitor seriale i valori letti della variabile
  servo2.write(90);                                       //pongo il servo2 a 90 gradi
  delay(3000);                                            //pausa di 3 secondi
  servo2.write(0);                                        //pongo il servo2 a 0 gradi
  Serial.println("qualcuno è uscito");                    //scrivo nel monitor seriale la scritta "qualcuno è uscito"
  delay(1000);                                            //pausa di un secondo
}

else{                                                     //altrimenti
servo2.write(0);                                          //pongo il servo2 a 0 gradi
}

statosensore1=digitalRead(sensore1);                      //attribuisco la lettura digitale del sensore1 alla variabile statosensore1
if(statosensore1==LOW){                                   //se lo statosensore1 è alto
  digitalWrite(led1,HIGH);                                //pingo il led1 altro
}
else{                                                     //altrimenti
  digitalWrite(led1,LOW);                                 //pongo il led1 basso
}

statosensore2=digitalRead(sensore2);                      //attribuisco la lettura digitale del sensore2 alla variabile statosensore2
if(statosensore2==LOW){                                   //se lo statosensore2 è alto
  digitalWrite(led2,HIGH);                                //pongo il led2 alto 
}
else{
  digitalWrite(led2,LOW);                                 //pongo il led2 basso
}

statosensore3=digitalRead(sensore3);                      //attribuisco la lettura digitale del sensore3 alla variabile statosensore3
if(statosensore3==LOW){                                   //se lo statosensore3 è alto
  //statoLED=!statoLED;
  digitalWrite(led3,HIGH);                                //pongo il led3 alto
}
else{                                                     //altrimenti
  digitalWrite(led3,LOW );                                //pongo il led3 basso
}

  if((statosensore1==LOW) and (statosensore2==LOW) and (statosensore3==LOW)){           //se lo stato dei tre sensori sono alti
    digitalWrite(led4,HIGH);                                                            //apongo il led4 alto
        
  }
  else{                                                                                 //altrimenti
    digitalWrite(led4,LOW);                                                             //pongo il led4 basso
  }
}
