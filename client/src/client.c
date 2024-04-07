#include "client.h"



int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */


	logger = iniciar_logger();


	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "Hola! soy un log");
	


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	valor = config_get_string_value(config ,"CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");

	log_info(logger , valor);
	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//EL SERVER FUNCIONA OK 

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto); //PROBLEMA EN CREAR CONEXION

	enviar_mensaje(valor, conexion);
	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	printf ("Adjuntes los archivos a enviar al servidor: \n");

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}


t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	if((nuevo_logger =  log_create("tp0.log" , "tp0" , true ,LOG_LEVEL_INFO))== NULL){
		printf("no pude crear el logger \n");
		exit(1);
	}
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	if ((nuevo_config = config_create("/home/utnso/tp0/tp0/client/cliente.config")) == NULL) {
	printf("No se pudo crear un nuevo config\n");
	exit(2); // se pone un numeor diferente para saber el error que ocurrio 
	}

	printf("Config creada con exito.\n");
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	while(1){
	leido = readline("> ");  

	if(string_is_empty(leido)){  
		free(leido);
		//printf("sali por vacio \n");
		break;
	}
	log_info(logger ,leido);	
	free(leido);
	}

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	paquete = crear_paquete();
	while(1){

	leido = readline("> ");  

	if(string_is_empty(leido)){
	printf("No hay nada mas que empaquetar\n");

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);

	free(leido);

	break;
	}

	// Leemos y esta vez agregamos las lineas al paquete
	agregar_a_paquete(paquete, leido , strlen(leido)+ 1);

	free(leido);
	//Enviao el paquete mediante el socket "conexion"

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!

}
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{

	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	if(logger != NULL ){
		log_destroy(logger);

	}
	if(config != NULL) {
		config_destroy(config);
	}
	
	
		liberar_conexion(conexion);

}
