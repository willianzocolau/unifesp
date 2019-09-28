package com.mycompany.atividade_01;

public class Main {

    public static void main(String[] args) {
        Thread[] threads = new Thread[Config.TP_size + Config.TC_size];
        int n = Config.N / Config.TP_size;

        for (int i = 0; i < Config.TP_size; i++) {
            threads[i] = new Thread(new TP(n));
            threads[i].start();
        }
        
        for (int i = Config.TP_size; i < Config.TP_size + Config.TC_size; i++) {
            threads[i] = new Thread(new TC());
            threads[i].start();
        }

        for (int i = 0; i < Config.TP_size + Config.TC_size; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) { }
        }
    }
}
