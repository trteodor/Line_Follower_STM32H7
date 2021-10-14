/*
 *  Created on: 10.10.2021
 *      Author: Teodor
 */

#ifndef HM10Commands_H_
#define HM10Commands_H_

#include "main.h"


#define DrivingStartCommand 'I'
#define DrivingStopCommand 'U'

#define StarngCommand 226 //?

/* @@@@@ @@@@ "Basic" Screen in Mobile App */


#define StartPIDScanning 'P'
#define StopPIDScanning 'O'
#define SendActualPidSettings '>'
/* Comands from Mobile App (Set variables) */
#define SetPid_Kp '+'
#define SetPid_Kd '-'
#define SetPid_Ki '('
#define SetBaseMotorSpeedValue ')'

/* Send to mobile app commands*/
#define PID_ActualValue "a"
#define LeftMotorSpeed "s"
#define RightMotorSpeed "d"
#define ActualPositionError "ERROR:"
#define PID_Ki_Sum "f"

#define PID_KpComm "l"
#define PID_KdComm "k"
#define BaseMotorSpeed "m"
#define PID_KdProbeTime "w"

/* @@@@@ @@@@ Command for Save data to .txt file on Phone */
#define SaveDataVal1 147
#define SaveDataVal2 134
#define StopSavingData 146

/* @@@@@ @@@@ Sensor Screen in Mobile App */

#define  StartSendActualSensorData 'B'
#define  StopSendActualSensorData 'V'
#define  StopSendActualSensorDataAndSendActualErrorWeights '~'

/* Read value Error Weights for each sensor from mobile App*/
#define SensorErW_1 '*'
#define SensorErW_2 '&'
#define SensorErW_3 '^'
#define SensorErW_4 '%'
#define SensorErW_5 '$'
#define SensorErW_6 '#'
#define SensorErW_7 '@'
#define SensorErWMax '!'

/* Send Error Weights for each sensor to mobile App commands*/
#define SensorErWToM_App_1 '*'
#define SensorErWToM_App_2 '&'
#define SensorErWToM_App_3 '^'
#define SensorErWToM_App_4 "_"
#define SensorErWToM_App_5 '$'
#define SensorErWToM_App_6 '#'
#define SensorErWToM_App_7 '@'
#define SensorErWToM_App_Max '!'

/* Read value when the line is detected from mobile App*/
#define S1_LineIsDetV 167
#define S2_LineIsDetV 'H'
#define S3_LineIsDetV 'Q'
#define S4_LineIsDetV 'W'
#define S5_LineIsDetV '?'
#define S6_LineIsDetV 'L'
#define S7_LineIsDetV 'T'
#define S8_LineIsDetV 'Y'

/* Send actual value when the line is detected to mobile App*/
#define SensorLine_1_DetectValueToMobileAPP "§"
#define SensorLine_2_DetectValueToMobileAPP 'H'
#define SensorLine_3_DetectValueToMobileAPP 'Q'
#define SensorLine_4_DetectValueToMobileAPP 'W'
#define SensorLine_5_DetectValueToMobileAPP '?'
#define SensorLine_6_DetectValueToMobileAPP 'L'
#define SensorLine_7_DetectValueToMobileAPP 'T'
#define SensorLine_8_DetectValueToMobileAPP 'Y'
/* Actual line sensor detect data*/
#define Sensor_1_Data_ToM_App_Comm "CZ1:"
#define Sensor_2_Data_ToM_App_Comm "CZ2:"
#define Sensor_3_Data_ToM_App_Comm "CZ3:"
#define Sensor_4_Data_ToM_App_Comm "CZ4:"
#define Sensor_5_Data_ToM_App_Comm "CZ5:"
#define Sensor_6_Data_ToM_App_Comm "CZ6:"
#define Sensor_7_Data_ToM_App_Comm "CZ7:"
#define Sensor_8_Data_ToM_App_Comm "CZ8:"
#define ActualPositionError_SS "ERROR:"
/*@@@@@ @@@@  Mobile App Screen "Adv" */

/* Read or Write to mobile App (same command)*/

#define PrintActualDataFor_Adv_ScreenToM_App 'X'

#define MAX_Pid_Value 'g'
#define ReverseSpeed 'h'
#define MaxSumValue_forPidKi 'q'
#define PID_KdProbeTime "w"

#define Motor1TestStart 'e'
#define Motor1TestStop '`'

#define Reserv3 't'
#define Reserv4 'y'

#define IrSensor 'j' //?
#define LedMode 'J' //?


#endif /* HM10Commands_H_ */
