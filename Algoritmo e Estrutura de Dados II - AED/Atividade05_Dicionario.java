#include <stdio.h>
 
typedef struct
{
    int chave;
} TItem;
 
typedef struct
{
    TItem *item;
    int tamanho;
    int max_tam;
} Dicionario;
 
Dicionario* Inicializar(Dicionario *vetor)
{
    vetor = (Dicionario*)malloc(sizeof(Dicionario));
    vetor->item = (TItem*)malloc(sizeof(TItem));
    vetor->tamanho = 0;
    vetor->max_tam = 0;
    return vetor;
}
 
int TDicionario_Pesquisa(Dicionario *vetor, TItem registro)
{
    int i = vetor->tamanho;
    vetor->item[0] = registro;
    while(vetor->item[i].chave != registro.chave)
    {
        i--;
    }
    return i;
}
 
void TDicionario_Insere(Dicionario *vetor, TItem registro)
{
    vetor->tamanho++;
    vetor->max_tam++;
    vetor->item[vetor->tamanho].chave = registro.chave;
}
 
int TDicionario_Remove(Dicionario *vetor, TItem registro)
{
    int indice_chave = TDicionario_Pesquisa(vetor, registro), removido = 0;
    if(indice_chave > 0)
    {
        vetor->item[indice_chave].chave = vetor->item[vetor->tamanho].chave;
        vetor->tamanho--;
        removido = 1;
    }
    return removido;
}
 
void TDicionario_Finalizar(Dicionario *vetor)
{
    free(vetor);
}
 
void Read_Vetor(Dicionario *vetor)
{
    int verificar = 0;
    do
    {
        TItem registro;
        scanf("%d",&registro.chave);
        if(registro.chave != -1)
        {
            TDicionario_Insere(vetor, registro);
        }
        verificar = registro.chave;
    }while(verificar != -1);
}
 
int main()
{
    TItem registro;
    Dicionario *vetor = Inicializar(vetor);
    Read_Vetor(vetor);
    scanf("%d", &registro.chave);
    int removido = TDicionario_Remove(vetor, registro);
    if(removido == 0)
    {
        TDicionario_Insere(vetor, registro);
    }
    printf("%d", vetor->tamanho);
    TDicionario_Finalizar(vetor);
    return 0;
}