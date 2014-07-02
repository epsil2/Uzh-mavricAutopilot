 /** 
 * \page The MAV'RIC license
 *
 * The MAV'RIC Framework
 *
 * Copyright � 2011-2014
 *
 * Laboratory of Intelligent Systems, EPFL
 */
 
 
/**
 * \file orca.h
 *
 * This file computes a collision-free trajectory for the ORCA algorithm
 */


#ifndef ORCA_H__
#define ORCA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define ORCA_TIME_STEP_MILLIS 10.0
#define TIME_HORIZON 12.0
#define MAXSPEED 4.5
#define RVO_EPSILON 0.0001

/**
 * \brief The 3D plane structure
 */
typedef struct{
	float normal[3];	///< The normal vector to the plane
	float point[3];		///< A point of the plane
}plane_t;

/**
 * \brief The 3D line structure
 */
typedef struct{
	float direction[3];	///< The direction vector of a line
	float point[3];		///< A point of the line
}line_t;

/**
 * \brief	Initialize the ORCA module
 */
void init_orca(void);
/**
 * \brief	Initialize the ORCA module
 *
 * \param	OptimalVelocity		a 3D array
 * \param	NewVelocity			the 3D output array
 */
void computeNewVelocity(float OptimalVelocity[], float NewVelocity[]);

/**
 * \brief	computes the solution of a 1D linear program
 * 
 * \param	planes				the array of all planes
 * \param	index				the starting index of the plane
 * \param	line				the intersecting line between the two conflicting planes
 * \param	OptimalVelocity		a 3D array
 * \param	NewVelocity			the 3D output array
 * \param	directionOpt		whether we are solving a 4D or a 3D linear program
 *
 * \return	whether the linear program has a solution or not
 */
bool linearProgram1(plane_t planes[], uint8_t index, line_t line, float maxSpeed, float OptimalVelocity[], float NewVelocity[], bool directionOpt);

/**
 * \brief	computes the solution of a 2D linear program
 *
 * \param	planes				the array of all planes
 * \param	ind					the index of the plane
 * \param	maxSpeed			the norm of the max velocity
 * \param	OptimalVelocity		a 3D array
 * \param	NewVelocity			the 3D output array
 * \param	directionOpt		whether we are solving a 4D or a 3D linear program
 *
 * \return	whether the linear program has a solution or not
 */
bool linearProgram2(plane_t planes[], uint8_t ind, float maxSpeed, float OptimalVelocity[], float NewVelocity[], bool directionOpt);

/**
 * \brief	computes the solution of a 3D linear program
 *
 * \param	planes				the array of all planes
 * \param	planeSize			the number of planes
 * \param	OptimalVelocity		a 3D array
 * \param	maxSpeed			the norm of the max velocity
 * \param	NewVelocity			the 3D output array
 * \param	directionOpt		whether we are solving a 4D or a 3D linear program
 *
 * \return the number of the last plane to be evaluated, if smaller than the number of planes, linear program is infeasible
 */
float linearProgram3(plane_t planes[], uint8_t planeSize, float OptimalVelocity[], float maxSpeed, float NewVelocity[], bool directionOpt);

/**
 * \brief	computes the solution of a 3D linear program
 *
 * \param	planes			the array of all planes
 * \param	planeSize		the number of planes
 * \param	ind				the index of the plane for which the 3D linear program is infeasible
 * \param	maxSpeed		the norm of the max velocity
 * \param	NewVelocity		the 3D output array
 */
void linearProgram4(plane_t planes[], uint8_t planeSize, uint8_t ind, float maxSpeed, float NewVelocity[]);

#ifdef __cplusplus
}
#endif

#endif // ORCA_H__