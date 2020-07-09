import java.util.Scanner;

/**
 *
 * @author Willian Zocolau
 */
public class MergeSort {
    
    private static int troca;
    
    public static void main(String[] args) 
    {        
        troca = 0;
        int[] vetor;
        vetor = Read_Vetor();
        Processar(vetor);
        if(troca % 2 == 0)
        {
            System.out.print("Carlos");
        }
        else
        {
            System.out.print("Marcelo");
        }
    }
    
    private static int[] Read_Vetor()
    {
        Scanner s = new Scanner(System.in);
        int[] vetor = new int[s.nextInt()];
        for(int i = 0; i < vetor.length; i++)
        {
            vetor[i] = s.nextInt();
        }
        return vetor;
    }       
    
    private static int[] Swap(int[] vetor, int i, int j)
    {
        int auxiliar = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = auxiliar;
        return vetor;
    }
    
    private static void Processar(int[] vetor)
    {
        for(int i = 0; i < vetor.length; i++)
        {
            while (vetor[i] != i+1) {
                Swap(vetor, i, vetor[i]-1);
                troca++;
            }
        }
    }
}
