#ifndef INC_AppMainJobs_H_
#define INC_AppMainJobs_H_

extern void HM10BLE_Init();
extern void LF_App_MainConfig(void);
extern void LF_App_MainTask(void);


#define CountStatesWhenLineBy4SenDetToEndLapMark 25

typedef enum
{
	LF_Idle,
	LF_go_Stop,
	LF_go_Start,
	LF_Started,
}RobotState_t;

typedef enum
{
	MapSt_Idle,
	MapSt_GoToCreate,
	MapSt_Created,
}TrackMapActions_t;


typedef struct
{
	RobotState_t RobotState;
	TrackMapActions_t TrackMapActions;

}Robot_Cntrl_t;

extern Robot_Cntrl_t Robot_Cntrl;

#endif /* _AppMainJobs_H */
