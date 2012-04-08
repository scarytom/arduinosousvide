#include <OneWire.h>

const unsigned int  PIN_TEMPPROBE = 10;
const unsigned int  INTERVAL = 700;

OneWire  ds(PIN_TEMPPROBE);
unsigned long previousMillis = 0;

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  unsigned long currentMillis = millis();
  
  if (currentMillis < previousMillis) {
    previousMillis = 0;
  }
  
  if(currentMillis - previousMillis > INTERVAL) {
    previousMillis = currentMillis;
    Serial.println(temperature(0));
  }
}

float temperature(byte loggingEnabled) {
  byte i;
  byte present = 0;
  byte data[12];
  
  ds.reset();
  ds.skip();
  ds.write(0x44);
  present = ds.reset();
  ds.skip();    
  ds.write(0xBE);

  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  
  if (loggingEnabled) {
    Serial.print("  Data = ");
    Serial.print(present,HEX);
    Serial.print(" ");
    for ( i = 0; i < 9; i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.print(" CRC=");
    Serial.println(OneWire::crc8(data, 8), HEX);
  }
  
  return ((data[1] << 8) + data[0]) / 16.0;
}
