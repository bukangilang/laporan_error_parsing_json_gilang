#include <ArduinoJson.h>

int lamp1 = 11;
int lamp2 = 12;
int lamp3 = 13;
String databaca;
const int BAUD_RATE = 9600;
 
void setup() {
pinMode(lamp1, OUTPUT); 
pinMode(lamp2, OUTPUT);
pinMode(lamp3, OUTPUT);
Serial.begin(BAUD_RATE);
Serial.setTimeout(10);
while (!Serial) continue;
}

void loop()
{
if (Serial.available());
String input = Serial.readStringUntil('\n');
{

//Parsing JSON
StaticJsonDocument<100> doc;
DeserializationError error = deserializeJson(doc, input);

if (error) {
//Serial.print(F("deserializeJson() failed: "));
Serial.println("Error parsing JSON");
return;
}

const char* command = doc["command"];
if (strcmp(command, "matikan") == 0) {
      // Lakukan aksi sesuai dengan perintah "matikan"

      // Kirim balasan ke Node.js
      StaticJsonDocument<100> response;
      response["response"] = "pesan ok";
      serializeJson(response, Serial);
      Serial.println();
}

char buf[40];
sprintf(buf, "{\"sensor1\":%s}",command );
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
