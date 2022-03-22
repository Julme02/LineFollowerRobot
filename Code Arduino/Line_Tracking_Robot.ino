//L298N
#define enA 3 // PWM động cơ trái
#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define enB 9 // PWM động cơ phải

//5 Sensor
#define sensor1 A4  // Cảm biến ngoài cùng bên trái
#define sensor2 A3
#define sensor3 A2
#define sensor4 A1
#define sensor5 A0  // Cảm biến ngoài cùng bên phải

int ss[5] = {0, 0, 0, 0, 0};

int error = 0, prev_error = 0;
int P = 0, I = 0, D = 0, prev_I = 0, PID_value = 0;
int Kp = 20, Ki = 0.5, Kd = 15;   // Hệ số PID lấy từ thực nghiệm

int base_speed_l = 100;   // Do động cơ bánh trái yếu hơn bánh phải
int base_speed_r = 86;   // nên phải set xung PWM cao hơn thì xe mới đi thẳng

void readsensor(){
  ss[0] = !digitalRead(sensor1);  // 1 - vạch đen; 0 - nền trắng
  ss[1] = !digitalRead(sensor2);
  ss[2] = !digitalRead(sensor3);
  ss[3] = !digitalRead(sensor4);
  ss[4] = !digitalRead(sensor5);
  
  if     (ss[0]==0 && ss[1]==0 && ss[2]==0 && ss[3]==0 && ss[4] == 1)      // Lệch nhiều nhất về bên trái
    error = 4;
  else if(ss[0]==0 && ss[1]==0 && ss[2]==0 && ss[3]==1 && ss[4] == 1)
    error = 3;
  else if(ss[0]==0 && ss[1]==0 && ss[2]==0 && ss[3]==1 && ss[4] == 0)
    error = 2;
  else if(ss[0]==0 && ss[1]==0 && ss[2]==1 && ss[3]==1 && ss[4] == 0)
    error = 1;
  else if(ss[0]==0 && ss[1]==0 && ss[2]==1 && ss[3]==0 && ss[4] == 0)
    error = 0;
  else if(ss[0]==0 && ss[1]==1 && ss[2]==1 && ss[3]==0 && ss[4] == 0)
    error = -1;
  else if(ss[0]==0 && ss[1]==1 && ss[2]==0 && ss[3]==0 && ss[4] == 0)
    error = -2;
  else if(ss[0]==1 && ss[1]==1 && ss[2]==0 && ss[3]==0 && ss[4] == 0)
    error = -3;
  else if(ss[0]==1 && ss[1]==0 && ss[2]==0 && ss[3]==0 && ss[4] == 0)     // Lệch nhiều nhất về bên phải 
    error = -4;
  else if(ss[0]==0 && ss[1]==0 && ss[2]==0 && ss[3]==0 && ss[4] == 0)     // Ra khỏi quỹ đạo đường đi
    error = 1000;
  else if(ss[0]==1 && ss[1]==1 && ss[2]==1 && ss[3]==1 && ss[4] == 1)     // Tất cả nhận vạch đen
    error = 2000;
  else if(ss[0]==1 && ss[1]==1 && ss[2]==1 && (ss[3]==0 || ss[3]==1) && ss[4] == 0)     // Đường rẽ trái
    error = 3000;
  else if(ss[0]==0 && (ss[1]==0 || ss[1]==1) && ss[2]==1 && ss[3]==1 && ss[4] == 1)     // Đường rẽ phải
    error = 4000;
  
 
}

void calculate_pid(){   // Tính toán giá trị PID
  P = error;
  I = I + error;
  D = error - prev_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);
    
  prev_error = error;
}

void Forward(){   // Tiến
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Reverse(){   // Lùi
  analogWrite(enA, 100);
  analogWrite(enB, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
}

void TurnLeft(){  // Rẽ trái
  analogWrite(enA, 100);
  analogWrite(enB, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void TurnRight(){  // Rẽ phải
  analogWrite(enA, 100);
  analogWrite(enB, 100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Stop(){      // Dừng
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void motor_control(){
  // Tính tốc độ phù hợp cho động cơ trái phải
  int left_motor_speed = base_speed_l + PID_value;
  int right_motor_speed = base_speed_r - PID_value;
    
  // Giới hạn giá trị PWM nằm trong khoảng từ 0 đến 255
  constrain(left_motor_speed, 0, 255);
  constrain(right_motor_speed, 0, 255);
 
  analogWrite(enA, left_motor_speed);   // Tốc độ động cơ trái
  analogWrite(enB, right_motor_speed);  // Tốc độ động cơ phải

  Forward(); 
}

void setup(){
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
}

void loop(){
  readsensor();
  
  if(error == 1000){           // Điều khiển lùi lại khi ra khỏi vạch đen đến khi tìm lại được vạch
    Reverse();  
  }
  
  else if(error == 2000){      // Điều khiển dừng lại khi cả 5 sensor nhận được vạch đen
    Stop();
  }
  
  else if(error == 3000) {     // Điều khiển rẽ trái
    do {
      readsensor();
      TurnLeft();
    } while (error != 4 && error != 3 && error != 2 && error != 1);  
    Stop();
  }
  
  else if(error == 4000) {     // Điều khiển rẽ phải
    do {
      readsensor();
      TurnRight();
    } while (error != -4 && error != -3 && error != -2 && error != -1);  
    Stop();  
  }
  
  else{                        // Điều khiển dò đường sử dụng pid
    calculate_pid();
    motor_control();
  }
}
