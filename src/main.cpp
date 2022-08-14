#include <Arduino.h>
#include <Keyboard.h>
#include <KeyboardLayout.h>

const byte rows = 4; //four rows
const byte cols = 12; //three columns
const int ascii_shift = 32;

//char keys[rows][cols] = {
 //   {'esc', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'del'},
   // {'tab', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'enter'},
   // {'shift', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '''},
    //{'ctrl', 'win', 'alt', 'func', '5', '6', '7', '8', 'left', 'down', 'up', 'right'}
    //};

int keys_no_shift[rows][cols] = { //ascii values
    {177, 113, 119, 101, 114, 116, 121, 117, 105, 111, 112, 178},
    {179, 97, 115, 100, 102, 103, 104, 106, 107, 108, 59, 39},
    {129, 122, 120, 99, 118, 98, 110, 109, 44, 46, 47, 176},
    {128, 135, 130, 0, 0, 0, 32, 0, 216, 217, 218, 215}
    };

int keys_funct[rows][cols] = { //ascii values
    {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 95, 61},
    {179, 97, 115, 100, 102, 103, 104, 106, 107, 108, 59, 39},
    {129, 122, 120, 99, 118, 98, 110, 109, 44, 46, 47, 176},
    {128, 135, 130, 0, 0, 0, 32, 0, 216, 217, 218, 215}
    };

boolean status[rows][cols] ={
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}
    }; 

byte rowPins[rows] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[cols] = {6, 7, 9, 8, 10, 16, 14, 15, 18, 19, 20, 21}; //connect to the column pinouts of the keypad, 8 and 9 are flipped when soldering

//byte rowPins[rows] = {21, 20, 19, 18}; //connect to the row pinouts of the keypad
//byte colPins[cols] = {15, 14, 16, 10, 9, 8, 7, 6, 5, 4, 3, 2}; //connect to the column pinouts of the keypad

void setCurrentKeyState(boolean col_state[], int row ){
  boolean function_status = 1;
  if (status[3][3] == 0){
    function_status = 0;
  }
  for (int col = 0; col < 12; col++){
    if(function_status == 0){
      if(col_state[col] == 0 && status[row][col] == 1){
        Serial.println("in funct loop");
        Keyboard.press(keys_funct[row][col]);
        status[row][col] = col_state[col];
      }
      else if (col_state[col] == 1 && status[row][col] == 0){
        Keyboard.release(keys_funct[row][col]);
        status[row][col] = col_state[col];
      }
    }
    else{
    if(col_state[col] == 0 && status[row][col] == 1){
      Keyboard.press(keys_no_shift[row][col]);
      status[row][col] = col_state[col];
    }
    else if (col_state[col] == 1 && status[row][col] == 0){
      Keyboard.release(keys_no_shift[row][col]);
      status[row][col] = col_state[col];
    }
    }
  }
}

void setup() {
  Serial.begin(115200);
  Keyboard.begin();

  pinMode(rowPins[0], OUTPUT);
  pinMode(rowPins[1], OUTPUT);
  pinMode(rowPins[2], OUTPUT);
  pinMode(rowPins[3], OUTPUT);

  pinMode(colPins[0], INPUT_PULLUP);
  pinMode(colPins[1], INPUT_PULLUP);
  pinMode(colPins[2], INPUT_PULLUP);
  pinMode(colPins[3], INPUT_PULLUP);
  pinMode(colPins[4], INPUT_PULLUP);
  pinMode(colPins[5], INPUT_PULLUP);
  pinMode(colPins[6], INPUT_PULLUP);
  pinMode(colPins[7], INPUT_PULLUP);
  pinMode(colPins[8], INPUT_PULLUP);
  pinMode(colPins[9], INPUT_PULLUP);
  pinMode(colPins[10], INPUT_PULLUP);
  pinMode(colPins[11], INPUT_PULLUP);
  pinMode(colPins[12], INPUT_PULLUP);
  
}

void loop() {
  digitalWrite(rowPins[0], HIGH);
  digitalWrite(rowPins[1], HIGH);
  digitalWrite(rowPins[2], HIGH);
  digitalWrite(rowPins[3], HIGH);

  for (int row = 0; row < 4; row++){
    digitalWrite(rowPins[row], LOW);
    boolean col_states[12] = {digitalRead(colPins[0]), 
                              digitalRead(colPins[1]), 
                              digitalRead(colPins[2]), 
                              digitalRead(colPins[3]),
                              digitalRead(colPins[4]),
                              digitalRead(colPins[5]),
                              digitalRead(colPins[6]),
                              digitalRead(colPins[7]),
                              digitalRead(colPins[8]),
                              digitalRead(colPins[9]),
                              digitalRead(colPins[10]),
                              digitalRead(colPins[11])
                              };
    setCurrentKeyState(col_states, row);
    digitalWrite(rowPins[row], HIGH);
    delay(1);
  }
}


