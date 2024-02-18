#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include <arduino-timer.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// declaring variables 
// String text[4];
// String color[4];
int ran; 
// long duration;
bool buttonPressed = false;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long pressedMillis = 0;
int interval = 10; 
int currentbutton = 0; 
int previousbutton = 1; 
int buttoncount = 0; 
bool is_win = false; 
bool firstpress = true;
// auto timer = timer_create_default();

// define pin number for button 
const int buttonPin = 0; //change the pinnumber later 
int redPin = 5; 
int greenPin = 6; 
int bluePin = 7; 


int buttonstate = 0;


void setup() {
  Serial.begin(115200);

  // button setup 
  pinMode(buttonPin, INPUT);

  // text setup 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();


  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.println("BUTTON...");
  display.display(); 
  // display.println("DETONATE"); 
  // display.display(); 

  // color setup 
  pinMode(redPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
  pinMode(greenPin, OUTPUT);
  // setColor(255,0,0);
  // setColor(255, 255, 0);
  // setColor(0,0,255);
  
  // color[0] = getColor(255,0,0); //RED
  // color[1] = getColor(255, 255, 0); // yellow
  // color[2] = getColor(0,0,255); // blue
  // color[3] = getColor(0,0,0); // white 
  
  //randomize text and colour 
  randomSeed(analogRead(0));
  // ran = random(4);
  ran =2;
}

void loop() {
  currentMillis = millis();
  // buttonstate = digitalRead(buttonPin);
  // Serial.println(buttonstate);
  Serial.println(buttoncount);
  // loss(); 
  button_game(); 
}

void button_game() {
  if (currentMillis - previousMillis >= interval && !is_win) {
    // save the last time you blinked the LED
    previousMillis = currentMillis; 
    // text[ran]; 
    // display.clearDisplay();
    // color[ran]; 
    if (ran == 0) {
      display.println("PRESS");
      display.display(); 
      setColor(255,0,0);
      currentbutton = digitalRead(buttonPin);
      if(firstpress){
        pressedMillis = currentMillis; 
        firstpress = false;
      }
      if (currentbutton == 0) {
        buttonPressed = true; 
        win();
      }
       else if (currentMillis - pressedMillis > 5000){
        buttonPressed = false;
        loss();
       }
    } 
    else if(ran ==1) {
      display.println("HOLD");
      display.display(); 
      setColor(255, 255, 0);
      currentbutton = digitalRead(buttonPin);
      if(firstpress){
        pressedMillis = currentMillis; 
        firstpress = false;
      }
      if (currentbutton == 0){
        buttonPressed = true;
        while (currentMillis - pressedMillis > 3000){
          win();
        }
      }
      else if(currentbutton == 1 && currentMillis - pressedMillis > 5000){
        loss();
      }
      //   if(currentMillis - pressedMillis < 3000) {
      //     loss();
      //   } 
      //   else{
      //     win(); 
      //   }
      // }
    }
    else if(ran == 2){
      display.println("DETONATE");
      display.display(); 
      setColor(0,0,255);
      currentbutton = digitalRead(buttonPin);
      if(firstpress){
        pressedMillis = currentMillis; 
        firstpress = false;
      }
      if (currentbutton == 0){
        buttonPressed = true;
        loss();
      }
      else if(currentbutton == 1 && currentMillis - pressedMillis > 3000){
        win();
      }
    }
    else{
      display.println("SMASH");
      display.display();  
      setColor(255,255,255);
      currentbutton = digitalRead(buttonPin); 

      if(firstpress){
        pressedMillis = currentMillis; 
        firstpress = false;
      }

      if (currentbutton == 0 && previousbutton == 1){
        buttonPressed = true;
        previousbutton = 0;
        buttoncount++;
      }

      if (currentbutton == 1){
        previousbutton = 1;
      }

      if (buttoncount >= 5){
        win();
      }
      else if(currentMillis - pressedMillis > 5000){
        loss();
      }
    }
  }
}

void win() {
  // setColor(0,0,0);
  digitalWrite(redPin, 0); 
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 0);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.println("PASS"); 
  display.display();
  is_win = true; 
}

void loss(){
  // setColor(0,0,0);
  digitalWrite(redPin, 0); 
  digitalWrite(greenPin, 0);
  digitalWrite(bluePin, 0);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 32);
  display.println("STRICK"); 
  display.display(); 
  is_win = true;
}



void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

// String getColor(int redValue, int greenValue, int blueValue){
//   return "(" + String(redValue) + "," + String(greenValue) + "," + String(blueValue) + ")";
// }
