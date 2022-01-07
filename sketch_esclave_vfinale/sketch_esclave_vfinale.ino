#include <SoftwareSerial.h>

SoftwareSerial ArduinoMaster(2,3);
String msg = String();
bool check_first_loop = true;

String class_name;
String student_name = "Pierre";

void setup(){

  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  
  Serial.begin(9600);
  ArduinoMaster.begin(9600); 
  
}

void loop(){

  if(check_first_loop) {
    check_first_loop = false;
  }

  listenClassroomPresentation();
  delay(10000);
  
}

void readSerialPort(){
 while (ArduinoMaster.available()) {
   delay(10); 
   if (ArduinoMaster.available() >0) {
     char c = ArduinoMaster.read();  //gets one byte from serial buffer
     msg += c; //makes the string readString
   }
 }
 ArduinoMaster.flush();
}


void listenClassroomPresentation() {
 //ArduinoMaster.flush();
 while (ArduinoMaster.available()) {
   delay(10); 
   if (ArduinoMaster.available() >0) {
     char c = ArduinoMaster.read();  //gets one byte from serial buffer
     msg += c; //makes the string readString
   }
 }
 ArduinoMaster.flush();
  
 if(msg.substring(0, 33).equals("Bonjour, bienvenue dans la classe")) {
    class_name = msg.substring(34, 42);
    Serial.println("Nous sommes en classe : " +class_name +".");
    giveMyPresentation();
 }
 else {
    askRepetition();
 }
}

void giveMyPresentation() {
  msg = "Bonjour, je suis " +student_name;
  // Send answer to master
  if(msg!=""){
    ArduinoMaster.print(msg);
    msg=""; 
  }
}

void askRepetition() {
  msg = "00000000";
  // Send answer to master
  if(msg!=""){
    ArduinoMaster.print(msg);
    msg=""; 
  }
}

