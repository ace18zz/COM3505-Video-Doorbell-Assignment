/*
 * @Author: Ziting Zhao
 * @Date: 2021-05-10 15:18:30
 * @LastEditTime: 2021-05-19 22:57:09
 * @FilePath: /ProjectThing/button_doorbell/button_doorbell.ino
 */
#define BUTTON_PIN1 2             //button 1
#define BUTTON_PIN2 3             //button 2
#define BUTTON_PIN3 4             //button 3
#define BUTTON_PIN4 5             //button 4
#define BUTTON_PIN5 6             //button 5
#define BEE_PIN 7                 //Buzzer Pins

const int music[5] = {147, 165, 175, 196, 221};       // do re mi fa so 

/*
 * Defining keystroke information related structures
 */
struct Button {
  int buttonState = HIGH;        
  int lastButtonState = HIGH;     
  long lastDebounceTime = 0;      //recording jitter variables
  long debounceDelay = 30;     
};
Button button[5];                 //creat 5 buttons



void Get_Button(int button_pin, int button_num) {
  int button_value = digitalRead(button_pin);                 //Read I/O port status and update time if status changes
  if (button_value != button[button_num].lastButtonState) {   
    button[button_num].lastDebounceTime = millis();           
  }                                                           
  if ((millis() - button[button_num].lastDebounceTime) > button[button_num].debounceDelay) {
    if (button_value != button[button_num].buttonState) {     
      button[button_num].buttonState = button_value;          //update buttonState
    }
  }
  button[button_num].lastButtonState = button_value;          
}

void setup() {
  Serial.begin(9600);                           //Initialize serial port baud rate 9600
  pinMode(BUTTON_PIN1, INPUT_PULLUP);           
  pinMode(BUTTON_PIN2, INPUT_PULLUP);          
  pinMode(BUTTON_PIN3, INPUT_PULLUP);           
  pinMode(BUTTON_PIN4, INPUT_PULLUP);           
  pinMode(BUTTON_PIN5, INPUT_PULLUP);          
  pinMode(BEE_PIN, OUTPUT);                     
  digitalWrite(BEE_PIN, LOW);                   
}

void loop() {
  Get_Button(BUTTON_PIN1, 0);                   //Reading the level of key 1
  Get_Button(BUTTON_PIN2, 1);                
  Get_Button(BUTTON_PIN3, 2);                 
  Get_Button(BUTTON_PIN4, 3);                  
  Get_Button(BUTTON_PIN5, 4);                   
  if (button[0].buttonState == LOW) {           //Key 1 is detected as being pressed and the buzzer plays do
    tone(BEE_PIN, music[0]);
  }
  else if (button[1].buttonState == LOW) {      //Key 2 is detected as being pressed and the buzzer plays re
    tone(BEE_PIN, music[1]);
  }
  else if (button[2].buttonState == LOW) {      //Key 3 is detected as being pressed and the buzzer plays mi 
    tone(BEE_PIN, music[2]);
  }
  else if (button[3].buttonState == LOW) {      //Key 4 is detected as being pressed and the buzzer plays fa
    tone(BEE_PIN, music[3]);
  }
  else if (button[4].buttonState == LOW) {      //Key 5 is detected as being pressed and the buzzer plays so
    tone(BEE_PIN, music[4]);
  }
  else {                                  
    noTone(BEE_PIN);
  }
  Serial.println(String("") + "button1\tbutton2\tbutton3\tbutton4\tbutton5"); 
  Serial.println(String("") + button[0].buttonState + "\t" + button[1].buttonState + "\t" + button[2].buttonState + "\t" + button[3].buttonState + "\t" + button[4].buttonState);   //串口打印按键的值
}
