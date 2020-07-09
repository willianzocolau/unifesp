    import java.util.Scanner;
     
    /**
     *
     * @author Willian Zocolau
     */
    public class MergeSort {
              
        public static void main(String[] args) {
            int[] vetor;
            vetor = Read_Vetor();
            vetor = MergeSort(vetor, vetor.length);
            Print_Vetor(vetor, vetor.length);
        }
        
        private static int[] Read_Vetor()
        {
            Scanner s = new Scanner(System.in);
            int[] vetor = new int[s.nextInt()];
            s.nextLine();
            for(int i = 0; i < vetor.length; i++)
            {
                vetor[i] = s.nextInt();
            }
            return vetor;
        }   
        
        private static void Print_Vetor(int[] vetor, int n)
        {
            for(int i = 0; i < n; i++)
            {
                System.out.print(vetor[i] + " ");
            }
        }   
        
        private static int[] Copy_Vetor(int[] vetor, int inicio, int fim)
        {
            int tam = fim - inicio;
            int[] novo_vetor = new int[tam];
            for(int i = 0; i < tam; i++)
            {
                novo_vetor[i] = vetor[inicio];
                inicio++;
            }
            return novo_vetor;
        }   
        
        private static int[] MergeSort(int[] vetor, int n)
        {
            
            vetor = Intercalar(vetor, vetor.length);
            return vetor;
        }
        
        private static int[] Intercalar(int[] vetor, int n)
        {
            if(n == 2 && vetor[0] > vetor[1])
            {
                int aux = vetor[0];
                vetor[0] = vetor[1];
                vetor[1] = aux;
            }
            else if(n > 2) 
            {
                int m = n/2;
                int[] vetor_a = Copy_Vetor(vetor, 0, m);
                int[] vetor_b = Copy_Vetor(vetor, m, n);
                vetor_a = Intercalar(vetor_a, m);
                vetor_b = Intercalar(vetor_b, n-m);
                vetor = Ordenar(vetor_a, vetor_b, n);
            }
            
            return vetor;
        }
        
        private static int[] Ordenar(int[] vetor_a, int[] vetor_b, int n)
        {
            int i = 0, j = 0, cheio_i = 0, cheio_j = 0;
            int[] vetor = new int[vetor_a.length + vetor_b.length];
            for(int k = 0; k < n; k++)
                {
                    if((vetor_a[i] <= vetor_b[j] && cheio_i == 0) || (cheio_i == 0 && cheio_j == 1))
                    {
                        vetor[k] = vetor_a[i];
                        if((i+1)== vetor_a.length)
                        {
                            cheio_i = 1;
                        }
                        else
                        {
                            i++;
                        }
                    }
                    else 
                    {
                        vetor[k] = vetor_b[j];
                        if((j+1)== vetor_b.length)
                        {
                            cheio_j = 1;
                        }
                        else
                        {
                            j++;
                        }
                    }
                }
                
                return vetor;
        }
    }