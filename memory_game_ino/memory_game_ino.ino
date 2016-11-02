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

int ledPins[] = {8, 9, 10, 12, 11};
int buttonPins[] = {3, 4, 5, 7, 6};
int answerArray[] = {};
int startButton = 2;
int readyLed = 13;
int pinCount = 5;
boolean result;  // this variable will hold the compare result

void setup() {
  Serial.begin(9600);
  // initialize the startbutton pin as an input:
  pinMode(startButton, INPUT_PULLUP);
    // initialize the readyled button
  pinMode(readyLed, OUTPUT);
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  // Do the same for the buttons, just as input this time:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(buttonPins[thisPin], INPUT_PULLUP);
  }
  
  // Generate a welcome message on the LCD

  // TESTING LEDS by flashing them
  digitalWrite(readyLed, HIGH);

  for (int ledPin = 0; ledPin < pinCount; ledPin++) {
    digitalWrite(ledPins[ledPin], HIGH);
    delay(250);
  }
  for (int ledPin = 0; ledPin < pinCount; ledPin++) {
    digitalWrite(ledPins[ledPin], LOW);
    delay(250);
  }
  delay(250);
  digitalWrite(readyLed, LOW);

}

void loop() {
  // Wait for start/reset button to be pressed
  //Serial.println("Venter paa knapp");
  
  if (digitalRead(startButton) == LOW) {
    Serial.println("Game is started!");
    int randArray[5];
    // Make numbers more random
    randomSeed(micros());
    // Fill the array random numbers from 1-5
    for (int i = 0; i < pinCount; i++) {
      randArray[i] = random(0, 4);
      Serial.println(randArray[i]);
    }
    
    // Illuminate LEDs according to this array of random numbers
    for (int ledPin = 0; ledPin < pinCount; ledPin++) {
      digitalWrite(ledPins[randArray[ledPin]],HIGH);
      delay(250);
      digitalWrite(ledPins[randArray[ledPin]],LOW);
      delay(1000);
    }
    
    // Give ready signal
    digitalWrite(readyLed, HIGH);

    // Read input when counted five button pushes
    //long timeout = millis()+20000;
    int buttonPushCounter = 0;
    while (buttonPushCounter < pinCount) { // scan buttons
      for (int i = 0; i < pinCount; i++) { 
        if (digitalRead(buttonPins[i]) == LOW) {
          Serial.print("Denne knappen ble trykt: ");
          Serial.println(i);
          // fill temporary answerArray
          answerArray[buttonPushCounter] = i;
          buttonPushCounter++;
          delay(500); // hack to let each buttonpress count once
        } // end if
      } // end for
    } // end scan buttons loop 
    
    // Compare randArray with values from answerArray
    result = true; // set variable equal to one.
    for (int i = 0; i < pinCount; i++) { 
      int test1 = answerArray[i];// asign each index of arrays to test, one by one and compare
      int test2 = randArray[i];
      if (test1 != test2) {
        result = false; 
      }
    }
    if (result == true) { // if the arrays are equal, do something.
      Serial.println("You won the game!");
    }
    else if (result ==  false) {
      Serial.println("You lost the game!");
    }

    digitalWrite(readyLed, LOW);
    Serial.println("End of game!");
    delay(2000);
    
  } // end while startbutton pressed loop
  delay(50);
} // end main loop
