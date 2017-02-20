/*
sine delay
none       1736 Hz
20  micros 1500 Hz
50  micros 1250 Hz
100 micros 1000 Hz
190 micros 750  Hz
350 micros 500  Hz
*/
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

  #define defaultFreq 1700
  #define freq0 500
  #define freq1 750
  #define freq2 1000
  #define freq3 1250

  
  uint16_t a = 0;
  uint16_t input[4] = {0,0,0,0};
  const uint16_t sine[4]  = {2048,4095,2048,0};   // At 1700 Hz     
  int del = 0;
  int c00 = 0;
  int c01 = 0;
  int c10 = 0;
  int c11 = 0;
  int delay0,delay1,delay2,delay3;
  
  Adafruit_MCP4725 dac;
  
void setup(void) {
  
  Serial.begin(115200);                         // set buadrate serial
  dac.begin(0x62);                              // set DAC default 

  delay0 = (1000000/freq0 - 1000000/defaultFreq)/4;   // caculate period/4 of sinewave
  delay1 = (1000000/freq1 - 1000000/defaultFreq)/4;
  delay2 = (1000000/freq2 - 1000000/defaultFreq)/4;
  delay3 = (1000000/freq3 - 1000000/defaultFreq)/4;
  
}

void loop(void) {

      if(Serial.available() > 0){               // for get input

        int in = Serial.parseInt();             // get Dec from Serial
        for(int i=0 ; i<4 ; i++){               // 4 time of loop for a byte input
          input[i] = in & 3;                    // and bit b0000 0011 and save to array
          in >>= 2;                             // shift bit right 2 bit
        }
        
        //for(int i=0 ; i<10 ; i++)
        for(int k=3 ; k>=0 ; k--){
          
            if(input[k] == 0){                    // for input 00 - 500 Hz
                //Serial.println("out 00");
                for(int j=0 ; j<2 ; j++)
                  for(int i=0 ; i<4 ; i++){
                    dac.setVoltage(sine[i], false);
                    delayMicroseconds(delay0);    //360
                  }
             }
              
             else if(input[k] == 1){              // for input 01 - 750 Hz
                //Serial.println("out 01");
                for(int j=0 ; j<3 ; j++)
                  for(int i=0 ; i<4 ; i++){
                    dac.setVoltage(sine[i], false);
                    delayMicroseconds(delay1);    //190
                   }                
             }
 
              else if(input[k] == 2){             // for input 10 - 1000 Hz
                 //Serial.println("out 10");
                 for(int j=0 ; j<4 ; j++)
                    for(int i=0 ; i<4 ; i++){
                      dac.setVoltage(sine[i], false);
                      delayMicroseconds(delay2);  //100 
                    }
              }
              
              else if(input[k] == 3){            // for input 11 - 1250 Hz
                 //Serial.println("out 11");
                 for(int j=0 ; j<5 ; j++)      
                    for(int i=0 ; i<4 ; i++){
                      dac.setVoltage(sine[i], false);
                      delayMicroseconds(delay3); //50
                    }             
              }
        } 
      } 
      dac.setVoltage(0, false);                 // for don't send
}
