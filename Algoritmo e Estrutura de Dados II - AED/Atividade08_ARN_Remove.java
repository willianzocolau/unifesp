import java.util.Scanner;

public class pArvoreARN {

    public static final int PRETO = 0;
    public static final int VERMELHO = 1;

    private class pNo {

        public int chave;
        public pNo esquerda, direita, pai;
        public int cor;

        public pNo() {
            esquerda = null;
            direita = null;
            pai = null;
            cor = PRETO;
        }

        public pNo(int chave, int cor) {
            this.chave = chave;
            this.cor = cor;
        }

    }

    private pNo nil = new pNo();
    private pNo root = nil;

    private void pArvoreARN_RotateLeft(pNo x) {
        pNo y = x.direita;
        x.direita = y.esquerda;
        if (y.esquerda != nil) {
            y.esquerda.pai = x;
        }
        y.pai = x.pai;
        if (x.pai == nil) {
            root = y;
        } else if (x == x.pai.esquerda) {
            x.pai.esquerda = y;
        } else {
            x.pai.direita = y;
        }
        y.esquerda = x;
        x.pai = y;
    }

    private void pArvoreARN_RotateRight(pNo x) {
        pNo y = x.esquerda;
        x.esquerda = y.direita;
        if (y.direita != nil) {
            y.direita.pai = x;
        }
        y.pai = x.pai;
        if (x.pai == nil) {
            root = y;
        } else if (x == x.pai.direita) {
            x.pai.direita = y;
        } else {
            x.pai.esquerda = y;
        }
        y.direita = x;
        x.pai = y;
    }

    private void pArvoreARN_Insert(pNo z) {

        pNo y = nil;
        pNo x = root;

        while (x != nil) {
            y = x;
            if (z.chave < x.chave) {
                x = x.esquerda;
            } else {
                x = x.direita;
            }
        }
        z.pai = y;
        if (y == nil) {
            root = z;
        } else if (z.chave < y.chave) {
            y.esquerda = z;
        } else {
            y.direita = z;
        }

        z.esquerda = nil;
        z.direita = nil;
        //z.cor = VERMELHO;
        //pArvoreARN_BalancearInsercao(z);
    }

    public void pArvoreARN_Insert(int chave, int cor) {
        pNo novo = new pNo(chave, cor);
        pArvoreARN_Insert(novo);
    }

    public void pArvoreARN_Remove(int chave) {
        pNo no = pArvoreARN_Search(chave);
        if(no != null)
        {
            pArvoreARN_Remove(no);
        }
    }

    private pNo pArvoreARN_Remove(pNo z) {
        pNo y;
        pNo x;
        if (z.esquerda == nil || z.direita == nil) {
            y = z;
        } else {
            y = pArvoreARN_Sucessor(z);
        }

        if (y.esquerda != nil) {
            x = y.esquerda;
        } else {
            x = y.direita;
        }
        x.pai = y.pai;
        if (y.pai == nil) {
            root = x;
        } else if (y == y.pai.esquerda) {
            y.pai.esquerda = x;
        } else {
            y.pai.direita = x;
        }
        if (y != z) {
            z.chave = y.chave;
        }
        if (y.cor == PRETO) {
            pArvoreARN_BalancearRemocao(x);
        }
        return y;
    }

    private void pArvoreARN_BalancearRemocao(pNo x) {
        pNo w;
        while (x != root && x.cor == PRETO) {
            if (x == x.pai.esquerda) {
                w = x.pai.direita;
                if (w.cor == VERMELHO) {
                    w.cor = PRETO;
                    x.pai.cor = VERMELHO;
                    pArvoreARN_RotateLeft(x.pai);
                    w = x.pai.direita;
                }
                if (w.esquerda.cor == PRETO && w.direita.cor == PRETO) {
                    w.cor = VERMELHO;
                    x = x.pai;
                } else {
                    if (w.direita.cor == PRETO) {
                        w.esquerda.cor = PRETO;
                        w.cor = VERMELHO;
                        pArvoreARN_RotateRight(w);
                        w = x.pai.direita;
                    }
                    w.cor = x.pai.cor;
                    x.pai.cor = PRETO;
                    w.direita.cor = PRETO;
                    pArvoreARN_RotateLeft(x.pai);
                    x = root;
                }
            } else {
                w = x.pai.esquerda;
                if (w.cor == VERMELHO) {
                    w.cor = PRETO;
                    x.pai.cor = VERMELHO;
                    pArvoreARN_RotateRight(x.pai);
                    w = x.pai.esquerda;
                }
                if (w.direita.cor == PRETO && w.esquerda.cor == PRETO) {
                    w.cor = VERMELHO;
                    x = x.pai;
                } else {
                    if (w.esquerda.cor == PRETO) {
                        w.direita.cor = PRETO;
                        w.cor = VERMELHO;
                        pArvoreARN_RotateLeft(w);
                        w = x.pai.esquerda;
                    }
                    w.cor = x.pai.cor;
                    x.pai.cor = PRETO;
                    w.esquerda.cor = PRETO;
                    pArvoreARN_RotateRight(x.pai);
                    x = root;
                }
            }
        }
        x.cor = PRETO;
    }

    public pNo pArvoreARN_Search(int chave) {

        pNo aux = root;

        while (aux != nil) {
            if (chave < aux.chave) {
                aux = aux.esquerda;
            } else if (chave > aux.chave) {
                aux = aux.direita;
            } else if (chave == aux.chave) {
                return aux;
            }
        }

        return null;

    }

    private pNo pArvoreARN_Sucessor(pNo z) {
        pNo aux = z.direita;
        while (aux.esquerda != nil) {
            aux = aux.esquerda;
        }
        return aux;
    }

    private void pArvoreARN_PrintPreOrder() {
        pArvoreARN_PreOrder(root);
    }

    private void pArvoreARN_PreOrder(pNo no) {
        System.out.print("(");
        if (no != nil && no != null) {
            if (no.cor == 0) {
                System.out.print("N" + no.chave);
            } else {
                System.out.print("R" + no.chave);
            }
            pArvoreARN_PreOrder(no.esquerda);
            pArvoreARN_PreOrder(no.direita);
        }
        System.out.print(")");
    }

    public static void main(String args[]) {
        pArvoreARN pARN = new pArvoreARN();
        Scanner input = new Scanner(System.in);
        int abre = 0, fecha = 0, i = 0, is_numeric = 0, cor = -1;
        char entrada = ' ';
        do {
            if (is_numeric == 0) {
                entrada = input.useDelimiter("").next().charAt(0);
            }

            if (entrada == '(') {
                abre++;
                entrada = ' ';
            } else if (entrada == ')') {
                fecha++;
                entrada = ' ';
            } else if (entrada == 'N') {
                is_numeric = 1;
                entrada = ' ';
                cor = 0;
            } else if (entrada == 'R') {
                is_numeric = 1;
                entrada = ' ';
                cor = 1;
            } else if (is_numeric == 1) {
                pARN.pArvoreARN_Insert(input.useDelimiter("[^0-9]+").nextInt(), cor);
                is_numeric = 0;
                cor = -1;
            }
        } while (abre > fecha);
        int remover = input.useDelimiter("[^0-9]+").nextInt();
        pARN.pArvoreARN_Remove(remover);
        pARN.pArvoreARN_PrintPreOrder();
    }
}
