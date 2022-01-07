#include <SoftwareSerial.h>

SoftwareSerial ArduinoSlave(2,3);
String answer = String();
String msg = String();

bool check_first_loop = true;
bool meet_student = false;

String class_name = "SoWeWLAN";
String student_name;

void setup(){

  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);

  Serial.begin(9600);
  ArduinoSlave.begin(9600); 
          
}

void loop(){

  if(check_first_loop) {
    delay(500);
    sayHelloToStudent();
    check_first_loop = false;
  }

  if (!meet_student) {
    listenStudentPresentation();
  }

  delay(10000);
  answer = "";
  
}

void sayHelloToStudent() {
  msg = "Bonjour, bienvenue dans la classe " +class_name +" !";
  Serial.print("Master sent : ");
  Serial.println(msg);
  ArduinoSlave.print(msg);
  msg=""; 
}

void listenStudentPresentation() {

   //Read answer from slave
   while (ArduinoSlave.available()) {
     delay(10);  
     if (ArduinoSlave.available() >0) {
       char c = ArduinoSlave.read();  //gets one byte from serial buffer
       answer += c; //makes the string readString
     }
   }

  //ArduinoSlave.flush();

   if(answer.charAt(0) == '0' || answer.charAt(0) == '0') {
      sayHelloToStudent();
    }
    else if(answer.substring(0, 17).equals("Bonjour, je suis ")) {
      meet_student = true;
      student_name = answer.substring(17, 24);
      Serial.println(student_name + " est présent.");
    }  
}
