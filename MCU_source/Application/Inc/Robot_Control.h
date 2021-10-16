/*
 * Uruchamianie.h
 *
 *  Created on: Sep 28, 2020
 *      Author: Teodor
 */

#ifndef INC_URUCHAMIANIE_H_
#define INC_URUCHAMIANIE_H_

typedef enum
{
	LF_Idle,
	LF_go_Stop,
	LF_go_Start,
	LF_Started,
}RobotState_t;

typedef struct
{
	RobotState_t RobotState;

}Robot_Cntrl_t;

extern Robot_Cntrl_t Robot_Cntrl;


extern RobotState_t LF_Robot_ControlTask();

#endif /* INC_URUCHAMIANIE_H_ */
