/* 
 Projeto Semestral - LG1A1 
 Leonardo Galindo da Silva - SP3081656 
 Guilherme Nara de Souza Stambonsky - SP3082156 
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

#define   MAX  4 /* máximo de pessoas na fila */

int fila[MAX];
int inicioFila, finalFila, maximo, numeroPedido;

char menuOpcoes (void);
void admin (char tecla);
int encaminha (void);
int atendeFila (void);

char menuOpcoes (void)
{
	char opcao;
	system("cls");
	printf("\n _____________ GERENCIAMENTO FILA________________\n");
    printf("\n 1- Encaminhar cliente");
    printf("\n 2- Atender fila");
    printf("\n 3- Consultar fila");
    printf("\n 4- Sair");
    printf("\n ________________________________________________");
    printf("\n Escolha: ");
    fflush(stdin);
    opcao = getche();
    return opcao;      
}

void admin (char tecla)
{
	switch(tecla)
	{
		case '1': encaminha();
		break;
		
		case '2': atendeFila();
		break;
		
		case '3': consultaFila();
		break;
		
		case'4': exit(0);
		
		default: printf("\n Opção inválida!!!!");
		
		getch();
	}
}

int encaminha (void)
{
	char escolha;
	printf("\n\n\n Atendendo pedido: %02i", numeroPedido);
	printf("\n Este pedido vai para fila? SIM = [S/s]: ");
	fflush(stdin);
	escolha = getche();
	if(escolha == 'S' || escolha == 's')
	{
		if(finalFila == MAX) /* valida se a fila está cheia */
		{
			printf("\n Fila lotada!!");
			getch();
		} else {
			fila[finalFila] = numeroPedido;
			finalFila++;
		}
	}
	numeroPedido++;
	getch();
}

int atendeFila (void)
{
	int aux;
	if(inicioFila == finalFila) /* valida se a fila esta vazia */
	{
		printf("\n Fila vazia!!");
		inicioFila = finalFila = 0;
		getch();
	} else {
		printf("\n\n Pedido a ser atendido: %02i", fila[inicioFila]);
		inicioFila++;
		maximo = finalFila;
		for (aux = 1; aux < maximo; aux++) /* faz com que todos da fila andem para frente */ 
		{
			fila[aux-1] = fila[aux];
		}
		inicioFila = 0;
		finalFila--;
	}
	getch();
}


int consultaFila (void)
{
	int i;
	printf("\n\n Pedidos na fila: ");
	if(fila[MAX] == 0) /* valida se há pedidos na fila */
	{
		printf("nenhum!!");
	} else {
		for(i = inicioFila; i < finalFila; i++) /* varre pelos pedidos na fila */
		{
			printf("[%02i]", fila[i]);
		}
	}
	
	getch();
}


int main (void)
{	
	char opc;
	inicioFila = finalFila = 0; /* vila vazia */
	numeroPedido = 1; /* assumindo que o primeiro pedido é 1*/
	setlocale(LC_ALL, "");
	
	do{
        opc = menuOpcoes();              
        admin(opc);              
    }while(opc != '4');
	
	getch();	
	return 0;
}

