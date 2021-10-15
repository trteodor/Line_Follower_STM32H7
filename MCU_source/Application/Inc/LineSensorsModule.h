#ifndef _LineSensor_H
#define _LineSensor_H

typedef struct
{
	float PositionErrorValue;
	uint16_t SensorADCValues[8];
	float SensorErrorValue[7];
	float SensorErrorMaxValue;
	int LineDetectValue[8];
}SensorModule_t;

extern SensorModule_t SensorModule;
/*Few field of the structure above are also modified by HM10Ble App Module*/

void SensorModuleInit();
float SensorsCalculateError();


#endif //_LineSensor_H
