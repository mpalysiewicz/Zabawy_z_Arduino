int przycisk = 2;
int led = 3; 
int zakres = 5;
int i = 0;

void setup() { 
  Serial.begin(9600);
  pinMode(przycisk, INPUT_PULLUP); 
  pinMode(led, OUTPUT);
}

void loop() {

  int stanPrzycisku = digitalRead(przycisk);
  if(stanPrzycisku == 0){
    for(i = 0; i<=255; i+=zakres){ 
      Serial.println(i);
      analogWrite(led, i ); 
      delay(20);
    }
  for(i = 255; i>=0; i-=zakres){
    Serial.println(i);
      analogWrite(led, i );
      delay(20); 
    }
  }
  Serial.println(stanPrzycisku);
  delay(100);
}
