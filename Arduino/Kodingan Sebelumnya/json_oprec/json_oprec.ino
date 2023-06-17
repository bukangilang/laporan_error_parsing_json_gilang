#include <ArduinoJson.h>

int lamp1 = 11;
int lamp2 = 12;
int lamp3 = 13;
String databaca;
 
void setup() {
pinMode(lamp1, OUTPUT); 
pinMode(lamp2, OUTPUT);
pinMode(lamp3, OUTPUT);
Serial.begin(9600);
Serial.setTimeout(10);
while (!Serial) continue;
}

StaticJsonDocument<200> doc;

char json[] =
"{\"bacadata\":\"ada data\", \"sensor2\":\"16\"}";
DeserializationError error = deserializeJson(doc, json);

const char* bacadata = doc["sensor2"];

void loop()
{
if (Serial.available()>0);
{

if (error) {
Serial.print(F("deserializeJson() failed: "));
Serial.println(error.f_str());
return;
}
char buf[40];
sprintf(buf, "{\"sensor1\":%s}",bacadata );
Serial.print(buf);

//char input = Serial.parseInt();
String bacadata = Serial.readString();
bacadata.trim();
//(bacadata != -1){
//Serial.println("ada data");
//}

if (bacadata =="a") {databaca="a";}
if (bacadata =="b") {databaca="b";}
if (bacadata =="c") {databaca="c";}
 Serial.println(bacadata);
if(databaca=="a")
running: //LED akan berjalan pada mode running
{
digitalWrite(lamp1, HIGH);
delay(250);
digitalWrite(lamp1, LOW);
delay(250);
digitalWrite(lamp2, HIGH);
delay(250);
digitalWrite(lamp2, LOW);
delay(250);
digitalWrite(lamp3, HIGH);
delay(250);
digitalWrite(lamp3, LOW);
delay(250);
Serial.println("LED mode running");
loop();
goto running;
}

if(databaca=="b")
flipflop: // LED akan berjalan pada mode flip flop
{
digitalWrite(lamp1, LOW);
digitalWrite(lamp2, LOW);
digitalWrite(lamp3, LOW);
delay(500);
digitalWrite(lamp1, HIGH);
digitalWrite(lamp2, HIGH);
digitalWrite(lamp3, HIGH);
delay(500);
Serial.println("LED mode flip flop");
loop();
goto flipflop;
}
 
if(databaca=="c")
modeoff: // Semua LED akan off
{
digitalWrite(lamp1,LOW);
digitalWrite(lamp2,LOW);
digitalWrite(lamp3,LOW);
delay(1000);
Serial.println("LED mode off");
loop();
goto modeoff; }
}

if(Serial.available() > 0);
    {
      char ReaderFromNode;
      ReaderFromNode = (char) Serial.read();
      convertToState(ReaderFromNode);
    }
  delay(1000); 
}

void convertToState(char chr) {
  if(chr=='o'){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100); 
  }
  if(chr=='f'){
    digitalWrite(LED_BUILTIN, LOW);
    delay(100); 
  }
}
