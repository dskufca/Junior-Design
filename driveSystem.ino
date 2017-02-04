int forward_1 = 2;
int backward_1 = 3;
int forward_2 = 5;
int backward_2 = 6;

int maxSpeed = 255;
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
    // accelerate forward
    analogWrite(backward_1,currSpeed_1b);
    analogWrite(backward_2,currSpeed_2b);
    currentMillis = millis();
    if (currentMillis-previousMillis > 100) {
        if (currSpeed_1f < maxSpeed and currSpeed_2f < maxSpeed) {
            currSpeed_1f = currSpeed_1f + 5;
            currSpeed_2f = currSpeed_2f + 5;
        }

        analogWrite(forward_1,currSpeed_1f);
        analogWrite(forward_2,currSpeed_2f);
    }
    
}



