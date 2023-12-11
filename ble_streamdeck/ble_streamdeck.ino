// Key definitions
#define BUTTON_KEY1 KEY_F13
#define BUTTON_KEY2 KEY_F14
#define BUTTON_KEY3 KEY_F15
#define BUTTON_KEY4 KEY_F16
#define BUTTON_KEY5 KEY_F17
#define BUTTON_KEY6 KEY_F18
#define BUTTON_KEY7 KEY_F19
#define BUTTON_KEY8 KEY_F20
#define BUTTON_KEY9 KEY_F21
#define BUTTON_KEY10 KEY_F22

// Pin definitions
#define BUTTON_PIN1 4
#define BUTTON_PIN2 5
#define BUTTON_PIN3 12
#define BUTTON_PIN4 14
#define BUTTON_PIN5 15
#define BUTTON_PIN6 16
#define BUTTON_PIN7 17
#define BUTTON_PIN8 18
#define BUTTON_PIN9 19
#define BUTTON_PIN10 21

// ---------------------------------


#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

// Button helper class for handling press/release and debouncing
class button {
  public:
  const char key;
  const uint8_t pin;
 
  button(uint8_t k, uint8_t p) : key(k), pin(p){}

  void press(boolean state){
    if(state == pressed || (millis() - lastPressed <= debounceTime)){
      return;
    } 
    lastPressed = millis();
 
    state ? bleKeyboard.press(key) : bleKeyboard.release(key);    
    Serial.print("Key ");
    Serial.println(pin);
    pressed = state;
  }

  void update(){
    press(!digitalRead(pin));
    // print keypress + key char to serial monitor
    // Serial.print("Key ");
    // Serial.print(pin);
    // Serial.print(" ");
    // Serial.println(&key);
  }

  private:
  const unsigned long debounceTime = 30;
  unsigned long lastPressed = 0;
  boolean pressed = 0;

};

// Button objects, organized in array
button buttons[] = {
 {BUTTON_KEY1, BUTTON_PIN1},
 {BUTTON_KEY2, BUTTON_PIN2},
 {BUTTON_KEY3, BUTTON_PIN3},
 {BUTTON_KEY4, BUTTON_PIN4},
 {BUTTON_KEY5, BUTTON_PIN5},
 {BUTTON_KEY6, BUTTON_PIN6},
 {BUTTON_KEY7, BUTTON_PIN7},
 {BUTTON_KEY8, BUTTON_PIN8},
 {BUTTON_KEY9, BUTTON_PIN9},
 {BUTTON_KEY10, BUTTON_PIN10},
 };



void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
  Serial.println("Starting BLE work!");


  for (int i = 0; i < 10; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }

}

void loop() {
  if (bleKeyboard.isConnected()) {
    for (int i = 0; i < 10; i++) {
      buttons[i].update();
    }
  }
  // Serial.println("Waiting 1 seconds...");
  // delay(1000);
}
