
#define ENA 3
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 9

void setup() {
  Serial.begin(9600); // KHởi động serial ở mức baudrate(toc do truyen) 9600 - muc trung binh  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void tien(){
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        analogWrite(ENA,200);
        analogWrite(ENB,200);
}
void lui(){
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        analogWrite(ENA,100);
        analogWrite(ENB,100);
}

void ReTrai(){
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        analogWrite(ENA,80);
        analogWrite(ENB,200);
}

void RePhai(){
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        analogWrite(ENA,200);
        analogWrite(ENB,80);
    }
void TangToc(){
  int i;
  for(i=0;i<256;i++){
        analogWrite(ENA,i);
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        analogWrite(ENB,i);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
  }
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,LOW);
}

void DaoDauXe(){
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,HIGH);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
}

void loop() {
  tien();
  delay(3000);

  lui();
  delay(5000);
  
  ReTrai();
  delay(2000);
  
  RePhai();
  delay(4000);
  
  TangToc();
  delay (5000);

  DaoDauXe();
  delay(4000);
}
