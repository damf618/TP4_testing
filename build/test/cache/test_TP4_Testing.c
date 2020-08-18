#include "build/temp/_test_TP4_Testing.c"
#include "mock_primario4.h"
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



static const Casos_Prueba_t Casos_Alarma[]= {

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



static const Casos_Prueba_t Casos_Falla[]= {

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



static const Casos_Prueba_t Casos_Normal[]= {

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



static const Casos_Prueba_t Casos_General[]= {

 {



  .Estado_Inicial = NORMAL,

  .Transicion_Alarma = PREALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = PREALARM,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = NORMAL,

  .Expected_Result = PREALARM,

 },

 {



  .Estado_Inicial = PREALARM,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = ALARM,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = NORMAL,

  .Expected_Result = ALARM,

 },

 {



  .Estado_Inicial = ALARM,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = PREFAIL,

  .Comm_Response = ALARM,

  .Expected_Result = PRE_ALARM_FAIL,

 },

 {



  .Estado_Inicial = PRE_ALARM_FAIL,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = FAIL,

  .Comm_Response = ALARM,

  .Expected_Result = ALARM_FAIL,

 },

 {



  .Estado_Inicial = ALARM_FAIL,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = FAIL,

  .Comm_Response = PRENORMAL,

  .Expected_Result = FAIL,

 },

 {



  .Estado_Inicial = FAIL,

  .Transicion_Alarma = PREALARM,

  .Transicion_Falla = FAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = PREALARM,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = PREALARM,

  .Expected_Result = PREALARM,

 },

 {



  .Estado_Inicial = PREALARM,

  .Transicion_Alarma = ALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = PRENORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = ALARM,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = NORMAL,

  .Expected_Result = ALARM,

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

 },

};



static const Casos_Prueba_t Casos_Errores[]= {

 {



  .Estado_Inicial = NORMAL,

  .Transicion_Alarma = PREALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response = NO_STATE,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = ALARM,

  .Expected_Result = FAIL,

 },

 {



  .Estado_Inicial = NORMAL,

  .Transicion_Alarma = PREALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response =PREFAIL,

  .Local_Fail_Response = NO_STATE,

  .Comm_Response = NORMAL,

  .Expected_Result = FAIL,

 },

 {



  .Estado_Inicial = NORMAL,

  .Transicion_Alarma = PREALARM,

  .Transicion_Falla = PREFAIL,

  .Transicion_Normal = NORMAL,

  .Transicion_Alarma_Falla = PRE_ALARM_FAIL,

  .Local_Alarm_Response =NO_STATE,

  .Local_Fail_Response = ALARM,

  .Comm_Response = NORMAL,

  .Expected_Result = FAIL,

 },

};



static int caso_actual = 0;

dprimario_t prim;



void Cambio_De_Estado(Casos_Prueba_t * Caso_de_Estudio){

 prim.state = Caso_de_Estudio[caso_actual].Estado_Inicial;

 ButtonCheck_CMockExpectAndReturn(





                                                  285

 , &prim, Caso_de_Estudio[caso_actual].Transicion_Alarma, Caso_de_Estudio[caso_actual].Transicion_Normal, ALARM, Caso_de_Estudio[caso_actual].Local_Alarm_Response)





                                                   ;



 ButtonCheck_CMockExpectAndReturn(





                                                 290

 , &prim, Caso_de_Estudio[caso_actual].Transicion_Falla, Caso_de_Estudio[caso_actual].Transicion_Normal, FAIL, Caso_de_Estudio[caso_actual].Local_Fail_Response)





                                                  ;



 CommCheck_CMockExpectAndReturn(





                                           295

 , &prim, Caso_de_Estudio[caso_actual].Transicion_Alarma, Caso_de_Estudio[caso_actual].Transicion_Falla, Caso_de_Estudio[caso_actual].Transicion_Normal, Caso_de_Estudio[caso_actual].Comm_Response)





                                            ;



 ResetChange_CMockExpect(297, &prim);

}





void test_Error_Respuesta_NO_Definida(void){

 char Text_ID[30];



 printf("\n *** Inicio de Pruebas de Error: Respuesta NO DEFINIDA  ***");

 for(caso_actual = 0; caso_actual < sizeof(Casos_Errores) / sizeof(struct Casos_Prueba_s); caso_actual++){

  printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);



  Cambio_De_Estado((Casos_Prueba_t *)Casos_Errores);



  FullCheck (&prim,Casos_Errores[caso_actual].Transicion_Alarma,

    Casos_Errores[caso_actual].Transicion_Falla,

    Casos_Errores[caso_actual].Transicion_Normal,

    Casos_Errores[caso_actual].Transicion_Alarma_Falla);



  sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);

  UnityAssertEqualNumber((UNITY_INT)((Casos_Errores[caso_actual].Expected_Result)), (UNITY_INT)((prim.state)), ((Text_ID)), (UNITY_UINT)(316), UNITY_DISPLAY_STYLE_INT);

 }

 printf("\n ___ Final de Pruebas de Error: Respuesta NO DEFINIDA  __");

}





void test_Prueba_Casos_Alarma(void){

 char Text_ID[30];

 printf("\n *** Inicio de Pruebas de Alarma ***");

 for(caso_actual = 0; caso_actual < sizeof(Casos_Alarma) / sizeof(struct Casos_Prueba_s); caso_actual++){

  printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);



  Cambio_De_Estado((Casos_Prueba_t *)Casos_Alarma);



  FullCheck (&prim,Casos_Alarma[caso_actual].Transicion_Alarma,

    Casos_Alarma[caso_actual].Transicion_Falla,

    Casos_Alarma[caso_actual].Transicion_Normal,

    Casos_Alarma[caso_actual].Transicion_Alarma_Falla);



  sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);

  UnityAssertEqualNumber((UNITY_INT)((Casos_Alarma[caso_actual].Expected_Result)), (UNITY_INT)((prim.state)), ((Text_ID)), (UNITY_UINT)(336), UNITY_DISPLAY_STYLE_INT);

 }

 printf("\n __ Final de Pruebas de Alarma __");

}





void test_Prueba_Casos_Falla(void){

 char Text_ID[30];

 printf("\n *** Inicio de Pruebas de Falla ***");

 for(caso_actual = 0; caso_actual < sizeof(Casos_Falla) / sizeof(struct Casos_Prueba_s); caso_actual++){

  printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);



  Cambio_De_Estado((Casos_Prueba_t *)Casos_Falla);



  FullCheck (&prim,Casos_Falla[caso_actual].Transicion_Alarma,

    Casos_Falla[caso_actual].Transicion_Falla,

    Casos_Falla[caso_actual].Transicion_Normal,

    Casos_Falla[caso_actual].Transicion_Alarma_Falla);



  sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);

  UnityAssertEqualNumber((UNITY_INT)((Casos_Falla[caso_actual].Expected_Result)), (UNITY_INT)((prim.state)), ((Text_ID)), (UNITY_UINT)(356), UNITY_DISPLAY_STYLE_INT);

 }

 printf("\n __ Final de Pruebas de Falla __");

}





void test_Prueba_Casos_Normal(void){

 char Text_ID[30];



 printf("\n *** Inicio de Pruebas de Normal ***");

 for(caso_actual = 0; caso_actual < sizeof(Casos_Normal) / sizeof(struct Casos_Prueba_s); caso_actual++){

  printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);

  Cambio_De_Estado((Casos_Prueba_t *)Casos_Normal);



  FullCheck (&prim,Casos_Normal[caso_actual].Transicion_Alarma,

    Casos_Normal[caso_actual].Transicion_Falla,

    Casos_Normal[caso_actual].Transicion_Normal,

    Casos_Normal[caso_actual].Transicion_Alarma_Falla);



  sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);

  UnityAssertEqualNumber((UNITY_INT)((Casos_Normal[caso_actual].Expected_Result)), (UNITY_INT)((prim.state)), ((Text_ID)), (UNITY_UINT)(376), UNITY_DISPLAY_STYLE_INT);

 }

 printf("\n __ Final de Pruebas de Normal __");

}





void test_Logica_Transicion_de_Estados(void){



 char Text_ID[30];



 printf("\n *** Inicio de Pruebas Generales ***");

 for(caso_actual = 0; caso_actual < sizeof(Casos_General) / sizeof(struct Casos_Prueba_s); caso_actual++){

  printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);

  Cambio_De_Estado((Casos_Prueba_t *)Casos_General);

  primControl(&prim);

  sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);

  UnityAssertEqualNumber((UNITY_INT)((Casos_General[caso_actual].Expected_Result)), (UNITY_INT)((prim.state)), ((Text_ID)), (UNITY_UINT)(392), UNITY_DISPLAY_STYLE_INT);

 }

 printf("\n __ Final de Pruebas Generales __");

}





void test_Error_Estado_NO_Definido(void){



 char Text_ID[30];

 prim.state=NO_STATE;

 primControl(&prim);

 UnityAssertEqualNumber((UNITY_INT)((FAIL)), (UNITY_INT)((prim.state)), (

((void *)0)

), (UNITY_UINT)(403), UNITY_DISPLAY_STYLE_INT);

}
