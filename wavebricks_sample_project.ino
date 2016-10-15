// Your key as hex is
// 89bc8f6d0719e8445392dd8d2e50018f
// Use the following key in Arduino IDE

unsigned char my_key[] = {
  0x89, 0xbc, 0x8f, 0x6d, 0x07, 0x19, 0xe8, 0x44, 0x53, 0x92, 0xdd, 0x8d,
  0x2e, 0x50, 0x01, 0x8f
};

unsigned int my_key_len = 16;

#define lora PUT_HERE_SERIAL_PORT_OF_LORA_XBEE_SHIELD

#define BEE_VCC PUT_HERE_PIN_ID_OF_VCC_PIN_FOR_XBEE_SHIELD
#define Serial PUT_HERE_SERIAL_PORT_FOR_DEBUGGING

#include <RnBee.h>
#include <StgProto.h>

RnBee rnb(BEE_VCC, &Serial1);
StgProto radio;

void setup()
{
  while ((!SerialUSB) && (millis() < 10000));

  rnb.setLogSerial((HardwareSerial*)&SerialUSB);
  radio.setLogSerial((HardwareSerial*)&SerialUSB);

  SerialUSB.begin(57600);

  SerialUSB.println("Wavebricks sample Arduino project");

  rnb.setup();
  radio.setDeviceAddress(0,0,1);
}

void loop()
{
  unsigned char rawData[] = "{\"a\":1}";
  unsigned char sendData[256];

  uint16_t len = radio.computePayload(rawData,7,sendData,256);
  rnb.sendRawPayload(sendData,len);

  delay(60000);
}
