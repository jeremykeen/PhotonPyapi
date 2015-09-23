#include "InternetButton/InternetButton.h"

/* How about we make this interactive? */

InternetButton b = InternetButton();
int pushCount = 0;
int toggle = 0;
int swVersion = .016;

void setup() {
    // Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();
    Spark.variable("pushCount", &pushCount, INT);
    Spark.variable("toggle", &toggle, INT);
    Spark.variable("swVersion", &swVersion, INT);
    Spark.subscribe("free_capacity", myHandler);
    Spark.publish("version",".016");
}

void loop(){

    // When you click the second button (at the 3 o'clock position) let's turn that LED on
    if(b.buttonOn(2)){

        pushCount++;
        b.ledOn(3, 255, 255, 255);
        toggle = 1;

        Spark.publish("buttonstatus","pushed");
    }
    // And if the button's not on, then the LED should be off
    else if (toggle==1){
        if (b.buttonOn(4)){
            toggle = 0;
            b.ledOff(3);
        }
    }
    //wait for a second
    delay(1000);
    /* Much like the LEDs, there are also functions to check if all the buttons are on- b.allButtonsOn()
    or if all the buttons are off- b.allButtonsOff() */
}

void myHandler(const char *event, const char *data)
{
/*    if data > 65{
        leds=yellow
        ledsnumber=(data/100)*12
    }
    else if data > 80
*/
    Spark.publish("from_orabi",data);
    Spark.publish("compare",strcmp(data,"green"))
    if (!strcmp(data,"green")) {

    // if green set leds to green
    b.allLedsOn(0,128,0);
    Spark.publish("greentrue");
  }
  else if (!strcmp(data,"off")) {
    // if 'off' turn off the leds
    b.allLedsOff();  }
  else {
      Spark.publish("else");
    // if the data is something else, don't do anything.
    // Really the data shouldn't be anything but those two listed above.
  }
}
