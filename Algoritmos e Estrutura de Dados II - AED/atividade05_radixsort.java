import java.util.Scanner;

/**
 *
 * @author Willian Zocolau
 */
public class RadixSort {

    private static int numeral = 10;

    public static void main(String[] args) {
        int[] vetor;
        vetor = Read_Vetor();
        RadixSort(vetor);
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

    private static void RadixSort(int[] vetor) {
        int i;
        int[] aux = new int[vetor.length];
        int expn = 1;

        for (i = 0; i != numeral; ++i) {
            int j;
            int[] count = new int[numeral];
            for (j = 0; j != vetor.length; ++j) {
                count[vetor[j] / expn % 10]++;
            }

            for (j = 1; j != 10; ++j) {
                count[j] += count[j - 1];
            }

            for (j = vetor.length - 1; j >= 0; --j) {
                aux[--count[vetor[j] / expn % 10]] = vetor[j];
            }

            for (j = 0; j != vetor.length; ++j) {
                vetor[j] = aux[j];
            }

            expn *= 10;
        }
    }
}
