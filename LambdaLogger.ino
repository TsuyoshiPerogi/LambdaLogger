

/* Lambda Logger v1.0, Written by Tsuyoshi Perogi(hasherbasher@protonmail.com)
If you require notation to use software then you probably shouldn't be using this.

*/
#include <SD.h>
#include <arduino-timer.h>
#include <mcp_can.h>
#include <SPI.h>
#define standard 1  
#define txID 0x7DF 

auto timer = timer_create_default(); 
File dataFile = SD.open("datalog.txt", FILE_WRITE); 
String dataString = ""; 

const int chipSelect = 10; 

byte back2 = 0; 
unsigned int RPM = 100; 
  
byte back = 0; 
float Lambda; 
float AFER;
float Time = 0;


bool Datalog(void *){
    Time = (Time + .1);
    dataString += String(Time),",",String(RPM),",",String(Lambda) ;
    if (dataFile) { 
      dataFile.println(dataString); 
      Serial.println(dataString);
      
    }

}
byte lastStep = 0;

unsigned long rxId;
byte len;
byte rxBuf[8]; 
byte rxBuf2[8];

unsigned char txData[8] = {0x02, 0x01, 0x24, 0x55, 0x55, 0x55, 0x55, 0x55};  
unsigned char txData2[8] = {0x02, 0x01, 0x0C, 0x55, 0x55, 0x55, 0x55, 0x55}; 

MCP_CAN CAN0(10); 


void setup()  { 
  
  Serial.begin(115200);
  
  
  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) { 

    Serial.println("initialization failed. Things to check:");

    Serial.println("1. is a card inserted?");

    Serial.println("2. is your wiring correct?");

    Serial.println("3. did you change the chipSelect pin to match your shield or module?");

    Serial.println("Note: press reset after fixing your issue!");

    while (true);

  }

   Serial.println("initialization done.");
   


  
  if(CAN0.begin(MCP_STDEXT, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("OBD-2 Initialized Successfully!"); 
  else
    Serial.println("**Error Initializing OBD-2**");
  
  CAN0.setMode(MCP_NORMAL);  
  
 
 
   timer.every(100,Datalog); 

}

void loop()       { 
  
   
    if (back = 0 && back2 == 0) {
    CAN0.sendMsgBuf(txID, 8, txData);
    for(byte i=0;i<20;++i){     
    CAN0.readMsgBuf(&rxId, &len, rxBuf);   
     
     if(rxId == 0x7E8 && back == 0){
        Serial.print(rxId, HEX); 
        Serial.print("\t");
        for(byte i = 0; i<len; i++) 
        {
            Serial.print(rxBuf[i], HEX);
            
             
            Serial.print("\t");            
        }
        Serial.println();
        
        
        back=1;
     }
    }
    }
     if(back == 1 && back2 ==0) { 
     back2 =1;
     CAN0.sendMsgBuf(txID, 8, txData2);
     for(byte i=0;i<20;++i){     
     CAN0.readMsgBuf(&rxId, &len, rxBuf2); 
         if(rxId == 0x7E8){
              Serial.print(rxId, HEX);  
              Serial.print("\t");
              for(byte i = 0; i<len; i++)  
            {
               Serial.print(rxBuf2[i], HEX);
               Serial.print("\t");            
            }
              Serial.println();
              lastStep = 1;
                         
        }    

      }
     }
     
     if(back2 && lastStep){ //If Lambda and RPM 
              Lambda = (rxBuf[3]*256 + rxBuf[4])* 2/65536 ; 
              AFER = Lambda * 14.7;
              RPM = (rxBuf2[3]*256 + rxBuf2[4])/4; 
              back = 0;
              back2 = 0;
              lastStep = 0; 
        }

     while(1) {
              if(Time >= 30) {
               timer.cancel();
               dataFile.close();
               Time = 0;
              }
              if(Time == 0) {
               timer.tick();
              }
              
    }
}
    
