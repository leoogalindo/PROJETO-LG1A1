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

typedef struct
{
     int codProd; /* código do produto */
     char nomeProd[256]; /* nome do produto */   
     float costProd; /* valor unitário do produto */
} produto;

typedef struct
{
     produto prod;
     int quantProd;
     float costFinal;   
} pedido;

typedef struct
{
     int numeroPedido;           
     char numeroCartao [16+1];      
} cartao;
typedef struct
{
     int numeroPedido;
	 char *FormaPgto;           
     float costFinal;     
} pagamento;

/* variáveis globais */
int i;
FILE *arq;
FILE *Dat;
cartao Cartao;
pagamento pagtosFeitos[1];
pagamento pagto;
produto itens[10];
pedido itensPedido[10];
int ValorTotal;

int mostraMenu(void);
int fazPedido (void);
int pagtoDinheiro (void);
char menuCobranca (void);
void admin (char tecla);
int pagtoCartao (void);
int pagtoDinheiro (void);
int pagtoCheque (void);
int main ();

int mostraMenu(void)
{
    int i;
    arq = fopen ("PRODUTOS.DAT", "r+b");
    if(arq == NULL)
    {
          printf("\n Erro ao abrir o arquivo PRODUTOS.DAT");
          getch();               
          exit(0);        
    }
    while(!feof(arq))
    {
          fread(&itens, sizeof(itens), 1, arq);                      
    }
    printf("______________________________________________");
    printf("\n             FAÇA SEU PEDIDO                  ");
    printf("\n______________________________________________");
    printf("\n\n\n CodProd        NomeProd        CustoProd");
    printf("\n______________________________________________");
    /* varre os elementos dentro de itens */
    for(i = 0; i < 10; i++)
    {
        printf("\n %02i %20s %14.2f", itens[i].codProd, itens[i].nomeProd, itens[i].costProd);      
    }  
    fclose(arq);
}

int fazPedido (void)
{
    int item, quant, achou, inicio;
    float total;
    char opc;
    do
    {
        printf("\n\n\n Insira o código do produto desejado: ");
        fflush(stdin);
        scanf("%i", &item); 
        
        printf("\n Insira a quantidade do produto desejado: ");     
        fflush(stdin);
        scanf("%i", &quant);
        
        achou = 0; /* flag */
        for(i = 0; i <= 10; i++)
        {
              if(item == itens[i].codProd) /* valida o nro do item digitado */
              {
                      itensPedido[inicio].prod = itens[i];
                      itensPedido[inicio].quantProd = quant;
                      itensPedido[inicio].costFinal = quant * itens[i].costProd;
                      achou = 1;
                      inicio++;
              }         
        }
        if(achou == 0)
        {
              printf("\n Código não encontrado!");         
        }    
        printf("\n Deseja pedir algo mais? [n/N = não]: ");       
        fflush(stdin); 
        opc = getche();                       
    }while(opc != 'N' && opc != 'n');
    
    system("cls");
    system("mode 110, 20");
    printf("\n Código              Produto                 Custo (R$)            Quantidade         Valor do item (R$)");
    printf("\n------------------------------------------------------------------------------------------------------------");
    for(i = 0; i <= inicio - 1; i++)
    {
          total += itensPedido[i].costFinal;
          printf("\n %02i          %20s               %.2f                %2i                 %.2f  ", itensPedido[i].prod.codProd, itensPedido[i].prod.nomeProd, itensPedido[i].prod.costProd, itensPedido[i].quantProd, itensPedido[i].costFinal);      
    }
    printf("\n------------------------------------------------------------------------------------------------------------");
    printf("\n Total: R$ %.2f", total); 
    ValorTotal= total;
    getch(); 
}

char menuCobranca (void)
{
     char opc;
     system("cls");
     printf("\n ============= MENU DE COBRANÇA =============");
     printf("\n 1-Dinheiro");
     printf("\n 2-Cartão");
     printf("\n 3-Cheque");
     printf("\n 4-Sair");
     printf("\n Escolha: ");
     fflush(stdin);
     opc = getche();
     return opc;         
}

void admin (char tecla)
{
     switch(tecla)
     {
           case '1': pagtoDinheiro();      
           break; 
           
           case '2': pagtoCartao();
           break;
           
           case '3': pagtoCheque();
           break;
           
           case '4': exit(0);
           break;
           
           default: printf("\n Opção inválida");
           getch();     
     }     
}

int pagtoCartao (void)
{
    int tam;
    system("cls");
    printf("\n======== PAGAMENTO EM CARTÃO ========");
    
    	do {
      	system("cls");
    	   printf("\n Insira o número do cartão: ");
    	   fflush(stdin);
    	   gets(Cartao.numeroCartao);
    	   tam = strlen(Cartao.numeroCartao); /* armazena o tamanho do numero do cartao digitado */
           if(tam == 16){
           	break;}
		   printf("\n Cartão inválido!");
           printf("\n Seu cartão deve ter 16 digitos");
           printf("\n Digite enter para digitar novamente");
           getch();
		}while(tam != 16);
		   printf("\n Parabéns compra aprovada!"); 
           printf("\n Pressione qualquer tecla para ver PAGAMENTOS.DAT");
           getch();
           
           system("cls");
    	Dat = fopen("PAGAMENTOS.DAT", "a+b");
    if(Dat == NULL)
    {
          printf("\n Erro em abrir PAGAMENTOS.DAT");
          getch();       
          exit(0);                 
    }
    system("cls");
    while(!feof(Dat))
    		{
          	fread(&pagtosFeitos, sizeof(pagtosFeitos), 1, Dat);                      
    		}
    printf("\n_________________________________________");
    printf("\nNro Pedido      Forma Pagto      Valor");
    printf("\n_________________________________________");
    pagamento pagto = {pagtosFeitos[0].numeroPedido+1, "Cartao", ValorTotal};
    fwrite(&pagto, sizeof(pagto), 1, Dat);
	fclose(Dat);    
	printf("\n %02i		 %s	  R$ %.2f", pagto.numeroPedido, pagto.FormaPgto, pagto.costFinal); 
    printf("\n Pressione qualquer tecla para acessar CARTOES.DAT");
    getch();
    system("cls");
     // gravando no arquivo DAT 
    Dat = fopen("CARTOES.DAT", "a+b");
        if(Dat == NULL)
        {
        printf("\n Erro em abrir CARTOES.DAT");
        getch();       
        exit(0);                 
        }
    printf("\n_________________________________________");
    printf("\nNro Pedido      Numero Cartao ");
    printf("\n_________________________________________");
	for(i=4;i<12;i++){
		Cartao.numeroCartao[i]='*';
	}
    Cartao.numeroPedido = pagto.numeroPedido;
	printf("\n%3i		 %16s", Cartao.numeroPedido, Cartao.numeroCartao);
    fwrite(&Cartao, sizeof(Cartao), 1, Dat);                 
    fclose(Dat);
    getch();
	system("cls");
	system("color 0D");
    printf("\nPEDIDO PAGO COM CARTÃO");  
    getch();
}

int pagtoDinheiro (void)
{
    Dat = fopen("PAGAMENTOS.DAT", "a+b");
    if(Dat == NULL)
    {
          printf("\n Erro em abrir PAGAMENTOS.DAT");
          getch();       
          exit(0);                 
    }
    system("cls");
    while(!feof(Dat))
    		{
          	fread(&pagtosFeitos, sizeof(pagtosFeitos), 1, Dat);                      
    		}
    printf("\n_________________________________________");
    printf("\nNro Pedido      Forma Pagto      Valor");
    printf("\n_________________________________________");
    pagamento pagto = {pagtosFeitos[0].numeroPedido+1, "Dinheiro", ValorTotal};
    fwrite(&pagto, sizeof(pagto), 1, Dat);
	fclose(Dat);    
	printf("\n %02i		 %s	  R$ %.2f", pagto.numeroPedido, pagto.FormaPgto, pagto.costFinal); 
	getch();
	system("cls");
		system("color 02");
		printf("\nPEDIDO PAGO COM DINHEIRO");
		getch(); 
}

int pagtoCheque (void)
{	
    Dat = fopen("PAGAMENTOS.DAT", "a+b");
    if(Dat == NULL)
    {
          printf("\n Erro em abrir PAGAMENTOS.DAT");
          getch();       
          exit(0);                 
    }
    system("cls");
    while(!feof(Dat))
    		{
          	fread(&pagtosFeitos, sizeof(pagtosFeitos), 1, Dat);                      
    		}
    printf("\n_________________________________________");
    printf("\nNro Pedido      Forma Pagto      Valor");
    printf("\n_________________________________________");
    pagamento pagto = {pagtosFeitos[0].numeroPedido+1, "Cheque", ValorTotal};
    fwrite(&pagto, sizeof(pagto), 1, Dat);
	fclose(Dat);    
	printf("\n %02i		 %s	  	R$ %.2f", pagto.numeroPedido, pagto.FormaPgto, pagto.costFinal); 
	getch();
	system("color 01");
	system("cls");
	printf("\nPEDIDO PAGO COM CHEQUE");
    getch(); 
}

int main (void)
{   
    setlocale(LC_ALL, "");
    mostraMenu();
    fazPedido();
    char escolha;
    escolha = menuCobranca();               
    admin(escolha);   
    getch();
    return 0;    
}
