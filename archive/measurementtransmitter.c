#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverAddress[] = {0xC0, 0x49, 0xEF, 0xCE, 0x0D, 0xB8};
esp_now_peer_info_t peerInfo;

//Pinbelegung für die Potentiometer
const byte potentio1 = 36;
const byte potentio2 = 39;
const byte potentio3 = 34;
const byte potentio4 = 35;
const byte potentio5 = 33;

typedef struct message{
  int measurement1 = 0;
  int measurement2 = 0;
  int measurement3 = 0;
  int measurement4 = 0;
  int measurement5 = 0; 
} message;

message myMessage;

int messung(byte potentiometer){
    int wert = 0;
    int i = 0;
    for (; i < 150; i++){
      wert += analogRead(potentiometer);
    }
    return wert/i;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  esp_now_init();

  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  esp_now_add_peer(&peerInfo);
  
  pinMode(potentio1, INPUT);
  pinMode(potentio2, INPUT);
  pinMode(potentio3, INPUT);
  pinMode(potentio4, INPUT);
  pinMode(potentio5, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  myMessage.measurement1 = messung(potentio1);
  myMessage.measurement2 = messung(potentio2);
  myMessage.measurement3 = messung(potentio3);
  myMessage.measurement4 = messung(potentio4);
  myMessage.measurement5 = messung(potentio5);

  esp_now_send(receiverAddress, (uint8_t *)&myMessage, sizeof(myMessage));

  Serial.print(myMessage.measurement1);
  Serial.print("\t");
  Serial.print(myMessage.measurement2);
  Serial.print("\t");
  Serial.print(myMessage.measurement3);
  Serial.print("\t");
  Serial.print(myMessage.measurement4);
  Serial.print("\t");
  Serial.println(myMessage.measurement5);
 
}
