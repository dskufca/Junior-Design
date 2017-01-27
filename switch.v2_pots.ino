const int run_led = 9;           // the PWM pin the LED is attached to
const int sleep_led  = 10;
const int on_switch = 52;
const int run_switch = 50;
const int switch_one = 2;
const int switch_two = 3;
const int potPin_brightness = 15; // select the input pin for the potentiometer
const int potPin_flashing = 14;

int brightness = 255;    // how bright the LED is
int blueBrightness = 255;
int fadeAmount = 1;    // how many points to fade the LED by
int problems = 5;
unsigned long inactive = 0;
unsigned long previousMillis = 0;
unsigned long previousBlueMillis = 0;
unsigned long previousBlinkMillis;
unsigned long currentMillis;
int onLed_state = LOW;
int runLed_state = LOW;
int sleepLed_state = LOW;
int fade_status = LOW;

int sys_state;
volatile int vol_sys_state;
int prev_state = 1;

int count = 0;

const int on_delay = 50;
int green_delay = 500;
volatile int blue_delay = 500;
volatile int red_state = LOW;

void setup() {
  // initialize LEDs as input
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(run_led, OUTPUT);
  pinMode(sleep_led, OUTPUT);
  
  // initialize switches as input
  pinMode(on_switch, INPUT);
  pinMode(run_switch, INPUT);
  pinMode(switch_one, INPUT);
  pinMode(switch_two, INPUT);

  // initialize interrupt
  attachInterrupt(digitalPinToInterrupt(switch_one), blueDelay, CHANGE);
  attachInterrupt(digitalPinToInterrupt(switch_two), redLed, CHANGE); 

  // initialize serial printer 
  Serial.begin(9600);
}

void loop() {
    // Select state of machine
    if (digitalRead(on_switch) == HIGH) {
        if (problems > 0) {
            sys_state = 5;
        } else if (digitalRead(run_switch) == HIGH) {
            sys_state = 3;
        } else if (inactive > 200) {
            sys_state = 4;
        } else {
            sys_state = 2;
        }   
    } else {
        sys_state = 1;
    }

    // initialize state parameters when entering new state
    if (prev_state != sys_state) {
        switch(sys_state) {
            case 2: {
                // turn off blue and green LEDs
                digitalWrite(sleep_led, LOW);
                sleepLed_state = LOW;
                digitalWrite(run_led, LOW);
                runLed_state = LOW;
                break;
            }
            case 3: {
                fade_status = HIGH;
                runLed_state = LOW;
                brightness = 255;
                count = 0;
                previousBlinkMillis = millis();
                break;
            }
            case 4: {
                // turn off red and green LEDs
                digitalWrite(LED_BUILTIN, LOW);
                onLed_state = LOW;
                digitalWrite(run_led, LOW);
                runLed_state = LOW;

                //initialize parameters
                fade_status = LOW;
                sleepLed_state = LOW;
                brightness = 255;
                count = 0;
                break;
            }
            case 5: {
                // turn off blue and green LEDs
                digitalWrite(sleep_led, LOW);
                sleepLed_state = LOW;
                digitalWrite(run_led, LOW);
                runLed_state = LOW;
                break;
            }
        }
    }
  
    switch(sys_state) {
        case 1: {
            // OFF CODE //
            // Turn off all leds
            digitalWrite(LED_BUILTIN, LOW);
            onLed_state = LOW;
            digitalWrite(sleep_led, LOW);
            sleepLed_state = LOW;
            digitalWrite(run_led, LOW);
            runLed_state = LOW;

            // reset inactive and problems
            inactive = 0;
            problems = 5;
            
            break;
        }
        case 2: {
            // ON CODE //
            
            // blink ON LED if enough time has passed
            currentMillis = millis();
            if (currentMillis - previousMillis >= on_delay) {
                if (onLed_state == LOW) {
                    onLed_state = HIGH;
                } else {
                    onLed_state = LOW;
                }
                previousMillis = currentMillis;
                digitalWrite(LED_BUILTIN, onLed_state);
                // increment inactive
                inactive = inactive + 1;
            }

            break;
        }
        case 3: {
            // RUN CODE //

            // set red led to appropriate state
            digitalWrite(LED_BUILTIN, red_state);

            // get delay for green LED from potentiometer
            green_delay = analogRead(potPin_flashing) / 2;

            // check that green delay exists
            if (green_delay != 0) {
                // FADE GREEN LED
                // decrement brightness
               currentMillis = millis();
               if (currentMillis - previousMillis >= green_delay and fade_status == HIGH) {
                   brightness = brightness/1.45;
                   previousMillis = currentMillis;
                   analogWrite(run_led, brightness);
               }
               // if brightness too low, switch to blink
                if (currentMillis - previousBlinkMillis >= green_delay * 15) {
                    fade_status = LOW;
                    brightness = 255;
                    runLed_state = HIGH;
                    digitalWrite(run_led, HIGH);
                    previousBlinkMillis = millis();
                    previousMillis = millis();
                }

                // BLINK GREEN LED
                currentMillis = millis();
                if (currentMillis - previousMillis >= green_delay and fade_status == LOW) {
                    if (runLed_state == LOW) {
                        runLed_state = HIGH;
                    } else {
                        runLed_state = LOW;
                    }
                    previousMillis = currentMillis;
                    digitalWrite(run_led, runLed_state);
                    count = count+1;
                    if (count == 4) {
                        fade_status = HIGH;
                        count = 0;
                        previousBlinkMillis = currentMillis;
                    }
                }
            } else {
                // turn off green LED
                digitalWrite(run_led, LOW);
                runLed_state = LOW;
            }

            // BLINK BLUE LED
            // get blue brightness
            blueBrightness = analogRead(potPin_brightness)/4.02;
            
            currentMillis = millis();
            if (currentMillis - previousBlueMillis >= blue_delay) {
                if (sleepLed_state == LOW) {
                    sleepLed_state = blueBrightness;
                } else {
                    sleepLed_state = LOW;
                }
                previousBlueMillis = currentMillis;
                analogWrite(sleep_led, sleepLed_state);
            }

            // reset inactive
            inactive = 0;

            break;
        }
        case 4: {
            // SLEEP CODE //

            // blink blue led
            currentMillis = millis();
            if (currentMillis - previousMillis >= 125 and fade_status == LOW) {
                if (sleepLed_state == LOW) {
                    sleepLed_state = HIGH;
                } else {
                    sleepLed_state = LOW;
                }
                previousMillis = currentMillis;
                digitalWrite(sleep_led, sleepLed_state);
                count = count+1;                    ///how many times it blinks
                if (count == 6) {
                    fade_status = HIGH;
                    count = 0;
                    previousBlinkMillis = currentMillis;
                }
            }
      
            // fade blue led
            currentMillis = millis();
            if (currentMillis - previousMillis >= 125 and fade_status == HIGH) {
                brightness = brightness/2;
                previousMillis = currentMillis;
                analogWrite(sleep_led, brightness);
            }
            if (currentMillis - previousBlinkMillis >= 1000) {
                fade_status = LOW;
                brightness = 255;
                digitalWrite(sleep_led, LOW);
                previousBlinkMillis = millis();
            }

            break;
        }
        case 5: {
            // DIAGNOSTICS CODE //

            // blink red LED
            currentMillis = millis();
            if (currentMillis - previousMillis >= 200) {
                if (onLed_state == LOW) {
                    onLed_state = HIGH;
                } else {
                    onLed_state = LOW;
                    problems = problems-1;
                }
                previousMillis = currentMillis;
                digitalWrite(LED_BUILTIN, onLed_state);
            }

            break;
        }
    }

    // store state that just occured
    prev_state = sys_state;
}

void blueDelay() {
    if (sys_state == 3) {
        if (digitalRead(switch_one)) {
            blue_delay = 50;
            if (!digitalRead(switch_two)) {
                red_state = HIGH;
            }
        } else {
            blue_delay = 500;
            red_state = LOW;
        }
    }
}

void redLed() {
    if (sys_state == 3) {
        if (digitalRead(switch_two)) {
            red_state = LOW;
        } else {
            if (blue_delay == 50) {
                red_state = HIGH;
            }
        }
    }
}

