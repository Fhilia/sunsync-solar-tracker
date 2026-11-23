#include <Servo.h>

// Servo
Servo servoX;
Servo servoY;
const int X = 10;
const int Y = 9;
int posX = 90;  // Initial horizontal position (centered)
int posY = 90;  // Initial vertical position (centered)

// Photoresistor pins
const int ldrTopRight = A2;
const int ldrTopLeft = A3;
const int ldrBottomRight = A1;
const int ldrBottomLeft = A0;

// Values for photoresistors
int topRightValue;
int topLeftValue;
int bottomRightValue;
int bottomLeftValue;
const int threshold = 50;

void setup() {
  // Attach servos to pins
  servoX.attach(X);
  servoY.attach(Y);

  // Set initial positions
  servoX.write(posX);
  servoY.write(posY);

  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read photoresistor values
  topRightValue = analogRead(ldrTopRight);
  topLeftValue = analogRead(ldrTopLeft);
  bottomRightValue = analogRead(ldrBottomRight);
  bottomLeftValue = analogRead(ldrBottomLeft);

  // Calculate the horizontal and vertical differences
  int verticalDiff = (topRightValue + topLeftValue) - (bottomRightValue + bottomLeftValue);
  int horizontalDiff = (topRightValue + bottomRightValue) - (topLeftValue + bottomLeftValue);

  // Debugging: Print the sensor values and differences
  Serial.print("TR: "); Serial.print(topRightValue);
  Serial.print(" TL: "); Serial.print(topLeftValue);
  Serial.print(" BR: "); Serial.print(bottomRightValue);
  Serial.print(" BL: "); Serial.println(bottomLeftValue);
  Serial.print("Vertical Diff: "); Serial.println(verticalDiff);
  Serial.print("Horizontal Diff: "); Serial.println(horizontalDiff);


  // Adjust vertical position (up/down)
  if (abs(verticalDiff) > threshold) {
    if (verticalDiff < 0 && posY < 180) {  // More light on top (smaller value), move up
      posY--;
    } else if (verticalDiff > 0 && posY > 0) {  // More light on bottom (smaller value), move down
      posY++;
    }
    posY = constrain(posY, 0, 180);  // Ensure within servo range
    servoY.write(posY);
    Serial.print("Servo Y Position: "); Serial.println(posY);
  }

  // Adjust horizontal position (left/right)
  if (abs(horizontalDiff) > threshold) {
    if (horizontalDiff < 0 && posX < 180) {  // More light on left (smaller value), move left
      posX++;
    } else if (horizontalDiff > 0 && posX > 0) {  // More light on right (smaller value), move right
      posX--;
    }
    posX = constrain(posX, 0, 180);  // Ensure within servo range
    servoX.write(posX);
    Serial.print("Servo X Position: "); Serial.println(posX);
  }

  delay(80);  // Delay for smooth operation
}
