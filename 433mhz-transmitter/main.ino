#include <VirtualWire.h>

#define ledPin 13
#define packetLength 27



char msg[packetLength];

String sendingString;
String currentState = "initial;";
String strMsg = currentState;

char incomingByte;
String inputLine;

unsigned int packetNum = 0;

void setup() {
    Serial.begin(9600);
    vw_setup(1000);
    vw_set_tx_pin(7);
}

void loop() {
    // delay(1000);

    if (Serial.available() > 0) {
        incomingByte = Serial.read();
        if (incomingByte == ';') {
            currentState = inputLine;
            currentState.trim();
            currentState += ";";
            // Serial.println(currentState);
            inputLine = "";
        } else {
            inputLine = inputLine + incomingByte;
        }
    }

    strMsg = currentState;

    // sending message in packets chunks
    while (strMsg.length() > 0) {
        digitalWrite (ledPin, HIGH);
        packetNum++;

        sendingString = packetNum;
        sendingString += " ";
        sendingString += strMsg.substring(0, packetLength - 6);
        
        strMsg.remove(0, packetLength - 6);

        sendingString.toCharArray(msg, packetLength);
        vw_send((uint8_t *)msg, sendingString.length());
        vw_wait_tx();

        // Serial.println(sendingString.length());
        
        digitalWrite (ledPin, LOW);
    }


}


