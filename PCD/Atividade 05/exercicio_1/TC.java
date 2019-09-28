package com.mycompany.atividade_01;

public class TC implements Runnable {
    
    boolean checkPrimo(int n) {
        if (n % 2 == 0) return false;
        
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    @Override
    public void run() {
        while (true) {
            Integer v = Config.numeros.poll();
            if (!v.equals(null)) {
                if (v < 0) break;
                if (checkPrimo(v)) {
                    System.out.println("Thread TC: " + Thread.currentThread().getId() + " - Número primo encontrado: " + v);
                }
            }
        }
        System.out.println("Finalizada Thread TC: " + Thread.currentThread().getId());
    }
}
