import java.util.Scanner;

class pArvorePatricia {

    public static final int ROTEADOR = 0;
    public static final int EXTERNO = 1;
    public static final int ESQUERDA = 0;
    public static final int DIREITA = 1;

    class pNo {

        public long chave;
        public pNo esquerda;
        public pNo direita;
        public pNo pai;
        public int tipo;

        public pNo() {
            esquerda = null;
            direita = null;
            pai = null;
            tipo = ROTEADOR;
        }

        public pNo(long chave, int tipo, pNo pai) {
            this.chave = chave;
            this.tipo = tipo;
            this.pai = pai;
        }
        
        public pNo(long chave, int tipo, pNo pai, int lado) {
            if(lado == ESQUERDA && pai != null)
            {
                pai.esquerda = new pNo(chave, tipo, pai);
            }
            else if(lado == DIREITA && pai != null)
            {
                pai.direita = new pNo(chave, tipo, pai);
            }
        }

    }

    public static pNo root = null;

    public static long pArvorePatricia_RetornaDigito(long numero, long indice) {
        return ((numero >> indice) & 1);
    }

    public static int pArvorePatricia_QuantidadeDigitos(int numero) {
        return (int) (Math.log10(numero));
    }

    public static long pArvorePatricia_ConverterBinario(long numero) {
        return Long.parseLong(Long.toBinaryString(numero));
    }

    public void pArvorePatricia_Inicializar() {
        root = new pNo(0, ROTEADOR, null);
    }

    public long pArvorePatricia_RetornaIndice(long numero, long numero_externo) {
        long i = -1;
        long bin = pArvorePatricia_ConverterBinario(numero);
        long bin_externo = pArvorePatricia_ConverterBinario(numero_externo);
        int size = Long.toString(bin).length();
        int size_externo = Long.toString(bin_externo).length();
        do {
            i++;
            long digito = pArvorePatricia_RetornaDigito(numero, i);
            long digito_externo = pArvorePatricia_RetornaDigito(numero_externo, i);
            if (digito_externo != digito) {
                break;
            }
            else if(i >= size && i >= size_externo)
            {
                i = -1;
                break;
            }
        } while (true);
        return i;
    }

    public void pArvorePatricia_Inserir(int numero) {
        pNo no = root;
        pNo pai = null;
        int lado = -1;
        pNo no_externo = null;
        pNo novo = null;
        pNo subarvore = null;
        long indice_difere = -1;
        do {
            long digito = -1;
            if (no == null && indice_difere == -1) {
                no = new pNo(numero, EXTERNO, pai, lado);
                break;
            //Volta do percursso para achar o indice maior
            } else if (indice_difere > -1 && indice_difere > no.chave && no.tipo == ROTEADOR) {
                novo.pai = subarvore.pai;
                if(no.esquerda == subarvore)
                {
                    no.esquerda = novo;
                }
                else
                {
                    no.direita = novo;
                }
                subarvore.pai = novo;
                if (novo.esquerda == null) {
                    novo.esquerda = subarvore;
                } else if (novo.direita == null) {
                    novo.direita = subarvore;
                }
                break;
            } else if (no.tipo == ROTEADOR && indice_difere == -1) {
                digito = pArvorePatricia_RetornaDigito(numero, no.chave);
                pai = no;
                if (digito == 0) {
                    no = no.esquerda;
                    lado = 0;
                } else if (digito == 1) {
                    no = no.direita;
                    lado = 1;
                }
            } else if (no.tipo == EXTERNO) {
                indice_difere = pArvorePatricia_RetornaIndice(numero, no.chave);
                if(indice_difere == -1)
                {
                    break;
                }
                digito = pArvorePatricia_RetornaDigito(numero, indice_difere);
                novo = new pNo(indice_difere, ROTEADOR, null);
                if (digito == 0) {
                    novo.esquerda = new pNo(numero, EXTERNO, novo);
                } else if (digito == 1) {
                    novo.direita = new pNo(numero, EXTERNO, novo);
                }
                subarvore = no;
                no = no.pai;

            } else {
                subarvore = no;
                no = no.pai;
            }
        } while (true);
    }

    public void pArvorePatricia_Pesquisar(int numero) {
        pNo no = root;
        int i = -1;
        do {
            i++;
            long digito = pArvorePatricia_RetornaDigito(numero, i);
            if (digito == 0) {
                if (no.esquerda == null) {
                    pArvorePatricia_Inserir(numero);
                    break;
                } else if (no.esquerda.chave == numero) {
                    pArvorePatricia_Remover(no.esquerda, ESQUERDA);
                    break;
                } else {
                    no = no.esquerda;
                }
            } else if (no.direita == null) {
                pArvorePatricia_Inserir(numero);
                break;
            } else if (no.direita.chave == numero) {
                pArvorePatricia_Remover(no.direita, DIREITA);
                break;
            } else {
                no = no.direita;
            }
        } while (true);
    }

    public void pArvorePatricia_Remover(pNo remover, int esquerda_direita) {
        if (remover.pai == root) {
            if (root.esquerda == remover) {
                root.esquerda = null;
            } else {
                root.direita = null;
            }
        } else if (esquerda_direita == 1 && remover.pai.esquerda.tipo == ROTEADOR) {
            pNo pai = remover.pai;
            pNo avo = remover.pai.pai;
            avo.esquerda = pai.esquerda;
            pai.direita = null;
        } else if (esquerda_direita == 0 && remover.pai.direita.tipo == ROTEADOR) {
            pNo pai = remover.pai;
            pNo avo = remover.pai.pai;
            avo.direita = pai.direita;
            pai.esquerda = null;
        } else if (esquerda_direita == 1 && remover.pai.esquerda.tipo == EXTERNO) {
            pNo externo = remover.pai.esquerda;
            pNo pai = remover.pai;
            pai.direita = null;
            do {
                pNo avo = externo.pai.pai;
                if (avo.direita == externo.pai) {
                    avo.direita = externo;
                    esquerda_direita = DIREITA;
                } else {
                    avo.esquerda = externo;
                    esquerda_direita = ESQUERDA;
                }
                externo.pai = avo;

                if (externo.pai == root) {
                    break;
                } else if (esquerda_direita == 0 && externo.pai.direita != null) {
                    break;
                } else if (esquerda_direita == 1 && externo.pai.esquerda != null) {
                    break;
                }
            } while (true);
        } else if (esquerda_direita == 0 && remover.pai.direita.tipo == EXTERNO) {
            pNo externo = remover.pai.direita;
            pNo pai = remover.pai;
            pai.esquerda = null;
            do {
                pNo avo = externo.pai.pai;
                if (avo.direita == externo.pai) {
                    avo.direita = externo;
                    esquerda_direita = DIREITA;
                } else {
                    avo.esquerda = externo;
                    esquerda_direita = ESQUERDA;
                }
                externo.pai = avo;

                if (externo.pai == root) {
                    break;
                } else if (esquerda_direita == 0 && externo.pai.direita != null) {
                    break;
                } else if (esquerda_direita == 1 && externo.pai.esquerda != null) {
                    break;
                }
            } while (true);
        }
    }

    private void pArvorePatricia_Imprimir() {
        pArvorePatricia_PreOrder(root);
    }

    private void pArvorePatricia_PreOrder(pNo no) {
        System.out.print("(");
        if (no != null) {
            if (no.tipo == EXTERNO) {
                System.out.print("C" + no.chave);
            } else {
                System.out.print("D" + no.chave);
            }
            pArvorePatricia_PreOrder(no.esquerda);
            pArvorePatricia_PreOrder(no.direita);
        }
        System.out.print(")");
    }

    public static void main(String[] args) {
        pArvorePatricia pPatricia = new pArvorePatricia();
        pPatricia.pArvorePatricia_Inicializar();
        Scanner input = new Scanner(System.in);
        int tam = input.nextInt();
        for (int i = 0; i < tam; i++) {
            int number = input.nextInt();
            pPatricia.pArvorePatricia_Inserir(number);
        }
        pPatricia.pArvorePatricia_Pesquisar(input.nextInt());
        pPatricia.pArvorePatricia_Imprimir();
    }
}
