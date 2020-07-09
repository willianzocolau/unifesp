import java.util.Scanner;

class pArvoreARN {

    private pNo nil = new pNo(-1);
    private pNo raiz = nil;

    class pNo {

        public pNo esquerda;
        public pNo direita;
        public pNo pai;
        public int chave;
        public int coloracao;

        public pNo(int k) {
            esquerda = nil;
            direita = nil;
            pai = nil;
            chave = k;
            coloracao = 1; //0 - Vermelho, 1 - Preto
        }
    }

    boolean is_arn = true;

    private boolean pArvoreAVL_IsArn() {
        is_arn = true;
        pArvoreRubroNegra_Arn(this.raiz);
        return is_arn;
    }

    private void pArvoreRubroNegra_Arn(pNo no) {
        if (no != null) {
            boolean not = pArvoreRubroNegra_VerificaColoracao(no);
            if (not) {
                is_arn = false;
            }
            pArvoreRubroNegra_Arn(no.esquerda);
            pArvoreRubroNegra_Arn(no.direita);
        }
    }

    private void pArvoreRubroNegra_TrocaColoracao(pNo no) {
        if (no != null) {
            if (no.coloracao == 1) {
                no.coloracao = 2;
            } else {
                no.coloracao = 1;
            }
        }
    }

    private boolean pArvoreRubroNegra_VerificaColoracao(pNo pai) {
        return (pai.esquerda.coloracao == pai.coloracao || pai.direita.coloracao == pai.coloracao);
    }

    private int pArvoreRubroNegra_AlturaNegra() {
        return pArvoreRubroNegra_AlturaNegra(raiz);
    }

    private int pArvoreRubroNegra_AlturaNegra(pNo no) {
        int esquerda = 0, direita = 0;
        if (no == null || no == nil) {
            return 0;
        }

        esquerda = pArvoreRubroNegra_AlturaNegra(no.esquerda);
        direita = pArvoreRubroNegra_AlturaNegra(no.direita);

        if (esquerda > direita) {
            if (no.coloracao == 0) {
                return esquerda;
            } else {
                return esquerda + 1;
            }
        } else {
            if (no.coloracao == 0) {
                return direita;
            } else {
                return direita + 1;
            }
        }
    }

    private void pArvoreARN_Insert(int chave) {
        pNo no = new pNo(chave);
        pNo temp = raiz;
        if (raiz == nil) {
            raiz = no;
            no.coloracao = 1;
            no.pai = nil;
        } else {
            no.coloracao = 0;
            while (true) {
                if (no.chave < temp.chave) {
                    if (temp.esquerda == nil) {
                        temp.esquerda = no;
                        no.pai = temp;
                        break;
                    } else {
                        temp = temp.esquerda;
                    }
                } else if (no.chave >= temp.chave) {
                    if (temp.direita == nil) {
                        temp.direita = no;
                        no.pai = temp;
                        break;
                    } else {
                        temp = temp.direita;
                    }
                }
            }
            pArvoreRubroNegra_Balancear(no);
        }
    }

    private void pArvoreRubroNegra_Balancear(pNo no) {
        while (no.pai.coloracao == 0) {
            pNo tio = nil;
            if (no.pai == no.pai.pai.esquerda) {
                tio = no.pai.pai.direita;

                if (tio != nil && tio.coloracao == 0) {
                    no.pai.coloracao = 1;
                    tio.coloracao = 1;
                    no.pai.pai.coloracao = 0;
                    no = no.pai.pai;
                    continue;
                }
                if (no == no.pai.direita) {
                    no = no.pai;
                    pArvoreRubroNegra_RotateLeft(no);
                }
                no.pai.coloracao = 1;
                no.pai.pai.coloracao = 0;
                pArvoreRubroNegra_RotateRight(no.pai.pai);
            } else {
                tio = no.pai.pai.esquerda;
                if (tio != nil && tio.coloracao == 0) {
                    no.pai.coloracao = 1;
                    tio.coloracao = 1;
                    no.pai.pai.coloracao = 0;
                    no = no.pai.pai;
                    continue;
                }
                if (no == no.pai.esquerda) {
                    no = no.pai;
                    pArvoreRubroNegra_RotateRight(no);
                }
                no.pai.coloracao = 1;
                no.pai.pai.coloracao = 0;
                pArvoreRubroNegra_RotateLeft(no.pai.pai);
            }
        }
        raiz.coloracao = 1;
    }

    void pArvoreRubroNegra_RotateLeft(pNo no) {
        if (no.pai != nil) {
            if (no == no.pai.esquerda) {
                no.pai.esquerda = no.direita;
            } else {
                no.pai.direita = no.direita;
            }
            no.direita.pai = no.pai;
            no.pai = no.direita;
            if (no.direita.esquerda != nil) {
                no.direita.esquerda.pai = no;
            }
            no.direita = no.direita.esquerda;
            no.pai.esquerda = no;
        } else {
            pNo right = raiz.direita;
            raiz.direita = right.esquerda;
            right.esquerda.pai = raiz;
            raiz.pai = right;
            right.esquerda = raiz;
            right.pai = nil;
            raiz = right;
        }
    }

    void pArvoreRubroNegra_RotateRight(pNo no) {
        if (no.pai != nil) {
            if (no == no.pai.esquerda) {
                no.pai.esquerda = no.esquerda;
            } else {
                no.pai.direita = no.esquerda;
            }

            no.esquerda.pai = no.pai;
            no.pai = no.esquerda;
            if (no.esquerda.direita != nil) {
                no.esquerda.direita.pai = no;
            }
            no.esquerda = no.esquerda.direita;
            no.pai.direita = no;
        } else {
            pNo left = raiz.esquerda;
            raiz.esquerda = raiz.esquerda.direita;
            left.direita.pai = raiz;
            raiz.pai = left;
            left.direita = raiz;
            left.pai = nil;
            raiz = left;
        }
    }

    private void pArvoreRubroNegra_PrintPreOrder() {
        pArvoreRubroNegra_PreOrder(raiz);
    }

    private void pArvoreRubroNegra_PreOrder(pNo no) {
        System.out.print("(");
        if (no != nil) {
            if (no.coloracao == 1) {
                System.out.print("N" + no.chave);
            } else {
                System.out.print("R" + no.chave);
            }
            pArvoreRubroNegra_PreOrder(no.esquerda);
            pArvoreRubroNegra_PreOrder(no.direita);
        }
        System.out.print(")");
    }

    public static void main(String[] args) {
        pArvoreARN pArvore = new pArvoreARN();
        Scanner input = new Scanner(System.in);
        int tam = input.nextInt();
        for (int i = 0; i < tam; i++) {
            int chave = input.nextInt();
            pArvore.pArvoreARN_Insert(chave);
        }
        System.out.println(pArvore.pArvoreRubroNegra_AlturaNegra());
        pArvore.pArvoreRubroNegra_PrintPreOrder();
    }
}
