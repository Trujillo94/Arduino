/*
 * Wrox Template
 * Professional Android Open Accessory Programming
 * debug the MQTT protocol
 * 
 * Connects to a phone, and gets commands packed as MQTT
 * This app is used to debug how the communication works
 *
 * (c) 2012 Andreas Goransson & David Cuartielles
 * GPLv3
 */

#include <AndroidAccessory.h>
#include <P2PMQTT.h>

// timer
long timer = millis();

// to store the data
int payload = -1;

P2PMQTT mqtt(true); // add parameter true for debugging

void setup() {
  // use the serial port to monitor that things work
  Serial.begin(9600);
  Serial.println("ready");
  
  // initiate the communication to the phone
  mqtt.begin("Miau");
  mqtt.connect(0,60000);  // add 1min timeout

}

void loop() {
  // get a P2PMQTT package and extract the type
  int type = mqtt.getType(mqtt.buffer); 

  // depending on the package type do different things
  switch(type) {
    
    case CONNECT:
      Serial.println("connected");
      break;

    case SUBSCRIBE:
      Serial.println("subscribed");
      break;

    case UNSUBSCRIBE:
      Serial.println("unsubscribed");
      break;

    case PINGREQ:
      Serial.println("ping request");
      break;

    case PUBLISH:
      payload = mqtt.getPayload(mqtt.buffer, type)[0];
      Serial.print("command: ");
      Serial.println(payload);
      break;

    default:
      // do nothing
      break;
  }
}

