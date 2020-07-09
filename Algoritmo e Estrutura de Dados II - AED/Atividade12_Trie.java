import java.util.Scanner;

class pArvoreTrie {

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

    }

    public static pNo root = null;

    public static long pArvoreTrie_RetornaDigito(long numero, long indice) {
        return (numero / (long) Math.pow(10, indice)) % 10;
    }

    public static int pArvoreTrie_QuantidadeDigitos(int numero) {
        return (int) (Math.log10(numero));
    }

    public static long pArvoreTrie_ConverterBinario(int numero) {
        return Long.parseLong(Integer.toBinaryString(numero)) ;
    }

    public void pArvoreTrie_Inicializar() {
        root = new pNo(-1, ROTEADOR, null);
    }

    public void pArvoreTrie_Inserir(int numero) {
        long n_binario = pArvoreTrie_ConverterBinario(numero);
        pNo no = root;
        pNo no_externo = null;
        int i = -1;
        do {
            i++;
            long digito = pArvoreTrie_RetornaDigito(n_binario, i);
            if (digito == 0) {
                if (no.esquerda == null && no.tipo == ROTEADOR && no_externo == null) {
                    no.esquerda = new pNo(n_binario, EXTERNO, no);
                    break;
                } else if (no.esquerda == null && no.direita == null) {
                    long digito_externo = pArvoreTrie_RetornaDigito(no_externo.chave, i);
                    if (digito_externo != digito) {
                        if (digito_externo == 0) {
                            no.esquerda = no_externo;
                            no_externo.pai = no;
                            no.direita = new pNo(n_binario, EXTERNO, no);
                            break;
                        } else {
                            no.esquerda = new pNo(n_binario, EXTERNO, no);
                            no.direita = no_externo;
                            no_externo.pai = no;
                            break;
                        }
                    } else {
                        no.esquerda = new pNo(-1, ROTEADOR, no);
                        no = no.esquerda;
                    }
                } else if (no.esquerda.tipo == EXTERNO) {
                    if (no.esquerda.chave == n_binario) {
                        break;
                    }
                    pNo novo_roteador = new pNo(-1, ROTEADOR, no);
                    no_externo = no.esquerda;
                    no_externo.pai = no;
                    no.esquerda = novo_roteador;
                    no = no.esquerda;
                } else {
                    no = no.esquerda;
                }
            } else if (no.direita == null && no.tipo == ROTEADOR && no_externo == null) {
                no.direita = new pNo(n_binario, EXTERNO, no);
                break;
            } else if (no.esquerda == null && no.direita == null) {
                long digito_externo = pArvoreTrie_RetornaDigito(no_externo.chave, i);
                if (digito_externo != digito) {
                    if (digito_externo == 0) {
                        no.esquerda = no_externo;
                        no_externo.pai = no;
                        no.direita = new pNo(n_binario, EXTERNO, no);
                        break;
                    } else {
                        no.esquerda = new pNo(n_binario, EXTERNO, no);
                        no.direita = no_externo;
                        no_externo.pai = no;
                        break;
                    }
                } else {
                    no.direita = new pNo(-1, ROTEADOR, no);
                    no = no.direita;
                }
            } else if (no.direita.tipo == EXTERNO) {
                if (no.direita.chave == n_binario) {
                    break;
                }
                pNo novo_roteador = new pNo(-1, ROTEADOR, no);
                no_externo = no.direita;
                no_externo.pai = no;
                no.direita = novo_roteador;
                no = no.direita;
            } else {
                no = no.direita;
            }
        } while (true);
    }

    public void pArvoreTrie_Pesquisar(int numero) {
        long n_binario = pArvoreTrie_ConverterBinario(numero);
        pNo no = root;
        int i = -1;
        do {
            i++;
            long digito = pArvoreTrie_RetornaDigito(n_binario, i);
            if (digito == 0) {
                if (no.esquerda == null) {
                    pArvoreTrie_Inserir(numero);
                    break;
                } else if (no.esquerda.chave == n_binario) {
                    pArvoreTrie_Remover(no.esquerda, ESQUERDA);
                    break;
                } else {
                    no = no.esquerda;
                }
            } else if (no.direita == null) {
                pArvoreTrie_Inserir(numero);
                break;
            } else if (no.direita.chave == n_binario) {
                pArvoreTrie_Remover(no.direita, DIREITA);
                break;
            } else {
                no = no.direita;
            }
        } while (true);
    }

    public void pArvoreTrie_Remover(pNo remover, int esquerda_direita) {
        if (remover.pai == root) {
            if (root.esquerda == remover) {
                root.esquerda = null;
            } else {
                root.direita = null;
            }
        } else if (esquerda_direita == 1 && remover.pai.esquerda.tipo == ROTEADOR) {
            pNo pai = remover.pai;
            pai.direita = null;
        } else if (esquerda_direita == 0 && remover.pai.direita.tipo == ROTEADOR) {
            pNo pai = remover.pai;
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

    private void pArvoreTrie_Imprimir() {
        pArvoreTrie_PreOrder(root);
    }

    private void pArvoreTrie_PreOrder(pNo no) {
        System.out.print("(");
        if (no != null) {
            if (no.tipo == EXTERNO) {
                String strLong = Long.toString(no.chave);
                System.out.print("C" + Long.parseLong(strLong, 2));
            }
            pArvoreTrie_PreOrder(no.esquerda);
            pArvoreTrie_PreOrder(no.direita);
        }
        System.out.print(")");
    }

    public static void main(String[] args) {
        pArvoreTrie pTrie = new pArvoreTrie();
        pTrie.pArvoreTrie_Inicializar();
        Scanner input = new Scanner(System.in);
        int tam = input.nextInt();
        for (int i = 0; i < tam; i++) {
            pTrie.pArvoreTrie_Inserir(input.nextInt());
        }
        pTrie.pArvoreTrie_Pesquisar(input.nextInt());
        pTrie.pArvoreTrie_Imprimir();
    }
}
