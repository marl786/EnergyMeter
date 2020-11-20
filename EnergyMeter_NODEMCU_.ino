#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance


  const int analogInPin = A0;
  int mVperAmp = 100; // use 100 for 20A Module and 66 for 30A Module
  int RawValue= 0;
  int voltageValue= 0;
  int ACSoffset = 0; 
  double Voltage = 0;
  double Amps = 0;
  float inst_power=0; 
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFactor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable
  int i,n=5; 
  float sum_inst_power,real_power,inst_voltage,squared_voltage;
  float mean_square_voltage,sum_squared_voltage,root_mean_square_voltage,squared_current,inst_current;
  float sum_squared_current=0;
  float mean_square_current,root_mean_square_current,apparent_power,power_factor;
  int frequency = 50;
  int outputValue = 0;

  
  void setup()
{ 
  Serial.begin(9600);
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
}

void loop()
{

 RawValue = analogRead(analogInPin);
 Voltage = (RawValue / 1024.0) * 5; // Gets you mV
 Amps = ((Voltage - ACSoffset) / mVperAmp);

 Serial.print("\t V = "); // shows the voltage measured 
 Serial.print(Voltage,3); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("\t Amps = "); // shows the voltage measured 
 Serial.println(Amps,3); // the '3' after voltage allows you to display 3 digits after decimal point
 Serial.print("\t Raw Value = "); // shows the voltage measured
 Serial.println(RawValue,3); // the '3' after voltage allows you to display 3 digits after decimal point
  
  inst_power = Voltage*Amps;
  sum_inst_power += inst_power;
  squared_voltage = Voltage*Voltage;
  sum_squared_voltage += squared_voltage;


  voltageValue = analogRead(analogInPin);

  
  squared_current = Amps*Amps;
  sum_squared_current += squared_current;
  mean_square_current = sum_squared_current/n;
  root_mean_square_current = sqrt(mean_square_current);
  
  real_power = sum_inst_power / n;
  mean_square_voltage = sum_squared_voltage / n;
  root_mean_square_voltage = sqrt(mean_square_voltage);
  apparent_power = root_mean_square_voltage * root_mean_square_current;
  power_factor = real_power / apparent_power;
  Serial.print("\t Apparent Power = "); // shows the voltage measured 
  Serial.print( apparent_power,3);
  Serial.print("\t Power Factor = "); // shows the voltage measured 
  Serial.print( power_factor,3);
  Serial.print("\t Frequency = "); // shows the voltage measured 
  Serial.print( frequency);
  Serial.print("\t Vrms = "); // shows the voltage measured 
  Serial.print( root_mean_square_voltage ,3);
  Serial.print("\t Irms = "); // shows the voltage measured 
  Serial.print( root_mean_square_current ,3);
  Serial.print("\t volatge value = ");
  Serial.print(voltageValue);
  outputValue = map(voltageValue, 0, 1024, 0, 255);
  Serial.print(outputValue);
  delay(2000); 
  
     
}
