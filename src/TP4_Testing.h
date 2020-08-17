/*=====[TP4_Testing]==========================================================
 * Copyright 2020 Author Marquez Daniel <damf618@gmail.com>
 * All rights reserved.
 * License: license text or at least name and link
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 1.0.0
 * Creation Date: 2020/07/25
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef TP4_TESTING_H_
#define TP4_TESTING_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include"stdint.h"
#include"stdbool.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

typedef enum{ NORMAL , ALARM, FAIL,ALARM_FAIL, PRENORMAL, PREALARM, PREFAIL,PRE_ALARM_FAIL, NO_STATE} dprim_state_t;
//uint16_t code[3] ={987,654,321};

// Structure with the different data types to generate an independent Monitor
/*
typedef struct{
	dprim_state_t state;
	bool boton1;
	bool boton2;
//	uint16_t code;
}dprimario_t;
*/
typedef struct{
	//tick_t timeout;
	//delay_t delay;
	dprim_state_t state;
	bool boton1;	//Buttons with  debounce pattern
	bool boton2;
	uint8_t count;			//Count of Cycles.
	bool COMMFLAG;		//Flag for UART interaction 1 ON, 0 OFF
	bool TEST_MODE;		//Flag for defining TEST mode
	dprim_state_t comm_state;
//	dprim_state_t AlarmContact_state;
//	dprim_state_t FailContact_state;

}dprimario_t;
/*=====[Prototypes (declarations) of public functions]=======================*/
void Button_CheckA(dprimario_t * prim, dprim_state_t casea);
void Button_CheckF(dprimario_t * prim, dprim_state_t casef);
void RF_Listening(dprimario_t * prim, dprim_state_t casea, dprim_state_t casef, dprim_state_t casen );
void Contact_Monitoring(dprimario_t * prim, dprim_state_t casea, dprim_state_t casef, dprim_state_t casen );
void FullCheck(dprimario_t * prim,dprim_state_t casea, dprim_state_t casef,dprim_state_t casen,dprim_state_t caseaf);
bool primControl(dprimario_t * pPrimario);
/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* TP4_TESTING_H_ */
