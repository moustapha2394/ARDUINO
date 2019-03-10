#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>
const int  pin_RST=9;
const int pin_SS=10;
const int pinled=3;
const String success="95FBF945";
const String success2="3AC5E6AB";
const int buzz=3;
String tagID="";
int alarme=0;
const byte rows=4;
const byte cols=4;
String codeacces="*2312";
String codetaper="";
int nb=0;
char keys[rows][cols]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowspins[rows]={7,6,5,4};
byte colspins[cols]={3,2,1,0};

Keypad keypad=Keypad(makeKeymap(keys),rowspins,colspins,rows,cols);

MFRC522 rfid(pin_SS,pin_RST); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  pinMode(3,OUTPUT);
  SPI.begin();
  rfid.PCD_Init();
  rfid.PCD_DumpVersionToSerial();
  Serial.println("the module is ready to scan");
          tone(buzz,523,50);
          delay(50);
          tone(buzz, 783, 50);
          delay(50);
          tone(buzz, 1046, 50);
          delay(50);
          tone(buzz, 1568, 50);
          delay(50);
          tone(buzz, 2093, 70);
          delay(250);
          tone(buzz,370,50);
        delay(100);
        tone(buzz, 370, 300);
        delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!rfid.PICC_IsNewCardPresent()){
    return;
    }
  if(!rfid.PICC_ReadCardSerial()){
    return;
    }
    getID();
    if(tagID==success){
      noTone(3);
     Serial.println("okaayyy");
          tone(buzz,523,50);
          delay(50);
          tone(buzz, 783, 50);
          delay(50);
          tone(buzz, 1046, 50);
          delay(50);
          tone(buzz, 1568, 50);
          delay(50);
          tone(buzz, 2093, 70);
          delay(250);
          alarme=0;
    }else{
        Serial.println(tagID);
        if(alarme<3){
        tone(buzz,370,50);
        delay(100);
        tone(buzz, 370, 300);
        delay(1000);
        }
        alarme++;
        Serial.println(alarme);
       }

    if(alarme<=3){
        tone(3,1000);
      }
      char key=keypad.getKey();
  if(key=='A'){
   codetaper="";
   nb=0;
   Serial.print("clear: ");
   Serial.print(codetaper);
   Serial.print(" :");
   Serial.println(nb);
   return;
  }
  if(int(key) !=0){
    nb++;
    codetaper=codetaper+String(key);
    if(nb==5){
      if(codetaper==codeacces){
        Serial.println("okay");
        nb=0;
        codetaper="";
      }else{
        Serial.println("incorrect password");
        nb=0;
        codetaper="";
      }
    }
  }
    }
void getID(){
  tagID="";
  //rfid.PICC_DumpToSerial(&(rfid.uid));
  
  for(int i=0;i<4;i++){
      //curbadge[i]=rfid.uid.uidByte[i];
      tagID.concat(String(rfid.uid.uidByte[i], HEX));
    }
    tagID.toUpperCase();
    rfid.PICC_HaltA();
  }
