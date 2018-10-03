/* MySettings.h - v2.0

 (c) 2009 Seung-Won Lee  http://whoisit.tistory.com  SoftWareYi@gmail.com
 (c) 2017,2018 LeoKevin    http://leokevin.com

 Shift Gear Position Gauge for Manual Transmission (7-Segment)
 https://github.com/LeoKevinKR/AVR-GearGauge

 NOT COMMERCIALLY AVAILABLE
*/

#ifndef MYSETTINGS_H_
#define MYSETTINGS_H_


//=== STATIC SETTING : START =====================================
//=== 고정설정 : 컴파일 후에는 변경 불가능

//시스템 클럭
#define F_CPU		16000000UL


// 입출력 포트설정
#define DDR_SNR		DDRA	//sensor register
#define PORT_SNR	PORTA	//sensor port
#define PIN_SNR		PINA	//sensor value

#define DDR_LED		DDRC	//debug LED register
#define PORT_LED	PORTC	//debug LED port

#define DDR_SEG		DDRF	//7-Segment FND register
#define PORT_SEG	PORTF	//7-Segment FND port

#define DDR_PWM		DDRB	//PWM register
#define PORT_PWM	PORTB	//PWM port
#define PIN_PWM		DDB7	//PWM out pin(OC2)

/** SEG_COM_ANODE : FND Type
 * 0 = Common Cathode(공통-)
 * 1 = Common Anode(공통+)
 */
#define SEG_COM_ANODE	1


/** SEG_USE_TR : Segment 전원으로 Tr 사용여부
 * 0 = 사용안함(OC2 단자에서 FND 공통단자로 연결)
 * 1 = 사용함(OC2 단자 - Tr - FND 공통단자로 연결)
 */
#define SEG_USE_TR		1


/** PREF_MOTN : 설정모드 진입모션
 * 조작할 단수를 중립기어를 제외하고 원하는만큼 나열하여 작성
 * 조작후 중립으로 해야 인식됨
 * 설정모드 종료는 후진
 * !!! 시동을 끄고 안전한 곳에서 조작할것을 권장 !!!
 */
#define PREF_MOTN		"5151"


/** sensorMap[] : 센서Map
 * PORT_SNR 으로 입력되는 값
 * 차량에 맞게 설정
 * 최대 12개까지 가능
 * 0b0 뒤에 [3bit:shift cable] [4bit:select cable]
 */
#define SENSOR_MAP	{\
	{ 0b00100010, 'N' }, \
	{ 0b00010100, '1' }, \
	{ 0b01000100, '2' }, \
	{ 0b00010010, '3' }, \
	{ 0b01000010, '4' }, \
	{ 0b00010001, '5' }, \
	{ 0b01000001, '6' }, \
	{ 0b00011000, 'B' }, \
	{ 0b00100100, 'L' }, \
	{ 0b00101000, 'L' }, \
	{ 0b00100001, 'R' }, \
	{ 0b00000000, '0' } \
}

#define SENSOR_UP	3
#define SENSOR_DW	4

#define SPD_FACT	1
#define UART_LOG	1
//=== STATIC SETTING : END =======================================



//=== DYNAMIC SETTING : START : 사용중에 변경가능 ================

//---
/** My_Cemny (C) : 웰컴 세레모니
 * 0 = 사용안함
 * 1 = 전체점등 1회
 * 2 = 애니메이션
 */
#define My_Cemny	2


/** My_eFx (F) : 변속조작시 효과
 * 0 = 효과없음
 * 1 = 이전 기어 서서히 사라짐 & 입력 기어 깜빡임
 * 2 = 이전 기어 깜빡임
 */
#define My_eFx		1


/** My_Sleep (S) : 슬립모드 효과
 * 0 = 효과없음
 * 1 = Rolling
 * 2 = Breathing
 * 3 = Turn Off
 */
#define My_Sleep	2


/** My_rvs (r) : 후진 표시 옵션
 * 0 = 글자가 깜빡임
 * 1 = 점이 깜빡임
 */
#define My_rvs		0


/** My_High (H) : 고조도% (기본 밝기)
 * 5(dark) ~ 100(bright) 까지 설정
 */
#define My_High		100


/** My_Low (L) : 저조도% (야간 밝기)
 * 1(dark) ~ 80(bright) 까지 설정
 */
#define My_Low		10


/** Power (P) : 동작전원
 * 위로 올리거나(3단) 아래로 내리면(4단) 재시작될때까지 동작 중지됨
 */
//=== DYNAMIC SETTING : END ======================================


#endif /* MYSETTINGS_H_ */