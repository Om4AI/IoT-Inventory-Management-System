int echo = D2;
int trig =D1;

void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
}

void generatetrig(){
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);   
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
}


void loop() {
  generatetrig();
  long duration = pulseIn(echo,HIGH);
  duration/=2;
  double dist = (duration * 0.033);
  Serial.print("Hello is: ");
  Serial.print(dist);
  Serial.println();
  delay(2000);
}
