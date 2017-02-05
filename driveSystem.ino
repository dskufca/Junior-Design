int forward_R = 2; // right wheel
int backward_R = 3;
int forward_L = 5; // left wheel
int backward_L = 6;

int drive_mode = 0;
int previous_mode;

int maxSpeed = 50;
int currSpeed_Rf = 0;
int currSpeed_Rb = 0;
int currSpeed_Lf = 0;
int currSpeed_Lb = 0;

unsigned long previousMillis = 0;
unsigned long currentMillis;


// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(forward_R, OUTPUT);
  pinMode(backward_R, OUTPUT);
  pinMode(forward_L,OUTPUT);
  pinMode(backward_L,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
    // choose state of drive system
    currentMillis = millis();
    if (currentMillis > 5000) {
        drive_mode = 0;
    } else if (currentMillis > 3500) {
        drive_mode = 2;
    } else if (currentMillis > 2500) {
        drive_mode = 3;
    } else if (currentMillis > 1500) {
        drive_mode = 4;
    } else {
        drive_mode = 1;
    }

    // adjust if in new state
    if (drive_mode != previous_mode) {
        switch (drive_mode) {
            case 0:
            {
                // initialize off
                currSpeed_Rf = 0;
                currSpeed_Rb = 0;
                currSpeed_Lf = 0;
                currSpeed_Lb = 0;
                break;
            }
            case 1:
            {
                // initialize forward
                currSpeed_Rb = 0;
                currSpeed_Lb = 0;
                analogWrite(backward_R,currSpeed_Rb);
                analogWrite(backward_L,currSpeed_Lb);

                break;
            }
            case 2:
            {
                // initialize backward
                currSpeed_Rf = 0;
                currSpeed_Lf = 0;
                analogWrite(forward_R, currSpeed_Rf);
                analogWrite(forward_L, currSpeed_Lf;
              
                break;
            }
            case 3:
            {
                // initialize right
                
              
                break;
            }
            case 4:
            {
                // initialize left
                currSpeed_Lf = 0;
                currSpeed_Rb = 0;
                analogWrite(forward_L,currSpeed_Lf);
                analogWrite(backward_R,currSpeed_Rb);
                break;
            }
        }
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
            currentMillis = millis();
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
            }
            break;
        }
        case 2:
        {
            // BACKWARD
            
            break;
        }
        case 3:
        {
            // RIGHT

            break;
        }
        case 4:
        {
            // LEFT
            // maybe accelerate here? right now constant
            currSpeed_Rf = maxSpeed;
            currSpeed_Lf = maxSpeed;
            analogWrite(forward_R,currSpeed_Rf);
            analogWrite(backward_L,currSpeed_Lb);
            break;
        }
    }

    previous_mode = drive_mode;
    
}



