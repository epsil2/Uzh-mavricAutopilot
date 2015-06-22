/*******************************************************************************
 * Copyright (c) 2009-2014, MAV'RIC Development Team
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/*******************************************************************************
 * \file 	serial_udp.hpp
 * 
 * \author 	MAV'RIC Team
 *   
 * \brief 	Linux implementation of serial peripherals using UDP
 *
 ******************************************************************************/

#ifndef SERIAL_UDP_H_
#define SERIAL_UDP_H_

#include "serial.hpp"

extern "C"
{
	#include <stdint.h>
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include "buffer.h"
}

/**
 * 	Configuration structure
 */
typedef struct
{
	const char* tx_ip;
	int32_t 	tx_port;
	int32_t 	rx_port;


	bool flag; // TODO: remove

} serial_udp_conf_t;


/**
 * @brief 	Default configuration
 * 
 * @return 	Config structure
 */
static inline serial_udp_conf_t serial_udp_default_config();


class Serial_udp
{
public:
	/**
	 * @brief 	Initialises the peripheral
	 * 
	 * @param 	config 		Device configuration
	 */
	Serial_udp(serial_udp_conf_t config = serial_udp_default_config());


	/**
	 * @brief 	Hardware initialization
	 * 
	 * @return  true Success
	 * @return  false Error
	 */
	virtual bool init(void);


	/**
	 * @brief 	Test if there are bytes available to read
	 * 
	 * @return 	Number of incoming bytes available
	 */	
	virtual uint32_t readable(void);


	/**
	 * @brief 	Test if there is space available to write bytes
	 * 
	 * @return 	Number of bytes available for writing
	 */	
	virtual uint32_t writeable(void);


	/**
	 * @brief 	Sends instantaneously all outgoing bytes
	 * 
	 * @return 	Number of bytes available for writing
	 */	
	virtual void flush(void);

	/**
	 * @brief 	Write a byte on the serial line
	 * 
	 * @param 	byte 		Outgoing bytes
	 * @param 	size 		Number of bytes to write
	 * 
	 * @return 	true		Data successfully written
	 * @return 	false		Data not written
	 */
	virtual bool write(const uint8_t* bytes, const uint32_t size=1);


	/**
	 * @brief 	Read bytes from the serial line
	 * 
	 * @param 	bytes 		Incoming bytes
	 * @param 	size 		Number of bytes to read
	 * 
	 * @return 	true		Data successfully read
	 * @return 	false		Data not read
	 */	
	virtual bool read(uint8_t* bytes, const uint32_t size=1);


private:
	serial_udp_conf_t 	config_;
	
	buffer_t 			tx_buffer_;
	struct sockaddr_in  tx_addr_; 
	int32_t 			tx_sock_;

	buffer_t 			rx_buffer_;
	struct sockaddr_in  rx_addr_; 
	int32_t 			rx_sock_;
};


/**
 * @brief 	Default configuration
 * 
 * @return 	Config structure
 */
static inline serial_udp_conf_t serial_udp_default_config()
{
	serial_udp_conf_t 	conf;

	conf.tx_ip 		= "127.0.0.1";
	conf.tx_port	= 14555;
	conf.rx_port 	= 14555;

	conf.flag = true;

	return conf;
}


#endif /* SERIAL_UDP_H_ */