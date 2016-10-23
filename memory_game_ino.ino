/*

  Memory game implemantation in arduino
  
  Five buttons, five LEDs, a start button
  Upon start/reset, the LEDs flash in 
  random order. Your job is to press the 
  buttons in same order after a signal has 
  been given.
  
  Written by Ørjan Vøllestad, 2016
  http://gitlab.com/orjanv/memorygame

*/

// setup led array and button array
int ledPins[] = {8, 9, 10, 11, 12};
int buttonPins[] = {3, 4, 5, 6, 7};
// Setup startbutton
int startButton = 2;
int buttonState = 0;
int buttonPushCounter = 0;
// Setup the signal LED
int readyLed = 13;
int pinCount = 6;

void setup() {
  // initialize the startbutton pin as an input:
  pinMode(startButton, INPUT);
  
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  // Do the same for the buttons, just as input this time:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(buttonPins[thisPin], INPUT);
  }
  
  // Generate a welcome message on the LCD

}

void loop() {

  buttonState = digitalRead(startButton);
  // Wait for start/reset button to be pressed
  while (buttonState == HIGH) {
    
    int randArray[5];
    // Make numbers more random
    randomSeed(micros());
    // Fill the array random numbers from 1-5
    for (int i = 0; i < pinCount; i++) {
      randArray[i] = random(0.1, 1.5);
    }
    
    // Illuminate LEDs according to this array of random numbers
    for (int ledPin = 0; ledPin < pinCount; ledPin++) {
      digitalWrite(ledPins[ledPin],randArray[ledPin]);
      delay(1000);
    }
    
    // Give ready signal
    digitalWrite(readyLed, HIGH);
        
    // Read input when counted five button pushes
    while (buttonPushCounter < pinCount) {
      for (int buttonPin = 0; buttonPin < pinCount; buttonPin++) {
        digitalRead(buttonPins[buttonPin]);
        
      }
      
      //digitalRead(inPin)
      
    }
    
    // Compare randArray with values from buttons
    
    
}
