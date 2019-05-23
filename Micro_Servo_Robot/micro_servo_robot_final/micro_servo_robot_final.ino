#include<Servo.h>
Servo servo0, servo1, servo2, servo3;
int analogout[4] = {0, 0, 0, 0};
const int pin_button = 12;
int pin_button_state = 0;
int last_pin_button_state = 0;
int stor0[200];
int stor1[200];
int stor2[200];
int stor3[200];
int recording;
int sensorVal[4];
int storage_loc;

void setup() {

  servo0.attach(11);
  servo1.attach(10);
  servo2.attach(9);
  servo3.attach(6);
  pinMode(pin_button, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

}

void loop() {
  button();
  mapval();
  writeval();
  record();
  play();

}


void button() {
  pin_button_state = digitalRead(pin_button);
  if (pin_button_state != last_pin_button_state) {
    if (pin_button_state == HIGH) {
      delay(100);
      recording++;
    }
    delay(50);
  }
}
void mapval() {
  if (recording == 0) {
    sensorVal[0] = analogRead(A0);
    sensorVal[1] = analogRead(A1);
    sensorVal[2] = analogRead(A2);
    sensorVal[3] = analogRead(A3);
    analogout[0] = map(sensorVal[0], 0, 1023, 0, 180);
    analogout[1] = map(sensorVal[1], 0, 1023, 0, 180);
    analogout[2] = map(sensorVal[2], 0, 1023, 0, 180);
    analogout[3] = map(sensorVal[3], 0, 1023, 0, 180);
  }
}

void writeval() {
  servo0.write(analogout[0]);
  servo1.write(analogout[1]);
  servo2.write(analogout[2]);
  servo3.write(analogout[3]);
}


void record() {
  if (recording == 1) {
    sensorVal[0] = analogRead(A0);
    sensorVal[1] = analogRead(A1);
    sensorVal[2] = analogRead(A2);
    sensorVal[3] = analogRead(A3);

    analogout[0] = map(sensorVal[0], 0, 1023, 0, 180);
    analogout[1] = map(sensorVal[1], 0, 1023, 0, 180);
    analogout[2] = map(sensorVal[2], 0, 1023, 0, 180);
    analogout[3] = map(sensorVal[3], 0, 1023, 0, 180);
    writeval();
    if (storage_loc < 180) {
      stor0[storage_loc] = analogout[0];
      stor1[storage_loc] = analogout[1];
      stor2[storage_loc] = analogout[2];
      stor3[storage_loc] = analogout[3];
      delay(50);
      storage_loc++;
    }
  }
}
void play() {
  if (recording > 1) {
    while (true) {
      for (int i = 0; i < storage_loc; i++) {
        servo0.write(stor0[i]);
        servo1.write(stor1[i]); 
        servo2.write(stor2[i]);
        servo3.write(stor3[i]);
        delay(50);
      }
    }
  }
}

