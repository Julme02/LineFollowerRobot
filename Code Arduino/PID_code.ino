
#define SS1  A4 
#define SS2  A3
#define SS3  A2
#define SS4  A1
#define SS5  A0
#define CLP  11// Don't use pin 13 as an input..
#define NEAR 12 // Used as digital, probably 

/*byte  sensor[0]; 
byte  sensor[1];
byte  sensor[2];
byte  sensor[3];
byte  sensor[4];

byte  Bump;
int   Near; */

#define ENA 3
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 9

//Specify the links and initial tuning parameters
float Kp=0,Ki=0,Kd=0;
float error=0, P=0, I=0, D=0, PID_value=0;
float error_prev=0, prev_I=0;
int sensor[5]={0, 0, 0, 0, 0};
int initial_motor_speed=100;

void GetSensorData(void);
void CalculatePID(void);
void MotorControl(void);

void setup(){
     Serial.begin(9600); //Enable Serial Communications
     pinMode(ENA,OUTPUT); //PWM Pin 1
     pinMode(ENB,OUTPUT); //PWM Pin 2
     pinMode(IN1,OUTPUT); //Left Motor Pin 1
     pinMode(IN2,OUTPUT); //Left Motor Pin 2
     pinMode(IN3,OUTPUT); //Right Motor Pin 1
     pinMode(IN4,OUTPUT);  //Right Motor Pin 2

       pinMode(SS1, INPUT);
       pinMode(SS2, INPUT);
       pinMode(SS3, INPUT);
       pinMode(SS4, INPUT);
       pinMode(SS5, INPUT);
       pinMode(CLP, INPUT);
       pinMode(NEAR, INPUT);
}

void GetSensorData(){
      sensor[0]=digitalRead(SS1);
      sensor[1]=digitalRead(SS2);
      sensor[2]=digitalRead(SS3);
      sensor[3]=digitalRead(SS4);
      sensor[4]=digitalRead(SS5);
      /* Bump     = digitalRead(CLP_BUMP);   
      Near     = digitalRead(NEAR);*/
  
  if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==1))
        error=4;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==1)&&(sensor[4]==1))
        error=3;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==1)&&(sensor[4]==0))
        error=2;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[4]==1)&&(sensor[4]==0))
        error=1;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[4]==0)&&(sensor[4]==0))
        error=0;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[4]==0)&&(sensor[4]==0))
        error=-1;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
        error=-2;
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
        error=-3;
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
        error=-4;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[4]==0)&&(sensor[4]==0))
    if(error==-4) error=-5;
    else error=5;
}

void CalculatePID(){
    P = error;
    I = I + error;
    D = error - error_prev;
   
    prev_I = I;
    error_prev = error;
     
    PID_value = (Kp*P) + (Ki*I) + (Kd*D);
}

void MotorControl(){
    // Calculating the effective motor speed:
    int left_motor_speed = initial_motor_speed - PID_value;
    int right_motor_speed = initial_motor_speed + PID_value;
    
    // The motor speed should not exceed the max PWM value
    constrain(left_motor_speed,0,255);
    constrain(right_motor_speed,0,255);
 
    analogWrite(9,initial_motor_speed-PID_value);   //Left Motor Speed
    analogWrite(10,initial_motor_speed+PID_value);  //Right Motor Speed
    //following lines of code are to make the bot move forward
    /*The pin numbers and high, low values might be different
    depending on your connections */
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
}

 void loop(){
    GetSensorData();
    delay(1000);
    CalculatePID();
    MotorControl();
}
