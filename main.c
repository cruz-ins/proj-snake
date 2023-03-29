#include <stdio.h>
#include <stdlib.h>
#include <conio.h>// para adicionar o getch e o rand
#include <locale.h>
#include <string.h>
#include <time.h> // para incluir a possibilidade de usar tempo
#include <unistd.h> // adicionamos para usar o sleep
#include <windows.h>

#define TAM 12

// Aluno: Jean da Silva Cruz / 2011312026 / TADS
// Aluno: Guilherme Goulart Climaco / 2021312050 / TADS

/*

|--------------------------------------------------------comentários-------------------------------------------------------------------|
|     O programa foi desenvolvido em "funções em camadas", em que a primeira a ser chamada é a geração do menu, após isso ocorre a     |
| chamada de obstaculos: quantidade e armazenamento da posição dos obstáculos (armazenados no vetor de struct, variáveis obsx e obsy); |
| depois é chamada a função posição que é responsável por dar ao usuário a escolha da posição inicial da cobra e quantidade de         |
| movimento; então dentro de um for é executado as funções simulação e movimento: a função simulação que é responsavel por gerar o     |
| campo e o corpo da minhoca e a função movimento para alterar o deslocamento da minhoca e verificar se é uma movimentação válida.     |
| Após a finalização da contagem de movimentos ou caso a minhoca fique sem saida é feita a "contagem" de movimento atraves da          |
| matriz campocount.                                                                                                                   |
|--------------------------------------------------------------------------------------------------------------------------------------|

 */
int generationmenu();
void obstaculos();
void posicao ();
void simulacao();
void movimento();
int matrix_copiar_colar();
int count, valobs;

// struct obstaculo
typedef struct obstaculos {
    int obsx, obsy;
}obs;

// fim struct obstaculo

// inicio obstaculos
void obstaculos()
 {
    int campo[TAM][TAM], x, y;
    for (y = 0; y < TAM; y++)
        {
            for (x = 0; x < TAM; x++)
                {
                    if((x == 0) || (y == 0) || (x == TAM-1) || (y == TAM-1))
                    {
                        campo[x][y] = 0;
                    } else
                        {
                            campo[x][y] = 1;
                        }
                }
        }
        printf("Diga o numero de obstaculos\n");
        scanf("%d", &valobs);
        fflush(stdin);
        obs loslos[valobs];
        for(count=0 ; count < valobs; count++)
            {
            do {
                printf ("Informe a coordenada x (horizontal) do obstaculo %d\n", count+1);
                scanf ("%d", &loslos[count].obsx);
                fflush(stdin);
                } while ((loslos[count].obsx) > 10 && (loslos[count].obsx > 0));
            do {
                printf ("Informe a coordenada y (vertical) do obstaculo %d\n", count+1);
                scanf ("%d", &loslos[count].obsy);
                fflush(stdin);
                } while ((loslos[count].obsy) > 10 && (loslos[count].obsy > 0));
                campo[loslos[count].obsx][loslos[count].obsy] = 2;
            }
            posicao(campo, count, loslos);
 }
// fim obstaculo

// começo posicao
void posicao (int campo[TAM][TAM], int count, obs loslos[count])
 {
    int campocpy[TAM][TAM], campocount[TAM][TAM];
    matrix_copiar_colar(campo, campocpy);
    matrix_copiar_colar(campo, campocount);
    int poscx, poscy, x;
    do
    {
        printf("Informe onde a minhoca deve iniciar a sua jornada,\nem que x esta na coordenada horizontal e y esta na coordenada vertical\nnumeros de 0 a 10\n");
        scanf("%d %d", &poscx, &poscy);
        x = 1;
        for(count = 0; count < valobs; count++)
        {
            if((poscx == loslos[count].obsx) && (poscy == loslos[count].obsy))
                {
                x = 0;
                printf("Posição invalida!!\n");
                }
        }
        if((poscx == 0) || (poscy == 0) || (poscx == TAM-1) || (poscy == TAM-1)){
           x = 0;
           printf("Posição invalida!!\n");
        }
        fflush(stdin);
    } while(x == 0);
    int qtdmove, rosavento = 0;
    printf("Quantidade de movimentos que a minhoca deve realizar : \n");
    scanf("%d", &qtdmove);
    int duploqtdmove = qtdmove * 2, regqtdmove[duploqtdmove];
    count = 0;
    fflush(stdin);
    for(qtdmove = qtdmove; qtdmove > 0; qtdmove--)
        {
            system("cls");
            matrix_copiar_colar(campocpy, campo);
            regqtdmove[count] = poscx;
            regqtdmove[count+1] = poscy;
            simulacao(poscx, poscy, campo, count, duploqtdmove, regqtdmove);
            campocount[poscx][poscy] = 2;
            movimento(&poscx, &poscy, campo, &rosavento);
            if(rosavento == 4)  {
                                    break;
                                }
            count = count + 2;
            Sleep(350);
        }
    int y, countb = 0;
    for (y = 0; y < TAM; y++)
        {
            for (x = 0; x < TAM; x++)
                {
                    if(campocount[x][y] == 1){
                        countb++;
                                            }
                }
        }
    printf("\n Numero de casas visitadas : %d \n", count/2);
    printf("\n Casas não visitadas : %d \n", countb);
}
// fim posicao

// inicio simulacao \/ \/ \/ \/ \/ \/ \/ \/ \/ \/ \/
void simulacao(int poscx, int poscy, int campo[TAM][TAM], int count, int duploqtdmove, int regqtdmove[duploqtdmove])
 {
int ale = count, gui = 0;
campo[poscx][poscy]=3;
do {
    if(ale > 0) {
        campo[regqtdmove[ale-2]][regqtdmove[ale-1]] = 4;
        ale = ale - 2;
                }
    else {
            break;
         }
            gui++;
    } while (gui < 3 && ale > 0);
if (count >= 8) {
    campo[regqtdmove[count-8]][regqtdmove[count-7]] = 5;
                }
 int y, x;
 printf("Movimento %d\n", count/2);
        for (y = 0; y < TAM; y++)
        {
            for (x = 0; x < TAM; x++)
                {
                if((campo[x][y] == 0)){
                    printf(" + ");
                } else if (campo[x][y] == 2){
                    printf(" X ");
                } else if (campo[x][y] == 3){
                    printf(" C ");
                } else if (campo[x][y] == 4){
                    printf(" * ");
                } else if (campo[x][y] == 5){
                    printf(" O ");
                } else if (campo[x][y] == 1){
                    printf("   ");
                }
                }
            printf("\n");
        }
 }
// fim simulacao

// CONSTRUÇÃO Movimento
void movimento(int *poscx, int *poscy, int campo[TAM][TAM], int *rosavento){
    int okx = *poscx, oky = *poscy, ok = 0, cima = 0, direita = 0, baixo = 0, esquerda = 0;
    while(ok == 0)
    {
     int x=rand()%100; //esse comando rand serve para gerar números aleatórios de 1 a 100, e usamos ele para simular uma movimentação "aleatória" na cobra
     if(x <= 25)
        {
            *poscx = *poscx + 1;
            ok = 1;
                if (campo[*poscx][*poscy] == 0 || (campo[*poscx][*poscy] == 2) || (campo[*poscx][*poscy] == 4) || (campo[*poscx][*poscy] == 5))
                {
                    *poscx = okx;
                    ok = 0;
                    direita = 1;
                }
                if((cima == 1) && (baixo == 1) && (esquerda == 1) && (direita == 1))
                    {
                        *rosavento = 4;
                        break;
                    }
        } else if(x > 25 && x <= 50)
            {
              *poscx = *poscx - 1;
              ok = 1;
              if (campo[*poscx][*poscy] == 0 || (campo[*poscx][*poscy] == 2) || (campo[*poscx][*poscy] == 4) || (campo[*poscx][*poscy] == 5))
                {
                    *poscx = okx;
                    ok = 0;
                    esquerda = 1;
                }
                if((cima == 1) && (baixo == 1) && (esquerda == 1) && (direita == 1))
                    {
                        *rosavento = 4;
                        break;
                    }
            } else if(x > 50 && x <= 75)
                {
                     *poscy = *poscy + 1;
                    ok = 1;
                    if (campo[*poscx][*poscy] == 0 || (campo[*poscx][*poscy] == 2) || (campo[*poscx][*poscy] == 4) || (campo[*poscx][*poscy] == 5)){
                        *poscy = oky;
                        ok = 0;
                        baixo = 1;
                    }
                    if((cima == 1) && (baixo == 1) && (esquerda == 1) && (direita == 1))
                    {
                            *rosavento = 4;
                            break;
                    }
                } else if(x > 75 && x <= 100)
                    {
                        *poscy = *poscy - 1;
                        ok = 1;
                        if (campo[*poscx][*poscy] == 0 || (campo[*poscx][*poscy] == 2) || (campo[*poscx][*poscy] == 4) || (campo[*poscx][*poscy] == 5))
                            {
                            *poscy = oky;
                            ok = 0;
                            cima = 1;
                            }
                        if((cima == 1) && (baixo == 1) && (esquerda == 1) && (direita == 1))
                        {
                            *rosavento = 4;
                            break;
                        }
                    }

            }
}
// fim movimento

// resetcampo
int matrix_copiar_colar (int copia[TAM][TAM], int colar[TAM][TAM]){
int x, y;
    for (y = 0; y < TAM; y++)
        {
            for (x = 0; x < TAM; x++)
                {
                    colar[x][y] = copia[x][y];

                }
        }
    return 0;
}
//fim de resetcampo

// inicio menu
char menus[5][1000] = {
    "1- Para iniciar Jogo",
    "2- Para sair",};

int generationmenu(int x) //essa função é responsável pela seleção inicial do menu, usamos 2 switchs em que o primeiro leva inicia a função obstaculos e a segunda finaliza o programa
{
	printf("\n\n");
	printf("pressione 1 ou 2 em que : \n");
	for (count = 0; count < 4; count++){
        	printf ("\n %s", menus[count]);
		}
int s;
s = getch();
switch (s){
    case '1':
        obstaculos();
        x = 1;
            break;
    case '2':
        exit(0);
        x = 0;
        break;
            }
            return x;
}
//fim menu

int main() {
setlocale(LC_ALL, "Portuguese");
int x = 1;
srand(time(NULL));
while(x == 1){
x = generationmenu(x); //chama a funçao menu
}
   return 0;
}
