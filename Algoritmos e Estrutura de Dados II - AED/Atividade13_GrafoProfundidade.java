import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

class pGrafoProfundidade {

    public static ArrayList[] table;
    public static ArrayList<Integer> arestas = new ArrayList<>();
    public static int size;

    private static void BuscaProfundidade(int vertice, ArrayList<Integer> lvertice) {
        ArrayList<Integer> pilha = new ArrayList<>();
        if (lvertice.size() > 0) {
            pilha.add(vertice);
            Iterator<Integer> itr = table[vertice].iterator();
            while (itr.hasNext()) {
                int next = itr.next();
                if (arestas.contains(next) == false) {
                    arestas.add(next);
                    if(table[next] != null)
                    {
                        BuscaProfundidade(next, table[next]);
                    }
                }
            }
            pilha.remove(pilha.size() - 1);
        }
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        size = input.nextInt() + 1;
        int ruas = input.nextInt();
        table = new ArrayList[size];
        for (int i = 0; i < ruas; i++) {
            int u = input.nextInt();
            int v = input.nextInt();
            int p = input.nextInt();
            if (table[u] == null) {
                table[u] = new ArrayList<Integer>();
            }
            table[u].add(v);
            if (p == 2) {
                if (table[v] == null) {
                    table[v] = new ArrayList<Integer>();
                }
                table[v].add(u);
            }
        }

        int conexividade = 1;
        for (int i = 1; i < size; i++) {
            arestas.clear();
            BuscaProfundidade(i, table[i]);
            if (arestas.size() <= (size - 2)) {
                conexividade = 0;
                break;
            }
        }
        System.out.println(conexividade);
    }
}
