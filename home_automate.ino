#define BLYNK_PRINT Serial
#include<Servo.h>
#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLin7g7sK4"
#define BLYNK_DEVICE_NAME "home automate"
#define BLYNK_AUTH_TOKEN "Vif18qL46SajaxNqn4PjBDdanz0FMF20"

#define IR D5
bool ir;
Servo servo;
char auth[]=BLYNK_AUTH_TOKEN;
char ssid[]="Aanchal phone";
char pass[]="";

BLYNK_WRITE(V0)
{
  digitalWrite(D0,param.asInt());
}
BLYNK_WRITE(V1)
{
  digitalWrite(D2,param.asInt());
}
BLYNK_WRITE(V2)
{
  int key =param.asInt();
  if(key==1) //motor on
  {
    servo.write(180); //180 degree turn
    delay(500); //half second wait
    servo.write(0); // back to normal
    delay(1000); // 1 sec gap next button on off
  }
}
void setup() {
  
  pinMode(D0,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(IR,INPUT);
  servo.attach(2); //D4 
  Blynk.begin(auth,ssid,pass,"blynk.cloud",80);
}

void loop() {
  Blynk.run();
  static int set=0;
  ir = digitalRead(IR);
  if(ir==0) //step down ir i.e hand present
  {
    Serial.println("present!!");
    Serial.println(set);
   
    if (set==0) //lights off
      {
        digitalWrite(D0,1);
        digitalWrite(D2,1);
        set=1;
        servo.write(180);
        delay(300);
        servo.write(0);
        delay(300);  
      }
    else
      {
        digitalWrite(D0,0);
        digitalWrite(D2,0);
        Blynk.email("home status","all lights are off !!!");
        set=0;
        //servo
        servo.write(0);
        delay(300);
       }
  }
else
  {
    Serial.println("not present");
    if(set==1)
        {
          servo.write(180);
          delay(300);
          servo.write(0);
          delay(300);
        }
        else
        {
          //do nothing
        }
  }
}
