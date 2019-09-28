package com.mycompany.atividade_01;

import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Semaphore;

public class Config {
    public static int TP_size = 4;
    public static int TC_size = 2;
    public static int N = 100;
    public static ConcurrentLinkedQueue<Integer> numeros = new ConcurrentLinkedQueue<Integer>();
    public static Semaphore sem = new Semaphore(1);    
}
