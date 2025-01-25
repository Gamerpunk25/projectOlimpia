#include <Servo.h>
#include <WiFi.h>
#include <esp_now.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
int angle1 = 0;
int angle2 = 0;
int angle3 = 0;
int angle4 = 0;
int angle5 = 0;

typedef struct message{
  int measurement1 = 0;
  int measurement2 = 0;
  int measurement3 = 0;
  int measurement4 = 0;
  int measurement5 = 0; 
} message;

message myMessage;

void setup() {
  // put your setup code here, to run once:

pinMode(33, OUTPUT);
pinMode(32, OUTPUT);
pinMode(27, OUTPUT);
pinMode(26, OUTPUT);
pinMode(25, OUTPUT);

servo1.attach(33);
servo2.attach(32);
servo3.attach(27);
servo4.attach(26);
servo5.attach(25);

Serial.begin(115200);
WiFi.mode(WIFI_STA);
esp_now_init();

esp_now_register_recv_cb(messageReceived);

}

void messageReceived(const uint8_t* macAddr, const uint8_t* incomingData, int len){
  memcpy(&myMessage, incomingData, sizeof(myMessage));

  angle1 = map(myMessage.measurement1, 0, 4095, 180, 0);
  servo1.write(angle1);

  angle2 = map(myMessage.measurement2, 0, 4095, 180, 0);
  servo2.write(angle2);

  angle3 = map(myMessage.measurement3, 0, 4095, 0, 180);
  servo3.write(angle3);

  angle4 = map(myMessage.measurement4, 0, 4095, 180, 0);
  servo4.write(angle4);

  angle5 = map(myMessage.measurement5, 0, 4095, 180, 0);
  servo5.write(angle5);

  Serial.print(angle1);
  Serial.print("\t");
  Serial.print(angle2);
  Serial.print("\t");
  Serial.print(angle3);
  Serial.print("\t");
  Serial.print(angle4);
  Serial.print("\t");
  Serial.println(angle5);

}

void loop() {

  // put your main code here, to run repeatedly:
}
