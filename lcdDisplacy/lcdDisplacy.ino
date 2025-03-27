#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); // Adjust to (0x27,20,4) for 20x4 LCD
  int A0pin = A0;
  int A1pin = A1;
  int A2pin = A2;
  int A3pin = A3;
  int val0 = 0;
  int val1 = 0;
  int val2 = 0;
  int val3 = 0;
  int shouldReset = 0;
  int positivePin1 = 2;
  int negativePin1 = 3;
  int speedPin1 = 9;

void setup() {
  // Initiate the LCD and turn on the backlight
  lcd.init();          // Initiate the LCD module
  lcd.backlight();     // Turn on the backlight
  
  //lcd.setCursor(0, 0);          // Set the cursor on the first column and first row.
  //lcd.print("Good Hits!..........rahhh");    // Print the string "Hello World!"
  
  //lcd.setCursor(0, 1);          //Set cursor to 2nd column and 2nd row (counting starts at 0)
 // lcd.print("your mom");

//  lcd.setCursor(9, 1);
//  lcd.print("slawg");
  
  pinMode(positivePin1, OUTPUT);
  pinMode(negativePin1, OUTPUT);
  pinMode(speedPin1, OUTPUT);
}

void loop() {

  // Print 'Hello World!' on the first line of the LCD
  //lcd.setCursor(0 ,1);
  //lcd.print(actualFunction(A0pin, val0, 70));         //analog pin to read from, resistance value red from sensor, voltage tolerance for return type
  int Hit1 = actualFunction(A0pin, val0, 70);
  //lcd.setCursor(8 ,1);
  //lcd.print(actualFunction(A1pin, val1, 60));
  int Block1 = actualFunction(A1pin, val1, 55);
  int Hit2 = actualFunction(A2pin, val2, 65);
  int Block2 = actualFunction(A3pin, val3, 65);

  hitBlockLogic("2", Hit1, Block2, 0);          //what player will be hit, what players hit to use, what players block to use, what place to print the feedback
  hitBlockLogic("1", Hit2, Block1, 8);

  if (Hit1 == 1){
    analogWrite(speedPin1, 0);        //the longer you run the more scuffed it is
    digitalWrite(positivePin1, HIGH);
    digitalWrite(negativePin1, LOW);
  }
  else{
    analogWrite(speedPin1, 0);
    digitalWrite(positivePin1, LOW);
    digitalWrite(negativePin1, HIGH);
  } 
  //val0 = analogRead(A0pin);
  //lcd.setCursor(0,1);
  //lcd.print(val0);
  //scrollDisplay();

  //if (checkClear(val0) == 0){
    //val2 = analogRead(A3pin);
    //lcd.setCursor(0,1);
    //lcd.print(val2);
  //}
  
}

void scrollDisplay(){
  delay(2000);
  for (int i = 0; i < 40; i++){             //40 is the number the lcd has to scroll before it reaches the start again
    delay(500);               //create a method to call in loop so it doesn't delay loop
    lcd.scrollDisplayLeft();
  }
}

int checkClear(int val){
  int shouldReset;
  if (val < 80){
    shouldReset = 1;
  }
  else{
    shouldReset = 0;
  }
  return shouldReset;
}

int actualFunction(int AnalogPin, int val, int tolerance){
  /* val = analogRead(AnalogPin);
  lcd.setCursor(slotArea, 1);
  lcd.print(val);

  if (checkClear(val) == 0){
    lcd.setCursor(slotArea,1);
    lcd.print("    ");
  } */
  int output = 0;
  val = analogRead (AnalogPin);
  if (val >= tolerance){
    output = 1;
    return output;
  }
  else {
    output = 0;
    return output;
  }
}

void hitBlockLogic (char player, int hit, int block, int print){
  if (hit == 1 && block == 0){
    lcd.setCursor(print,1);
    lcd.print("YOUCH");
  }
  else if (hit == 1 && block == 1){
    lcd.setCursor(print,1);
    lcd.print("block");
  }
  else{
    lcd.setCursor(print,1);
    lcd.print("chill");
  }
}