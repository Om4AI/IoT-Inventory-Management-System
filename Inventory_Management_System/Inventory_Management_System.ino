#include <ESP8266WiFi.h>
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

//------------------------

//Wifi connection code
char *ssid = "USERNAME";
char *pass = "PASSWORD";

unsigned long channelID= (INTEGER CHANNEL ID) ;
 
const char *writeAPI = "WRITEAPI KEY";
const char *readAPI = "READAPI KEY";

WiFiClient client;
int trig1 = D1;
int echo1 = D2;
int trig2 = D6;
int echo2 = D7;

int Stack1 = 0;
int Stack2 = 0;

//------------------------

//Actual code
void setup() {
  Serial.begin(9600); //Baud rate
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
  stack1();
  generatetrig2(); 
  stack2();
  delay(2000);
}


//------------------------
//Connect to WiFi
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
//------------------------

//Generate ultrasonic signals
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
//------------------------


//Functions for getting the number of items in inventory
void stack1(){
  int duration, distance;
  duration = pulseIn(echo1, HIGH);
  distance = (duration * 0.033)/2;

//  Check items: Stack 1
  if (distance <23) {  // Change the number for long or short distances.
    Stack1=5;
    Serial.println("\n");
    Serial.print(Stack1); 
    Serial.print("  Stack1");
    }
    if (distance >23 && distance <35) {  // Change the number for long or short distances.
    Stack1=4;
    Serial.println("\n");
    Serial.print(Stack1);
    Serial.print("  Stack1"); 
    }
    if (distance >35 && distance <47) {  // Change the number for long or short distances.
    Stack1=3;
    Serial.println("\n");
    Serial.print(Stack1);
    Serial.print("  Stack1"); 
    }
    if (distance >47 && distance <60) {  // Change the number for long or short distances.
    Stack1=2;
    Serial.println("\n");
    Serial.print(Stack1);
    Serial.print("  Stack1"); 
    }
    if (distance >60 && distance <70) {  // Change the number for long or short distances.
    Stack1=1;
    Serial.println("\n");
    Serial.print(Stack1); 
    Serial.print("  Stack1");
    }
    if(distance >70){
    Stack1= 0; 
    Serial.println("\n");    
    Serial.print(Stack1);
    Serial.print("  Stack1");
    }

//    Write to cloud
    ThingSpeak.writeField(channelID, 1,Stack1, writeAPI);
}
//------------------------


//Stack 2
void stack2(){
  int duration, distance;
  duration = pulseIn(echo2, HIGH);
  distance = (duration * 0.033)/2;

//  Check items
  if (distance <23) {  // Change the number for long or short distances.
    Stack2=5;
    Serial.println("\n");
    Serial.print(Stack2); 
    Serial.print("  Stack2");
    }
    if (distance >23 && distance <35) {  // Change the number for long or short distances.
    Stack2=4;
    Serial.println("\n");
    Serial.print(Stack2);
    Serial.print("  Stack2"); 
    }
    if (distance >35 && distance <47) {  // Change the number for long or short distances.
    Stack2=3;
    Serial.println("\n");
    Serial.print(Stack2);
    Serial.print("  Stack2"); 
    }
    if (distance >47 && distance <60) {  // Change the number for long or short distances.
    Stack2=2;
    Serial.println("\n");
    Serial.print(Stack2);
    Serial.print("  Stack2"); 
    }
    if (distance >60 && distance <70) {  // Change the number for long or short distances.
    Stack2=1;
    Serial.println("\n");
    Serial.print(Stack2); 
    Serial.print("  Stack2");
    }
    if(distance >70){
    Stack2= 0; 
    Serial.println("\n");    
    Serial.print(Stack2);
    Serial.print("  Stack2");
    }

    ThingSpeak.writeField(channelID, 2,Stack2, writeAPI);
}

//------------------------
