// pin definitions
int forward_R = 2; // right wheel
int backward_R = 3;
int forward_L = 5; // left wheel
int backward_L = 6;
int blueLED = 8;
int redLED = 9;
int sensor = A10;

// driving modes
int drive_mode = 0;
int previous_mode;

// vars for light sensor state
int red_output;
int reading;
int surfaceColor;

// threshold vars
int redThresh = 75;
int bbThresh = 20;
int ryThresh = 145;

// vars for motor speeds
int maxSpeed = 40;
int currSpeed_Rf = 0;
int currSpeed_Rb = 0;
int currSpeed_Lf = 0;
int currSpeed_Lb = 0;

// counting vars
// unsigned long previousMillis = 0;
unsigned long currentMillis;
unsigned long bluePrevMillis = 100;
unsigned long redPrevMillis = 0;

// the setup routine runs once when you press reset:
void setup() {
    // initialize motor outputs
    pinMode(forward_R, OUTPUT);
    pinMode(backward_R, OUTPUT);
    pinMode(forward_L,OUTPUT);
    pinMode(backward_L,OUTPUT);

    // intialize sensor system
    pinMode(blueLED, OUTPUT);
    pinMode(redLED, OUTPUT);
    pinMode(sensor, INPUT);
    analogWrite(redLED,255);
}

// the loop routine runs over and over again forever:
void loop() {
    // check color of ground
    currentMillis = millis();
        if (currentMillis - redPrevMillis >= 200) {
        // check sensor with just red LED on
        if (analogRead(sensor) < redThresh) {
            red_output = 0;
        } else {
            red_output = 1;
        }
        // reset timer counter
        redPrevMillis = millis();
        // turn on blue LED
        analogWrite(blueLED, 255);
    } else if (currentMillis - bluePrevMillis >= 200) {
        // check sensor with both LEDs on
        if (red_output == 0) {
            reading = analogRead(sensor);
            if (analogRead(sensor) < bbThresh) {
                surfaceColor = 1;
            } else {
                surfaceColor = 2;
            }
        } else {
            if (analogRead(sensor) < ryThresh) {
                surfaceColor = 3;
            } else {
                surfaceColor = 4;
            }
        }
        // reset timer counter
        bluePrevMillis = millis();
        // turn off blue LED
        analogWrite(blueLED,0);
    }

    // pick drive mode
    if (surfaceColor == 2) {
        drive_mode = 0;
    } else {
        drive_mode = 1;
    }

    // adjust if in new state
    if (drive_mode != previous_mode) {
        // reset everything
        currSpeed_Rf = 0;
        currSpeed_Rb = 0;
        currSpeed_Lf = 0;
        currSpeed_Lb = 0;
        analogWrite(forward_R,currSpeed_Rf);
        analogWrite(forward_L,currSpeed_Lf);
        analogWrite(backward_R,currSpeed_Rb);
        analogWrite(backward_L,currSpeed_Lb);
    }
    
    // create a switch statement for the drive controls
    switch (drive_mode) {
        case 0:
        {
            // OFF

            break;
        }
        case 1:
        {
            // FORWARD
            // accelerate forward
            /*currentMillis = millis();
            if (currentMillis-previousMillis > 10) {
                if (currSpeed_Rf < maxSpeed) {
                    currSpeed_Rf = currSpeed_Rf + 1;
                }
                if (currSpeed_Lf < maxSpeed) {
                    currSpeed_Lf = currSpeed_Lf + 1;
                }
                previousMillis = millis();

                analogWrite(forward_R,currSpeed_Rf);
                analogWrite(forward_L,currSpeed_Lf);
            }*/

            //going forwards at constant speed
            currSpeed_Rf = maxSpeed;
            currSpeed_Lf = maxSpeed;
            analogWrite(forward_R,currSpeed_Rf);
            analogWrite(forward_L,currSpeed_Lf);
            
            break;
        }
        case 2:
        {
            // BACKWARD
            //going backwards at constant speed
            currSpeed_Rb = maxSpeed;
            currSpeed_Lb = maxSpeed;
            analogWrite(backward_R,currSpeed_Rb);
            analogWrite(backward_L,currSpeed_Lb);
          
            break;
        }
        case 3:
        {
            // RIGHT
            //turning at a constant speed
            currSpeed_Rb = maxSpeed;
            currSpeed_Lf = maxSpeed;
            analogWrite(forward_L, currSpeed_Lf);
            analogWrite(backward_R, currSpeed_Rb);  
          
            break;
        }
        case 4:
        {
            // LEFT
            // maybe accelerate here? right now constant
            currSpeed_Rf = maxSpeed;
            currSpeed_Lb = maxSpeed;
            analogWrite(forward_R,currSpeed_Rf);
            analogWrite(backward_L,currSpeed_Lb);
            break;
        }
    }

    previous_mode = drive_mode;
    
}



