#define in 9

void setup() {
  // put your setup code here, to run once:
  pinMode( in, OUTPUT);
  digitalWrite( in, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite( in, HIGH);
  delay( 1000);
  digitalWrite( in, LOW);
  delay( 5000);
}
