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

/* variáveis globais */
FILE *arq;
produto itens[10] = {
        {1, "X-Picanha", 26.00}, 
        {2, "X-Burger", 23.50},
        {3, "X-Salada", 19.00},
        {4, "X-Tudo", 22.00},
        {5, "Batata Rustica", 8.00},
        {6, "Batata Frita", 6.00},
        {7, "Batata c/ cheddar", 10.00},
        {8, "Coca cola", 7.00},
        {9, "Guarana", 8.00},
        {10, "Fanta Uva", 7.00}        
};

char menuEscolha (void);
void admin (char tecla);
int consultaProd (void);
int main (void);

char menuEscolha (void)
{
     char opcao;
     
     system("cls");
     printf("\n _____________ MENU DE ESCOLHA________________");
     printf("\n 1-Consultar produtos cadastrados (MENU)");
     printf("\n 2-Sair do programa");
     printf("\n ______________________________________________");
     printf("\n Escolha: ");
     fflush(stdin);
     opcao = getche();
     return opcao;       
}

void admin (char tecla)
{
     switch (tecla)
     {
          case '1': 
               consultaProd(); /* função para consultar produtos cadastrados */
          break;
          
          case '2': 
               exit(0); /* Sai do programa */
          break;
              
          default: printf("\n Opção inválida!");
                       
          getch();  
     }    
}

int consultaProd (void)
{
    int i;
    system("cls");
    /* abre o arquivo para gravar*/
    arq = fopen ("PRODUTOS.DAT", "w+b");
    if(arq == NULL)
    {
          printf("\n Erro ao gravar no arquivo PRODUTOS.DAT");
          getch();               
          exit(0);        
    }    
    fwrite(&itens, sizeof(itens), 1, arq);
    printf("\n CodProd        NomeProd        CustoProd");
    printf("\n______________________________________________");
    /* varre os elementos dentro de itens */
    for(i = 0; i < 10; i++)
    {
        printf("\n %02i %20s %14.2f", itens[i].codProd, itens[i].nomeProd, itens[i].costProd);      
    }
    fclose(arq);
    getch();
}


int main (void) 
{
    char escolha;
    setlocale(LC_ALL, "");
    do{
        escolha = menuEscolha();              
        admin(escolha);                
    }while(escolha != '2');
    
    getch();
    return 0;   
}
