#ifndef primario4_H_
#define primario4_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include"stdint.h"
#include"stdbool.h"
#include "TP4_Testing.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif


// Verify the transition conditions related to uart codes
dprim_state_t CommCheck(dprimario_t * prim,dprim_state_t casea, dprim_state_t casef,dprim_state_t casen  );

// Verify the transition conditions related to pushbuttons
dprim_state_t ButtonCheck(dprimario_t * prim, dprim_state_t eventcase,dprim_state_t casen,dprim_state_t Mode );	

void ResetChange(dprimario_t * prim);
#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* primario4_H_ */
