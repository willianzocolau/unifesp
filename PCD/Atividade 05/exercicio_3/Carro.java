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
public class Carro extends Thread {

    private int identificador;
    private static Config config;
    private static Controle pc;

    public Carro(Config config, Controle pc, int identificador) {
        Carro.config = config;
        Carro.pc = pc;
        this.identificador = identificador;
    }

    @Override
    public void run() {
        try {
            pc.consume(this.identificador);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
