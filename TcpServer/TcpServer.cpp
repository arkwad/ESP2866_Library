/*
 * TcpServer.cpp
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

#include "TcpServer.h"

TcpServer::TcpServer(HardwareSerial& serial, uint16_t port_no):m_tcp_server(port_no),m_serial(serial)
{
    m_tcp_server.begin();
}

TcpServer::~TcpServer( void ) 
{

}

void TcpServer::poll( void ) 
{
    // if new client available add it to the array is there is empty space
    if ( m_tcp_server.hasClient() ) {
        m_serial.print( "New client!\n" );
        for ( int i = 0; i < MAX_NUM_OF_CLIENTS; i++ ) {
            // search for empty place in array
            if ((!m_tcp_clients[i])) {
                m_tcp_clients[i] = m_tcp_server.available();
            } else if (!m_tcp_clients[i].connected()) {
                m_tcp_clients[i].stop();
                m_tcp_clients[i] = m_tcp_server.available();
            }
        }
    }
    for (int i = 0; i < MAX_NUM_OF_CLIENTS; i++) {
        if (m_tcp_clients[i]) {
            if ( m_tcp_clients[i].available() ) {
                String txt = m_tcp_clients[i].readStringUntil('a');
                m_tcp_clients[i].write( txt.c_str() );
                m_serial.println( txt );
            }
        }
    }
}

