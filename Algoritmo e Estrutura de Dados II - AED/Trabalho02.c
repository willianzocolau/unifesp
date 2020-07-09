#include <stdio.h>
#include <stdlib.h>

/**
 *
 * @author Willian Zocolau
 */

void Read_Vetor(int *vetor, int tam){

    int i =0;
    for(i=0;i<tam;i++)
    {
        scanf("%d", &vetor[i]);
    }
}
void Swap(int *vetor, int i, int j) {
    int aux = vetor[j];
    vetor[j] = vetor[i + 1];
    vetor[i + 1] = aux;
}

int Particionar(int *vetor, int inicio, int fim) {
    int pivo = vetor[fim], j, i = inicio - 1;
    for (j = inicio; j < fim; j++) {
        if(vetor[j] < pivo)
        {
            if((j - i) > 1)
            {
                if(vetor[j] <  vetor[j-1])
                {
                    Swap(vetor, i, j);
                }
            }
            i++;
        }
    }
    vetor[fim] = vetor[i + 1];
    vetor[i + 1] = pivo;
    return (i+1);
}

void Ordenar(int *vetor, int p, int r) {
    if (p < r) {
        int q = Particionar(vetor, p, r);
        Ordenar(vetor, p, q - 1);
        Ordenar(vetor, q + 1, r);
    }
}

void QuickSort(int *vetor, int tam) {
    Ordenar(vetor, 0, tam - 1);
}

int Processar(int *vetor_a, int tam_a, int *vetor_b, int tam_b) {
    int max_troca_a = 0, max_troca_b = 0, i = 0;
    int j = 0, anterior = -1;
    for (i = 0; i < tam_a; i++) {
        int sn_chave = 1;
        if (i < tam_b) {
            while (vetor_a[i] >= vetor_b[j]) {
                if (vetor_a[i] == vetor_b[j]) {
                    sn_chave = 0;
                    break;
                }
                if((j+1) >= tam_b){
                    break;
                }
                else
                {
                    j++;
                }
            }

            max_troca_a += (sn_chave && anterior != vetor_a[i]) ? 1 : 0;
        }
        else if(vetor_a[i] > vetor_b[j] && anterior != vetor_a[i])
        {
            max_troca_a += tam_a - tam_b;
            break;
        }
        anterior = vetor_a[i];
    }

    j = 0;
    anterior = -1;
    for (i = 0; i < tam_b; i++) {
        int sn_chave = 1;
        if (i < tam_a) {
            while (vetor_b[i] >= vetor_a[j]) {
                if (vetor_b[i] == vetor_a[j]) {
                    sn_chave = 0;
                    break;
                }
                if((j+1) >= tam_a){
                    break;
                }
                else
                {
                    j++;
                }
            }
            max_troca_b += (sn_chave == 1 && anterior != vetor_b[i]) ? 1 : 0;
        }
        else if(vetor_b[i] > vetor_a[j] && anterior != vetor_b[i])
        {
            max_troca_b += tam_b - tam_a;
            break;
        }
        anterior = vetor_b[i];
    }

    if (max_troca_a < max_troca_b) {
        return max_troca_a;
    } else {
        return max_troca_b;
    }
}

int main()
{
    int tam_a=0, tam_b=0;
    scanf("%d %d", &tam_a, &tam_b);
    int *vetor_a = malloc(sizeof(int) * tam_a * 2);
    int *vetor_b = malloc(sizeof(int) * tam_b * 2);
    Read_Vetor(vetor_a, tam_a);
    Read_Vetor(vetor_b, tam_b);
    QuickSort(vetor_a, tam_a);
    QuickSort(vetor_b, tam_b);
    printf("%d", Processar(vetor_a, tam_a, vetor_b, tam_b));
}
