const int joyH = 1;        // L/R Parallax Thumbstick
const int joyV = 2;        // U/D Parallax Thumbstick

void setup() {
  // Inizialize Serial
 // Serial.begin(9600);
}
void loop(){

    // Display Joystick values using the serial monitor
    outputJoystick();
    
    delay(200);                                      

}
void outputJoystick(){

    Serial.print(analogRead(joyH));
    Serial.print ("---"); 
    Serial.print(analogRead(joyV));
    Serial.println ("----------------");
}
