/*
 * This is a 6 channel nrf24l01 transmitter and receiver code.
 * There are 6 outputs in the receiver end, of which 2 outputs are for led(on/off) and the remaining 4 outputs are for 4 leds with brigtness control.
 * 
 * To know more refer the below links:
 *  https://youtu.be/Pd7rus79j_4
 *  https://dhirajkushwaha.com/elekkrypt
 *  
 */
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// declaring where the leds are connected in Arduino
int led01 = A0; 
int led02 = A1; 

int led03 = A2; 
int led04 = A3; 
int led05 = A4; 
int led06 = A5; 

RF24 radio(7,8);
const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);  
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
  while(radio.available()){
    radio.read(&data, sizeof(data));


    analogWrite(led02, data.joystickLeft_x);
    analogWrite(led01, data.joystickLeft_y);

    analogWrite(led03, data.joystickRight_x);
    analogWrite(led04, data.joystickRight_y);

     analogWrite(led03, data.joystickRight_x);
    analogWrite(led04, data.joystickRight_y);
    
  }
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
    Serial.print("threewayswitch1  =");
  Serial.println(data.switchthree2 );
  delay(1000);
}
