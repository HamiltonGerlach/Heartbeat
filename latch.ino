#include "InputDebounce.h"

int SWITCH_DELAY = 50;
int DURATION = 50;
int PIN_OUT = 1;
int PIN_POT = 1;
int PIN_SWITCH = 3;

static InputDebounce Switch;
bool Active = true;

// the setup routine runs once when you press reset:
void setup() {                
    // initialize the digital pin as an output.
    pinMode(PIN_OUT, OUTPUT); //LED
    digitalWrite(PIN_OUT, LOW);
    
    Switch.registerCallbacks(cbPressed, cbReleased, cbPressedDuration, cbReleasedDuration);
    Switch.setup(PIN_SWITCH);
}

// the loop routine runs over and over again forever:
void loop() {
    unsigned long t = millis();
    Switch.process(t);
    delay(1);
}


int GetSpeed(int Pin) {
    int pot = analogRead(Pin);
    float v = 100.0 * (1.0 + 5.0 * (pot / 1023.0));
    int out = round(v);
    return out;
}

void Fire(int PulseDuration, int Speed) {
    digitalWrite(PIN_OUT, HIGH);
    delay(PulseDuration);
    digitalWrite(PIN_OUT, LOW);
    delay(Speed);
    digitalWrite(PIN_OUT, HIGH);
    delay(PulseDuration);
    digitalWrite(PIN_OUT, LOW);
    
    Active = false;
}


void cbPressed(uint8_t pinIn) {
    
}

void cbReleased(uint8_t pinIn) {
    
}

void cbPressedDuration(uint8_t pinIn, unsigned long duration) {
    if ((Active == true) && (duration > SWITCH_DELAY)) {
      int Speed = GetSpeed(PIN_POT);
      Fire(DURATION, Speed);
    }
}

void cbReleasedDuration(uint8_t pinIn, unsigned long duration) {
    if ((Active == false) && (duration > SWITCH_DELAY)) {
        Active = true;
    }
}