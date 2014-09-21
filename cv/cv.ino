
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

// Rotary knob state
volatile int old_state = 0;
volatile int state = 0;

// Value to send to DAC
volatile int value = 0;
volatile int new_value = 4095;

// Used to limit the frequency of timer updates to 30 times per sec
int old_time = 0;

// Interrupt handler for rotary encoder
ISR(PCINT2_vect) {
  state = PIND;
  int changes = state ^ old_state;
  // If bit 2, update the value
  if (bitRead(changes, 2)) {
    if (bitRead(state, 2) ^ bitRead(old_state, 3)) {
      new_value++;
    } else {
      new_value--;
    }
  }
  // If bit 4, update the value with a coarse resolution
  if (bitRead(changes, 4)) {
    if (bitRead(state, 4) ^ bitRead(old_state, 5)) {
      new_value += 8;
    } else {
      new_value -= 8;
    }
  }

  // Store the state to compare against next time
  old_state = state;
}

void setup(void) {
  pinMode(13, OUTPUT);     
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
  dac.begin(0x60);
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
  pinMode(5, INPUT);
  digitalWrite(5, HIGH);

  noInterrupts();
  // Pin change interrupt control register
  PCICR |= 0b100;
  
  // Pin change mask registers decide which pins are enabled as triggers
  PCMSK2 |= (_BV(PCINT18) | _BV(PCINT19) | _BV(PCINT20) | _BV(PCINT21));
  interrupts();
}

void loop(void) {
  int time = millis();
  // Limit frequency of timer updates to 30 per second
  if (time - old_time < 33) {
    return;
  }
  old_time = time;

  if (value != new_value) {
    digitalWrite(13, HIGH);
    delay(10);
    digitalWrite(13, LOW);
    delay(10);
    value = new_value;
  
    if (value > 4095) {
      new_value = value = 4095;
    }
    if (value < 8) {
      new_value = value = 8;
    }
  
    dac.setVoltage(value, false);
  }
}


