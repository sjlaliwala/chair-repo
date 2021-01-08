#define INPUTMODE INPUT_PULLUP    // INPUT or INPUT_PULLUP
#define BOUNCETIME 50              // bouncing time in milliseconds
byte buttonPins[]={2, 3, 4, 5, 6, 7, 8, 9, 10, 11};// pin numbers of all buttons
#define NUMBUTTONS sizeof(buttonPins) // number of buttons (automatically calculated)
byte buttonState[NUMBUTTONS];  // array holds the actual HIGH/LOW states
byte buttonChange[NUMBUTTONS]; // array holds the state changes when button is pressed or released
long startIntervals[NUMBUTTONS];
long endIntervals[NUMBUTTONS];
//String toPublish[NUMBUTTONS];
enum{UNCHANGED,BUTTONUP,BUTTONDOWN};

const int tillBuzz = 10;
int second;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void input(){
// read the input state and state changes of all buttons
  static unsigned long lastButtonTime; // time stamp for remembering the time when the button states were last read
  memset(buttonChange,0,sizeof(buttonChange)); // reset all old state changes
  if (millis()-lastButtonTime<BOUNCETIME) return;  // within bounce time: leave the function
  lastButtonTime=millis(); // remember the current time
  for (int i=0;i<NUMBUTTONS;i++)
  {
    byte curState=digitalRead(buttonPins[i]);        // current button state
    if (INPUTMODE==INPUT_PULLUP) curState=!curState; // logic is inverted with INPUT_PULLUP
    if (curState!=buttonState[i])                    // state change detected
    {
      if (curState==LOW) 
      {
        startIntervals[i] = millis();
        buttonChange[i]=BUTTONUP;
      }
      else 
      {
        endIntervals[i] = millis();
        buttonChange[i]=BUTTONDOWN;
      }
    }
    buttonState[i]=curState;  // save the current button state
  }
}


void output(){
// send a message to Serial if a button state (pressed/released) has changed
// button pressed: Send button pin number with minus sign
// button released: Send button pin number
  for (int i=0;i<NUMBUTTONS;i++)
  {
    switch (buttonChange[i])  
    {
      //this will need to be changed to buttondown with chair
      //maybe you can split this up if processing gets too messy and follow Input Processing Output format
      //this will have to change to buttondown, after default state with chair
      case BUTTONDOWN: {
          Serial.print(String(i) + "," + String(startIntervals[i]) + "," + String(endIntervals[i]) + "#");
//        Serial.print(i);
//        Serial.print(",");
//        Serial.print(startIntervals[i]);
//        Serial.print(",");
//        Serial.print(endIntervals[i]);
//        Serial.print(">");
          break; 
      }
    }
  }
}

//void output(){
//// send a message to Serial if a button state (pressed/released) has changed
//// button pressed: Send button pin number with minus sign
//// button released: Send button pin number
//  byte action;
//  Serial.print("<");
//  for (int i=0;i<NUMBUTTONS;i++)
//  {
//    switch (buttonChange[i])  
//    {
//      case BUTTONUP: {
//        //ButtonUP is our indication to send to server on breadboard
//        Serial.print(toPublish[i]);
//        Serial.print(",");
//      }
//    }
//  }
//}

//    switch (buttonChange[i])  
//    {
//      case BUTTONUP: {
//        //ButtonUP is our indication to send to server on breadboard
//        Serial.println(String(buttonPins[i]);
//        Serial.println(startIntervals[i]);
//        Serial.println(endIntervals[i]);
//        break;
//        
//      }
//      case BUTTONDOWN: {
//        //ButtonDOWN is our indication to send to server on chair since default state is sitting down
//        //Serial.println(-buttonPins[i]);break;
//      }
//    }
//  }
//}


void setup()
{
  
  Serial.begin(115200); // initialize Serial at 9600 baud
  // then initialize all buttons
  for (int i=0;i<NUMBUTTONS;i++) pinMode(buttonPins[i],INPUTMODE);
}

void loop()
{
  input();
  


  output();
//  buttState = digitalRead(buttPin);
//  backState = digitalRead(backPin);
//  legState = digitalRead(legPin);
//  
//  if (buttState != lastButtState) {
//    // reset the debouncing timer
//    lastDebounceTime = millis();
//  }
//  Serial.println(buttState);
//  Serial.println(backState);
//  Serial.println(legState);
//  Serial.println();
//  delay(1000);
//  if (buttState == HIGH)
//  {
//    Serial.println("ON");
//    backState = digitalRead(backPin);
//    legState = digitalRead(legState);
//    if (backState == LOW || legState == LOW)
//    {
//      for (second = 0; second < tillBuzz; second++)
//      {
//        buttState = digitalRead(buttPin);
//        backState = digitalRead(backPin);
//        if (buttState == HIGH || backState == HIGH || legState == HIGH)
//        {
//          continue;
//        }
//        delay(1000);
//      }
//      //tone(buzzer, 500);
//      while (buttState == HIGH && (legState == LOW || backState == LOW))
//      {
//        Serial.println("Seated incorrectly");
//        buttState = digitalRead(buttPin);
//        backState = digitalRead(backPin);
//        legState = digitalRead(legPin);
//      }
//    }
//    else
//    {
//      //noTone(buzzer);
//      Serial.println("Seated correctly");
//    }
//  }
//  else
//  {
//    Serial.println("OFF");
//    //noTone(buzzer);
//  }
}
