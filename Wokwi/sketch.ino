#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <Ultrasonic.h>

Servo myservo; 
Ultrasonic ultrasonic(13, 12); //pin trig, pin echo
int counter = 0;
bool flag = false;

char auth[] = "<YOUR_AUTH>";
char ssid[] = "Wokwi-GUEST";
char password[] = "";

void setup() {
  myservo.attach(5);  //pin servo
  pinMode(2, OUTPUT); //pin led
  pinMode(4, OUTPUT); //pin buzzer
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password, "blynk.cloud", 80); 
  myservo.write(0);
}

void loop() {

  int distance = ultrasonic.read(); 
  Blynk.run();
  
  if (distance == 10) {
    if(!flag) {
      counter++;
      flag = true;
    }
    digitalWrite(2, HIGH); //led menyala
    tone(4, 1000); //buzzer berbunyi
    delay(1000); //delay selama 1 detik
    noTone(4); //matikan buzzer
    myservo.write(90); //putar servo 90 derajat
  } else {
    digitalWrite(2, LOW); //matikan led
    myservo.write(0); //kembalikan servo ke posisi semula
    flag = false;
  }

  Blynk.virtualWrite(V0, counter);
  Serial.println(distance);
  Serial.println(flag);
}
