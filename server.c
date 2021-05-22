#include     <unistd.h>
#include     <netinet/in.h>//familia de protocolos de internet. sockaddr_in
#include     <arpa/inet.h>  //htonl, htons inet_atonl, inet_ntoal
#include     <sys/types.h>
#include     <sys/socket.h>
#include     <stdlib.h>
#include     <string.h>
#include     <stdio.h>

#define SIZE 255

char* concatenarMensajeAsientos(char *mensajeTx, char *asientosDisponibles, int asientosLinea,char *mensajeAsiento);

int main(){

	const int PORT = 7200;

	int socket_servidor, tam;
	int nuevo_cliente;
	int opcion_rx;

	int asientos_linea1[25][1];
  	int asientos_linea2[25][1];
  	int asientos_linea3[25][1];

	for (int i = 0; i < 25; i++){
    	asientos_linea1[i][0] = 10;
    	asientos_linea2[i][0] = 10;
    	asientos_linea3[i][0] = 10;
	}

 	char menu_tx[] = "\t-------------------\n\tLineas de Autobuses\n\t1.ADO\n\t2.Estrella Roja\n\t3.ORO\n";
  	char menu_destinos_tx[]= "\t-------------------\n\tDestinos\n\t1.Puebla\n\t2.Veracruz\n\t3.CDMX\n\t4.Morelos\n\t5.Oaxaca\n";
  	char menu_horario_tx[] = "\t-------------------\n\tHorarios\n\t1.5 AM\n\t2.9 AM\n\t3.1 PM\n\t4.5 PM\n\t5.10 PM\n";
  	char buff_rx[SIZE];

  	char mensaje_compra_tx[] = "Compra realizada.";
  	char mensaje_compra_rechazada_tx[] = "No hay asientos disponibles\n¿Volver a intentar?";
  	char mensaje_asientos[] = "Numero de asientos disponibles:";
  	char mensaje_salir[] = "saliendo...";

  	char mensaje_asientos_tx[65];
  	char mensaje_tx[65];
  	char asientos_disponibles[10];

  	struct sockaddr_in estructura_servidor;
  	socket_servidor = socket( AF_INET, SOCK_STREAM, 0 );
  	estructura_servidor.sin_family = AF_INET;//Familia TCP/IP
  	estructura_servidor.sin_port = htons(PORT);//PUERTO
  	estructura_servidor.sin_addr.s_addr = INADDR_ANY;//CUALQUIER CLIENTE PUEDE CONECTARSE
  	memset( &(estructura_servidor.sin_zero), '\0', 8 );
  	tam = sizeof( struct sockaddr );
  	bind( socket_servidor, (struct sockaddr *)&estructura_servidor,  tam);//se enlaza a un puerto
  	listen( socket_servidor, 5 );//modo escucha

	while( 1 ){ // bucle infinito para tratar conexiones 1
		nuevo_cliente = accept( socket_servidor,(struct sockaddr *)&estructura_servidor, &tam); //aceptamos a los clientes

		while(1){//2
			send( nuevo_cliente, menu_tx, sizeof(menu_tx), 0 );
	      	recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	      	opcion_rx = atoi(buff_rx);

	      	if(opcion_rx == 1){//linea 1
	      		send( nuevo_cliente, menu_destinos_tx, sizeof(menu_destinos_tx), 0 );
	        	recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	        	opcion_rx = atoi(buff_rx);

	      		if(opcion_rx == 1){//destino 1
	      			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	      			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[0][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[0][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[0][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[1][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[1][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[1][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}      				

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[2][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[2][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[2][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[3][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[3][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[3][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[4][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[4][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[4][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}

	       		if(opcion_rx == 2){//destino 2
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[5][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[5][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[5][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[6][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[6][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[6][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[7][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[7][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[7][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[8][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[8][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[8][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[9][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[9][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[9][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}
	       		if(opcion_rx == 3){//destino 3
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[10][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[10][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[10][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[11][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[11][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[11][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[12][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[12][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[12][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[13][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[13][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[13][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[14][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[14][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[14][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}

	       		if(opcion_rx == 4){//destino 4
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[15][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[15][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[15][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[16][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[16][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[16][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[17][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[17][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[17][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[18][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[18][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[18][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[19][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[19][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[19][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}
	       		if(opcion_rx == 5){//destino 5
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[20][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[20][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[20][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[21][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[21][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[21][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[22][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[22][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[22][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[23][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[23][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[23][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea1[24][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea1[24][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea1[24][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}
	       	}//linea 1

			if(opcion_rx == 2){//linea 2
				send( nuevo_cliente, menu_destinos_tx, sizeof(menu_destinos_tx), 0 );
	        	recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	        	opcion_rx = atoi(buff_rx);

				if(opcion_rx == 1){//destino 1
					send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
					recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
					opcion_rx = atoi(buff_rx);

					if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[0][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[0][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[0][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

					}
					if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[1][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[1][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[1][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

					}
					if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[2][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[2][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[2][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

					}
					if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[3][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[3][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[3][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

					}
					if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[4][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[4][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[4][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

					}
				}
	       		if(opcion_rx == 2){//destino 2
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[5][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[5][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[5][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[6][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[6][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[6][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[7][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[7][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[7][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[8][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[8][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[8][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[9][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[9][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[9][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}
	       		if(opcion_rx == 3){//destino 3
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[10][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[10][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[10][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[11][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[11][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[11][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[12][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[12][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[12][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[13][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[13][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[13][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[14][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[14][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[14][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}

	       		if(opcion_rx == 4){//destino 4
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[15][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[15][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[15][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}


	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[16][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[16][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[16][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[17][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[17][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[17][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[18][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[18][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[18][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[19][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[19][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[19][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}
	       		if(opcion_rx == 5){//destino 5
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[20][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[20][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[20][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[21][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[21][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[21][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[22][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[22][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[22][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[23][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[23][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[23][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea2[24][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea2[24][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea2[24][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}

	       	}//linea 2

			if(opcion_rx == 3){//linea 3
				send( nuevo_cliente, menu_destinos_tx, sizeof(menu_destinos_tx), 0 );
	        	recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	        	opcion_rx = atoi(buff_rx);

				if(opcion_rx == 1){//destino 1
					send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

					if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[0][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[0][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[0][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

					}
					if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[1][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[1][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[1][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

					}
					if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[2][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[2][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[2][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

					}
					if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[3][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[3][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[3][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

					}
					if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[4][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[4][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[4][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

					}
				}
	       		if(opcion_rx == 2){//destino 2
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[5][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[5][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[5][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[6][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[6][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[6][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[7][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[7][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[7][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[8][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[8][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[8][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[9][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[9][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[9][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}
	       		if(opcion_rx == 3){//destino 3
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[10][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[10][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[10][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[11][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[11][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[11][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[12][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[12][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[12][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[13][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[13][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[13][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[14][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[14][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[14][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}

	       		if(opcion_rx == 4){//destino 4
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[15][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[15][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[15][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[16][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[16][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[16][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[17][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[17][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[17][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[18][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[18][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[18][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[19][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[19][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[19][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}
	       		if(opcion_rx == 5){//destino 5
	       			send( nuevo_cliente, menu_horario_tx, sizeof(menu_horario_tx), 0 );
	          		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	          		opcion_rx = atoi(buff_rx);

	       			if(opcion_rx == 1){//hora 1
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[20][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[20][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[20][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 2){//hora 2
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[21][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[21][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[21][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 3){//hora 3
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[22][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[22][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[22][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 4){//hora 4
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[23][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[23][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[23][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}
	      			if(opcion_rx == 5){//hora 5
	      				strcpy(mensaje_tx, concatenarMensajeAsientos(mensaje_asientos_tx, asientos_disponibles, asientos_linea3[24][0],mensaje_asientos));
	            		send( nuevo_cliente,mensaje_tx,sizeof(mensaje_tx),0);//muestra numero de asientos
	            		recv( nuevo_cliente, buff_rx, SIZE-1, 0 );

	            		if (strcmp(buff_rx,"s") == 0){
	              			if(asientos_linea3[24][0] > 0){//si hay asientos
	                			send( nuevo_cliente,mensaje_compra_tx,sizeof(mensaje_compra_tx),0);//muestra numero de asientos
	                			asientos_linea3[24][0]--;
	               				break;
	              			}else{//si no hay boletos
	                			send( nuevo_cliente,mensaje_compra_rechazada_tx,sizeof(mensaje_compra_rechazada_tx),0);
	                			recv( nuevo_cliente, buff_rx, SIZE-1, 0 );
	                			if (strcmp(buff_rx,"n") == 0){
	                  				send( nuevo_cliente,mensaje_salir,sizeof(mensaje_salir),0);
	                  				break;
	                			}
	              			}
	            		}

	      			}

	       		}

	       	}//linea 3
       
   		}//salir while 2
   		
    	close( nuevo_cliente );
    	printf("[Exit]\n");
	}//salir while 1

	return 0;

}//salir main

char* concatenarMensajeAsientos(char *mensajeTx, char *asientosDisponibles, int asientosLinea,char *mensajeAsiento)
{
  sprintf(asientosDisponibles, " %d" ,asientosLinea);
  strcpy(mensajeTx, mensajeAsiento);
  strcat(mensajeTx, asientosDisponibles);
  strcat(mensajeTx, "\n¿Desea Comprar boleto? s/n");

  return mensajeTx;
}
       