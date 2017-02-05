int forward_1 = 2;
int backward_1 = 3;
int forward_2 = 5;
int backward_2 = 6;

int drive_mode = 0;
int previous_mode;

int maxSpeed = 50;
int currSpeed_1f = 0;
int currSpeed_1b = 0;
int currSpeed_2f = 0;
int currSpeed_2b = 0;

unsigned long previousMillis = 0;
unsigned long currentMillis;


// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(forward_1, OUTPUT);
  pinMode(backward_1, OUTPUT);
  pinMode(forward_2,OUTPUT);
  pinMode(backward_2,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
    // chose state of drive system

    // adjust if in new state
    if (drive_mode != previous_mode) {
        switch (drive_mode) {
            case 0:
            {
                // initialize off
                
                break;
            }
            case 1:
            {
                // initialize forward
                currSpeed_1b = 0;
                currSpeed_2b = 0;
                analogWrite(backward_1,currSpeed_1b);
                analogWrite(backward_2,currSpeed_2b);

                break;
            }
            case 2:
            {
                // initialize backward

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
                if (currSpeed_1f < maxSpeed) {
                    currSpeed_1f = currSpeed_1f + 1;
                }
                if (currSpeed_2f < maxSpeed) {
                    currSpeed_2f = currSpeed_2f + 1;
                }
                previousMillis = millis();

                analogWrite(forward_1,currSpeed_1f);
                analogWrite(forward_2,currSpeed_2f);
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

            break;
        }
    }

    previous_mode = drive_mode;
    
}



