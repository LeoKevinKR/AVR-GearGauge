/* GearGauge.c

 (c) 2009 Seung-Won Lee  http://whoisit.tistory.com  SoftWareYi@gmail.com
 (c) 2018 LeoKevin    http://leokevin.com

 Manual Shift Gear Position Gauge with AVR (7-Segment)
 https://github.com/LeoKevinKR/AVR-GearGauge

 NOT COMMERCIALLY AVAILABLE
*/
#include <avr/io.h>
#include "MySettings.h"
#include "GearGaugeLib.h"

int main(void)
{
	/* Set unused ports
	 * Repeat as all device have
	 */
	SET_UNUSEDPORT(A);
	SET_UNUSEDPORT(B);
	SET_UNUSEDPORT(C);
	SET_UNUSEDPORT(D);
	SET_UNUSEDPORT(E);
	SET_UNUSEDPORT(F);
	SET_UNUSEDPORT(G);

	/***** Do NOT edit below if not sure *****/

	while(ready(F_CPU, START_DELAY_MS));

	//Initialize Device
	INIT_LOG;
	char mySet[]={My_Crmny,My_eFx,My_Sleep,My_Rvs,My_High,My_Low,My_Tempo};
	cKeyVal snrMap[] = SENSOR_MAP;
	if(!initDev(
		SEG_COM_ANODE,
		SEG_USE_TR,
		snrMap,
		sizeof(snrMap)/sizeof(snrMap[0]),
		SENSOR_UP,
		SENSOR_DW,
		PREF_MOTN,
		mySet,

		&DDR_SNR,
		&PORT_SNR,
		&PIN_SNR,
		&DDR_LED,
		&PORT_LED,
		&DDR_SEG,
		&PORT_SEG,
		&DDR_PWM,
		&PORT_PWM,
		PIN_PWM,
		&DDR_INT,
		PIN_INT0,
		PIN_INT1,

		UNUSED_STY,
		USE_LED,
		USART_LOG
	)){
		PRT_LOG;
		while(1);
	}
	PRT_LOG;

	while(gauge()){PRT_LOG;} //Main Process

	while(1);
}