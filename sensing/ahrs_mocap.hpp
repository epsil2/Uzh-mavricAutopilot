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
 * \file ahrs_mocap.hpp
 *
 * \author MAV'RIC Team
 * \author Matthew Douglas
 *
 * \brief Records the ahrs quaternion from the motion capture system and updates
 * the ahrs vector accordingly.
 *
 ******************************************************************************/

#ifndef __AHRS_MOCAP_HPP__
#define __AHRS_MOCAP_HPP__

#include "communication/mavlink_message_handler.hpp"

extern "C"
{
#include "sensing/ahrs.h"
}


/**
 * \brief The AHRS class for the motion capture system
 */
class Ahrs_mocap
{
public:


    /**
     * \brief   AHRS EKF controller
     *
     * \param   message_handler The message handler to handle the incoming mocap message
     * \param   ahrs            Attitude estimation structure (output)
     */
    Ahrs_mocap(Mavlink_message_handler& message_handler, ahrs_t& ahrs);


private:

    float last_update_us_;                      ///< The time at last mocap ahrs update
    ahrs_t& ahrs_;                              ///< The ahrs structure

    /**
     * \brief   Method used to update internal state when a message is received
     *
     * \param   ahrs_mocap      The ahrs_ekf_mocap object
     * \param   sysid           ID of the system
     * \param   msg             Pointer to the incoming message
     */
    static void callback(Ahrs_mocap* ahrs_mocap, uint32_t sysid, mavlink_message_t* msg);
};

#endif // __AHRS_MOCAP_HPP__