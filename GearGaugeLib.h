﻿/* GearGaugeLib.h - v2.0

 (c) 2009 Seung-Won Lee  http://whoisit.tistory.com  SoftWareYi@gmail.com
 (c) 2018 LeoKevin    http://leokevin.com

 Manual Shift Gear Position Gauge with AVR (7-Segment)
 https://github.com/LeoKevinKR/AVR-GearGauge

 NOT COMMERCIALLY AVAILABLE
*/

/***** Do NOT this file if not sure *****/

#ifndef GEARGAUGELIB_H_
#define GEARGAUGELIB_H_	1


#ifndef F_CPU
#	error "F_CPU is not defined"
#endif

#ifndef DDR_SNR
#	error "DDR_SNR is not defined"
#endif
#ifndef DDR_LED
#	error "DDR_LED is not defined"
#endif
#ifndef DDR_SEG
#	error "DDR_SEG is not defined"
#endif
#ifndef DDR_PWM
#	error "DDR_PWM is not defined"
#endif

#ifndef TIMSK
#	error "TIMSK is not defined"
#endif

#ifndef TCNT0
#	error "TCNT0 is not defined"
#endif
#ifndef TCCR0
#	error "TCCR0 is not defined"
#endif

#ifndef TCNT2
#	error "TCNT2 is not defined"
#endif
#ifndef TCCR2
#	error "TCCR2 is not defined"
#endif
#ifndef OCR2
#	error "OCR2 is not defined"
#endif

#ifndef SFIOR
#	error "SFIOR is not defined"
#endif

#if SEG_COM_ANODE > 1
#	error "SEG_COM_ANODE is not avail"
#endif
#if SEG_USE_TR > 1
#	error "SEG_USE_TR is not avail"
#endif
#if UART_LOG > 1
#	error "UART_LOG is not avail"
#endif
#if UNUSED_STY > 1
#	error "UNUSED_STY is not avail"
#endif
#if My_Crmny > 2
#	error "My_Crmny is not avail"
#endif
#if My_eFx > 2
#	error "My_eFx is not avail"
#endif
#if My_Sleep > 3
#	error "My_Sleep is not avail"
#endif
#if My_Rvs > 1
#	error "My_Rvs is not avail"
#endif
#if (My_High > 100 || My_High < 5)
#	error "My_High is not avail"
#endif
#if (My_Low > 80 || My_Low < 1)
#	error "My_Low is not avail"
#endif
#if (My_Tempo > 9 || My_Tempo < 1)
#	error "My_Tempo is not avail"
#endif
#if UART_LOG > 1
#	error "UART_LOG is not avail"
#endif


//debugging-LED output
#define LEDOUT(x)	(char)~x

//set unused port
#if UNUSED_STY==0 //input with pull-up
#	define SET_UNUSEDPORT(x) \
	if(&DDR##x != &DDR_SNR && &DDR##x != &DDR_LED && &DDR##x != &DDR_SEG && &DDR##x != &DDR_PWM) { \
		DDR##x=0x00; PORT##x=0xFF; \
	}
#elif UNUSED_STY==1 //output with nothing
#	define SET_UNUSEDPORT(x) \
	if(&DDR##x != &DDR_SNR && &DDR##x != &DDR_LED && &DDR##x != &DDR_SEG && &DDR##x != &DDR_PWM) { \
		DDR##x=0xFF; PORT##x=0x00; \
	}
#endif


//UART
#if UART_LOG == 1
#include <stdio.h> //puts()
#define INIT_LOG init_uart();stdout = &mystdout;
#define PRT_LOG	if(*gLogStr){puts(gLogStr);gLogStr[0]='\0';}

static int putchar0(char c, FILE *stream);	// 1 char Transmit
static FILE mystdout = FDEV_SETUP_STREAM(putchar0, NULL, _FDEV_SETUP_WRITE);
int putchar0(char c, FILE *stream)
{
	if (c == '\n') putchar0('\r', stream);
	while(!(UCSR0A & 0x20)); // UCSR0A 5bit = UDRE
	UDR0 = c; // 1 character trans
	return 0;
}
void init_uart()
{
	UBRR0H = 0;		// 12bit
	UBRR0L = 8;		// Look ATmega128 datasheet. 16Mhz, 115200 baud
	UCSR0B = 0x18;	// Receive(RX) and Transmit(TX) Enable
	UCSR0C = 0x06;	// UART Mode, 8 Bit Data, No Parity, 1 Stop Bit
}
extern char gLogStr[];

#else
#define INIT_LOG
#define PRT_LOG
#endif /*UART_LOG == 1*/


typedef struct { char k; char v; } cKeyVal;

char initDev(
	unsigned long v_F_CPU,
	char v_SegComAnode,
	char v_SegUseTr,
	cKeyVal *v_SnrMap,
	signed char v_SnrMapSize,
	char v_SnrUp,
	char v_SnrDw,
	char *v_PrefMtn,
	char *v_MySets,

	volatile uint8_t *v_DDR_SNR,
	volatile uint8_t *v_PORT_SNR,
	volatile uint8_t *v_PIN_SNR,

	volatile uint8_t *v_DDR_LED,
	volatile uint8_t *v_PORT_LED,

	volatile uint8_t *v_DDR_SEG,
	volatile uint8_t *v_PORT_SEG,

	volatile uint8_t *v_DDR_PWM,
	volatile uint8_t *v_PORT_PWM,
	char v_PIN_PWM,

	char v_unuse,
	char v_uart_log
);
char crmny(void);
char gauge(void);
char chkShtDw(void);
#endif /* GEARGAUGELIB_H_ */