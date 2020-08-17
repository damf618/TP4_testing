#include "build/temp/_test_TP4_Testing.c"
#include "build/test/mocks/mock_primario4.h"
#include "src/TP4_Testing.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.30.0/vendor/unity/src/unity.h"




typedef struct Casos_Prueba_s {

 dprim_state_t Estado_Inicial;

 dprim_state_t Transicion_Alarma;

 dprim_state_t Transicion_Falla;

 dprim_state_t Transicion_Normal;

 dprim_state_t Transicion_Alarma_Falla;

 dprim_state_t Local_Alarm_Response;

 dprim_state_t Local_Fail_Response;

 dprim_state_t Comm_Response;

 dprim_state_t Expected_Result;

} Casos_Prueba_t;





typedef struct Casos_Prueba_Gral_s {

 dprim_state_t Estado_Inicial;

 dprim_state_t Transicion_Alarma;

 dprim_state_t Transicion_Falla;

 dprim_state_t Transicion_Normal;

 dprim_state_t Transicion_Alarma_Falla;

 dprim_state_t Local_Alarm_Response;

 dprim_state_t Local_Fail_Response;

 dprim_state_t Comm_Response;

 dprim_state_t Expected_Result;

 dprim_state_t Next_State;

} Casos_Prueba_Gral_t;



Casos_Prueba_t Casos_Alarma[]= {

 {



  .Estado_Inicial = NORMAL,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = ALARM_FAIL,

  .Local_Alarm_Response = ALARM,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = NORMAL,

  .Expected_Result = ALARM,

 },

 {



  .Estado_Inicial = NORMAL,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = ALARM,

  .Expected_Result = ALARM,

 },

};



Casos_Prueba_t Casos_Falla[]= {

 {



  .Estado_Inicial = NORMAL,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = FAIL,

  .Comm_Response = NORMAL,

  .Expected_Result = FAIL,

 },

 {



  .Estado_Inicial = NORMAL,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = FAIL,

  .Expected_Result = FAIL,

 },

};



Casos_Prueba_t Casos_Normal[]= {

 {



  .Estado_Inicial = FAIL,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = NORMAL,

  .Expected_Result = NORMAL,

 },

 {



  .Estado_Inicial = ALARM,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = NORMAL,

  .Expected_Result = NORMAL,

 },

};



Casos_Prueba_Gral_t Casos_General[]= {

 {



  .Estado_Inicial = NORMAL,

  .Transicion_Alarma = PREALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = NORMAL,

  .Expected_Result = NORMAL,

  .Next_State = ALARM,

 },

 {



  .Estado_Inicial = ALARM,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = PRENORMAL,

  .Expected_Result = PRENORMAL,

  .Next_State = FAIL,

 },

 {



  .Estado_Inicial = FAIL,

  .Transicion_Alarma = PREALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = PRENORMAL,

  .Expected_Result = PRENORMAL,

  .Next_State = ALARM_FAIL,

 },

 {



  .Estado_Inicial = ALARM-FAIL,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = PRENORMAL,

  .Expected_Result = PRENORMAL,

  .Next_State = PRENORMAL,

 },

 {



  .Estado_Inicial = PRENORMAL,

  .Transicion_Alarma = PREALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = NORMAL,

  .Expected_Result = NORMAL,

  .Next_State = PREALARM,

},

{



  .Estado_Inicial = PREALARM,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = PRENORMAL,

  .Expected_Result = PRENORMAL,

  .Next_State = PREFAIL,

 },

 {



  .Estado_Inicial = PREFAIL,

  .Transicion_Alarma = PREALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = PRENORMAL,

  .Expected_Result = PRENORMAL,

  .Next_State = PRE_ALARM_FAIL,

 },

 {



  .Estado_Inicial = PRE_ALARM_FAIL,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = PRENORMAL,

  .Expected_Result = PRENORMAL,

  .Next_State = NORMAL,

 },

};





static int caso_actual = 0;

dprimario_t prim;



void Cambio_De_Estado(void){

 ButtonCheck_CMockExpectAndReturn(





                                                252

 , &prim, Casos_General[caso_actual].Transicion_Alarma, Casos_General[caso_actual].Transicion_Normal, ALARM, Casos_General[caso_actual].Local_Alarm_Response)





                                                 ;



 ButtonCheck_CMockExpectAndReturn(





                                               257

 , &prim, Casos_General[caso_actual].Transicion_Falla, Casos_General[caso_actual].Transicion_Normal, FAIL, Casos_General[caso_actual].Local_Fail_Response)





                                                ;



 CommCheck_CMockExpectAndReturn(





                                         262

 , &prim, Casos_General[caso_actual].Transicion_Alarma, Casos_General[caso_actual].Transicion_Falla, Casos_General[caso_actual].Transicion_Normal, Casos_General[caso_actual].Comm_Response)





                                          ;



 ResetChange_CMockExpect(264, &prim);

}



void setUp(void) {



 prim.state = Casos_Alarma[caso_actual].Estado_Inicial;

}





void test_Prueba_Casos_Alarma(void){

 char Text_ID[30];

 printf("\n *** Inicio de Pruebas de Alarma ***");

 for(caso_actual = 0; caso_actual < sizeof(Casos_Alarma) / sizeof(struct Casos_Prueba_s); caso_actual++){



  printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);



  ButtonCheck_CMockExpectAndReturn(





                                                  283

  , &prim, Casos_Alarma[caso_actual].Transicion_Alarma, Casos_Alarma[caso_actual].Transicion_Normal, ALARM, Casos_Alarma[caso_actual].Local_Alarm_Response)





                                                   ;



  ButtonCheck_CMockExpectAndReturn(





                                                 288

  , &prim, Casos_Alarma[caso_actual].Transicion_Falla, Casos_Alarma[caso_actual].Transicion_Normal, FAIL, Casos_Alarma[caso_actual].Local_Fail_Response)





                                                  ;



  CommCheck_CMockExpectAndReturn(





                                           293

  , &prim, Casos_Alarma[caso_actual].Transicion_Alarma, Casos_Alarma[caso_actual].Transicion_Falla, Casos_Alarma[caso_actual].Transicion_Normal, Casos_Alarma[caso_actual].Comm_Response)





                                            ;



  ResetChange_CMockExpect(295, &prim);



  FullCheck (&prim,Casos_Alarma[caso_actual].Transicion_Alarma,

    Casos_Alarma[caso_actual].Transicion_Falla,

    Casos_Alarma[caso_actual].Transicion_Normal,

    Casos_Alarma[caso_actual].Transicion_Alarma_Falla);



  sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);

  UnityAssertEqualNumber((UNITY_INT)((Casos_Alarma[caso_actual].Expected_Result)), (UNITY_INT)((prim.state)), ((Text_ID)), (UNITY_UINT)(303), UNITY_DISPLAY_STYLE_INT);

 }

 printf("\n *** Final de Pruebas de Alarma ***");

}





void test_Prueba_Casos_Falla(void){

 char Text_ID[30];

 printf("\n *** Inicio de Pruebas de Falla ***");

 for(caso_actual = 0; caso_actual < sizeof(Casos_Falla) / sizeof(struct Casos_Prueba_s); caso_actual++){



  printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);



  ButtonCheck_CMockExpectAndReturn(





                                                 319

  , &prim, Casos_Falla[caso_actual].Transicion_Alarma, Casos_Falla[caso_actual].Transicion_Normal, ALARM, Casos_Falla[caso_actual].Local_Alarm_Response)





                                                  ;



  ButtonCheck_CMockExpectAndReturn(





                                                324

  , &prim, Casos_Falla[caso_actual].Transicion_Falla, Casos_Falla[caso_actual].Transicion_Normal, FAIL, Casos_Falla[caso_actual].Local_Fail_Response)





                                                 ;



  CommCheck_CMockExpectAndReturn(





                                          329

  , &prim, Casos_Falla[caso_actual].Transicion_Alarma, Casos_Falla[caso_actual].Transicion_Falla, Casos_Falla[caso_actual].Transicion_Normal, Casos_Falla[caso_actual].Comm_Response)





                                           ;



  ResetChange_CMockExpect(331, &prim);



  FullCheck (&prim,Casos_Falla[caso_actual].Transicion_Alarma,

    Casos_Falla[caso_actual].Transicion_Falla,

    Casos_Falla[caso_actual].Transicion_Normal,

    Casos_Falla[caso_actual].Transicion_Alarma_Falla);



  sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);

  UnityAssertEqualNumber((UNITY_INT)((Casos_Falla[caso_actual].Expected_Result)), (UNITY_INT)((prim.state)), ((Text_ID)), (UNITY_UINT)(339), UNITY_DISPLAY_STYLE_INT);

 }

 printf("\n *** Final de Pruebas de Falla ***");

}





void test_Prueba_Casos_Normal(void){

 char Text_ID[30];



 printf("\n *** Inicio de Pruebas de Normal ***");

 for(caso_actual = 0; caso_actual < sizeof(Casos_Normal) / sizeof(struct Casos_Prueba_s); caso_actual++){



  printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);

  ButtonCheck_CMockExpectAndReturn(





                                                  355

  , &prim, Casos_Normal[caso_actual].Transicion_Alarma, Casos_Normal[caso_actual].Transicion_Normal, ALARM, Casos_Normal[caso_actual].Local_Alarm_Response)





                                                   ;



  ButtonCheck_CMockExpectAndReturn(





                                                 360

  , &prim, Casos_Normal[caso_actual].Transicion_Falla, Casos_Normal[caso_actual].Transicion_Normal, FAIL, Casos_Normal[caso_actual].Local_Fail_Response)





                                                  ;



  CommCheck_CMockExpectAndReturn(





                                           365

  , &prim, Casos_Normal[caso_actual].Transicion_Alarma, Casos_Normal[caso_actual].Transicion_Falla, Casos_Normal[caso_actual].Transicion_Normal, Casos_Normal[caso_actual].Comm_Response)





                                            ;



  ResetChange_CMockExpect(367, &prim);



  FullCheck (&prim,Casos_Normal[caso_actual].Transicion_Alarma,

    Casos_Normal[caso_actual].Transicion_Falla,

    Casos_Normal[caso_actual].Transicion_Normal,

    Casos_Normal[caso_actual].Transicion_Alarma_Falla);



  sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);

  UnityAssertEqualNumber((UNITY_INT)((Casos_Normal[caso_actual].Expected_Result)), (UNITY_INT)((prim.state)), ((Text_ID)), (UNITY_UINT)(375), UNITY_DISPLAY_STYLE_INT);

 }

 printf("\n *** Final de Pruebas de Normal ***");

}





void test_Logica_Transicion_de_Estados(void){



 char Text_ID[30];



  printf("\n *** Inicio de Pruebas Generales ***");

  for(caso_actual = 0; caso_actual < sizeof(Casos_General) / sizeof(struct Casos_Prueba_Gral_s); caso_actual++){

   printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);

   printf("\n *** Estado Actual: %d ***",prim.state);

   Cambio_De_Estado();

   primControl(&prim);

   sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);

   UnityAssertEqualNumber((UNITY_INT)((Casos_General[caso_actual].Expected_Result)), (UNITY_INT)((prim.state)), ((Text_ID)), (UNITY_UINT)(392), UNITY_DISPLAY_STYLE_INT);

   prim.state=Casos_General[caso_actual].Next_State;

  }

}
