/*
 **===== Casos de Prueba ---¡COMPLETADAS!---=====
 * -- Al leer HIGH en el Contacto de "Alarma", se debe activar el estado de "Alarma"
 * -- Al leer HIGH en el Contacto de "Falla", se debe activar el estado de "Falla"
 * --
 * --
 * --
 * **===== Casos de Prueba ---¡COMPLETADAS!---=====
 * --
 *
 **===== Casos de Prueba ---¡PENDIENTES!---=====
 *
 * -- Al recibir el codigo RF de "Alarma", se debe activar el estado de "Alarma".
 * -- Al recibir el codigo RF de "Falla", se debe activar el estado de "Falla".
 * -- Al recibir el codigo RF de "Normal", se debe activar el estado de "Normal".
 * -- Al recibir el codigo RF de "Normal", se debe activar el estado de "Normal".
 * -- La ausencia de eventos de "Alarma"/"Falla", se considera la presencia de estado "Normal".
 * -- El estado recibido por codigos RF, tiene igual prioridad que el estado de los Contactos
 * -- El estado de "Alarma" tiene mayor prioridad que el estado "Falla".
 * -- El estado de "Falla" tiene mayor prioridad que el estado de "Alarma".
 * -- Se debe recibir un codigo RF, en un maximo de T segundos,de lo contrario se debe activar el estado de "Falla"
 *
*/

#include "unity.h"
#include "TP4_Testing.h"
#include "mock_primario4.h"


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
	//TRANSICION NORMAL --> ALARMA /**/ CONTACTO
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
		//TRANSICION NORMAL --> ALARMA  /**/ COMM
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
		//TRANSICION NORMAL --> FALLA  /**/ CONTACTO
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
		//TRANSICION NORMAL --> FALLA  /**/ COMM
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
		//TRANSICION FALLA --> NORMAL  /**/ CONTACTO
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
		//TRANSICION ALARMA --> NORMAL  /**/ COMM
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
	//NORMAL
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
	//ALARMA
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
	//FAIL
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
		//ALARM-FAIL
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
	//PRENORMAL
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
	//PREALARMA
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
	//PREFAIL
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
	//PREALARM-FAIL
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
	ButtonCheck_ExpectAndReturn(&prim,Casos_General[caso_actual].Transicion_Alarma,	//--> Transicion en caso de Alarma
	Casos_General[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
	ALARM,																			//--> Consulta de Contacto de Alarma
	Casos_General[caso_actual].Local_Alarm_Response);								//--> Respuesta Esperada del Contacto de Alarma

	ButtonCheck_ExpectAndReturn(&prim,Casos_General[caso_actual].Transicion_Falla,	//--> Transicion en caso de Falla
	Casos_General[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
	FAIL,																			//--> Consulta de Contacto de Falla
	Casos_General[caso_actual].Local_Fail_Response);								//--> Respuesta Esperada del Contacto de Falla

	CommCheck_ExpectAndReturn(&prim,Casos_General[caso_actual].Transicion_Alarma,	//--> Transicion en caso de Alarma
	Casos_General[caso_actual].Transicion_Falla,									//--> Transicion en caso de Falla
	Casos_General[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
	Casos_General[caso_actual].Comm_Response);										//--> Respuesta Esperada de la Comunicaion

	ResetChange_Expect(&prim);
}

void setUp(void) {
	//Estado Normal
	prim.state = Casos_Alarma[caso_actual].Estado_Inicial;
}

//! @test Prueba de Diferentes Posibilidades de Transicion a "Alarma".
void test_Prueba_Casos_Alarma(void){
	char Text_ID[30];
	printf("\n *** Inicio de Pruebas de Alarma ***");
	for(caso_actual = 0; caso_actual < sizeof(Casos_Alarma) / sizeof(struct Casos_Prueba_s); caso_actual++){

		printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);

		ButtonCheck_ExpectAndReturn(&prim,Casos_Alarma[caso_actual].Transicion_Alarma,			//--> Transicion en caso de Alarma
				Casos_Alarma[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				ALARM,																			//--> Consulta de Contacto de Alarma
				Casos_Alarma[caso_actual].Local_Alarm_Response);								//--> Respuesta Esperada del Contacto de Alarma

		ButtonCheck_ExpectAndReturn(&prim,Casos_Alarma[caso_actual].Transicion_Falla,			//--> Transicion en caso de Falla
				Casos_Alarma[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				FAIL,																			//--> Consulta de Contacto de Falla
				Casos_Alarma[caso_actual].Local_Fail_Response);									//--> Respuesta Esperada del Contacto de Falla

		CommCheck_ExpectAndReturn(&prim,Casos_Alarma[caso_actual].Transicion_Alarma,			//--> Transicion en caso de Alarma
				Casos_Alarma[caso_actual].Transicion_Falla,										//--> Transicion en caso de Falla
				Casos_Alarma[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				Casos_Alarma[caso_actual].Comm_Response);										//--> Respuesta Esperada de la Comunicaion

		ResetChange_Expect(&prim);

		FullCheck (&prim,Casos_Alarma[caso_actual].Transicion_Alarma,							//-->Transicion en caso de Alarma
				Casos_Alarma[caso_actual].Transicion_Falla,										//-->Transicion en caso de Falla
				Casos_Alarma[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				Casos_Alarma[caso_actual].Transicion_Alarma_Falla);								//--> Transicion en caso de Alarma / Falla

		sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);
		TEST_ASSERT_EQUAL_MESSAGE(Casos_Alarma[caso_actual].Expected_Result,prim.state,Text_ID);	// --> Prueba de Transicion Correcta de Estado
	}
	printf("\n *** Final de Pruebas de Alarma ***");
}

//! @test Prueba de Diferentes Posibilidades de Transicion a "Falla".
void test_Prueba_Casos_Falla(void){
	char Text_ID[30];
	printf("\n *** Inicio de Pruebas de Falla ***");
	for(caso_actual = 0; caso_actual < sizeof(Casos_Falla) / sizeof(struct Casos_Prueba_s); caso_actual++){

		printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);

		ButtonCheck_ExpectAndReturn(&prim,Casos_Falla[caso_actual].Transicion_Alarma,			//--> Transicion en caso de Alarma
				Casos_Falla[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				ALARM,																			//--> Consulta de Contacto de Alarma
				Casos_Falla[caso_actual].Local_Alarm_Response);								//--> Respuesta Esperada del Contacto de Alarma

		ButtonCheck_ExpectAndReturn(&prim,Casos_Falla[caso_actual].Transicion_Falla,			//--> Transicion en caso de Falla
				Casos_Falla[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				FAIL,																			//--> Consulta de Contacto de Falla
				Casos_Falla[caso_actual].Local_Fail_Response);									//--> Respuesta Esperada del Contacto de Falla

		CommCheck_ExpectAndReturn(&prim,Casos_Falla[caso_actual].Transicion_Alarma,			//--> Transicion en caso de Alarma
				Casos_Falla[caso_actual].Transicion_Falla,										//--> Transicion en caso de Falla
				Casos_Falla[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				Casos_Falla[caso_actual].Comm_Response);										//--> Respuesta Esperada de la Comunicaion

		ResetChange_Expect(&prim);

		FullCheck (&prim,Casos_Falla[caso_actual].Transicion_Alarma,							//-->Transicion en caso de Alarma
				Casos_Falla[caso_actual].Transicion_Falla,										//-->Transicion en caso de Falla
				Casos_Falla[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				Casos_Falla[caso_actual].Transicion_Alarma_Falla);								//--> Transicion en caso de Alarma / Falla

		sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);
		TEST_ASSERT_EQUAL_MESSAGE(Casos_Falla[caso_actual].Expected_Result,prim.state,Text_ID);	// --> Prueba de Transicion Correcta de Estado
	}
	printf("\n *** Final de Pruebas de Falla ***");
}

//! @test Prueba de Diferentes Posibilidades de Transicion a "Normal".
void test_Prueba_Casos_Normal(void){
	char Text_ID[30];

	printf("\n *** Inicio de Pruebas de Normal ***");
	for(caso_actual = 0; caso_actual < sizeof(Casos_Normal) / sizeof(struct Casos_Prueba_s); caso_actual++){

		printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);
		ButtonCheck_ExpectAndReturn(&prim,Casos_Normal[caso_actual].Transicion_Alarma,			//--> Transicion en caso de Alarma
				Casos_Normal[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				ALARM,																			//--> Consulta de Contacto de Alarma
				Casos_Normal[caso_actual].Local_Alarm_Response);								//--> Respuesta Esperada del Contacto de Alarma

		ButtonCheck_ExpectAndReturn(&prim,Casos_Normal[caso_actual].Transicion_Falla,			//--> Transicion en caso de Falla
				Casos_Normal[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				FAIL,																			//--> Consulta de Contacto de Falla
				Casos_Normal[caso_actual].Local_Fail_Response);									//--> Respuesta Esperada del Contacto de Falla

		CommCheck_ExpectAndReturn(&prim,Casos_Normal[caso_actual].Transicion_Alarma,			//--> Transicion en caso de Alarma
				Casos_Normal[caso_actual].Transicion_Falla,										//--> Transicion en caso de Falla
				Casos_Normal[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				Casos_Normal[caso_actual].Comm_Response);										//--> Respuesta Esperada de la Comunicaion

		ResetChange_Expect(&prim);

		FullCheck (&prim,Casos_Normal[caso_actual].Transicion_Alarma,							//-->Transicion en caso de Alarma
				Casos_Normal[caso_actual].Transicion_Falla,										//-->Transicion en caso de Falla
				Casos_Normal[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				Casos_Normal[caso_actual].Transicion_Alarma_Falla);								//--> Transicion en caso de Alarma / Falla

		sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);
		TEST_ASSERT_EQUAL_MESSAGE(Casos_Normal[caso_actual].Expected_Result,prim.state,Text_ID);	// --> Prueba de Transicion Correcta de Estado
	}
	printf("\n *** Final de Pruebas de Normal ***");
}

//! @test Prueba de Diferentes Posibilidades de Transicion.
void test_Logica_Transicion_de_Estados(void){

	char Text_ID[30];

		printf("\n *** Inicio de Pruebas Generales ***");
		for(caso_actual = 0; caso_actual < sizeof(Casos_General) / sizeof(struct Casos_Prueba_Gral_s); caso_actual++){
			printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);
			printf("\n *** Estado Actual: %d ***",prim.state);
			Cambio_De_Estado();
			primControl(&prim);
			sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);
			TEST_ASSERT_EQUAL_MESSAGE(Casos_General[caso_actual].Expected_Result,prim.state,Text_ID);	// --> Prueba de Transicion Correcta de Estado
			prim.state=Casos_General[caso_actual].Next_State;
		}
}

