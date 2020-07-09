import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

class pHash {

    public static int m;
    public static int[] table;

    private static void Inicialize(int size) {
        table = new int[size];
        for (int i = 0; i < size; i++) {
            table[i] = -1;
        }
    }

    private static int Hash(int k, int i) {
        return ((k % m) + i) % m;
    }

    private static void Add(int key) {
        for (int i = 0; i < m; i++) {
            int indice = Hash(key, i);
            if(table[indice] == -1)
            {
                table[indice] = key;
                break;
            }
        }
    }

    private static void Search(int key) {
        for (int i = 0; i < m; i++) {
            int indice = Hash(key, i);
            if(table[indice] == -1)
            {
                Add(key);
                break;
            }
            else if(table[indice] == key)
            {
                break;
            }
        }
    }

    private static void Print() {
        for (int i = 0; i < table.length; i++) {
            System.out.print("[" + i + "]");
            System.out.println(" " + table[i]);
        }
    }

    public static void main(String args[]) {
        Scanner input = new Scanner(System.in);
        int size = input.nextInt();
        int qtd = input.nextInt();
        pHash.Inicialize(size);
        m = size;
        for (int i = 0; i < qtd; i++) {
            pHash.Add(input.nextInt());
        }
        int adicionar = input.nextInt();
        pHash.Search(adicionar);
        pHash.Print();
    }
}
