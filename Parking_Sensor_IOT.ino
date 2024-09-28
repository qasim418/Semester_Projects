// Parking Sensor IoT Device
// This code utilizes an ultrasonic sensor to detect distances 
// and provides visual and audible alerts using LEDs and a buzzer.

const int trigPin = 9;      // Trigger pin for ultrasonic sensor
const int echoPin = 10;     // Echo pin for ultrasonic sensor
const int blueLEDPin = 5;   // Pin for blue LED
const int greenLEDPin = 6;  // Pin for green LED
const int redLEDPin = 7;    // Pin for red LED
const int buzzerPin = 8;    // Pin for buzzer

void setup() {
    Serial.begin(9600);           // Initialize serial communication at 9600 baud rate
    pinMode(trigPin, OUTPUT);     // Set trigPin as OUTPUT
    pinMode(echoPin, INPUT);      // Set echoPin as INPUT
    pinMode(blueLEDPin, OUTPUT);  // Set blueLEDPin as OUTPUT
    pinMode(greenLEDPin, OUTPUT); // Set greenLEDPin as OUTPUT
    pinMode(redLEDPin, OUTPUT);   // Set redLEDPin as OUTPUT
    pinMode(buzzerPin, OUTPUT);   // Set buzzerPin as OUTPUT
}

void loop() {
    int distance = measureDistance(); // Get the distance from the ultrasonic sensor

    // Print distance to the serial monitor (uncomment if needed)
    // Serial.print("Distance: ");
    // Serial.print(distance);
    // Serial.println(" cm");

    // Check distance and trigger LEDs and buzzer accordingly
    if (distance < 20) {
        blinkLEDWithSound(redLEDPin, 500);  // Blink red LED with sound for close proximity
    } else if (distance < 50) {
        blinkLEDWithSound(greenLEDPin, 300); // Blink green LED with sound for moderate proximity
    } else if (distance < 80) {
        blinkLED(blueLEDPin);  // Blink blue LED for distant proximity
    } else {
        turnOffLEDsAndBuzzer(); // No obstacle, turn off all indicators
    }

    delay(100); // Delay for stability; adjust as needed
}

// Function to measure distance using ultrasonic sensor
int measureDistance() {
    // Trigger the ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the duration of the echo
    long duration = pulseIn(echoPin, HIGH);
    // Calculate distance in centimeters
    return duration * 0.034 / 2;
}

// Function to blink an LED without sound
void blinkLED(int ledPin) {
    turnOffLEDsAndBuzzer(); // Turn off other LEDs before turning on a new one
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
}

// Function to blink an LED with sound from the buzzer
void blinkLEDWithSound(int ledPin, int soundFrequency) {
    turnOffLEDsAndBuzzer(); // Turn off other LEDs before turning on a new one
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, soundFrequency); // Sound the buzzer at specified frequency
    delay(100);
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin); // Stop the buzzer
    delay(100);
}

// Function to turn off all LEDs and buzzer
void turnOffLEDsAndBuzzer() {
    digitalWrite(blueLEDPin, LOW);
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
    noTone(buzzerPin); // Turn off the buzzer
}
