/* GearGauge.c - v2.0

 (c) 2009 Seung-Won Lee  http://whoisit.tistory.com  SoftWareYi@gmail.com
 (c) 2017,2018 LeoKevin    http://leokevin.com

 Shift Gear Position Gauge for Manual Transmission (7-Segment)
 https://github.com/LeoKevinKR/AVR-GearGauge

 NOT COMMERCIALLY AVAILABLE
*/
#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <avr/eeprom.h>
//#include <stdlib.h> //malloc() free()
//#include <string.h> //strlen()

#include "MySettings.h"
#include "GearGaugeLib.h"

/*
#include <stdio.h> //printf()
static int putchar0(char c, FILE *stream);	// 1 char 송신(Transmit)
static FILE mystdout = FDEV_SETUP_STREAM(putchar0, NULL, _FDEV_SETUP_WRITE);
int putchar0(char c, FILE *stream)
{
	if (c == '\n')
	putchar0('\r', stream);
	while(!(UCSR0A & 0x20)); 	// UCSR0A 5번 비트 = UDRE
	UDR0 = c;			// 1 character 전송
	return 0;
}

char getchar0()		// 1 character를 수신(receive)하는 함수
{
	while (!(UCSR0A & 0x80)); 	// UCSR0A 7번 비트 = RXC
	return(UDR0);		// 1 character 수신
}

void init_uart()
{
	UBRR0H = 0;		// 12비트가 의미를 가짐,
	UBRR0L = 8;		// ATmega128 datasheet 참조 요망. 16Mhz, 115200 baud의 경우
	UCSR0B = 0x18;	// Receive(RX) 및 Transmit(TX) Enable
	UCSR0C = 0x06;	// UART Mode, 8 Bit Data, No Parity, 1 Stop Bit
}
*/

//extern static FILE mystdout;

int main(void)
{
	//init_uart(); stdout = &mystdout;
	//printf("\nShift Gear Position Gauge Ver ");

	//set unused ports
	#ifdef DDRA
		SET_UNUSEDPORT(A);
	#endif
	#ifdef DDRB
		SET_UNUSEDPORT(B);
	#endif
	#ifdef DDRC
		SET_UNUSEDPORT(C);
	#endif
	#ifdef DDRD
		SET_UNUSEDPORT(D);
	#endif
	#ifdef DDRE
		SET_UNUSEDPORT(E);
	#endif
	#ifdef DDRF
		SET_UNUSEDPORT(F);
	#endif
	#ifdef DDRG
		SET_UNUSEDPORT(G);
	#endif

	//char currentPos = 0, input = 0;
	char my_sets[]={My_Cemny,My_eFx,My_Sleep,My_rvs,My_High,My_Low};
	charKeyVal sensorMap[] = SENSOR_MAP;
	initDevices(
		F_CPU,
		SEG_COM_ANODE,
		SEG_USE_TR,
		PREF_MOTN,
		my_sets,
		sensorMap,
		SENSOR_UP,
		SENSOR_DW,

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

		SPD_FACT,
		UART_LOG
	);
	//printf("g_ceremonyStep=%d\n",g_ceremonyStep);
	//while(g_ceremonyStep > 0) welcomeCeremony();
	while(welcomeCeremony());
	//printf("loop start\n");

	while(gage());
	/*
	{
		if ( g_itr_rised == 1 ) //every 100ms
		{
			g_itr_rised = 0;
			input = ~PIN_SNR; //sensor input value. 1=Off 0=On

			PORT_LED = LEDOUT( input ); //display LED
			currentPos = getTransmissionValue( input );
		}

		if( g_n1kHzCycles % g_display_Steps == 0 )
		{
			if( displaySegData( currentPos ) != 1 )
			{
				g_shutdwn_rised = 1;
				g_itr_rised = 0;
				g_delayMS = 500;
				break;
			}
		}
	}
	*/

	while(chkShutdown());
	/*
	while(g_shutdwn_rised > 0){
		if ( g_itr_rised == 1 ) //every 500ms
		{
			g_itr_rised = 0;
			goShutdown();
		}
	}
	*/

	return 0;
}