/* symax_rx.ino -- An arduino sketch to test the protocol symax
 *
 */

#include "SPI.h"
#include "symax_protocol.h"

nrf24l01p wireless; 
symaxProtocol protocol;

unsigned long time = 0;

void setup() {

  Serial.begin(115200);


  // SS pin must be set as output to set SPI to master !
  pinMode(SS, OUTPUT);

  // Set CE pin to 10 and CS pin to 9
  wireless.setPins(7,8);
  
  // Set power (PWRLOW,PWRMEDIUM,PWRHIGH,PWRMAX)
  wireless.setPwr(PWRLOW);
  
  protocol.init(&wireless);
  
  time = micros();
  Serial.println("Start");
  
}

rx_values_t rxValues;

unsigned long newTime;

void loop() 
{
  time = micros();
  uint8_t value = protocol.run(&rxValues); 
  newTime = micros();
   
  switch( value )
  {
    case  NOT_BOUND:
        Serial.println("Not bound");
    break;

    case  BIND_IN_PROGRESS:
        Serial.println("Bind in progress");
    break;
    
    case BOUND_NEW_VALUES:
      Serial.print(newTime - time);
      Serial.print(" :\t");Serial.print(rxValues.throttle);
      Serial.print("\t"); Serial.print(rxValues.yaw);
      Serial.print("\t"); Serial.print(rxValues.pitch);
      Serial.print("\t"); Serial.print(rxValues.roll);
      Serial.print("\t"); Serial.print(rxValues.trim_yaw);
      Serial.print("\t"); Serial.print(rxValues.trim_pitch);
      Serial.print("\t"); Serial.print(rxValues.trim_roll);
      Serial.print("\t"); Serial.print(rxValues.video);
      Serial.print("\t"); Serial.print(rxValues.picture);
      Serial.print("\t"); Serial.print(rxValues.highspeed);
      Serial.print("\t"); Serial.println(rxValues.flip);
      //time = newTime;
      
    break;

    case BOUND_NO_VALUES:
      //Serial.print(newTime - time); Serial.println(" : ----");
    break;

    default:
    break;

  }

}
