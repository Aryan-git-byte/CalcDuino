#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <Keypad.h>
//#include <Adafruit_LiquidCrystal.h>
#define IR_RECEIVER_PIN 11

//defining lcd
//Adafruit_LiquidCrystal lcd(0);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//defining keypad dimension
const byte rows = 4;
const byte columns = 4;
long currentnumber;
long firstnumber;
long lastnumber;
int digit;
char operation;

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


  if(IrReceiver.decode()){
    input = decodeRemote(IrReceiver.decodedIRData.command);
    IrReceiver.resume();
  }

  char customKey = myKeypad.getKey();
  if (customKey){
    input = customKey;
  }

  if (input !='\0') {
    // lcd.print(input);
    Serial.println(input);
  }

  if (operation == '\0' && input >= '0' && input <= '9') {
    digit = input - '0';
    if (currentnumber <= 9999999) {
    currentnumber = currentnumber * 10 + digit;
    }
    lcd.setCursor(0, 0);
    lcd.print("       ");
    lcd.setCursor(0, 0);
    lcd.print(currentnumber);  
  }

  if (input == '-' || input == '+' || input == '*' || input == '/') {
    if (operation == '\0') {
    firstnumber = currentnumber;
    currentnumber = 0;
    }

    operation = input;
    lcd.setCursor(8, 0);
    lcd.print(input);
  }

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


     firstnumber = 0;
     lastnumber = 0; 
     currentnumber = 0;
     operation = '\0';
    }
    

    
  

  if (input == 'c') {
    currentnumber = 0;
    reset_lcd();  
  }

}

void reset_lcd(){
  lcd.clear();
  lcd.setCursor(0,0);
}

char decodeRemote(uint8_t ir_input){
  switch (ir_input) {
  case 48:
  return '1';
  case 17:
  return '2';
  case 18:
  return '3';
  case 20:
  return '4';
  case 21:
  return '5';
  case 22:
  return '6';
  case 24:
  return '7';
  case 25:
  return '8';
  case 26:
  return '9';
  case 12:
  return '0';
  case 0:
  return 'c';
  case 2:
  return '=';
  case 1:
  return '+';
  case 4:
  return '*';
  case 5:
  return '=';
  case 6:
  return '/';
  case 9:
  return '-';
  default:
  return '\0';
  }
}

