import java.util.Scanner;

class No {

    public No esquerda;
    public No direita;
    public No pai;
    public int chave;
    public int balance;

    public No(int k) {
        esquerda = null;
        direita = null;
        pai = null;
        balance = 0;
        chave = k;
    }
}

class pArvoreAVL {

    protected No root;

    public void pArvoreAVL_Insert(int k) {
        No n = new No(k);
        pArvoreAVL_InsertAVL(this.root, n);
    }

    public void pArvoreAVL_InsertAVL(No p, No q) {
        if (p == null) {
            this.root = q;
        } else if (q.chave < p.chave) {
            if (p.esquerda == null) {
                p.esquerda = q;
                q.pai = p;
                pArvoreAVL_RecursiveBalance(p);
            } else {
                pArvoreAVL_InsertAVL(p.esquerda, q);
            }
        } else if (q.chave > p.chave) {
            if (p.direita == null) {
                p.direita = q;
                q.pai = p;
                pArvoreAVL_RecursiveBalance(p);
            } else {
                pArvoreAVL_InsertAVL(p.direita, q);
            }
        }
    }

    public void pArvoreAVL_Search(int k) {
        pArvoreAVL_SearchAVL(this.root, k);
    }

    public void pArvoreAVL_SearchAVL(No p, int q) {
        if (p == null) {
            return;
        } else if (p.chave > q) {
            pArvoreAVL_SearchAVL(p.esquerda, q);
        } else if (p.chave < q) {
            pArvoreAVL_SearchAVL(p.direita, q);
        } else if (p.chave == q) {
            pArvoreAVL_Remove(p);
        }
    }

    public void pArvoreAVL_Remove(No q) {
        No r;
        if (q.esquerda == null || q.direita == null) {
            if (q.pai == null) {
                this.root = null;
                q = null;
                return;
            }
            r = q;
        } else {
            r = pArvoreAVL_Successor(q);
            q.chave = r.chave;
        }
        No p;
        if (r.esquerda != null) {
            p = r.esquerda;
        } else {
            p = r.direita;
        }
        if (p != null) {
            p.pai = r.pai;
        }
        if (r.pai == null) {
            this.root = p;
        } else {
            if (r == r.pai.esquerda) {
                r.pai.esquerda = p;
            } else {
                r.pai.direita = p;
            }
            pArvoreAVL_RecursiveBalance(r.pai);
        }
        r = null;
    }

    public void pArvoreAVL_RecursiveBalance(No cur) {
        pArvoreAVL_SetBalance(cur);
        int balance = cur.balance;
        if (balance == -2) {
            if (pArvoreAVL_Height(cur.esquerda.esquerda) >= pArvoreAVL_Height(cur.esquerda.direita)) {
                cur = pArvoreAVL_RotateRight(cur);
            } else {
                cur = pArvoreAVL_DoubleRotateLeftRight(cur);
            }
        } else if (balance == 2) {
            if (pArvoreAVL_Height(cur.direita.direita) >= pArvoreAVL_Height(cur.direita.esquerda)) {
                cur = pArvoreAVL_RotateLeft(cur);
            } else {
                cur = pArvoreAVL_DoubleRotateRightLeft(cur);
            }
        }
        if (cur.pai != null) {
            pArvoreAVL_RecursiveBalance(cur.pai);
        } else {
            this.root = cur;
        }
    }

    public No pArvoreAVL_RotateLeft(No n) {
        No v = n.direita;
        v.pai = n.pai;
        n.direita = v.esquerda;
        if (n.direita != null) {
            n.direita.pai = n;
        }
        v.esquerda = n;
        n.pai = v;
        if (v.pai != null) {
            if (v.pai.direita == n) {
                v.pai.direita = v;
            } else if (v.pai.esquerda == n) {
                v.pai.esquerda = v;
            }
        }
        pArvoreAVL_SetBalance(n);
        pArvoreAVL_SetBalance(v);
        return v;
    }

    public No pArvoreAVL_RotateRight(No n) {
        No v = n.esquerda;
        v.pai = n.pai;
        n.esquerda = v.direita;
        if (n.esquerda != null) {
            n.esquerda.pai = n;
        }
        v.direita = n;
        n.pai = v;
        if (v.pai != null) {
            if (v.pai.direita == n) {
                v.pai.direita = v;
            } else if (v.pai.esquerda == n) {
                v.pai.esquerda = v;
            }
        }
        pArvoreAVL_SetBalance(n);
        pArvoreAVL_SetBalance(v);
        return v;
    }

    public No pArvoreAVL_DoubleRotateLeftRight(No u) {
        u.esquerda = pArvoreAVL_RotateLeft(u.esquerda);
        return pArvoreAVL_RotateRight(u);
    }

    public No pArvoreAVL_DoubleRotateRightLeft(No u) {
        u.direita = pArvoreAVL_RotateRight(u.direita);
        return pArvoreAVL_RotateLeft(u);
    }

    public No pArvoreAVL_Successor(No q) {
        if (q.direita != null) {
            No r = q.direita;
            while (r.esquerda != null) {
                r = r.esquerda;
            }
            return r;
        } else if (q.esquerda != null) {
            No r = q.esquerda;
            while (r.direita != null) {
                r = r.direita;
            }
            return r;
        } else {
            No p = q.pai;
            while (p != null && q == p.direita) {
                q = p;
                p = q.pai;
            }
            return p;
        }
    }

    private int pArvoreAVL_Height(No cur) {
        if (cur == null) {
            return -1;
        }
        if (cur.esquerda == null && cur.direita == null) {
            return 0;
        } else if (cur.esquerda == null) {
            return 1 + pArvoreAVL_Height(cur.direita);
        } else if (cur.direita == null) {
            return 1 + pArvoreAVL_Height(cur.esquerda);
        } else {
            return 1 + pArvoreAVL_Maximum(pArvoreAVL_Height(cur.esquerda), pArvoreAVL_Height(cur.direita));
        }
    }

    private int pArvoreAVL_Maximum(int a, int b) {
        if (a >= b) {
            return a;
        } else {
            return b;
        }
    }

    private void pArvoreAVL_SetBalance(No cur) {
        cur.balance = pArvoreAVL_Height(cur.direita) - pArvoreAVL_Height(cur.esquerda);
    }

    private void pArvoreAVL_PrintPreOrder() {
        pArvoreAVL_PreOrder(root);
    }

    private void pArvoreAVL_PreOrder(No n) {
        System.out.print("(");
        if (n != null) {
            System.out.print("C" + n.chave);
            pArvoreAVL_PreOrder(n.esquerda);
            pArvoreAVL_PreOrder(n.direita);
        }
        System.out.print(")");
    }

    public static void main(String args[]) {
        pArvoreAVL pAVL = new pArvoreAVL();
        Scanner input = new Scanner(System.in);
        int tam = input.nextInt();
        for (int i = 0; i < tam; i++) {
            int chave = input.nextInt();
            pAVL.pArvoreAVL_Insert(chave);
        }
        int remover = input.nextInt();
        pAVL.pArvoreAVL_Search(remover);
        pAVL.pArvoreAVL_PrintPreOrder();
    }
}
