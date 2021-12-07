#include <Servo.h> //includes the servo library
#include <Wire.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo myservo;

#define ir_enter 1
#define ir_back  6

#define ir_car1 7
#define ir_car2 8
#define ir_car3 9
#define ir_car4 10


int S1 = 0, S2 = 0, S3 = 0, S4 = 0;
int flag1 = 0, flag2 = 0;
int slot = 4;

void setup() {
  Serial.begin(9600);

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);


  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);

  myservo.attach(3);
  myservo.write(90);

  lcd.begin(20, 4);
  lcd.setCursor (0, 1);
  lcd.print("    Car  parking  ");
  lcd.setCursor (0, 2);
  lcd.print("       System     ");
  delay (2000);
  lcd.clear();

  Read_Sensor();

  int total = S1 + S2 + S3 + S4;
  slot = slot - total;
}

void loop() {

  Read_Sensor();

  lcd.setCursor (0, 0);
  lcd.print("   Have Slot: ");
  lcd.print(slot);
  lcd.print("    ");

  lcd.setCursor (0, 1);
  if (S1 == 1) {
    lcd.print("S1:Fill ");
  }
  else {
    lcd.print("S1:Empty");
  }

  lcd.setCursor (10, 1);
  if (S2 == 1) {
    lcd.print("S2:Fill ");
  }
  else {
    lcd.print("S2:Empty");
  }

  lcd.setCursor (0, 2);
  if (S3 == 1) {
    lcd.print("S3:Fill ");
  }
  else {
    lcd.print("S3:Empty");
  }

  lcd.setCursor (10, 2);
  if (S4 == 1) {
    lcd.print("S4:Fill ");
  }
  else {
    lcd.print("S4:Empty");
  }


  if (digitalRead (ir_enter) == 0 && flag1 == 0) {
    if (slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(180);
        slot = slot - 1;
      }
    } else {
      lcd.setCursor (0, 0);
      lcd.print(" Sorry Parking Full ");
      delay(1500);
    }
  }

  if (digitalRead (ir_back) == 0 && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(180);
      slot = slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay (1000);
    myservo.write(90);
    flag1 = 0, flag2 = 0;
  }

  delay(1);
}

void Read_Sensor() {s
  S1 = 0, S2 = 0, S3 = 0, S4 = 0;

  if (digitalRead(ir_car1) == 0) {
    S1 = 1;
  }
  if (digitalRead(ir_car2) == 0) {
    S2 = 1;
  }
  if (digitalRead(ir_car3) == 0) {
    S3 = 1;
  }
  if (digitalRead(ir_car4) == 0) {
    S4 = 1;
  }

}
