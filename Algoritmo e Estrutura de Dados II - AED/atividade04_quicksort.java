import java.util.Scanner;

/**
 *
 * @author Willian Zocolau
 */
public class QuickSort {

    private static boolean sn_print_particionar = true;

    public static void main(String[] args) {
        int[] vetor;
        vetor = Read_Vetor();
        QuickSort(vetor);
        Print_Vetor(vetor, vetor.length);
    }

    private static int[] Read_Vetor() {
        Scanner s = new Scanner(System.in);
        int[] vetor = new int[s.nextInt()];
        s.nextLine();
        for (int i = 0; i < vetor.length; i++) {
            vetor[i] = s.nextInt();
        }
        return vetor;
    }

    private static void Print_Vetor(int[] vetor, int n) {
        for (int i = 0; i < n; i++) {
            System.out.print(vetor[i]);
            System.out.print(" ");
        }
        System.out.printf("%n");
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
            if (sn_print_particionar) {
                Print_Vetor(vetor, vetor.length);
                sn_print_particionar = false;
            }
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