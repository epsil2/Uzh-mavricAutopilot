/*******************************************************************************
 * Copyright (c) 2009-2016, MAV'RIC Development Team
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
 * \file mavlink_communication_default_config.h
 * 
 * \author MAV'RIC Team
 * \author Gregoire Heitz
 *   
 * \brief Default configuration for the mavlink communication module
 *
 ******************************************************************************/


#ifndef MAVLINK_COMMUNICATION_DEFAULT_CONFIG_H_
#define MAVLINK_COMMUNICATION_DEFAULT_CONFIG_H_

#include "mavlink_communication.hpp"

static inline mavlink_communication_conf_t mavlink_communication_default_config()
{
	mavlink_communication_conf_t conf                  = {};

	conf.scheduler_config                              = {};
	conf.scheduler_config.max_task_count               = 30;
	conf.scheduler_config.schedule_strategy            = FIXED_PRIORITY;
	conf.scheduler_config.debug                        = false;
	conf.mavlink_stream_config                         = {};
	conf.mavlink_stream_config.sysid                   = 1;
	conf.mavlink_stream_config.compid                  = 50;
	conf.mavlink_stream_config.debug 		   		   = false,
	conf.message_handler_config                        = {};
	conf.message_handler_config.max_msg_callback_count = 20;
	conf.message_handler_config.max_cmd_callback_count = 20;
	conf.message_handler_config.debug                  = false;
	conf.onboard_parameters_config                     = {};
	conf.onboard_parameters_config.max_param_count     = MAX_ONBOARD_PARAM_COUNT;
	conf.onboard_parameters_config.debug               = false	;
	conf.max_msg_sending_count                         = 22;

	return conf;
};


#endif // MAVLINK_COMMUNICATION_DEFAULT_CONFIG_H_