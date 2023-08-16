// ADC input is connected to GPIO 34, 35, 32 (Analog ADC1) 
// const int analogPin1 = 34;
// const int analogPin2

const int analogPins[3] = {34, 35, 34};  //this is the exact pin order - a1, a2, a3
const int NUM_OF_CHANNELS = 1;
int16_t pinValues[3];
unsigned char pinValueBytes[2];  //to send the analog values as a byte array using Serial.Write(buff, len)



const int8_t SYNC_WORD = 0xAA;  //sync word for separating multiple data packets in binary mode

void setup() {
  // Serial.begin(115200);
  // Serial.begin(1000000);  //gives sync error in 16-bit binary mode i.e. serial.write 
  Serial.begin(1500000);   
  delay(1000);
}

void SerialWriteInt16(int16_t n) {
  /* writes 16-bit integer value one byte at a time using Serial.write */
  unsigned char _bytes[2];
  int8_t _bitmask = 0xFF;
  int8_t _higherByte = (n >> 8) & _bitmask;
  int8_t _lowerByte = n & _bitmask;
  _bytes[0] = _higherByte;
  _bytes[1] = _lowerByte;
  // Serial.write((n >> 8) & 0xFF); // MSB first, Send the upper byte first, 0xFF is 8-bit bitmask
  // Serial.write((n & 0xFF)); // Send the lower byte
  // Serial.write(_higherByte);
  // Serial.write(_lowerByte);
  Serial.write(_bytes, 2);  //Serial.write(buf, len) //int16 MSB first mode  
}

void loop() {
  // Read ADC value
  // pinValue = analogRead(analogPin);
  
  for (int i = 0; i < NUM_OF_CHANNELS; i++) {
    pinValues[i] = analogRead(analogPins[i]);
  }	


  // arbitrary header
  Serial.write((uint8_t)0xAA);

  // Serial.write((uint8_t*)&height_m, sizeof(height_m));
  // Serial.write((uint8_t*)&velocity_ms, sizeof(velocity_ms));
  for (int i = 0; i < NUM_OF_CHANNELS; i++) {
    int data_ = pinValues[i];
    float data1 = (float)data_ + 5.0;
    float data2 = data1 - 10.0;
//    Serial.write((uint8_t*)&data_, sizeof((int)data_));
    Serial.write((uint8_t*)&(data1), sizeof(data1));
    Serial.write((uint8_t*)&(data2), sizeof(data1));
  }	

  // delay(0);
}
