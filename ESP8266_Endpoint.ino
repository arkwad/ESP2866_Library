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
#include "TcpServer.h"
#include "TcpClient.h"

const char *ssid = "ExampleNetwork";
const char *password = "example1234";
TcpServer* server = NULL;
boolean setup_went_ok = false;
void setup() {
  delay(1000);
  Serial.begin(115200);// set boundrate
  Serial.println();
  Serial.setTimeout(60000); // set one minute as a timeout

  // device connected via UART needs to specify which app needs to be run on ESP
  String type_of_app = Serial.readStringUntil('\r');

  if ( type_of_app == "endpoint" ) {
    Serial.print( "endpoint_ok\n" );
    setup_went_ok = true;
  } else if ( type_of_app == "hub" ) {
    if ( !WiFi.softAP( ssid, password )){
        setup_went_ok = false;
        return;
    }
    // wait for dhcp service is ready
    delay(500);
    server = new(std::nothrow) TcpServer( Serial, 1234 );
    if ( NULL == server ){
        setup_went_ok = false;
        return;
    }
    Serial.print( "hub_ok\n" );
    setup_went_ok = true;
  } else {
    Serial.print( "nok\n" );
    setup_went_ok = false;
  }
  delay(500);
}

void loop() {
  if ( setup_went_ok != true ) {
    Serial.print("Error during setup procedure...\n");
    Serial.print("Restart required...\n");
    return;
  }
  server->poll();
}


