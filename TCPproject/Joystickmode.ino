#include <Servo.h>

Servo myservo1;
Servo myservo2;

int Servopin1 = 13;   //1번 서보모터
int Servopin2 = 12;   //2번 서보모터
// Pin 2 - > CLK
// Pin 3 - > DIO
int s1rad;
int s2rad;
int crr1;
int crr2;
int pr1;
int pr2;
int btnStat = 0;   //조이스틱이 눌렸을때의 값 저장
int s11 = 85;
int s12 = 100;
int s21 = 84;
int s22 = 69;
void setup()
{
  myservo1.attach(Servopin1);
  myservo2.attach(Servopin2);
  Serial.begin(9600); //시리얼 통신을 하기위한 통신속도설정
  pinMode(Servopin1, OUTPUT);
  pinMode(Servopin2, OUTPUT);
  pinMode(8, INPUT_PULLUP);
}

void loop()
{
  btnStat = digitalRead(8);  //조이스틱을 눌렀을때 0의 값이 수신된다.

/*
  Serial.print(isStart);
  Serial.print("  -  ");
  Serial.println(btnCnt);
*/
  
 

  //map(조이스틱 좌우 아날로그 값, 조이스틱 최소값, 조이스틱 최대값, 서보모터 최소값, 서보모터 최대값)
  //조이스틱값, 서보모터의 값은 조립방향에 따라 정 반대가 될 수도 있습니다.
  //테스트 하면서, 최적의 값을 찾아주어야 합니다.
  Serial.print(analogRead(A1)); // X축 값이 표기됩니다.
  Serial.print("  "); 
  s1rad =map(analogRead(A1), 0, 1023, s11, s12);
  Serial.print(analogRead(A2)); // X축 값이 표기됩니다.
  Serial.print("  "); 
  s2rad= map(analogRead(A0), 0, 1023, s21, s22);
  Serial.print(s1rad); // X축 값이 표기됩니다.
  Serial.print("  "); 
  Serial.print(s2rad); // X축 값이 표기됩니다.
  Serial.print("  ");
  crr1 = constrain(s1rad,s11+2, s12-2);
  crr2 = constrain(s2rad, s22+2, s21-2);

  if ((crr1 > pr1+2) or (crr1 < pr1 -2))
  {
    myservo1.attach(Servopin1);
    myservo1.write(crr1);
    delay(90);
    pr1 = crr1;
  }
  if ((crr2 > pr2+2) or (crr2 < pr2 -2))
  {
    myservo2.attach(Servopin2);
    myservo2.write(crr2);
    delay(90);
    pr2 = crr2;
  }
  Serial.print(s1rad); // X축 값이 표기됩니다.
  Serial.print("  "); 
  Serial.print(s2rad); // X축 값이 표기됩니다.
  Serial.print("  ");
  Serial.print(analogRead(A1)); // X축 값이 표기됩니다.
  Serial.print("  ");           //숫자가 헷깔리지않토록 중간에 공백칸을 두었습니다.
  Serial.print(analogRead(A0)); // X축 값이 표기 됩니다.
  Serial.print("  ");           //숫자가 헷깔리지않토록 중간에 공백칸을 두었습니다.
  Serial.println(digitalRead(8)); // Z축(스위치) 값이 표기됩니다.

  myservo1 .detach();
  delay(90);
}
