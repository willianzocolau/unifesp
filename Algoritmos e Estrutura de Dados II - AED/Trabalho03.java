import java.util.Scanner;

class pTrabalho03 {

    public static int Calcular_Altura(int matriz[][], int x, int j, int linha, int coluna, int limite_linha, int limite_coluna) {
        int altura = 0;
        while ((x < linha && j < coluna) && (matriz[x][j] >= limite_linha && matriz[x][j] <= limite_coluna)) {
            altura++;
            x++;
            j++;
        }
        return altura;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int linha = input.nextInt();
        int coluna = input.nextInt();
        int[][] matriz = new int[linha][coluna];
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                matriz[i][j] = input.nextInt();
            }
        }
        int consultas = input.nextInt();
        int[][] matriz_consultas = new int[consultas][2];
        for (int i = 0; i < consultas; i++) {
            matriz_consultas[i][0] = input.nextInt();
            matriz_consultas[i][1] = input.nextInt();
        }
        for (int i = 0; i < consultas; i++) {
            int altura = 0;
            for (int x = 0; x < linha; x++) {
                for (int j = 0; j < coluna; j++) {
                    int temp_altura = Calcular_Altura(matriz, x, j, linha, coluna, matriz_consultas[i][0], matriz_consultas[i][1]);
                    if (temp_altura > altura) {
                        altura = temp_altura;
                    }
                }
            }
            System.out.println(altura);
        }
    }
}
