// Run Stepper Motor with A4998  


#define BAUD (9600)

// Motor Pin Configuration
const int A_Pin = PB10;
const int B_Pin = PB4;
const int A_N_Pin = PB5;
const int B_N_Pin = PB3;

// Half-Stepping Sequence
const int stepSequence[8][4] = {
  {1, 0, 0, 0},  // S0
  {1, 0, 1, 0},  // S1
  {0, 0, 1, 0},  // S2
  {0, 1, 1, 0},  // S3
  {0, 1, 0, 0},  // S4
  {0, 1, 0, 1},  // S5
  {0, 0, 0, 1},  // S6
  {1, 0, 0, 1}   // S7
};

int x;
const int stepDelay = 5;

void setup()
{
  Serial.begin(BAUD);

  pinMode(A_Pin, OUTPUT);
  pinMode(B_Pin, OUTPUT);
  pinMode(A_N_Pin, OUTPUT);
  pinMode(B_N_Pin, OUTPUT);
}

void loop()
{
  Serial.println("Clockwise Rotation");

  for(x = 0; x < 1000; x++)
  {
    int step = x % 8;

    digitalWrite(A_Pin, stepSequence[step][0]);
    digitalWrite(B_Pin, stepSequence[step][1]);
    digitalWrite(A_N_Pin, stepSequence[step][2]);
    digitalWrite(B_N_Pin, stepSequence[step][3]);

    delay(stepDelay);
  }

  Serial.println("Pause");
  delay(1000);
}


