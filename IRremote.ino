#include <IRremote.h> //include the library
#include <Servo.h>

const int receiver = 7; //initialize pin 7 as recevier pin.
const int ldr1 = A0;
const int ldr2 = A1;
const int SERV = 6;
const int green = 12;
const int yellow = 11;
const int buzzer = 10;
int pos;

IRrecv irrecv(receiver); //create a new instance of receiver
decode_results results;
Servo myservo;

void setup() {
 Serial.begin(9600);
 irrecv.enableIRIn(); //start the receiver
 pinMode (ldr1, INPUT);
 pinMode (ldr2, INPUT);
 pinMode (green, OUTPUT);
 pinMode (yellow, OUTPUT);
 pinMode (buzzer, OUTPUT);
 myservo.attach(SERV);
}

void beep(){
  digitalWrite (yellow, HIGH);
  delay(500);
  digitalWrite (yellow, LOW);
  delay(500);
  }

void srv(int x){

  Serial.println(x);
  
  if(x==-8161)
  myservo.write(0);
  else if (x==-22441)
    myservo.write(x);
  }

void loop() {

  digitalWrite(green, HIGH);
  digitalWrite(buzzer, LOW);

  int Val1 = analogRead(ldr1);
  int Val2 = analogRead(ldr2);
  //Serial.print(Val1); // For troubleshooting
  //Serial.print("  ");
  //Serial.println(Val2);

  while(Val1<=200 && Val2>=150){
      digitalWrite(buzzer, HIGH);
      digitalWrite(green, LOW);
      Val2 = analogRead(ldr2);
      beep();
      if (irrecv.decode(&results)){  //if we have received an IR signal
        Serial.println (results.value, HEX); //display HEX results 
        srv(results.value);
        irrecv.resume(); //next value
        }
  }
  
  if (irrecv.decode(&results)){  //if we have received an IR signal
  Serial.println (results.value, HEX); //display HEX results 
  srv(results.value);
  irrecv.resume(); //next value
  }

  Serial.println(pos);
  
 }
