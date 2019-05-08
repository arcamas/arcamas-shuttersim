#define LEDPIN 13

#define MOTOR_INPUT 7
#define M0SENSOR 4
#define S2SENSOR 5
#define S1SENSOR 6

#define DELAY_TIME_STATE 1000
#define STATES_TOTAL 6

int currState = 0;
bool motorRead = false;

const unsigned char M0SensorStates[6] = {
  HIGH, LOW, LOW, LOW, LOW, LOW
};
const unsigned char S2SensorStates[6] = {
  LOW, LOW, HIGH, HIGH, HIGH, LOW
};
const unsigned char S1SensorStates[6] = {
  LOW, LOW, LOW, HIGH, LOW, LOW
};
long previousMillisState = 0;


void setup() {
	pinMode(LEDPIN, OUTPUT);
  pinMode(M0SENSOR, OUTPUT);
  pinMode(S1SENSOR, OUTPUT);
  pinMode(S2SENSOR, OUTPUT);
  digitalWrite(M0SENSOR, HIGH ^ M0SensorStates[0]);
  digitalWrite(S2SENSOR, HIGH ^ S2SensorStates[0]);
  digitalWrite(S1SENSOR, HIGH ^ S1SensorStates[0]);

	pinMode(latch, OUTPUT);
	pinMode(ser, OUTPUT);
	pinMode(srclk, OUTPUT);

	pinMode(MOTOR_INPUT, INPUT_PULLUP);

  currState = -1;
  previousMillisState = 0;
}

void loop() {

	//Digital Button Read
  motorRead = digitalRead(MOTOR_INPUT);

  //State change every 1000ms
  unsigned long currentMillisState = millis();
  int nextState = 0;
  if (motorRead == HIGH) {
    nextState = 0;
    previousMillisState = currentMillisState;
  }
  if (motorRead == LOW) {
    nextState = currState;
    if (currentMillisState - previousMillisState > DELAY_TIME_STATE) {
      nextState = (nextState + 1) % STATES_TOTAL;
      previousMillisState = currentMillisState;
    }
  }

  //Change Output depend on Status
  if (nextState != currState) {
    
    currState = nextState;

    digitalWrite(M0SENSOR, HIGH ^ M0SensorStates[currState]);
    digitalWrite(S2SENSOR, HIGH ^ S2SensorStates[currState]);
    digitalWrite(S1SENSOR, HIGH ^ S1SensorStates[currState]);
    digitalWrite(LEDPIN, HIGH);
    if (currState % 2 == 1) {
      digitalWrite(LEDPIN, LOW);
    }
  }
}
