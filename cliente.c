#include    <unistd.h>
#include    <netinet/in.h>
#include    <arpa/inet.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>

#define SIZE 255

int main(int argc, char *argv[])
{

  char opcion[2];
  int conectar_servidor;
  int tam;
  int valor;
  char buf_tx[]= "cliente xs";
  char buff_rx[SIZE];
  int opcion_tx;

  struct sockaddr_in mi_estructura;
  conectar_servidor = socket( AF_INET, SOCK_STREAM, 0);
  mi_estructura.sin_family = AF_INET;
  mi_estructura.sin_port = htons( atoi( argv[2] ) );
  inet_aton( argv[1], &(mi_estructura.sin_addr) );
  memset( &(mi_estructura.sin_zero), '\0', 8 );  
  tam = sizeof( struct sockaddr );
  connect( conectar_servidor, (struct sockaddr *)&mi_estructura, tam );
  while(1){
    recv( conectar_servidor, buff_rx, SIZE-1, 0 );

    int i = strcmp(buff_rx,"Compra realizada.");
    int j = strcmp(buff_rx,"saliendo...");

    if (i == 0){
      printf("%s\n", buff_rx);
      break;
    }
    if (j == 0){
      break;
    }
    printf("%s\n", buff_rx);
    printf("\n\t\t[ ");
    printf("]" );
    printf("\x1b[2D");
    scanf(" %s", opcion);
    send( conectar_servidor, opcion, sizeof(opcion), 0 );
  }
  
  close( conectar_servidor );
  printf("[Conexion Cerrada]\n");

 return 0;
}

