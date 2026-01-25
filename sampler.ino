#include <analogReadAsync.h>

// I/O [https://kookye.com/wp-content/uploads/2016/02/Pinout-ProMicro.jpg]
const int trigger_button = 14;
const int pwm_signal = 15;
const int laser_current = A0;

const unsigned long period_size_us = 10000; // 100 Hz
const int n_periods = 3000;                 // 30s

void setup() {
  Serial.begin(1000000);  // Pro micro (Leonardo) doesn't actually care
  while(!Serial);         // Wait for serial to be ready
  pinMode(trigger_button, INPUT_PULLUP);
  pinMode(pwm_signal, INPUT);
  analogReference(INTERNAL);  // 2.56V
}

void loop() {
  wait_trigger();
  sample();
}

void wait_trigger() {
  Serial.print("Waiting for trigger...");
  while(digitalRead(trigger_button) == HIGH) delay(100); // Wait for push
  while(digitalRead(trigger_button) == LOW) delay(100);; // Wait for release
  Serial.println("GO!");
}

void sample() {
  unsigned long t0 = micros();
  unsigned long t_period = t0 + period_size_us;
  unsigned long n_pwm, n_on;
  unsigned long n_current, sum_current;

  const uint8_t in_bit = digitalPinToBitMask(pwm_signal);
  const uint8_t in_port = digitalPinToPort(pwm_signal);

  for(int i = 0; i < n_periods; ++i) {
    n_pwm = n_on = n_current = sum_current = 0;

    while(micros() < t_period) {
      analogReadAsync(laser_current);

      while(!getAnalogReadComplete(false)) {
        n_on += (*portInputRegister(in_port) & in_bit);
        n_on += (*portInputRegister(in_port) & in_bit);
        n_on += (*portInputRegister(in_port) & in_bit);
        n_on += (*portInputRegister(in_port) & in_bit);
        n_on += (*portInputRegister(in_port) & in_bit);
        n_on += (*portInputRegister(in_port) & in_bit);
        n_on += (*portInputRegister(in_port) & in_bit);
        n_on += (*portInputRegister(in_port) & in_bit);
        n_on += (*portInputRegister(in_port) & in_bit);
        n_on += (*portInputRegister(in_port) & in_bit);

        n_pwm += 10;
      };

      ++n_current;
      sum_current += getAnalogReadValue();
    }
    t_period += period_size_us;

    Serial.print(i);
    Serial.print(',');
    Serial.print(n_on / in_bit);
    Serial.print(',');
    Serial.print(n_pwm);
    Serial.print(',');
    Serial.print(sum_current);
    Serial.print(',');
    Serial.println(n_current);
  }
}