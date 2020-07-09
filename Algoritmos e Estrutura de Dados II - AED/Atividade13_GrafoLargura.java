import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

class pGrafoLargura {

    public static ArrayList[] table;
    public static int size;

    private static void Inicialize(int size, int[] visitados) {
        table = new ArrayList[size];
        for (int i = 0; i < size; i++) {
            table[i] = new ArrayList<Integer>();
            visitados[i] = 0;
        }
    }

    private static boolean BuscaLargura(int interseccao, int[] visitados) {
        ArrayList<Integer> fila = new ArrayList<>();
        ArrayList<Integer> lista = new ArrayList<>();
        int controlador = interseccao;
        fila.add(controlador);
        boolean conexividade = false;
        do {
            controlador = fila.iterator().next();
            if (fila.contains(controlador) && fila.size() > 0) {
                fila.remove(0);
            }

            if (visitados[controlador] == 0) {
                Iterator<Integer> itr = table[controlador].iterator();
                while (itr.hasNext()) {
                    int next = itr.next();
                    if (fila.contains(next) == false && visitados[next] == 0) {
                        fila.add(next);
                        lista.add(next);
                    }
                }
                visitados[controlador] = 1;
            }

            if (lista.size() == size - 2) {
                conexividade = true;
            }
        } while (fila.size() > 0);
        return conexividade;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        size = input.nextInt() + 1;
        int ruas = input.nextInt();
        int[] visitados = new int[size];
        int[] distancia = new int[size];
        Inicialize(size, visitados);
        for (int i = 0; i < ruas; i++) {
            int u = input.nextInt();
            int v = input.nextInt();
            int p = input.nextInt();
            table[u].add(v);
            if (p == 2) {
                table[v].add(u);
            }
        }

        int conexividade = 1;
        for (int i = 1; i < size; i++) {
            int[] copy_v = visitados.clone();
            if (!BuscaLargura(i, copy_v)) {
                conexividade = 0;
                break;
            }
        }
        System.out.println(conexividade);
    }
}
