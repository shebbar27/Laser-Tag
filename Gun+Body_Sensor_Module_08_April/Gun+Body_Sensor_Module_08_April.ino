
#include <VirtualWire.h>

#include <IRremote.h>

//Sniper
//pin 3 for IR emitter
IRsend My_Sender;
int swPullUp = 4;
int laser = 5;
int LEDpin = 6;
int transmit_pin = 10;
//Jacket
IRrecv irrecv(11);//, My_Receiver2(8);
//IRdecode My_Decoder1;
decode_results results;
unsigned int Buffer1[RAWBUF];
char a1,a2,a3,a4,a5,a6,b1,b2,b3,b4,b5,b6;
unsigned long value;
boolean hit = false;
char hitcount = 0;
char message[14];

void setup()
{  a1=a2=a3=a4=a5=a6=b1=b2=b3=b4=b5=b6=0;
  //Sniper
  pinMode(swPullUp,INPUT);
  pinMode(laser,OUTPUT);
  pinMode(LEDpin,OUTPUT);
  digitalWrite(laser,HIGH);
 digitalWrite(LEDpin,HIGH);
  //Jacket
  Serial.begin(9600);
 irrecv.enableIRIn();
 // My_Receiver1.enableIRIn();
  //My_Decoder1.UseExtnBuf(Buffer1);
  //My_Decoder2.UseExtnBuf(Buffer2);
 //RF link
 // vw_setup(2000);
}

void loop() {
    //Sniper
    if(hit == false){
      Serial.println("case1");
        digitalWrite(LEDpin,LOW);
        digitalWrite(laser,LOW);
    }
 if(digitalRead(swPullUp) && hit == false ){
	//My_Sender.send(SONY,0xaa2, 12);
     for (int i = 0; i < 3; i++) {
     My_Sender.sendSony(0xa90, 12); // Sony TV power code
    delay(40);}
     irrecv.enableIRIn();
     
      Serial.println("case2");
 //   My_Receiver1.enableIRIn();
       // My_Receiver2.enableIRIn();
        //signal for vibration motor
        //signal for beam laser
    }
   
    //Jacket
   // if(My_Receiver1.GetResults(&My_Decoder1))
    
  if (irrecv.decode(&results))
    {
    //Restart the receiver so it can be capturing another code
    //while we are working on decoding this one.
  //  My_Decoder1.decode();
    value =results.value;
    //My_Decoder1.DumpResults();
    Serial.println("sensor 1:");
    Serial.println(results.value, DEC); 
    points(value,10);
    irrecv.resume();
   // My_Receiver1.resume();
    }
    
    if(digitalRead(transmit_pin)){
      compose();
      transmit();
      
      Serial.println("case3");
    }
}


void points(int value, int add){
  
  switch(value){
    case 2721 : a1 = a1 + add ;
                 hit = true;
                 effect();
                 break;
    case 2722 : a2 = a2 + add;
                 hit = true;
                 effect();
                 message[2]++;
                 break;
    case 2723 : a3 = a3 + add;
                 hit = true;
                 effect();
                 break;
    case 2724 :a4 = a4 + add;
                 hit = true;
                 effect();
                 break;
    case 2725 :a5 = a5 + add;
                 hit = true;
                 effect();
                 break;
                 
    case 2726 :a6 = a6 + add;
                 hit = true;
                 effect();
                 break;
    case 2993 :b1 = b1 + add;
                 hit = true;
                 effect();
                 break;
    case 2994 :b2 = b2 + add;
                 hit = true;
                 effect();
                 break;
    case 2995 :b3 = b3 + add;
                 hit = true;
                 effect();
                 break;
    case 2996 :b4 = b4 + add;
                 hit = true;
                 effect();
                 break;
    case 2997 :b5 = b5 + add;
                 hit = true;
                 effect();
                 break;
                 
    case 2998 :b6 = b6 + add;
                 hit = true;
                 effect();
                 break;
    default:     Serial.println("Fuck you");
                 hit = false;
                 break;
    }
}
   
void effect(){
   digitalWrite(laser, HIGH);
   digitalWrite(LEDpin, HIGH);
   //signal for vibration motor
   //signal for beam laser
   delay(5000);
   hit = false;
   hitcount++;
}
void compose(){
  message[0]='1';
  message[1]=a1;
  message[2]=a2;
  message[3]=a3;
  message[4]=a4;
  message[5]=a5;
  message[6]=a6;
  message[7]=b1;
  message[8]=b2;
  message[9]=b3;
  message[10]=b4;
  message[11]=b5;
  message[12]=b6;
  message[13]=hitcount;
}
void transmit()
{
  vw_send((uint8_t*)message,strlen(message));
  vw_wait_tx();
}

