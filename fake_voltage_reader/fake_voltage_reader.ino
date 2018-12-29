/* Sudo voltage reader
 * 
 * When I press the button connected to pin 2, I will read
 * read the analog value from the pin A0.
 * 
 */
const int ain_pin = A0;
const int btn_pin = 2;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(btn_pin, INPUT_PULLUP);

}

void loop() {
  int btn_read = digitalRead(btn_pin);

  if (btn_read == LOW) {
    int val = analogRead(ain_pin);
    float voltage = val * 5.0 / 1023;
    Serial.println(voltage); // will read really fast, probably should add debouncing
  }
}
