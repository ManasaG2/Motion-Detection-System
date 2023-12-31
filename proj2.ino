#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int sensor = A1; // Assigning analog pin A1 to variable 'sensor'
float TempC; //variable to store temperature in degree Celsius
//float TempF; //variable to store temperature in Fahreinheit
float Vout; //temporary variable to hold sensor reading

int calibrationTime = 30;
int led = 13;                // the pin that the LED is atteched to
int Psensor = 9;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
int count = 0;


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(Psensor, INPUT);    // initialize sensor as an input
  Serial.print("calibrating sensor ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(1000);

  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Patient Care");
  delay(2000); // Keep the words on screen for two seconds
  lcd.clear(); // clear the screen for writing anything else
  // Begin serial communication at a baud rate of 9600
}

void loop() {

  { val = digitalRead(Psensor);   // read sensor value
    if (val == HIGH) {           // check if the sensor is HIGH
      digitalWrite(led, HIGH);   // turn LED ON
      delay(100);                // delay 100 milliseconds

      if (state == LOW) {
        count = count + 1;
        lcd.setCursor(0, 1);
        lcd.print("Movements= ");
        lcd.print(count);
        delay(500);
        state = HIGH;       // update variable state to HIGH
      }
    }
    else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds

      if (state == HIGH) {
        state = LOW;       // update variable state to LOW
      }
    }
  }
  { Vout = analogRead(sensor);
    Vout = (Vout * 5000) / 1023;
    TempC = Vout / 10; // Storing value in Degree Celsius
    lcd.setCursor(0, 0);
    lcd.print("Degree C= ");
    lcd.print(TempC);
    delay(5000); //Delay of 1 second for ease of viewing in serial monitor
  }


}
