
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

//switch two way
int switchleft=2; //0 for down  and 1 for up

// declaring where the toggle switches are connected in Arduino
int toggleSwitch01_leftpin = 9;//0 when push
int toggleSwitch02_rightpin = 6;//0 when push

// declaring where the leftHandside joystick is connected
int joystickLeft_VRxPin = A0;
int joystickLeft_VRyPin = A1;

// declaring where the rightHandside joystick is connected
int joystickRight_VRxPin = A2;
int joystickRight_VRyPin = A3;

//potentiometer
int potentiometer_right   = A7;
int potentiometer_left   = A4;

int threewayswitch1=4;  //down is 4 and value is 0 and 5 is 1
int threewayswitch2=5;  ////up is 5 and value is 0 and 4 is 1
//in case of middel=both is 1

RF24 radio(7,8);
const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
  pinMode(switchleft, INPUT);
  pinMode(toggleSwitch01_leftpin, INPUT);
  pinMode(toggleSwitch02_rightpin, INPUT);
  pinMode(joystickLeft_VRxPin, INPUT);
  pinMode(joystickLeft_VRyPin, INPUT);
  pinMode(joystickRight_VRxPin, INPUT);
  pinMode(joystickRight_VRyPin, INPUT);
  pinMode(potentiometer_right, INPUT);
  pinMode(potentiometer_left, INPUT);
  pinMode(threewayswitch2, INPUT);
  pinMode(threewayswitch1, INPUT);
  digitalWrite(toggleSwitch01_leftpin,1);
  digitalWrite(toggleSwitch02_rightpin,1);
  digitalWrite(5,1);
  digitalWrite(4,1);
  Serial.begin(9600);
}

struct datapack{
  int toggleSwitch01left ;
  int toggleSwitch02right ;
  
  int joystickLeft_x ;
  int joystickLeft_y ;

  int joystickRight_x ;
  int joystickRight_y ;

  int potentiometer1_right; 
  int potentiometer2_left; 

  int  switch1;

  int switchthree1;
  int switchthree2;
};
datapack data;

void loop() {
  data.toggleSwitch01left = digitalRead(toggleSwitch01_leftpin);
  data.toggleSwitch02right = digitalRead(toggleSwitch02_rightpin);

  data.joystickLeft_x = map(analogRead(joystickLeft_VRxPin), 0, 1022,0,1023);
  data.joystickLeft_y = map(analogRead(joystickLeft_VRyPin), 0, 1022,0,1023);

  data.joystickRight_x = map(analogRead(joystickRight_VRxPin) , 0, 1022,0,1023); 
  data.joystickRight_y = map(analogRead(joystickRight_VRyPin) , 0, 1022,0,1023);

  data.switch1 = digitalRead(switchleft);

  data.switchthree2 = digitalRead(threewayswitch2);
  data.switchthree1 = digitalRead(threewayswitch1);

  data.potentiometer1_right = map(analogRead(potentiometer_right) , 0, 845,0,1023);
   data.potentiometer2_left = map(analogRead(potentiometer_left) , 0, 1023,0,1023);
  
  radio.write(&data, sizeof(data));
  Serial.print("toggleSwitch01left =");
  Serial.println(data.toggleSwitch01left);

    Serial.print("toggleSwitch02right =");
  Serial.println(data.toggleSwitch02right);

    Serial.print("joystickLeft_x  =");
  Serial.println(data.joystickLeft_x );

   Serial.print("joystickLeft_y  =");
  Serial.println(data.joystickLeft_y );

    Serial.print("joystickRight_x  =");
  Serial.println(data.joystickRight_x );

   Serial.print("joystickRight_y  =");
  Serial.println(data.joystickRight_y );

  Serial.print("potentiometer1_right  =");
  Serial.println(data.potentiometer1_right );

    Serial.print("potentiometer1_left  =");
  Serial.println(data.potentiometer2_left);

  Serial.print("switch1  =");
  Serial.println(data.switch1 );

    Serial.print("threewayswitch1  =");
  Serial.println(data.switchthree1 );
    Serial.print("threewayswitch2  =");
  Serial.println(data.switchthree2 );
   delay(50);
}
