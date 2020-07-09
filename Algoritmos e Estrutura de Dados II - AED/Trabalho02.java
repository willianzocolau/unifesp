
import java.util.Scanner;

/**
 *
 * @author Willian Zocolau
 */
public class Trabalho02 {

    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);
        int tam_a = entrada.nextInt();
        int tam_b = entrada.nextInt();
        int[] vetor_a = new int[tam_a];
        int[] vetor_b = new int[tam_b];
        ReadSort_Vetor(vetor_a);
        ReadSort_Vetor(vetor_b);
        System.out.print(Processar(vetor_a, vetor_b)); 
        
    }

    private static void ReadSort_Vetor(int[] vetor) {
        Scanner entrada = new Scanner(System.in);
        for (int i = 0; i < vetor.length; i++) {
            vetor[i] = entrada.nextInt();
        }
    }

    public static int Processar(int[] vetor_a, int[] vetor_b) {
        int max_troca_a = 0, max_troca_b = 0;

        int j = 0, anterior = -1;
        for (int i = 0; i < vetor_a.length; i++) {
            boolean sn_chave = true;
            if (i < vetor_b.length) {
                while (vetor_a[i] >= vetor_b[j]) {
                    if (vetor_a[i] == vetor_b[j]) {
                        sn_chave = false;
                        break;
                    }
                    if((j+1) >= vetor_b.length){
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
                max_troca_a += vetor_a.length - vetor_b.length;
                break;
            }
            anterior = vetor_a[i];
        }
        
        j = 0;
        anterior = -1;
        for (int i = 0; i < vetor_b.length; i++) {
            boolean sn_chave = true;
            if (i < vetor_a.length) {
                while (vetor_b[i] >= vetor_a[j]) {
                    if (vetor_b[i] == vetor_a[j]) {
                        sn_chave = false;
                        break;
                    }
                    if((j+1) >= vetor_a.length){
                        break;
                    }
                    else
                    {
                        j++;
                    }
                }
                max_troca_b += (sn_chave && anterior != vetor_b[i]) ? 1 : 0;
            }
            else if(vetor_b[i] > vetor_a[j] && anterior != vetor_b[i])
            {
                max_troca_b += vetor_b.length - vetor_a.length;
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
    
    private static void QuickSort(int[] vetor) {
        Ordenar(vetor, 0, vetor.length - 1);
    }
 
    private static int Particionar(int[] vetor, int inicio, int fim) {
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
 
    private static int[] Ordenar(int[] vetor, int p, int r) {
        if (p < r) {
            int q = Particionar(vetor, p, r);
            vetor = Ordenar(vetor, p, q - 1);
            vetor = Ordenar(vetor, q + 1, r);
        }
        return vetor;
    }
 
    private static int[] Swap(int[] vetor, int i, int j) {
        int aux = vetor[j];
        vetor[j] = vetor[i + 1];
        vetor[i + 1] = aux;
        return vetor;
    }
}
