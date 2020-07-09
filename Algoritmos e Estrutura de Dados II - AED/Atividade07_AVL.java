import java.util.Scanner;

class pNo {

    protected int chave;
    protected pNo esquerda, direita;

    public pNo(int registro) {
        this(registro, null, null);
    }

    public pNo(int registro, pNo left, pNo right) {
        chave = registro;
        esquerda = left;
        direita = right;
    }
}

class pArvoreAVL {

    private pNo raiz = null;

    private pArvoreAVL() {
        raiz = null;
    }

    private boolean pArvoreAVL_isEmpty() {
        return raiz == null;
    }

    private static int pArvoreAVL_Height(pNo no) {
        if (no == null) {
            return -1;
        } else {
            int he = pArvoreAVL_Height(no.esquerda);
            int hd = pArvoreAVL_Height(no.direita);
            if (he < hd) {
                return hd + 1;
            } else {
                return he + 1;
            }
        }
    }

    private int pArvoreAVL_Height() {
        return pArvoreAVL_Height(this.raiz);
    }

    private int pArvoreAVL_FactorBalance(pNo no) {
        return pArvoreAVL_Height(no.esquerda) - pArvoreAVL_Height(no.direita);
    }

    private boolean pArvoreAVL_Insert(int key) {
        raiz = pArvoreAVL_Insertion(key, raiz);
        return true;
    }

    private pNo pArvoreAVL_Insertion(int key, pNo no) {
        if (no == null) {
            no = new pNo(key, null, null);
        } else if (key < no.chave) {
            no.esquerda = pArvoreAVL_Insertion(key, no.esquerda);
        } else if (key > no.chave) {
            no.direita = pArvoreAVL_Insertion(key, no.direita);
        }
        return no;
    }

    private void pArvoreAVL_Balance() {
        pArvoreAVL_Balance(this.raiz);
    }

    private pNo pArvoreAVL_Balance(pNo no) {
        if (no == null) {
            return null;
        } else {
            no.esquerda = pArvoreAVL_Balance(no.esquerda);
            no.direita = pArvoreAVL_Balance(no.direita);
            int factor = pArvoreAVL_FactorBalance(no);
            if (factor > 1) {
                int factor_left = pArvoreAVL_FactorBalance(no.esquerda);
                if (factor_left == 1 && factor > 1) {
                    no = pArvoreAVL_RightRotation(no);
                } else if (factor_left == -1 && factor > 1) {
                    no = pArvoreAVL_DoubleRightRotation(no);
                }
            } else if (factor < -1) {
                int factor_right = pArvoreAVL_FactorBalance(no.direita);
                if (factor_right == -1 && factor < -1) {
                    no = pArvoreAVL_LeftRotation(no);
                } else if (factor_right == 1 && factor < -1) {
                    no = pArvoreAVL_DoubleLeftRotation(no);
                }
            }
            return no;
        }
    }

    private static pNo pArvoreAVL_RightRotation(pNo k2) {
        pNo k1 = k2.esquerda;
        k2.esquerda = k1.direita;
        k1.direita = k2;
        return k1;
    }

    private static pNo pArvoreAVL_LeftRotation(pNo k1) {
        pNo k2 = k1.direita;
        k1.direita = k2.esquerda;
        k2.esquerda = k1;
        return k2;
    }

    private static pNo pArvoreAVL_DoubleRightRotation(pNo k3) {
        pNo k2 = k3.esquerda;
        pNo k1 = k2.direita;
        k2.direita = k1.esquerda;
        k1.esquerda = k2;
        k3.esquerda = k1.direita;
        k1.direita = k3;
        return k1;
    }

    private static pNo pArvoreAVL_DoubleLeftRotation(pNo k1) {
        pNo k2 = k1.direita;
        pNo k3 = k2.esquerda;
        k2.esquerda = k3.direita;
        k3.direita = k2;
        k1.direita = k3.esquerda;
        k3.esquerda = k1;
        return k3;
    }

    private void pArvoreAVL_PrintPreOrder() {
        pArvoreAVL_PreOrder(raiz);
    }

    private void pArvoreAVL_PreOrder(pNo no) {
        System.out.print("(");
        if (no != null) {
            System.out.print("C" + no.chave);
            pArvoreAVL_PreOrder(no.esquerda);
            pArvoreAVL_PreOrder(no.direita);
        }
        System.out.print(")");
    }

    boolean is_avl = true;

    private boolean pArvoreAVL_IsAVL() {
        is_avl = true;
        pArvoreAVL_IsAVL(this.raiz);
        return is_avl;
    }

    private void pArvoreAVL_IsAVL(pNo no) {
        if (no != null) {
            int factor = pArvoreAVL_FactorBalance(no);
            if (factor > 1 || factor < -1) {
                is_avl = false;
            }
            pArvoreAVL_IsAVL(no.esquerda);
            pArvoreAVL_IsAVL(no.direita);
        }
    }

    public static void main(String args[]) {
        pArvoreAVL pAVL = new pArvoreAVL();
        Scanner input = new Scanner(System.in);
        int abre = 0, fecha = 0, i = 0, is_numeric = 0;
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
            } else if (entrada == 'C' || entrada == 'c') {
                is_numeric = 1;
                entrada = ' ';
            } else if (is_numeric == 1) {
                int chave = input.useDelimiter("[^0-9]+").nextInt();
                pAVL.pArvoreAVL_Insert(chave);
                is_numeric = 0;
            }
        } while (abre > fecha);
        System.out.println(pAVL.pArvoreAVL_Height());
        pAVL.pArvoreAVL_Balance();
        System.out.println(pAVL.pArvoreAVL_Height());
        pAVL.pArvoreAVL_PrintPreOrder();
    }
}
