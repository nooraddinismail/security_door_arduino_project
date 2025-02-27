#include <Servo.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>


const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; 
byte colPins[COLS] = {5, 6, 7, 8};     
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


LiquidCrystal_I2C lcd(0x27, 16, 2);


Servo myServo;
const int servoPin = 10;


const String password = "1234";
String inputPassword = "";


SoftwareSerial mySerial(2, 3); 
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Enter Password:");
  
  myServo.attach(servoPin);
  myServo.write(165); 
  
  Serial.begin(9600);
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor OK!");
  } else {
    lcd.clear();
    lcd.print("Sensor Error!");
    while (1);
  }
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if (key == '#') { 
      lcd.clear();
      if (inputPassword == password) {
        lcd.print("Scan Fingerprint:");
        delay(1000);
        verifyFingerprint(); 
      } else {
        lcd.print("Wrong Password!");
        delay(2000);
        resetSystem();
      }
    } else if (key == '*') {
      inputPassword = "";
      resetSystem();
    } else {
      inputPassword += key;
      lcd.setCursor(inputPassword.length() - 1, 1);
      lcd.print("*");
    }
  }
}

void verifyFingerprint() {
  int fingerprintID = -1;
  lcd.clear();
  lcd.print("Place Finger...");

  while (fingerprintID == -1) {
    uint8_t p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        finger.image2Tz();
        p = finger.fingerFastSearch();
        if (p == FINGERPRINT_OK) {
          fingerprintID = finger.fingerID;
        }
        break;
      case FINGERPRINT_NOFINGER:
        delay(500);
        break;
      default:
        lcd.clear();
        lcd.print("Sensor Error!");
        delay(2000);
        resetSystem();
        return;
    }
  }

  
  if (fingerprintID > 0) {
    lcd.clear();
    lcd.print("Access Granted!");
    myServo.write(60); 
    delay(4000);
    myServo.write(165);  
  } else {
    lcd.clear();
    lcd.print("Access Denied!");
    delay(2000);
  }
  resetSystem();
}

void resetSystem() {
  inputPassword = "";
  lcd.clear();

  lcd.print("Enter Password:");
}