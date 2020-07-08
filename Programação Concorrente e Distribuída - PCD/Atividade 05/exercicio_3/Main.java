package com.mycompany.montanharussa;

public class Main {

    public static void main(String[] args) throws InterruptedException {
        Config config = new Config();
        
        config.scanCapacidadeCarro();
        config.scanNumeroCarros();
        config.scanNumeroPasseios();
        config.scanPassageiros();
        config.saveTotalPassageiros();
        config.saveTicketsVendidos();
        
        final Controle pc = new Controle(config);
        
        Carro[] carros = new Carro[config.numeroCarros];
        Passageiro[] passageiros = new Passageiro[config.vendedores];

        for (int i = 0; i < config.numeroCarros; i++) {
            carros[i] = new Carro(config, pc, i);
            carros[i].start();
        }
        
        for (int i = 0; i < config.vendedores; i++) {
            passageiros[i] = new Passageiro(config, pc);
            passageiros[i].start();
        }
        
        for (int i = 0; i < config.numeroCarros; i++) {
            carros[i].join();
        }
        
        for (int i = 0; i < config.vendedores; i++) {
            passageiros[i].join();
        }
        
        System.out.println("Parque fechou!");
    }
}
