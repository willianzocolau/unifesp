package com.mycompany.montanharussa;

import java.util.Scanner;

public class Config {
    
    public int capacidadeCarro;
    public int numeroPasseios;
    public int numeroPassageiros;
    public int numeroCarros;
    public int numeroTotalTickets;
    public int ticketsVendidos;
    public int vendedores;

    public static void clean() {
        for (int i = 0; i < 25; ++i) {
            System.out.println();
        }
    }
    
    private final Scanner scanIn;

    public Config() {
        this.scanIn = new Scanner(System.in);
        this.vendedores = 2;
    }

    public void closeConfig() {
        this.scanIn.close();
    }

    public void scanCapacidadeCarro() {
        System.out.println("Capacidade do carro:");
        capacidadeCarro = Integer.parseInt(this.scanIn.nextLine());
        //capacidadeCarro = 10;
    }

    public void scanNumeroPasseios() {
        System.out.println("Número de passeios do carro:");
        numeroPasseios = Integer.parseInt(this.scanIn.nextLine());
        //numeroPasseios = 2;
    }

    public void scanPassageiros() {
        System.out.println("Número de passageiros:");
        numeroPassageiros = Integer.parseInt(this.scanIn.nextLine());
        //numeroPassageiros = 10;
    }
    
    public void scanNumeroCarros() {
        System.out.println("Números de carros:");
        numeroCarros = Integer.parseInt(this.scanIn.nextLine());
        //numeroCarros = 2;
    }
    
    public void saveTotalPassageiros(){
        numeroTotalTickets = capacidadeCarro * numeroCarros * numeroPasseios;
        System.out.println("Total de tickets: " + numeroTotalTickets);
    }  
    
    public void saveTicketsVendidos(){
        ticketsVendidos = numeroTotalTickets - numeroPassageiros;
        System.out.println("Tickets restantes: " + ticketsVendidos);
    }
}
