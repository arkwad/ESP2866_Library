/*
 * WifiConnection.cpp
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

WifiConnection::WifiConnection(HardwareSerial& serial,
                               wifi_mode_t wifi_mode,
                               const char* ssid,
                               const char* passwd):m_serial(serial),
                                                   m_wifi_mode(wifi_mode),
                                                   m_ssid(ssid),
                                                   m_passwd(passwd)
{
    if (WIFI_STATION_MODE == m_wifi_mode) {
        #ifdef DEBUG
        m_serial.println("Starting station mode...");
        #endif //DEBUG
        WiFi.mode(WIFI_STA); // set module to Station mode
        // check if module has no connection
        if (WiFi.status() != WL_CONNECTED) {
            // if so - try to connect to given access point
            if (!WiFi.begin(m_ssid, m_passwd)) {
                return;
            }
        }
        #ifdef DEBUG
        m_serial.println("Will wait for connection...");
        #endif //DEBUG
        // wait for connection is estabilished 
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
        }
    } else if (WIFI_ACCESS_POINT_MODE == m_wifi_mode) {
        WiFi.mode(WIFI_AP); // set module to Access Point mode
    } else {
        #ifdef DEBUG
        m_serial.println("Not supported WIFI mode...");
        #endif //DEBUG
    }
}

WifiConnection::~WifiConnection(void)
{
  
}

