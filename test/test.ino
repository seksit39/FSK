#include <Wire.h>
#include <Adafruit_MCP4725.h>

#define defaultFreq 1700
#define freq0 500
#define freq1 750
#define freq2 1000
#define freq3 1250

  Adafruit_MCP4725 dac;
  
  uint16_t a = 0;
  uint16_t input[1000];
  const uint16_t sine[4]  = {2048,4095,2048,0};   // At 1700 Hz     
  int delay0,delay1,delay2,delay3;
  int countData = 0;
  
void setup(void) {
  
  Serial.begin(115200);                         // set buadrate serial
  dac.begin(0x62);                              // set to default 

  delay0 = 250*(1000/freq0 - 1000/defaultFreq);
  delay1 = 250*(1000/freq1 - 1000/defaultFreq);
  delay2 = 250*(1000/freq2 - 1000/defaultFreq);
  delay3 = 250*(1000/freq3 - 1000/defaultFreq);

  Serial.print("delay0 is ");
  Serial.println(delay0);
  Serial.print("delay1 is ");
  Serial.println(delay1);
  Serial.print("delay2 is ");
  Serial.println(delay2);
  Serial.print("delay3 is ");
  Serial.println(delay3);
  
}

void loop(void) {
      countData = 0;
      if(Serial.available() > 0){               // for get input
        while(Serial.available() > 0){
            input[countData] = Serial.parseInt();
            countData++;
        }
        Serial.print(countData is ");
        Serial.println(countData);
        
        Serial.print("Data is ");
        for(int i=0 ; i<countData ; i++){
            Serial.print(input[countData]);
            Serial.print(" ");
        }
        Serial.println();

        if(countData%2 != 0){
          Serial.println("Data must be even please try again");
          break;
        }
        
        //for(int i=0 ; i<1000 ; i++)
        for(int k=0 ; k<countData ; k+=2){
          
          if(input[k] == 0){                
            if(input[k+1] == 0){                 // for input 00 - 500 Hz
              for(int j=0 ; j<3 ; j++)
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(delay0); //350
                }
            }
              
             else if(input[k+1] == 1){           // for input 01 - 750 Hz
              for(int j=0 ; j<4 ; j++)
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(delay1); //185
                }                
             }
          }
          else if(input[k] == 1){               // for input 10 - 1000 Hz
            if(input[k+1] == 0){
              for(int j=0 ; j<5 ; j++)
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(delay2); // 100 
                }
            }
            else if(input[k+1] == 1){            // for input 11 - 1250 Hz
              for(int j=0 ; j<6 ; j++)      
                for(int i=0 ; i<4 ; i++){
                  dac.setVoltage(sine[i], false);
                  delayMicroseconds(delay3); // 50 
                }             
            }
        } 
      } 
     }
}

