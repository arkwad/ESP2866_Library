/*
 * ESP8266_Endpoint.ino
 *
 *  Created on: 15.03.2018
 *      Author: Arkadiusz Wadowski
 *    Email: wadowski.arkadiusz@gmail.com
 *
 *  Copyright (c) 2018, Arkadiusz Wadowski
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#include "WifiConnection.h"
#include "TcpClient.h"

// for now the network ssid and passwd are fixed
const char *ssid = "Obrona2018";
const char *password = "Obrona2018..";
// global prototype of pointer to TCP client
TcpClient* client = NULL;

// an debug logs enable flag
//#define DEBUG

void setup() 
{
    Serial.begin(115200);// set boundrate
    Serial.println();
    Serial.setTimeout(60000); // set one minute as a timeout

    #ifdef DEBUG
    Serial.print("Setting WIFI connection...\n");
    #endif //DEBUG
    WifiConnection wifi = WifiConnection(Serial, WIFI_STATION_MODE, ssid, password);
    #ifdef DEBUG
    Serial.print("Creating TCP Client...\n");
    #endif //DEBUG
    delay(500);
    client = new TcpClient(Serial, "192.168.1.10", 1234);
    if (client == NULL) {
      //Serial.print("TCP Client not created...\n");
    }
    delay(500);

    #ifdef DEBUG
    Serial.print("Setup finished successfully...\n");
    #endif //DEBUG
    // wait for run command
    do {
        String cmd = Serial.readStringUntil('\r');
        if (cmd == "run") {
            Serial.print("OK\n");
            break;
        }
    } while (true);
}

void loop() 
{
    String cmd = Serial.readStringUntil('\r');
    if (cmd != "") {
      //Serial.print("echo: " + cmd);
        if (client->send(cmd)) {
            Serial.print("OK\n");
        }
    } 
    delay(500);
}
