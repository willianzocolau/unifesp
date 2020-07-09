import java.util.Scanner;

/**
 *
 * @author Willian Zocolau
 */
public class CountingSort {

    private static int numeral = 10;

    public static void main(String[] args) {
        int[] vetor;
        vetor = Read_Vetor();
        vetor = CountingSort(vetor);
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

    public static int[] CountingSort(int[] vetor) {
        int[] ordenado = new int[vetor.length];

        int min = vetor[0];
        int max = vetor[0];
        for (int i = 1; i < vetor.length; i++) {
            if (vetor[i] < min) {
                min = vetor[i];
            } else if (vetor[i] > max) {
                max = vetor[i];
            }
        }

        int[] count = new int[max - min + 1];
        for (int i = 0; i < vetor.length; i++) {
            count[vetor[i] - min]++;
        }

        count[0]--;
        for (int i = 1; i < count.length; i++) {
            count[i] = count[i] + count[i - 1];
        }

        for (int i = vetor.length - 1; i >= 0; i--) {
            ordenado[count[vetor[i] - min]--] = vetor[i];
        }

        return ordenado;
    }

}
