// Recieve FSK


int input,max,prev,currentTime,prevTime,period,cout = 0,totalTime = 0;
float currentFrequency,prevFrequency;
boolean check = false;

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))             // this for increase analogRead Speed
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

int c00 = 0,                                                    // for count number of data
    c01 = 0,
    c10 = 0,
    c11 = 0;

void setup(void) 
{
  sbi(ADCSRA,ADPS2) ;                                           // this for increase analogRead Speed
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  Serial.begin(115200);                                         // set buadrate of serial
}

void loop(void) 
{   
    input = analogRead(A0);                                     // read signal from pin A0
    
    if(input-prev>30 && check==false){                          // if signal is rising
      max = 0;                                                  // change max value to zero
      check = true;                                             // assign check is true
    }
    if(input>max){                                              // set max input
      max=input;
    }  
    if(max-input > 50 && check == true){                        // if signal is amplitude
      currentTime = micros();                                   // get time from in microsecond
      period =  currentTime - prevTime;                         // calculate period
      currentFrequency = 1000000/period;                        // calculate frequency
      prevFrequency = currentFrequency;
      prevTime = currentTime;
      
      //Serial.println(currentFrequency);                       // for debug frequency

      if(1125 < currentFrequency && currentFrequency <= 1375)   // if signal frequency is between 1125 to 1375 Hz
         c11++;                                                 // count up c11
      if(875 < currentFrequency && currentFrequency <= 1125)    // if signal frequency is between 875 to 1125 Hz
         c10++;
      if(625 < currentFrequency && currentFrequency <= 875)     // if signal frequency is between 625 to 875 Hz
         c01++;  
      if(375 < currentFrequency && currentFrequency <= 625)     // if signal frequency is between 375 to 625 Hz
         c00++;   
            
      if(c11 >= 5 || c10 >= 4 ||  c01 >= 3 || c00 >= 2){        // display data
        if(c11 == 5)                                            // if c11 = 5 
          Serial.print("1 1 ");                                 // print data or do other
        if(c10 == 4)
          Serial.print("1 0 ");                                 // print data
        if(c01 == 3)
          Serial.print("0 1 ");                                 // print data
        if(c00 == 2)
          Serial.print("0 0 ");                                 // print data 
          
        prevTime = 3000;                                        // set previous time for skip fuction count data
        c11 = 0;
        c10 = 0;
        c01 = 0;
        c00 = 0;
        cout++;
      }
        
      if(cout == 5){                                            // if print data for 5 time
        Serial.println();                                       // send /n to serial
        cout = 0;                                               // change count is zero 
      } 
      
      check = false;                                            // change statement for do this 1 time per a signal
    } 
    prev = input;                                               // save previos state
}

