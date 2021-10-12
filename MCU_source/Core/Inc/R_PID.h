/*
 * R_PID.h
 *
 *  Created on: Sep 17, 2020
 *      Author: Teodor
 */

#ifndef INC_R_PID_H_
#define INC_R_PID_H_
#include "stm32h7xx_hal.h"
extern float Kp,Kd,Ki, Kii,PID_value,KI_SUMA,P,Pr_PID_value;
extern float D,P,I,I_SUMA,P_ERR_CZ; //D rozniczkowo P - Proporcjonalnie , I suma
extern int CzasProbkowania_CZ_Rozniczkujacego;
extern uint32_t CzasProbkowania_CZ_Calkujacego;
extern int Pr_Silnika_Lewego;
extern int Pr_Silnika_Prawego;
extern float pr_pocz_silnikow;
extern uint32_t zCzas_PID;
extern float rz_IP;
extern float rz_IL;

extern float MAX_PID,SUMA_MAX,ZMIENNA3,ZMIENNA4;
extern int pr_tyl,REZZ1;

extern void EEPROM_PID_READ();
extern void EEPROM_ZAAW_READ();

extern void Decode_PID();
extern void Motor_PWM_Init();
extern void JAZDA_DO_PRZODU(int Pr_Sil_Lew, int Pr_Sil_Pr);
extern void PRAWY_DO_TYLU(int Pr_Sil_Lew, int Pr_Sil_Pr);
extern void LEWY_DO_TYLU(int Pr_Sil_Lew, int Pr_Sil_Pr);
extern void JAZDA_DO_TYLU(int Pr_Sil_Lew, int Pr_Sil_Pr);

extern float calculatePID();
#endif /* INC_R_PID_H_ */
