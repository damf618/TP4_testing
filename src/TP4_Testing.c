/*=====[TP4_Testing]==========================================================
 * Copyright 2020 Author Marquez Daniel <damf618@gmail.com>
 * All rights reserved.
 * License: license text or at least name and link
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 1.0.0
 * Creation Date: 2020/07/25
 */

/*=====[Inclusions of function dependencies]=================================*/

#include "TP4_Testing.h"
#include "primario4.h"
#include "stdio.h"

void RF_Listening(dprimario_t * prim, dprim_state_t casea, dprim_state_t casef, dprim_state_t casen ){
	dprim_state_t Comm_State;
	Comm_State=CommCheck(prim,casea,casef,casen);
	
	if (Comm_State==ALARM){
		prim->state=casea;			//The New state is the Alarm related state
	}
	else if (Comm_State==FAIL){
		prim->state=casef;			//The New state is the Fail related state
	}
	else if (Comm_State==NORMAL){
		prim->state=casen;			//The New state is the Normal related state
	}
}

void Contact_Monitoring(dprimario_t * prim, dprim_state_t casea, dprim_state_t casef, dprim_state_t casen ){
	dprim_state_t Contact_State;
	Contact_State=ButtonCheck(prim,casea,casef,casen);
	
	if (Contact_State==ALARM){
		prim->state=casea;			//The New state is the Alarm related state
	}
	else if (Contact_State==FAIL){
		prim->state=casef;			//The New state is the Fail related state
	}
	else if (Contact_State==NORMAL){
		prim->state=casen;			//The New state is the Normal related state
	}
}

void FullCheck(dprimario_t * prim,dprim_state_t casea, dprim_state_t casef,dprim_state_t casen,dprim_state_t caseaf){
	//dprim_state_t Actual=prim->state;
	dprim_state_t LocalA;
	dprim_state_t LocalF;
	dprim_state_t Comm;
	bool Event=0; 
	LocalA = ButtonCheck(prim,casea,casen,ALARM);
	if(/*(LocalA!=prim->AlarmContact_state)&&*/(LocalA!=NO_STATE))
	{
		printf("\r\n Local Alarm Signal \r\n");
		//prim->AlarmContact_state =LocalA;
		Event=1;
	}
	LocalF = ButtonCheck(prim,casef,casen,FAIL);
	if(/*(LocalF!=prim->FailContact_state)&&*/(LocalF!=NO_STATE))
	{
		printf("\r\n Local Fail Signal \r\n");
		//prim->FailContact_state =LocalF;
		Event=1;
	}
	Comm=CommCheck(prim,casea,casef,casen);
	if(Comm!=NO_STATE)
	{
		Event=1;
		if((Comm==ALARM)||(Comm==PREALARM)){
			printf("\r\n Alarm Comm Signal \r\n");
			//prim->comm_state =Comm;
		}
		else if((Comm==NORMAL)||(Comm==PRENORMAL)){
			printf("\r\n Normal Comm Signal \r\n");
			//prim->comm_state =Comm;
		}
		else if((Comm==FAIL)||(Comm==PREFAIL)){
			printf("\r\n Fail Comm Signal \r\n");
			//prim->comm_state =Comm;
		}
		else{
			printf("\r\n Unexpected Comm Signal \r\n");
			prim->state =FAIL;
		}
	}
	
	if(Event){
	if(((LocalA==casea)&&(LocalF==casef)) || (Comm==caseaf) || ((LocalA==casea)&&(Comm==casef)) || ((LocalF==casef)&&(Comm==casea)) )
	{	
		prim->state=caseaf;
		printf("\r\n ====== Alarm-Fail Status ====== \r\n");
		ResetChange(prim);
	}
	else if((LocalA==casea) || (Comm==casea))
	{
		prim->state=casea;
		printf("\r\n ====== Alarm Status ====== \r\n");
		ResetChange(prim);
	}
	else if((LocalF==casef) || (Comm==casef))
	{
		prim->state=casef;
		printf("\r\n ====== Fail Status ====== \r\n");
		ResetChange(prim);
	}
	else if(((LocalA==casen)&&(LocalF==casen)) || (Comm==casen))
	{
		prim->state=casen;
		printf("\r\n ====== Normal Status ====== \r\n");
		ResetChange(prim);
	}
	else
	{
		printf("\r\n ====== Unexpected Status ====== \r\n");
		prim->state=FAIL;
		ResetChange(prim);
	}
}
}

bool primControl(dprimario_t * pPrimario){

	if(NULL==pPrimario)
		return 0;

	switch( pPrimario->state ) {

		case NORMAL:
			printf("\n== Estado Principal ==\n  ** NORMAL **");
			FullCheck (pPrimario,PREALARM,PREFAIL,NORMAL,PRE_ALARM_FAIL);
			break;
		case ALARM:
			printf("\n== Estado Principal ==\n  ** ALARMA **");
			FullCheck (pPrimario,ALARM,PREFAIL,PRENORMAL,PRE_ALARM_FAIL);
			break;
		case FAIL:
			printf("\n== Estado Principal ==\n  ** FALLA **");
			FullCheck (pPrimario,PREALARM,FAIL,PRENORMAL,PRE_ALARM_FAIL);
			break;
		case ALARM_FAIL:
			printf("\n== Estado Principal ==\n  ** ALARMA-FALLA **");
			FullCheck (pPrimario,ALARM,FAIL,PRENORMAL,ALARM_FAIL);
			break;
		case PRENORMAL:
			printf("\n-- Estado Secundario --\n  ** PRE-NORMAL **");
			FullCheck (pPrimario,PREALARM,PREFAIL,NORMAL,PRE_ALARM_FAIL);
			break;
		case PREALARM:
			printf("\n-- Estado Secundario --\n  ** PRE-ALARMA **");
			FullCheck (pPrimario,ALARM,PREFAIL,PRENORMAL,ALARM);
			break;
		case PREFAIL:
			printf("\n-- Estado Secundario --\n  ** PRE-FALLA **");
			FullCheck (pPrimario,PREALARM,FAIL,PRENORMAL,PRE_ALARM_FAIL);
			break;
		case PRE_ALARM_FAIL:
			printf("\n-- Estado Secundario --\n  ** PRE-ALARMA/FALLA **");
			FullCheck (pPrimario,ALARM,FAIL,PRENORMAL,ALARM_FAIL);
			break;
		default:
			pPrimario->state=FAIL;
		}
	return 1;
}
