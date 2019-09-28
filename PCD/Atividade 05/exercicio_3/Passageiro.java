/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.mycompany.montanharussa;

/**
 *
 * @author willian
 */
public class Passageiro extends Thread {

    private static Config config;
    private static Controle pc;

    public Passageiro(Config config, Controle pc) {
        Passageiro.config = config;
        Passageiro.pc = pc;
    }

    @Override
    public void run() {
        try {
            pc.produce();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
