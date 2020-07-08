package com.mycompany.atividade_01;

import java.util.Random;

public class TP extends Thread {

    public int size_number;
    Random rand;

    public TP(int size_number) {
        this.size_number = size_number;
        rand = new Random();
    }

    @Override
    public void run() {
        try {
            while (size_number > 0) {
                Config.numeros.offer(rand.nextInt(100000000) + 1);
                size_number--;
            }
            Config.sem.acquire();
            if (Config.TP_size == 1) {
                for (int i = 0; i < Config.TC_size; i++) {
                    Config.numeros.offer(-1);
                }
            } else {
                Config.TP_size--;
            }
            Config.sem.release();
            System.out.println("Fim do processo TP - Thread ID: " + Thread.currentThread().getId());
        } catch (InterruptedException e) { }
    }
}
