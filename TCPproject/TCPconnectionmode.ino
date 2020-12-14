#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID        "EH408_2.4"

#define PASSWORD    "123456789" 

#define HOST_NAME   "192.168.0.35" 

#define HOST_PORT   5012

#include <Servo.h>

Servo myservo1;
Servo myservo2;
int Servopin1 = 7;   //1번 서보모터
int Servopin2 = 7;   //2번 서보모터
// Pin 2 - > CLK
// Pin 3 - > DIO
int s1rad;
int s2rad;
int crr1;
int crr2;
int pr1;
int pr2;
int btnStat = 0;   //조이스틱이 눌렸을때의 값 저장
int s11 = 79;
int s12 = 94;
int s21 = 82;
int s22 = 67;
int j;
int count[4] = { 0,0,0,0 };
String InputString = "";
boolean StringComplete = 0;
boolean SetValidData = 0;

SoftwareSerial mySerial(10, 9); /* RX:D10, TX:D9 */
ESP8266 wifi(mySerial);


void printUsage()
{
    uint8_t buf[] = "Usage\n1 : Turn On LED\n2 : Turn Off LED\nS : LED status\n\n";
    wifi.send(buf, strlen(buf));
}

bool isConnected = false;

void setup(void)
{
    Serial.begin(9600);
    Serial.print("setup begin\r\n");

    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());
    myservo1.attach(Servopin1);
     myservo2.attach(Servopin2);
    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    }
    else {
        Serial.print("to station + softap err\r\n");
    }

    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP:");
        Serial.println(wifi.getLocalIP().c_str());
    }
    else {
        Serial.print("Join AP failure\r\n");
    }

    if (wifi.disableMUX()) {
        Serial.print("single ok\r\n");
    }
    else {
        Serial.print("single err\r\n");
    }

    Serial.print("setup end\r\n");
    Serial.begin(9600); //시리얼 통신을 하기위한 통신속도설정
  pinMode(Servopin1, OUTPUT);
  pinMode(Servopin2, OUTPUT);
  myservo1.attach(7);
  myservo1.write(0);
 
}

void serialEvent() {
    char InChar;
    SetValidData = 1;
    while (Serial.available()) {
        InChar = Serial.read();

        if (SetValidData) {
            if (InChar == 0x0a) {
                StringComplete = 1;
                SetValidData = 0;
                return;
            }
            if (InputString.length() < 5) {
                InputString += InChar;
                return;
            }
            else {
                InputString = "";
                SetValidData = 0;
            }
        }
    }
}

void loop(void)
{
    if (isConnected == false) {

        while (1) {
            if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
                Serial.print("create tcp ok\r\n");
                isConnected = true;
                printUsage();
                break;
            }
            else {
                Serial.print("create tcp err\r\n");
            }
        }
    }

    


    uint8_t buffer[128] = { 0 };

    uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
    if (len > 0) {
        Serial.print("Received:[");
        for (uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");


        char command = buffer[0];
        int ledStatus = digitalRead(LED_BUILTIN);


        switch (command)
        {

        case 'w':
            if (count[0] == 0)
            { 
               myservo1.detach();
               myservo1.attach(7);
               for (j=0; j<90; j+=10)
               {
                myservo1.write(j);
                delay(90);
               }
               
                
                 myservo1.detach();
                sprintf(buffer, "w mode\n");
                wifi.send(buffer, strlen(buffer));
                count[0] = 1;
                count[1] = 0;
                count[2] = 0;
                count[3] = 0;
            }
            break;
        case 'A':
            
            if (count[1] == 0)
            {
              myservo1.detach();
               myservo1.attach(7);
              for (j=90; j>=0; j-=10)
               {
                myservo1.write(j);
                delay(90);
               }
               
                myservo1.detach();
                sprintf(buffer, "A mode\n");
                wifi.send(buffer, strlen(buffer));
                count[1] = 1;
                count[0] = 0;
                count[2] = 0;
                count[3] = 0;
            }
            break;
        case 'S':
            myservo1.attach(Servopin1);
            myservo1.write(75);
            delay(90);
            myservo2.attach(Servopin2);
            myservo2.write(92);
            delay(90);
            Serial.print(analogRead(A1)); // X축 값이 표기됩니다.
            Serial.print("  ");           //숫자가 헷깔리지않토록 중간에 공백칸을 두었습니다.
            Serial.print(analogRead(A0)); // X축 값이 표기 됩니다.
            Serial.print("  ");           //숫자가 헷깔리지않토록 중간에 공백칸을 두었습니다.
            Serial.println(digitalRead(8)); // Z축(스위치) 값이 표기됩니다.

            myservo1.detach();
            delay(90);
            if (count[2] == 0)
            {
                sprintf(buffer, "S mode\n");
                wifi.send(buffer, strlen(buffer));
                count[2] = 1;
                count[1] = 0;
                count[0] = 0;
                count[3] = 0;
            }
            break;
        case 'D':
            myservo1.attach(Servopin1);
            myservo1.write(80);
            delay(90);
            myservo2.attach(Servopin2);
            myservo2.write(86);
            delay(90);
            Serial.print(analogRead(A1)); // X축 값이 표기됩니다.
            Serial.print("  ");           //숫자가 헷깔리지않토록 중간에 공백칸을 두었습니다.
            Serial.print(analogRead(A0)); // X축 값이 표기 됩니다.
            Serial.print("  ");           //숫자가 헷깔리지않토록 중간에 공백칸을 두었습니다.
            Serial.println(digitalRead(8)); // Z축(스위치) 값이 표기됩니다.

            myservo1.detach();
            delay(90);
            if (count[3] == 0)
            {
                sprintf(buffer, "D mode\n");
                wifi.send(buffer, strlen(buffer));
                count[0] = 0;
                count[1] = 0;
                count[2] = 0;
                count[3] = 1;
            }
            break;

        }
    }
}
