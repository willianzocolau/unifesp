#include <stdio.h>
#include <stdlib.h>

//TAD.h
typedef struct Celula {
   float valor;
   struct Celula *prox;
} TCelula;

TCelula *topo=NULL;

void empilhar_Expressao(char *pDados, int *tam_expressao);
void empilhar_Valor(float valor);
float desempilhar_Valor();
void Calculadora(char *pDados, int *tam_expressao);

//TAD.c
void empilhar_Expressao(char *pDados, int *tam_expressao)
{
    int x = 0;
    for (x = 0; x < 50; x++)
    {
        char caracter;
        scanf("%c", &caracter);
        if (caracter == '\n')
        {
            *tam_expressao = x;
            break;
        }
        pDados[x] = caracter;
    }
}

void empilhar_Valor(float valor)
{
   TCelula *nova = malloc(sizeof(TCelula)*1000);
   (*nova).valor = valor;
   if(topo != NULL)
   {
        (*nova).prox = topo;
   }
   topo = nova;
}

float desempilhar_Valor()
{
   float valor = (*topo).valor;
   TCelula *temp = (*topo).prox;
   free(topo);
   topo = temp;
   return valor;
}

void Calculadora(char *pDados, int *tam_expressao)
{
    int x=0;
    for (x = 0; x < (*tam_expressao); x++)
    {
        if (!(pDados[x]=='+'||pDados[x]=='-'||pDados[x]=='*'||pDados[x]=='/'))
        {
            float valor=0;
            scanf("%f",&valor);
            empilhar_Valor(valor);
        }
        else
        {
            float total = 0;
            float valor2 = desempilhar_Valor();
            float valor1 = desempilhar_Valor();
            switch(pDados[x])
            {
                case '+':
                    total = valor1 + valor2;
                    break;
                case '-':
                    total = valor1 - valor2;
                    break;
                case '*':
                    total = valor1 * valor2;
                    break;
                case '/':
                    total = valor1 / valor2;
                    break;
            }
            empilhar_Valor(total);
        }
    }
}

int main()
{
    //Iniciar pilhar
    int tam_expressao = 0, topo = 0;
    char *pDados = (char*)malloc(sizeof(char)*1000);
    empilhar_Expressao(pDados, &tam_expressao);
    Calculadora(pDados, &tam_expressao);
    printf("%f",desempilhar_Valor());
}
