#include<ThingSpeak.h>
#include<ESP8266WiFi.h>

//Declare the I/O pins for Input & Output
int trig1 = D1;
int echo1 = D2;
int trig2 = D6;
int echo2 = D7;

//Wifi connection code
char *ssid = "wifiusername";
char *pass = "wifi password";

unsigned long channelID= 1363593 ;
 
const char *writeAPI = "writeapi key from channel";
const char *readAPI = "readapi key from channel";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
}

void loop() {
  getConnection();
  generatetrig1();
  long duration1 = pulseIn(echo1, HIGH);
  float dist1 = (duration1 * 0.033)/2;
  ThingSpeak.writeField(channelID, 1, dist1, writeAPI);
  //  Print the distance to serial monitor
  Serial.print("\nDistance (Sensor 1): ");
  Serial.print(dist1);

//  Second sensor
  generatetrig2();
  long duration2 = pulseIn(echo2, HIGH);
  float dist2 = (duration2 * 0.033)/2;
  ThingSpeak.writeField(channelID, 2, dist2, writeAPI);
  delay(4000);
  //  Print the distance to serial monitor
  Serial.print("\nDistance (Sensor 2): ");
  Serial.print(dist2);
}

void generatetrig1(){
//  First sensor
  digitalWrite(trig1,LOW);
  delayMicroseconds(2);
  digitalWrite(trig1,HIGH);   
  delayMicroseconds(10);
  digitalWrite(trig1,LOW);
}

void generatetrig2(){
//  Second Sensor
  digitalWrite(trig2,LOW);
  delayMicroseconds(2);
  digitalWrite(trig2,HIGH);   
  delayMicroseconds(10);
  digitalWrite(trig2,LOW);
}

void getConnection(){
  if (WiFi.status()!= WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status()!= WL_CONNECTED){
      WiFi.begin(ssid, pass);
      Serial.println(ssid);
      Serial.print("....");
      delay(5000);
    }
    Serial.println("Connected to...");
    Serial.print(ssid);
  }
}
