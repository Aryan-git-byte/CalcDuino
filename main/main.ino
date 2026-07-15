// include libs
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <Keypad.h>
//#include <Adafruit_LiquidCrystal.h>

// defining ir pin
#define IR_RECEIVER_PIN 11

//defining lcd
//Adafruit_LiquidCrystal lcd(0);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//defining keypad dimension
const byte rows = 4;
const byte columns = 4;

// defining variables
long currentnumber;
long firstnumber;
long lastnumber;
int digit;
char operation;
bool numberEntered = false;

//defining buttons
char keys[rows][columns] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'c', '0', '=', '/'}
};

//defining buttons to digital pins
byte rowPins[rows] = {2,3,4,5};
byte colPins[columns] = {6,7,8,9};
// declaring the keypad
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, columns);

void setup()
{
  Serial.begin(9600);
  // lcd.begin(16, 2);
  // lcd.setCursor(0,0);
  // lcd.print("Calculator init");
  // lcd.setCursor(0,1);
  // lcd.print("Welcome...");
  
  // delay(2000);
  // lcd.clear();
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  // lcd.print("Hellow World");
  lcd.print("Calculator init");
  delay(1500);
  lcd.clear();
  pinMode(13, OUTPUT);
  IrReceiver.begin(IR_RECEIVER_PIN);
}

/**
0-9: digits
A - +
B - -
C - *
D - /
* - clear
# - =
**/

void loop()
{
  char input = '\0';

// ir remote input
  if(IrReceiver.decode()){
    input = decodeRemote(IrReceiver.decodedIRData.command);
    IrReceiver.resume();
  }
// keypad input
  char customKey = myKeypad.getKey();
  if (customKey){
    input = customKey;
  }
// serial printing for debugging
  if (input !='\0') {
    // lcd.print(input);
    Serial.println(input);
  }
// first number input
  if (operation == '\0' && input >= '0' && input <= '9') {
    digit = input - '0';
    if (currentnumber <= 9999999) {
    currentnumber = currentnumber * 10 + digit;
    }
    numberEntered = true;
    lcd.setCursor(0, 0);
    lcd.print("       ");
    lcd.setCursor(0, 0);
    lcd.print(currentnumber); 
  }
// operator input
  if ((input == '-' || input == '+' || input == '*' || input == '/' ) && numberEntered) {
    if (operation == '\0') {
    firstnumber = currentnumber;
    currentnumber = 0;
    }

    operation = input;
    lcd.setCursor(8, 0);
    lcd.print(input);
  }
// second number input
  if (operation != '\0'&& input >= '0' && input <= '9') {
    digit = input - '0';
    if (currentnumber <= 9999999) {
    currentnumber = currentnumber * 10 + digit;
    }
    lcd.setCursor(9, 0);
    lcd.print("       ");
    lcd.setCursor(9, 0);
    lcd.print(currentnumber); 
  }
// performing the operation
  if (input == '=') {
    lastnumber = currentnumber;
    switch (operation) {
      case '+':
      currentnumber = firstnumber+lastnumber;
      break;
      case '-':
      currentnumber = firstnumber-lastnumber;
      break;
      case '*':
      currentnumber = firstnumber*lastnumber;
      break;
      // division case with error handling for division by zero
      case '/':
        if (lastnumber != 0) {
          currentnumber = firstnumber/lastnumber;
        }
        else{
          reset_lcd();
          lcd.print("ERROR");
          return;
        }
      break;
      }
     reset_lcd();
     lcd.print(currentnumber);

// ressetting all the variables for next operation
     firstnumber = 0;
     lastnumber = 0; 
     currentnumber = 0;
     operation = '\0';
// beep
     digitalWrite(13, HIGH);
     delay(500);
     digitalWrite(13, LOW);
    }
    
// clear
  if (input == 'c') {
    currentnumber = 0;
    reset_lcd();  
  }

}

void reset_lcd(){
  lcd.clear();
  lcd.setCursor(0,0);
}
// function to decode the ir remote input
char decodeRemote(uint8_t ir_input){
  switch (ir_input) {
  case 48:
  return '1';
  case 24:
  return '2';
  case 122:
  return '3';
  case 16:
  return '4';
  case 56:
  return '5';
  case 90:
  return '6';
  case 66:
  return '7';
  case 74:
  return '8';
  case 82:
  return '9';
  case 104:
  return '0';
  case 162:
  return 'c';
  case 226:
  return '=';
  case 2:
  return '+';
  case 224:
  return '*';
  case 168:
  return '=';
  case 144:
  return '/';
  case 152:
  return '-';
  default:
  return '\0';
  }
}

