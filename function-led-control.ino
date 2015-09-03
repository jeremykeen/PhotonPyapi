// This #include statement was automatically added by the Particle IDE.
#include "InternetButton/InternetButton.h"

// -----------------------------------
// Controlling LEDs over the Internet
// -----------------------------------

// First, let's create our "shorthand" for the pins
// Same as in the Blink an LED example:
// led1 is D0, led2 is D7

int led1 = D0;
int led2 = D7;

// Last time, we only needed to declare pins in the setup function.
// This time, we are also going to register our Spark function
InternetButton b = InternetButton();

bool rainbow_mode = false;
//setup
void setup()
{

 b.begin();
 b.allLedsOn(0,128,0);
 // We are also going to declare a Spark.function so that we can turn the LED on and off from the cloud.
 Spark.function("led",ledToggle);
 // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.

}


// Last time, we wanted to continously blink the LED on and off
// Since we're waiting for input through the cloud this time,
// we don't actually need to put anything in the loop

void loop()
{
 // Nothing to do here
}

// We're going to have a super cool function now that gets called when a matching API request is sent
// This is the ledToggle function we registered to the "led" Spark.function earlier.


int ledToggle(String command) {
  /* Spark.functions always take a string as an argument and return an integer.
  Since we can pass a string, it means that we can give the program commands on how the function should be used.
  In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
  Then, the function returns a value to us to let us know what happened.
  In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
  and -1 if we received a totally bogus command that didn't do anything to the LEDs.
  */

  if (command=="yellow") {
      b.allLedsOn(255,255,0);
      return 1;
  }
  else if (command=="green") {
        b.allLedsOn(0,128,0);
      return 1;
  }
  else if (command=="red") {
      b.allLedsOn(255,0,0);
      return 1;
  }
  else if (command=="rainbow") {
      //Enable rainbox mode
      b.rainbow(20);
      rainbow_mode = true;
      //delay(10000);
      //b.allLedsOff();
      return 1;
  }
  else if (command=="off") {
      b.allLedsOff();
      rainbow_mode = false;
      return 0;
  }
  else {
      return -1;
  }
}
