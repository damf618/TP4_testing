/*
 **===== Casos de Prueba ---¡COMPLETADAS!---=====
 * -- Al leer HIGH en el Contacto de "Alarma", se debe activar el estado asociado a "Alarma".
 * -- Al leer HIGH en el Contacto de "Falla", se debe activar el estado asociado a "Falla"
 * -- Al recibir el codigo RF de "Alarma", se debe activar el estado asociado a "Alarma".
 * -- Al recibir el codigo RF de "Falla", se debe activar el estado asociado a "Falla".
 * -- Al recibir el codigo RF de "Normal" y no existir un estado de "Alarma" o "Falla" activo, se debe activar el estado asociado a "Normal".
 * -- El estado recibido por codigos RF, tiene igual prioridad que el estado de los Contactos.
 * -- El estado de "Alarma" tiene mayor prioridad que el estado "Falla".
 * -- El estado de "Falla" tiene mayor prioridad que el estado de "Alarma".
 * -- En caso de recibir un estado NO contemplado, el sistema debera pasar al estado de Falla directamente.
 *
 *
 * -- La presencia de Alarmas y Fallas, no es excluyente, el sistema debe poder indicar la presencia de ambos eventos.
 * -- La transicion normal entre estados primario debe ser precedida por estados secundarios.
 * -- La transicion de ALARM_FAIL a ALARM o a FAIL es directa, ya que fue previamente precedida por un estado secundario.
 * -- En caso de estar en un estado NO contemplado, elsistema debera pasaral estadode Falla directamente.
 *
 * **===== Casos de Prueba ---¡COMPLETADAS!---=====
 * --
 *
 **===== Casos de Prueba ---¡PENDIENTES!---=====
 *
 * -- Se debe recibir un codigo RF, en un maximo de T segundos,de lo contrario se debe activar el estado de "Falla"
 *
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

static const Casos_Prueba_t Casos_Alarma[]= {
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

static const Casos_Prueba_t Casos_Falla[]= {
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

static const Casos_Prueba_t Casos_Normal[]= {
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

static const Casos_Prueba_t Casos_General[]= {
	{
	//NORMAL --> PREALARM
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
	//PREALARM --> ALARM
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
	//ALARM --> PRE_ALARM_FAIL
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
	//PRE_ALARM_FAIL --> ALARM_FAIL
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
	//ALARM_FAIL --> FAIL
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
	//FAIL-->PREALARM
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
	//PREALARM-->ALARM
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
	//ALARM-->PRENORMAL
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
	//PRENORMAL-->NORMAL
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
	//ERROR RESPUESTA NO CONTEMPLADA COMM
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
	//ERROR RESPUESTA NO CONTEMPLADA LOCAL ALARM
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
	//ERROR RESPUESTA NO CONTEMPLADA LOCAL FAIL
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
	ButtonCheck_ExpectAndReturn(&prim,Caso_de_Estudio[caso_actual].Transicion_Alarma,	//--> Transicion en caso de Alarma
	Caso_de_Estudio[caso_actual].Transicion_Normal,										//--> Transicion en caso de Normal
	ALARM,																				//--> Consulta de Contacto de Alarma
	Caso_de_Estudio[caso_actual].Local_Alarm_Response);									//--> Respuesta Esperada del Contacto de Alarma

	ButtonCheck_ExpectAndReturn(&prim,Caso_de_Estudio[caso_actual].Transicion_Falla,	//--> Transicion en caso de Falla
	Caso_de_Estudio[caso_actual].Transicion_Normal,										//--> Transicion en caso de Normal
	FAIL,																				//--> Consulta de Contacto de Falla
	Caso_de_Estudio[caso_actual].Local_Fail_Response);									//--> Respuesta Esperada del Contacto de Falla

	CommCheck_ExpectAndReturn(&prim,Caso_de_Estudio[caso_actual].Transicion_Alarma,		//--> Transicion en caso de Alarma
	Caso_de_Estudio[caso_actual].Transicion_Falla,										//--> Transicion en caso de Falla
	Caso_de_Estudio[caso_actual].Transicion_Normal,										//--> Transicion en caso de Normal
	Caso_de_Estudio[caso_actual].Comm_Response);										//--> Respuesta Esperada de la Comunicaion

	ResetChange_Expect(&prim);
}

//! @test Prueba de error ante respuesta con un Estado no definido.
void test_Error_Respuesta_NO_Definida(void){
	char Text_ID[30];

	printf("\n *** Inicio de Pruebas de Error: Respuesta NO DEFINIDA  ***");
	for(caso_actual = 0; caso_actual < sizeof(Casos_Errores) / sizeof(struct Casos_Prueba_s); caso_actual++){
		printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);

		Cambio_De_Estado((Casos_Prueba_t *)Casos_Errores);

		FullCheck (&prim,Casos_Errores[caso_actual].Transicion_Alarma,								//-->Transicion en caso de Alarma
				Casos_Errores[caso_actual].Transicion_Falla,										//-->Transicion en caso de Falla
				Casos_Errores[caso_actual].Transicion_Normal,										//--> Transicion en caso de Normal
				Casos_Errores[caso_actual].Transicion_Alarma_Falla);								//--> Transicion en caso de Alarma / Falla

		sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);
		TEST_ASSERT_EQUAL_MESSAGE(Casos_Errores[caso_actual].Expected_Result,prim.state,Text_ID);	// --> Prueba de Transicion Correcta de Estado
	}
	printf("\n ___ Final de Pruebas de Error: Respuesta NO DEFINIDA  __");
}

//! @test Prueba de Diferentes Posibilidades de Transicion a "Alarma".
void test_Prueba_Casos_Alarma(void){
	char Text_ID[30];
	printf("\n *** Inicio de Pruebas de Alarma ***");
	for(caso_actual = 0; caso_actual < sizeof(Casos_Alarma) / sizeof(struct Casos_Prueba_s); caso_actual++){
		printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);

		Cambio_De_Estado((Casos_Prueba_t *)Casos_Alarma);

		FullCheck (&prim,Casos_Alarma[caso_actual].Transicion_Alarma,							//-->Transicion en caso de Alarma
				Casos_Alarma[caso_actual].Transicion_Falla,										//-->Transicion en caso de Falla
				Casos_Alarma[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				Casos_Alarma[caso_actual].Transicion_Alarma_Falla);								//--> Transicion en caso de Alarma / Falla

		sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);
		TEST_ASSERT_EQUAL_MESSAGE(Casos_Alarma[caso_actual].Expected_Result,prim.state,Text_ID);	// --> Prueba de Transicion Correcta de Estado
	}
	printf("\n __ Final de Pruebas de Alarma __");
}

//! @test Prueba de Diferentes Posibilidades de Transicion a "Falla".
void test_Prueba_Casos_Falla(void){
	char Text_ID[30];
	printf("\n *** Inicio de Pruebas de Falla ***");
	for(caso_actual = 0; caso_actual < sizeof(Casos_Falla) / sizeof(struct Casos_Prueba_s); caso_actual++){
		printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);

		Cambio_De_Estado((Casos_Prueba_t *)Casos_Falla);

		FullCheck (&prim,Casos_Falla[caso_actual].Transicion_Alarma,							//-->Transicion en caso de Alarma
				Casos_Falla[caso_actual].Transicion_Falla,										//-->Transicion en caso de Falla
				Casos_Falla[caso_actual].Transicion_Normal,										//--> Transicion en caso de Normal
				Casos_Falla[caso_actual].Transicion_Alarma_Falla);								//--> Transicion en caso de Alarma / Falla

		sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);
		TEST_ASSERT_EQUAL_MESSAGE(Casos_Falla[caso_actual].Expected_Result,prim.state,Text_ID);	// --> Prueba de Transicion Correcta de Estado
	}
	printf("\n __ Final de Pruebas de Falla __");
}

//! @test Prueba de Diferentes Posibilidades de Transicion a "Normal".
void test_Prueba_Casos_Normal(void){
	char Text_ID[30];

	printf("\n *** Inicio de Pruebas de Normal ***");
	for(caso_actual = 0; caso_actual < sizeof(Casos_Normal) / sizeof(struct Casos_Prueba_s); caso_actual++){
		printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);
		Cambio_De_Estado((Casos_Prueba_t *)Casos_Normal);

		FullCheck (&prim,Casos_Normal[caso_actual].Transicion_Alarma,							//-->Transicion en caso de Alarma
				Casos_Normal[caso_actual].Transicion_Falla,										//-->Transicion en caso de Falla
				Casos_Normal[caso_actual].Transicion_Normal,									//--> Transicion en caso de Normal
				Casos_Normal[caso_actual].Transicion_Alarma_Falla);								//--> Transicion en caso de Alarma / Falla

		sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);
		TEST_ASSERT_EQUAL_MESSAGE(Casos_Normal[caso_actual].Expected_Result,prim.state,Text_ID);	// --> Prueba de Transicion Correcta de Estado
	}
	printf("\n __ Final de Pruebas de Normal __");
}

//! @test Prueba de Diferentes Posibilidades de Transicion.
void test_Logica_Transicion_de_Estados(void){

	char Text_ID[30];

	printf("\n *** Inicio de Pruebas Generales ***");
	for(caso_actual = 0; caso_actual < sizeof(Casos_General) / sizeof(struct Casos_Prueba_s); caso_actual++){
		printf("\n *** Ejecutando Caso de Prueba Nro: %d ***",caso_actual);
		Cambio_De_Estado((Casos_Prueba_t *)Casos_General);
		primControl(&prim);
		sprintf(Text_ID,"Caso de Prueba Nro: %d",caso_actual);
		TEST_ASSERT_EQUAL_MESSAGE(Casos_General[caso_actual].Expected_Result,prim.state,Text_ID);	// --> Prueba de Transicion Correcta de Estado
	}
	printf("\n __ Final de Pruebas Generales __");
}

//! @test Prueba de error ante Estado no definido.
void test_Error_Estado_NO_Definido(void){

	char Text_ID[30];
	prim.state=NO_STATE;
	primControl(&prim);
	TEST_ASSERT_EQUAL(FAIL,prim.state);	// --> Prueba de Transicion Correcta de Estado
}

