

//Connect the Receiver data pin to Arduino pin 11

#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
int ledPin=13;//led on pin 13 is ON except when bot is stationary
uint8_t matrix[12][14];

void setup()
{
 Serial.begin(9600);//Initialise the serial connection debugging
pinMode(ledPin,OUTPUT);
 vw_setup(2000); // Bits per sec
 vw_rx_start(); // Start the receiver
 
}
void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  int i;

  Serial.print("Got: ");//debugging

  for (i = 0; i < buflen; i++)
  {
  Serial.print(buf[i],HEX);
 // delay(100);
  // Serial.print(buf[i],HEX);//You may also use integer values debugging
    Serial.print(' ');// debugging
  
            matrix[(buf[0]-1)][i]=buf[i];
            }
  Serial.println();
  if (buf[0]==1)//Stationary
          {
            matrix[(buf[0]-1)][0]=1;
            }
          }
          
}

