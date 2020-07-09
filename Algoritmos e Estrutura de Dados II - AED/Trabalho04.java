import com.sun.org.apache.bcel.internal.generic.AALOAD;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

class pPoligono {

    public static class pNo {

        protected pNo proximo;
        protected Integer id;

        public pNo(Integer id) {
            this.id = id;
        }

        public Integer getId() {
            return id;
        }

        public pNo getProximo() {
            return proximo;
        }

        public void setProximo(pNo node) {
            proximo = node;
        }

    }

    public static class ListaCircular {

        protected pNo no_begin;
        protected pNo no_end;
        protected pNo no_max;
        protected int contador;

        public ListaCircular() {
            this.no_begin = null;
            this.no_end = null;
            this.no_max = new pNo(0);
            contador = 0;
        }

        public int getSize() {
            return contador;
        }

        public pNo getBegin() {
            return no_begin;
        }

        public pNo getEnd() {
            return no_end;
        }

        public pNo getMaximo() {
            return no_max;
        }

        public void setMaximo(pNo novo) {
            no_max = novo;
        }

        public void add(pNo node) {
            if (this.no_begin == null) {
                node.setProximo(node);
                this.no_begin = node;
                this.no_end = node;
            } else {
                this.no_end.setProximo(node);
                this.no_end = node;
                this.no_end.setProximo(this.no_begin);
            }
            contador++;
        }
    }

    public static class Grafo {

        public static int qtd_pontos;
        public static int pa;
        public static int size;
        public static ArrayList<pNo> visitados = new ArrayList<>();

        public Grafo(Integer pa, Integer size) {
            this.qtd_pontos = 0;
            this.pa = pa;
            this.size = size;
        }

        public int getPontos() {
            return qtd_pontos;
        }

        public static int getSize() {
            return size;
        }

        protected void setPontos(Integer qtd_pontos) {
            this.qtd_pontos = qtd_pontos;
        }

        protected void BuscaLargura(pNo atual, int comprimento) {
            pNo comeco = atual;
            int contador = 0, temp_comprimento = 0;
            do {
                int razao = 0;
                while (razao < pa) {
                    razao += atual.getId();
                    atual = atual.getProximo();
                    if (comeco == atual) {
                        break;
                    }
                }
                if (razao == pa) {
                    temp_comprimento += razao;
                    contador++;
                }
            } while (comeco != atual);
            
            int resto = comprimento - temp_comprimento;
            if(resto == pa)
            {
                contador++;
            }

            if (contador != 0 && (temp_comprimento == comprimento)) {
                setPontos(contador);
            }
        }
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int size = input.nextInt();
        ListaCircular lista = new ListaCircular();
        int comprimento = 0;
        for (int i = 0; i < size; i++) {
            pNo no = new pNo(input.nextInt());
            comprimento += no.getId();
            lista.add(no);
            if (no.getId() > lista.getMaximo().getId()) {
                lista.setMaximo(no);
            }
        }
        int minimo = comprimento;
        Grafo g = new Grafo(lista.getMaximo().getId(), size);
        g.BuscaLargura(lista.getMaximo(), comprimento);
        if ((size - g.getPontos()) < minimo && g.getPontos() >= 3) {
            minimo = (size - g.getPontos());
        }

        if ((minimo == comprimento) || minimo > (size - 3)) {
            System.out.println(-1);
        } else {
            System.out.println(minimo);
        }
    }
}
