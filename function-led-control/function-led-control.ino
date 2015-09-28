// This #include statement was automatically added by the Particle IDE.
#include "InternetButton.h"
#include <stdlib.h>     /* atoi */


// -----------------------------------
// Controlling LEDs over the Internet
// -----------------------------------

int i;
double howMany;
int red, green, blue;
int utilPercentage = 0;
double swVersion = 0.182;

InternetButton b = InternetButton();

bool rainbow_mode = false;

//setup
void setup()
{

   b.begin();
   b.allLedsOn(0,0,255);
   // We are also going to declare a Spark.function so that we can turn the LED on and off from the cloud.
   Spark.function("led",ledToggle);
   // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.

   Spark.variable("howMany", &howMany, DOUBLE);
   Spark.variable("utilPercentage", &utilPercentage, INT);
   Spark.variable("swVersion", &swVersion, DOUBLE);
   Serial.begin(9600);
   Serial.println("booted with version:");
   Serial.print(swVersion);
}


void loop()
{

  if (b.buttonOn(1)) {
        Spark.publish("ViPR: Expand ScaleIO Capacity","Expanding");
        int red = 0;
        int green = 255;
        int blue = 0;
        //make it green
        //turn any leds off
        b.allLedsOff();
        for(int x = 1; x <=3; x++){
          for(int i = 1; i <= 12; i++){
            b.ledOn(i, 0, 0, 255);
            delay(200);
          }
          b.allLedsOff();
        }
        b.allLedsOff();
        //turn to green because of expansion
        for(int i = 1; i <= 2; i++){
        b.ledOn(i, red, green, blue);
        }
        delay(500);
        Spark.publish("ViPR: Capacity Expansion:","Success");
    }

}

int ledToggle(String command) {
    /* Spark.functions always take a string as an argument and return an integer.
    Since we can pass a string, it means that we can give the program commands on how the function should be used.
    In this case, telling the function "on" will turn the LED on and telling it "off" will turn the LED off.
    Then, the function returns a value to us to let us know what happened.
    In this case, it will return 1 for the LEDs turning on, 0 for the LEDs turning off,
    and -1 if we received a totally bogus command that didn't do anything to the LEDs.
    */
    b.allLedsOff();
    Spark.publish("command:", command);
    utilPercentage = atoi (command);
    Serial.println(utilPercentage);
    //Spark.publish("utilPercentage:", utilPercentage);

    //calculate how many LEDs to turn on based on the utilization
    howMany = ((utilPercentage/100) * 12);
    Serial.println(howMany);
    //Spark.publish("howmany:", howMany);

    if (command=="rainbow") {
        //Enable rainbox mode
        b.rainbow(20);
        rainbow_mode = true;
        utilPercentage = 0;
        //delay(10000);
        //b.allLedsOff();
        return 4;
    }
    //if 70 all LEDs are yellow
    else if ((utilPercentage>=31) && (utilPercentage<90)) {
        int red = 255;
        int green = 255;
        int blue = 0;
        //make it yellow

        //loop to turn on the specified number of LEDs based on the utilization
        for(int i = 1; i <= 7; i++){
        b.ledOn(i, red, green, blue);
        }
        return 1;
    }
    else if (utilPercentage<=30) {
      int red = 0;
      int green = 255;
      int blue = 0;
      //make it green

      for(int i = 1; i <= 2; i++){
      b.ledOn(i, red, green, blue);
      }
      return 2;
    }
    else if (utilPercentage>=90) {
      int red = 255;
      int green = 0;
      int blue = 0;
      //make it red

      for(int i = 1; i <= 11; i++){
      b.ledOn(i, red, green, blue);
      }
      return 3;
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
