import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

class pHash {

    public static int m;
    public static ArrayList[] table;

    private static void Inicialize(int size) {
        table = new ArrayList[size];
        for (int i = 0; i < size; i++) {
            table[i] = new ArrayList<Integer>();
        }
    }

    private static int Hash(int k) {
        return k % m;
    }

    private static void Add(int key) {
        int indice = Hash(key);
        table[indice].add(key);
    }

    private static void Search(int key) {
        int indice = Hash(key);
        Iterator<Integer> itr = table[indice].iterator();
        int existe = 0;
        while (itr.hasNext()) {
            if (itr.next() == key) {
                existe = 1;
                break;
            }
        }
        
        if(existe == 0)
        {
            Add(key);
        }
        else
        {
            Remove(itr);
        }
    }

    private static void Remove(Iterator key) {
        key.remove();
    }

    private static void Print() {
        for (int i = 0; i < table.length; i++) {
            System.out.print("[" + i + "]");
            Iterator<Integer> itr = table[i].iterator();
            while (itr.hasNext()) {
                System.out.print(" " + itr.next());
            }
            System.out.println();
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
        int remove = input.nextInt();
        pHash.Search(remove);
        pHash.Print();
    }
}
