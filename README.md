# TP4_testing

## Prueba de la Logica del Dispositivo Primario.

### Casos de Prueba Considerados
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
