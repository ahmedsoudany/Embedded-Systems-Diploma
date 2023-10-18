#include "driver.h"
#include "MainAlgorithm.h"
#include "State.h"
#include "PressureSensor.h"
#include "AlarmActuator.h"
#include "AlarmMonitor.h"


void(*PS_state)() = STATE(PS_init);
void(*AlarmActuator_state)() = STATE(AlarmActuator_init);
void(*Alarmmonitor_state)() = STATE(AlarmMonitor_Off);
void(*MainAlgo_state)() = STATE(MainAlgo_HighPressure);

int main ()
{

	GPIO_INITIALIZATION();
	while (1)
	{
		//Implement your Design 
		PS_state();
		AlarmActuator_state();
		Alarmmonitor_state();
		MainAlgo_state();
	}

	return 0;

}
