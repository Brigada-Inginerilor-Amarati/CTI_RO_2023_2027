const int motorPin = 6;
const int echoPin = 11;
const int trigPin = 12;
const int ledPin = 8;

void setup() {
    Serial.begin(9600);
    pinMode(motorPin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    float distance = getDistance();

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Stop the motor and turn off the LED if the distance is less than 15 cm
    if (distance < 15) {
        analogWrite(motorPin, 0);  // Stop the motor
        digitalWrite(ledPin, LOW); // Turn OFF the LED
        Serial.println("Motor stopped! LED OFF");
    } else {
        // Map distance to motor speed
        int speed = map(distance, 15, 50, 150, 255);
        speed = constrain(speed, 150, 255);

        Serial.print("Motor Speed: ");
        Serial.println(speed);

        analogWrite(motorPin, speed);   // Run the motor
        digitalWrite(ledPin, HIGH);     // Turn ON the LED
    }

    delay(500);
}

float getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    float echoTime = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
    return echoTime / 58.2; // Convert to cm
}
