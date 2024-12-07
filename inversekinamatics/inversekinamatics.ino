#include <USBHost_t36.h>

// Create a USBHost object
USBHost myusb;
USBHIDParser hid_parser(myusb);
JoystickController joystick(hid_parser);
BluetoothController bluet(myusb, true, "0000");

int motor1_pwm = 3;
int motor1_dir = 2;
int motor2_pwm = 7;
int motor2_dir = 6;
int motor3_pwm = 5;
int motor3_dir = 4;
int led=13;

float sqrt3 = 1.73;

void setMotor(int pwmPin, int dirPin, float speed) {
  if (speed >= 0) {
    digitalWrite(dirPin, HIGH);
    analogWrite(pwmPin, speed);
  } 
  else {
    digitalWrite(dirPin, LOW);
    analogWrite(pwmPin, -speed);
  }
}

void setup() {
  Serial.begin(96500);
  delay(1000);

  Serial.println("Initializing USB Host...");
  myusb.begin();

  Serial.println("Setting up motor pins...");
  pinMode(motor1_pwm, OUTPUT);
  pinMode(motor1_dir, OUTPUT);
  pinMode(motor2_pwm, OUTPUT);
  pinMode(motor2_dir, OUTPUT);
  pinMode(motor3_pwm, OUTPUT);
  pinMode(motor3_dir, OUTPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
}

void loop() {
  myusb.Task();

  if (joystick.available()) {
    Serial.println("Controller detected!");

    int lx = joystick.getAxis(0);
    int ly = joystick.getAxis(1);
    int rx = joystick.getAxis(2);


    float Vx = map(lx, 0, 255, 100, -100);
    float Vy = map(ly, 0, 255, 100, -100);
    float rotation = map(rx, 0, 255, 100, -100);

    //print values of the mapped values
    Serial.print("Mapped Values: Vx=");
    Serial.print(Vx);
    Serial.print(", Vy=");
    Serial.print(Vy);
    Serial.print(", rotation=");
    Serial.println(rotation);

    float W1 = Vx * (-0.67) +  Vy * 0 + 0.33 * rotation;
    float W2 = Vx * (0.67/2) + Vy * (-0.57) + 0.33 * rotation;
    float W3 = Vx * (0.67/2) + Vy * (0.57) + 0.33* rotation;

    setMotor(motor1_pwm, motor1_dir, W1);
    setMotor(motor2_pwm, motor2_dir, W2);
    setMotor(motor3_pwm, motor3_dir, W3);
    
    float s1=map(W1,0,100,0,255);
    float s2=map(W2,0,100,0,255);
    float s3=map(W3,0,100,0,255);


    //print the values of each motor
    Serial.println("speed of Motor 1 :");
    Serial.print(s1);
    Serial.println("speed of motor 2:");
    Serial.print(s2);
    Serial.println("Speed of motor 3:");
    Serial.print(s3);
  } 
  else {
    Serial.println("No controller detected...");
  }

 delay(100);
}
