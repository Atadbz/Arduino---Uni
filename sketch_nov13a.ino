int i = 1000;
int count = 0;

int pot;
void setup() {
  // put your setup code here, to run once:
  pinMode (2,OUTPUT);
  pinMode (8,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(A1,INPUT);
  Serial.begin(9600);
    
    

}

void loop() {
int i =1000;
while(i>100){
// put your main code here, to run repeatedly:
count +=1;
  digitalWrite(2,HIGH); //ON LED 2
  //delay(600);
  
  digitalWrite(8,HIGH); //OFF LED 1
  delay(i);
  digitalWrite(2,LOW); //OFF LED 2
  //delay(100);
  digitalWrite(8,LOW); //ON LED 1
  delay(i);  
i = i - 80;
}
  
if (count>10){
digitalWrite(12,HIGH);

}
}
