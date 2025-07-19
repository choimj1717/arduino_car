// #include <Servo.h>

// #define TRIG 2 //TRIG 핀 설정 (초음파 보내는 핀)
// #define ECHO 3 //ECHO 핀 설정 (초음파 받는 핀)

// int moter = 12;
// Servo servo;

// int angle = 90;

// // int AA = 6;               //모터A의 A를 6번 핀에 배치
// // int AB = 7;               //모터A의 B를 7번 핀에 배치

// // int AA2 = 9;
// // int AB2 = 10;
 
// void setup() 
// {
//   Serial.begin(9600);
//   // pinMode(AA, OUTPUT);
//   // pinMode(AB, OUTPUT);
   
//   // pinMode(AA2, OUTPUT);
//   // pinMode(AB2, OUTPUT);

//   pinMode(TRIG, OUTPUT);
//   pinMode(ECHO, INPUT);

//   servo.attach(12);
//   delay(1000);
// }

// void loop(){
//   servo.write(0);
//   delay(1500);;

//   for (int i = 0; i <=180;){
//     servo.write(i);
//     delay(50);
//     i+=30;
//   }
//   long duration, distance;
  
//   digitalWrite(TRIG, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIG, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG, LOW);
  
//   duration = pulseIn (ECHO, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.
  
//   distance = duration * 17 / 1000; 




//   //PC모니터로 초음파 거리값을 확인 하는 코드 입니다.

//   Serial.println(duration ); //초음파가 반사되어 돌아오는 시간을 보여줍니다.
//   Serial.print("\nDIstance : ");
//   Serial.print(distance); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
//   Serial.println(" Cm");


//   delay(1000);
// }
 


#include <Servo.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define SERVO_PIN 12

int AA = 6;               
int AB = 7;             

int AA2 = 9;
int AB2 = 10;

Servo myServo;

long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myServo.attach(SERVO_PIN);

  pinMode(AA, OUTPUT);
  pinMode(AB, OUTPUT);
   
  pinMode(AA2, OUTPUT);
  pinMode(AB2, OUTPUT);
}

void loop() {
  for (int angle = 45; angle <= 125; angle += 3) {
    myServo.write(angle);
    delay(10);  // 서보 안정화 시간
    long distance = readDistanceCM();
    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);

    if (distance <= 50){
    digitalWrite(AA, LOW);
    digitalWrite(AB, HIGH);
    digitalWrite(AA2, LOW);
    digitalWrite(AB2, HIGH);
    delay(1500);
    digitalWrite(AA, HIGH);
    digitalWrite(AB, LOW);
    digitalWrite(AA2, LOW);
    digitalWrite(AB2, HIGH);
    delay(1000);
    } else{
    digitalWrite(AA, HIGH);
    digitalWrite(AB, LOW);
    digitalWrite(AA2, HIGH);
    digitalWrite(AB2, LOW);
    }
  }

  for (int angle = 125; angle >= 45; angle -= 3) {
    myServo.write(angle);;/////////
    delay(10);
    long distance = readDistanceCM();
    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
    if (distance <= 10){
    digitalWrite(AA, LOW);
    digitalWrite(AB, HIGH);
    digitalWrite(AA2, LOW);
    digitalWrite(AB2, HIGH);
    delay(1500);
    digitalWrite(AA, LOW);
    digitalWrite(AB, HIGH);
    digitalWrite(AA2, HIGH);
    digitalWrite(AB2, LOW);
    delay(1000);
    } else{
    digitalWrite(AA, HIGH);
    digitalWrite(AB, LOW);
    digitalWrite(AA2, HIGH);
    digitalWrite(AB2, LOW);
    }
  }
  
}

// #include <Servo.h>
// #include <SoftwareSerial.h>

// Servo myServo;
// SoftwareSerial BTSerial(4, 5); // RX, TX

// long readDistanceCM() {
//   return random(10, 100);  // 실제 거리 센서로 바꿔야 함
// }

// void setup() {
//   myServo.attach(12);
//   BTSerial.begin(9600);
// }

// void loop() {
//   for (int angle = 0; angle <= 180; angle+=1) {
//     myServo.write(angle);
//     delay(15);
//     long distance = readDistanceCM(); 

//     BTSerial.print(angle);
//     BTSerial.print(",");
//     BTSerial.println(distance);
//   }

//   for (int angle = 180; angle >= 0; angle-=1) {
//     myServo.write(angle);
//     delay(15);
//     long distance = readDistanceCM();

//     BTSerial.print(angle);
//     BTSerial.print(",");
//     BTSerial.println(distance);
//   }
// }
// #include <Servo.h>
// #include <SoftwareSerial.h>

// #define TRIG_PIN 2
// #define ECHO_PIN 3
// #define SERVO_PIN 12
// #define BT_RX 4  // 블루투스 RX ← 아두이노 TX
// #define BT_TX 5  // 블루투스 TX → 아두이노 RX

// Servo myServo;
// SoftwareSerial BTSerial(BT_RX, BT_TX); // RX, TX

// long readDistanceCM() {
//   digitalWrite(TRIG_PIN, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIG_PIN, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG_PIN, LOW);
  
//   long duration = pulseIn(ECHO_PIN, HIGH);
//   long distance = duration * 0.034 / 2;
//   return distance;
// }

// void setup() {
//   BTSerial.begin(9600);  // HC-06 기본 통신 속도
//   pinMode(TRIG_PIN, OUTPUT);
//   pinMode(ECHO_PIN, INPUT);
//   myServo.attach(SERVO_PIN);
// }

// void loop() {
//   for (int angle = 0; angle <= 180; angle += 1) {
//     myServo.write(angle);
//     delay(100);  // 서보 안정화 시간
//     long distance = readDistanceCM();
//     BTSerial.print(angle);
//     BTSerial.print(",");
//     BTSerial.println(distance);
//   }

//   for (int angle = 180; angle >= 0; angle -= 1) {
//     myServo.write(angle);
//     delay(100);
//     long distance = readDistanceCM();
//     BTSerial.print(angle);
//     BTSerial.print(",");
//     BTSerial.println(distance);
//   }
// }