#include <Esplora.h>
//Transmitter

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver(2000, 3, 11, 10, false );

//Multitasking Non Blocking graphics
long previousMillis = 0;  //Reference Millis
long period_time = 40;          //Frames per second Measurement

//----------------------------------//
//---------Joystick Manager----------//
//----------------------------------//
uint8_t X_offset = 50;
uint8_t Y_offset = 50;

uint8_t X_level = 100;
uint8_t Y_level = 100;

//----------------------------------//
//---------Buttons Manager----------//
//----------------------------------//


//----------------------------------//
void setup()
{
    Serial.begin(9600);    // Debugging only
    Serial.println("Radio Esplora");
    pinMode( 11, OUTPUT );
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
  readings();

}

void readings(){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > period_time) {
      previousMillis = currentMillis;

      readJoystick();

      readButtons();

      readSlider();
  }
}


void readJoystick(){
  int X, Y;
  
  X = Esplora.readJoystickX();
  Y = Esplora.readJoystickY();
  int Xvalue, Yvalue;
  String joystickmsg;
  
  if( abs(X) > X_offset ){
     Xvalue = map( X,-512,512,-X_level,X_level );
     sendMessage("Data X" );
  }

   if( abs(Y) > Y_offset ){
     Yvalue = map( X,-512,512,-Y_level,Y_level);
     sendMessage("Data Y" );
  }
}

void readButtons(){


  
}

void readSlider(){
  
}

void sendMessage(char *msg ){

    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    //delay(100);
}
