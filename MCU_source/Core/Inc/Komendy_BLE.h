/*
 * Komendy_BLE.h
 *
 *  Created on: Sep 21, 2020
 *      Author: Teodor
 * This application is of very poor quality, only a small refactoring has been made
 * to increase readability. However, somehow it leaves a lot to be desired.
 * Refactored 10.2021
 */

#ifndef SRC_KOMENDY_BLE_H_
#define SRC_KOMENDY_BLE_H_

#include "stm32h7xx_hal.h"


#define DrivingStartCommand 'I'
#define DrivingStopCommand 'U'

#define StarngCommand 226 //?

/* @@@@@ @@@@ "Basic" Screen in Mobile App */

#define StartPIDScanning 'P'
#define StopPIDScanning 'O'
#define SendActualPidSettings '>'
#define SetPid_Kp '+'
#define SetPid_Kd '-'
#define SetPid_Ki '('
#define SetBaseMotorSpeedValue ')'

/* Send to mobile app */
#define PID_ActualValue "a"
#define LeftMotorSpeed "s"
#define RightMotorSpeed "d"
#define ActualPositionError "ERROR:"
#define PID_Ki_Sum "f"
/* Actual PID from EEPROM */
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
#define SensorErW_8 '!'

/* Send Error Weights for each sensor to mobile App commands*/
#define SensorErWToM_App_1 '*'
#define SensorErWToM_App_2 '&'
#define SensorErWToM_App_3 '^'
#define SensorErWToM_App_4 "_"
#define SensorErWToM_App_5 '$'
#define SensorErWToM_App_6 '#'
#define SensorErWToM_App_7 '@'
#define SensorErWToM_App_8 '!'

/* Read value when the line is detected from mobile App*/
#define Sensor_1_LineIsDetectedValue 167
#define Sensor_2_LineIsDetectedValue 'H'
#define Sensor_3_LineIsDetectedValue 'Q'
#define Sensor_4_LineIsDetectedValue 'W'
#define Sensor_5_LineIsDetectedValue '?'
#define Sensor_6_LineIsDetectedValue 'L'
#define Sensor_7_LineIsDetectedValue 'T'
#define Sensor_8_LineIsDetectedValue 'Y'

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
#define PrintActualDataFor_Zaaw_Screen 'X'

#define MAX_Pid_Value 'g'
#define ReverseSpeed 'h'
#define MaxSumValue_forPidKi 'q'
#define Reserved1 'w'

#define Motor1TestStart 'e'
#define Motor1TestStop '`'

#define Reserv3 't'
#define Reserv4 'y'

#define IrSensor 'j' //?
#define IrLedMode 'J' //?

/* Send Advanced Data to mobile App*/
#define MAX_Pid_Value_ToM_App "g"
#define MAX_ReverseSpeed "h"
#define KI_MaxSumValue "q"
//#define PID_KdProbeTime "w" /*CzasProbkowania_CZ_Rozniczkujacego*/ #define above
//#define Reserv3 "t" //#definded above
//#define IrSensor "j" //#definded above
//#define IrLedMode "J" //#definded above
#define Reserv4_ToM_App "y"



extern uint32_t AktualnyCzasK_BLE;
extern uint32_t ZapamientanyCzasK_BLE;
extern uint32_t Z_Czas_Do_Pliku;

extern uint8_t wynik;
extern uint8_t drukowanie;
extern uint8_t c;
extern uint8_t DANE_DO_TEXT;


extern int k_wys_pom;
extern uint8_t czujnikiactiv;
extern 	float PID_value;

extern void KOMENDY_BLE();
extern void DRUKUJCZUJNIKI();
extern void WyslijWartoscERR();
extern void DRUKUJ_PID();
extern void PID_DO_BLE();
extern void DANE_DO_APLIKACJI_MOBILNEJ();
extern void ZMIENNE_ZAAW_DO_BLE();

extern void WYSLIJ_AKTUALNE_DANE_CZUJNIKOW_I_CZAS_DO_BLE();
extern void Wyslij_PojedynczyCzujnik(uint16_t nr_czujnika);

#endif /* SRC_KOMENDY_BLE_H_ */
