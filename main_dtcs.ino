#include <TimerOne.h>   // import timer library

// LED Pins
int signal1[] = {23, 25, 27};  // signal 1 LEDs
int signal2[] = {29, 31, 33};  // signal 2 LEDs
int signal3[] = {35, 37, 39}; // signal 3 LEDs
int signal4[] = {41, 43, 45}; // signal 4 LEDs

// Signal Timings
int redDelay = 5000;     // duration of RED signal
int yellowDelay = 1000;  // duration of YELLOW signal
int greenDelay = 3000;  // duration of GREEN signal

// Sensor Pins
volatile int triggerpin1 = 11;
volatile int echopin1 = 10;

volatile int triggerpin2 = 7;
volatile int echopin2 = 6;

volatile int triggerpin3 = 5;
volatile int echopin3 = 4;

volatile int triggerpin4 = 3;
volatile int echopin4 = 2;


volatile long time;  // Variable for storing the time traveled

volatile int S1, S2, S3, S4;  // Variables for storing the distance covered

int t = 10;  // distance under which it will look for vehicles.

void setup() {

  Serial.begin(9600); // serial monitor baud-rate

  Timer1.initialize(100000);            //Begin using the timer. This function must be called first. "microseconds" is the period of time the timer takes.
  Timer1.attachInterrupt(getDistance);  //Run a function each time the timer period finishes.

  // Declaring LED pins as output
  for (int i = 0; i < 3; i++) {
    pinMode(signal1[i], OUTPUT);
    pinMode(signal2[i], OUTPUT);
    pinMode(signal3[i], OUTPUT);
    pinMode(signal4[i], OUTPUT);
  }

  // Declaring ultrasonic sensor pins as output
  pinMode(triggerpin1, OUTPUT);
  pinMode(echopin1, INPUT);
  pinMode(triggerpin2, OUTPUT);
  pinMode(echopin2, INPUT);
  pinMode(triggerpin3, OUTPUT);
  pinMode(echopin3, INPUT);
  pinMode(triggerpin4, OUTPUT);
  pinMode(echopin4, INPUT);

  // Initialize traffic lights (all red initially)
  setRedLight();
  delay(1000);
}

void loop() {

  if (S1 < t)  // If there are vehicles at signal 1
  {
    signal1Function();
  }

  if (S2 < t) {   // If there are vehicles at signal 2
    signal2Function();
  }

  if (S3 < t)   // If there are vehicles at signal 3
  {
    signal3Function();
  }

   // If there are vehicles at signal 4
  if  (S4 < t)
  {
    signal4Function();
  }
}

// This is interrupt function and it will run each time the timer period finishes. The timer period is set at 100 milli seconds.
void getDistance() {
  // Reading from first ultrasonic sensor
  digitalWrite(triggerpin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin1, LOW);
  time = pulseIn(echopin1, HIGH);
  S1 = time * 0.034 / 2;

  // Reading from second ultrasonic sensor
  digitalWrite(triggerpin2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin2, LOW);
  time = pulseIn(echopin2, HIGH);
  S2 = time * 0.034 / 2;

  // Reading from third ultrasonic sensor
  digitalWrite(triggerpin3, LOW);  
  delayMicroseconds(2);
  digitalWrite(triggerpin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin3, LOW);
  time = pulseIn(echopin3, HIGH);
  S3= time*0.034/2;

  // Reading from fourth ultrasonic sensor
  digitalWrite(triggerpin4, LOW);  
  delayMicroseconds(2);
  digitalWrite(triggerpin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin4, LOW);
  time = pulseIn(echopin4, HIGH);
  S4= time*0.034/2;

  // Print distance values on serial monitor for debugging
  Serial.print(" S1: ");
  Serial.print(S1);
  Serial.print("\n");

  Serial.print("  S2: ");
  Serial.print(S2);
  Serial.print("\n");

  Serial.print("  S3: ");
  Serial.print(S3);
  Serial.print("\n");

  Serial.print("  S4: ");
  Serial.println(S4);
  Serial.print("\n");
}

void signal1Function()
{

  Serial.println("---------------- Lane 1 ----------------");
  Serial.print("\n");

  setRedLight();    // RED signal for every lane

  // Make RED LED LOW and make Green HIGH for 5 seconds
  digitalWrite(signal1[0], LOW);
  digitalWrite(signal1[2], HIGH);
  delay(greenDelay);

  // if there are vehicles at other signals
  if (S2 < t || S3 < t || S4 < t)
  {
    // Make Green LED LOW and make yellow LED HIGH for 2 seconds
    digitalWrite(signal1[2], LOW);
    digitalWrite(signal1[1], HIGH);
    delay(yellowDelay);
  }
}

void signal2Function()
{

  Serial.println("---------------- Lane 2 ----------------");
  Serial.print("\n");
  
  setRedLight();    // RED signal for every lane

  // Make Red LOW and make Green HIGH for 5 seconds
  digitalWrite(signal2[0], LOW);
  digitalWrite(signal2[2], HIGH);
  delay(greenDelay);

  // if there are vehicles at other signals
  if (S1 < t || S3 < t || S4 < t)
  {
    // Make Green LED LOW and make yellow LED HIGH for 2 seconds
    digitalWrite(signal2[2], LOW);
    digitalWrite(signal2[1], HIGH);
    delay(yellowDelay);
  }
}

void signal3Function()
{
  Serial.println("---------------- Lane 3 ----------------");
  
  setRedLight();    // RED signal for every lane

  // Make RED LED LOW and make Green HIGH for 5 seconds
  digitalWrite(signal3[0], LOW);
  digitalWrite(signal3[2], HIGH);
  delay(greenDelay);

  // if there are vehicles at other signals
  if(S1<t || S2<t || S4<t)
  {
    // Make Green LED LOW and make yellow LED HIGH for 2 seconds
    digitalWrite(signal3[2], LOW);
    digitalWrite(signal3[1], HIGH);
    delay(yellowDelay);

  }  

}

void signal4Function()
{
  Serial.println("---------------- Lane 4 ----------------");

  setRedLight();    // RED signal for every lane

  // Make RED LED LOW and make Green HIGH for 5 seconds
  digitalWrite(signal4[0], LOW);
  digitalWrite(signal4[2], HIGH);
  delay(greenDelay);

  // if there are vehicles at other signals
  if(S1<t || S2<t || S3<t)
  {
    // Make Green LED LOW and make yellow LED HIGH for 2 seconds
    digitalWrite(signal4[2], LOW);
    digitalWrite(signal4[1], HIGH);
    delay(yellowDelay);
  }

}

void signal01Function()
{
  Serial.println("/////////////  01  ////////////////");
  Serial.print("\n");

  setRedLight();

  digitalWrite(signal1[0], LOW);  // red OFF
  digitalWrite(signal1[1], LOW);  // yellow OFF

  digitalWrite(signal1[2], HIGH);  // green ON
  delay(greenDelay);
  digitalWrite(signal1[2], LOW);  // green OFF

  digitalWrite(signal1[1], HIGH);  // yellow ON
  delay(yellowDelay);
  digitalWrite(signal1[1], LOW);  // yellow OFF

  digitalWrite(signal1[0], HIGH);  // red ON
}

void signal02Function()

{

  Serial.println("////////////  02  //////////////");
  Serial.print("\n");

  setRedLight();

  digitalWrite(signal2[0], LOW);  // red OFF
  digitalWrite(signal2[1], LOW);  // yellow OFF
  digitalWrite(signal2[2], HIGH);  // green ON
  delay(greenDelay);
  digitalWrite(signal2[2], LOW);  // green OFF
  digitalWrite(signal2[1], HIGH);  // yellow ON
  delay(yellowDelay);
  digitalWrite(signal2[1], LOW);  // yellow OFF
  digitalWrite(signal2[0], HIGH);  // red ON
}

void signal03Function()

{

  Serial.println("//////////////  03  /////////////");

  setRedLight();

  digitalWrite(signal3[0], LOW);  // red OFF
  digitalWrite(signal3[1], LOW);  // yellow OFF
  digitalWrite(signal3[2], HIGH);  // green ON
  delay(greenDelay);
  digitalWrite(signal3[2], LOW);  // green OFF
  digitalWrite(signal3[1], HIGH);  // yellow ON
  delay(yellowDelay);
  digitalWrite(signal3[1], LOW);  // yellow OFF
  digitalWrite(signal3[0], HIGH);  // red ON

}

void signal04Function()

{
  Serial.println("///////////  04  /////////////");

  setRedLight();

  digitalWrite(signal4[0], LOW);  // red OFF
  digitalWrite(signal4[1], LOW);  // yellow OFF
  digitalWrite(signal4[2], HIGH);  // green ON
  delay(greenDelay);
  digitalWrite(signal4[2], LOW);  // green OFF
  digitalWrite(signal4[1], HIGH);  // yellow ON
  delay(yellowDelay);
  digitalWrite(signal4[1], LOW);  // yellow OFF
  digitalWrite(signal4[0], HIGH);  // red ON
}

// Function to make all LED's LOW except RED one's.
void setRedLight()
{
  for (int i = 1; i < 3; i++)     // Turn OFF other signals
  {
    digitalWrite(signal1[i], LOW);
    digitalWrite(signal2[i], LOW);
    digitalWrite(signal3[i], LOW);
    digitalWrite(signal4[i], LOW);
  }

  // Turn ON Red signal
  digitalWrite(signal1[0], HIGH);
  digitalWrite(signal2[0], HIGH);
  digitalWrite(signal3[0], HIGH);
  digitalWrite(signal4[0], HIGH);
}
