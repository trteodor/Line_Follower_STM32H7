#ifndef _LineSensor_H
#define _LineSensor_H

typedef struct
{
	float ERR_CZ;
	uint16_t SensorADCValues[8];
	float SensorErrorValue[7];
	float SensorErrorMaxValue;
	int LineDetectValue[8];
}SensorModule_t;

void SensorModuleInit();
float SensorsCalculateError();


#endif //_LineSensor_H
