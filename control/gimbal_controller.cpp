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
 * \file gimbal_controller.hpp
 *
 * \author MAV'RIC Team
 * \author Alexandre Cherpillod
 *
 * \brief   Gimbal control management
 *
 ******************************************************************************/


#include "control/gimbal_controller.hpp"
extern "C"
{
	#include "util/print_util.h"
}

//------------------------------------------------------------------------------
// PRIVATE FUNCTIONS IMPLEMENTATION
//------------------------------------------------------------------------------

void Gimbal_controller::gimbal_controller_mix_to_servos()
{
	/*int32_t i;
	float gimbal_servo_command[3]; //only gimbal stabilization in pitch and yaw

	gimbal_servo_command[GIMBAL_SERVO_PITCH]	= control->gimbal_rpy[PITCH];
	gimbal_servo_command[GIMBAL_SERVO_YAW]		= control->gimbal_rpy[YAW];

	for (i=4; i<6; i++)
	{
		servos_set_value( servos, i, gimbal_servo_command[i-4]);
	}*/
}

//------------------------------------------------------------------------------
// PUBLIC FUNCTIONS IMPLEMENTATION
//------------------------------------------------------------------------------

void Gimbal_controller::gimbal_controller_init(const gimbal_controller_conf_t config)
{
    //Init variables
	attitude_command_desired = config.attitude_command_desired_config;
	attitude_output = config.attitude_output_config;
	attitude_command_range[MIN_RANGE_GIMBAL] = config.attitude_command_range_config[MIN_RANGE_GIMBAL];
	attitude_command_range[MAX_RANGE_GIMBAL] = config.attitude_command_range_config[MAX_RANGE_GIMBAL];
}


bool Gimbal_controller::gimbal_controller_update(Gimbal_controller *not_used)
{

	//Set directly the desired input as output commands ensuring that they are in the allowed range (no controller here)
	for(int i = 0; i < 3; i++)
	{
		if(attitude_command_desired.rpy[i] < attitude_command_range[MIN_RANGE_GIMBAL].rpy[i])
			attitude_output.rpy[i] = attitude_command_range[MIN_RANGE_GIMBAL].rpy[i];
		else if(attitude_command_desired.rpy[i] > attitude_command_range[MAX_RANGE_GIMBAL].rpy[i])
			attitude_output.rpy[i] = attitude_command_range[MAX_RANGE_GIMBAL].rpy[i];
		else
			attitude_output.rpy[i] = attitude_command_desired.rpy[i];
	}

	/*print_util_dbg_print("output gimbal commands\r\n");
	print_util_dbg_print("roll ");
	print_util_dbg_putfloat(attitude_output.rpy[0], 4);
	print_util_dbg_print("\r\npitch ");
	print_util_dbg_putfloat(attitude_output.rpy[1], 4);
	print_util_dbg_print("\r\nyaw ");
	print_util_dbg_putfloat(attitude_output.rpy[2], 4);
	print_util_dbg_print("\r\n");*/

	return true;
}
