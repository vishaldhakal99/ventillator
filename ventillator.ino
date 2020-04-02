int area=100;

int solenoidPin1 = 4;
int solenoidPin2 = 5;//This is the output pin on the Arduino we are using
int flowPin = 2;    //This is the input pin on the Arduino
double flowRate;    //This is the value we intend to calculate. 
volatile int count; //This integer needs to be set as volatile to ensure it updates correctly during the interrupt process. 
void setup() {
  Serial.begin(9600);
  pinMode(solenoidPin1, OUTPUT);
  pinMode(solenoidPin2, OUTPUT);  //Sets the pin as an output
  pinMode(flowPin, INPUT);           //Sets the pin as an input
  attachInterrupt(0, Flow, RISING);  //Configures interrupt 0 (pin 2 on the Arduino Uno) to run the function "Flow" 
  pinMode(A0, INPUT);// Reading Pressure
}

void loop(){
  count = 0;      // Reset the counter so we start counting from 0 again
  interrupts();   //Enables interrupts on the Arduino
  delay (1000);   //Wait 1 second 
  noInterrupts(); //Disable the interrupts on the Arduino
  
  flowRate = (count * 2.25);        //Take counted pulses in the last second and multiply by 2.25mL 
  flowRate = flowRate * 60;         //Convert seconds to minutes, giving you mL / Minute
  flowRate = flowRate / 1000;
  float peakPressure = 40.0;
  float peep = 5.0;
  float pressure_val;
  float timee;
  double voloume_in = flowRate * area * timee;
  double voloume_out = flowRate * area * timee;
  if(voloume_in<=voloume_out){
    pressure_val = (analogRead(A0) * (5.0 / 1023.0) * 10.0);
  
    if(pressure_val >= peakPressure){
        digitalWrite(solenoidPin1, LOW);    //Switch Solenoid valve1 close
        digitalWrite(solenoidPin2, HIGH);    //Switch Solenoid valve2 open
        
    }else{
      while (pressure_val < peep) {
        pressure_val = (analogRead(A0) * (5.0 / 1023.0) * 10.0);
        Serial.println(pressure_val);
        // loop  to read pressure value until reach required  pressure with analog input A0
      }
      digitalWrite(solenoidPin1, HIGH);    //Switch Solenoid valve1 open
      digitalWrite(solenoidPin2, LOW);    //Switch Solenoid valve2 close
      voloume_in = ;
     }
    }else{
      digitalWrite(solenoidPin1, LOW);    //Switch Solenoid valve1 close
      digitalWrite(solenoidPin2, HIGH); 
      voloume_out = ;
  }
  
}
void Flow()
{
   count++; //Every time this function is called, increment "count" by 1
}
