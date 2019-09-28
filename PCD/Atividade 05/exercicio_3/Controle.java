/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.mycompany.montanharussa;

import java.util.ArrayList;
import java.util.LinkedList;

/**
 *
 * @author willian
 */
public class Controle {

    LinkedList<Integer> list_passageiros = new LinkedList<>();
    LinkedList<Integer> list_atendidos = new LinkedList<>();
    ArrayList<Integer>[] list_embarcados;
    private static Config config;
    private int value;

    public Controle(Config config) {
        Controle.config = config;
        list_embarcados = new ArrayList[config.numeroCarros];
        value = 1;
        for (int i = 0; i < config.numeroCarros; i++) {
            list_embarcados[i] = new ArrayList<>();
        }
    }

    public void produce() throws InterruptedException {
        while (((list_atendidos.size() + list_passageiros.size()) < config.numeroPassageiros) && config.numeroPassageiros != 0) {
            synchronized (this) {
                wait();
                if ((list_atendidos.size() + list_passageiros.size()) < config.numeroTotalTickets) {
                    System.out.println("Passageiro " + value + " está na fila");
                    System.out.flush();
                }

                list_passageiros.add(value);
                value++;

                Thread.sleep(1000);
                notify();
            }
        }
    }

    public void consume(int id) throws InterruptedException {
        while (((list_atendidos.size()) < config.numeroPassageiros) && config.numeroPassageiros != 0) {
            synchronized (this) {
                notify();
                if (list_passageiros.isEmpty()) {
                    continue;
                }

                int val = list_passageiros.removeFirst();
                list_atendidos.add(val);
                list_embarcados[id].add(val);

                System.out.println("Passageiro " + val + " embarcou no carro " + id);
                System.out.flush();

                Thread.sleep(1000);

                if (list_embarcados[id].size() == config.capacidadeCarro) {
                    System.out.println("Carro " + id + " iniciando volta!");
                    System.out.flush();
                    Thread.sleep(10000);
                    list_embarcados[id].clear();
                    System.out.println("Carro " + id + " finalizou a volta!");
                }
                if(list_atendidos.size() != config.ticketsVendidos)
                    wait();
            }
        }
    }
}
