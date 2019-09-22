import java.util.Random;
import java.util.concurrent.Semaphore;

class MyThread implements Runnable {
  private int inicio, fim;

  public MyThread(int inicio, int fim) {
    this.inicio = inicio;
    this.fim = fim;
  }

  @Override
  public void run() {
    long result_parcial = 0;
    for (int i = inicio; i < fim; i++) {
      result_parcial += scalar.vector1[i] * scalar.vector2[i];
    }

    try {
      scalar.sem.acquire();
      scalar.result += result_parcial;
      scalar.sem.release();
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
  }
}


public class scalar {
  static int SIZE = 10000000;
  static int NUM_THREADS = 8;
  static int result_th = SIZE / NUM_THREADS;

  static int[] vector1 = new int[SIZE];
  static int[] vector2 = new int[SIZE];
  static long result = 0;

  static Thread[] th = new Thread[NUM_THREADS];
  static Semaphore sem = new Semaphore(1);

  static void random_array() {
    Random r = new Random();
    for (int i = 0; i < SIZE; i++) {
      vector1[i] = r.nextInt(100) + 1;
      vector2[i] = r.nextInt(100) + 1;
    }
  }

  static int get_limit(int start, int thread) {
    int bonusAdd = 0;
    int finalValue = start + result_th;
    if (result_th % NUM_THREADS != 0)
      bonusAdd = 1;

    finalValue += bonusAdd;

    if (thread == NUM_THREADS - 1)
      finalValue = SIZE;

    return finalValue;
  }

  static void calcula(){
    for (int i = 0; i < NUM_THREADS; i++) {
      int startValue = result_th * i;
      th[i] = new Thread(new MyThread(startValue, get_limit(startValue, i)));
      th[i].start();
    }

    for (int i = 0; i < NUM_THREADS; i++) {
      try {
        th[i].join();
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }

  public static void main(String[] args) {
    random_array();

    long start = System.currentTimeMillis();
    calcula();
    long end = System.currentTimeMillis();

    System.out.println("Resultado: " + result );
    System.out.println("Tempo: " + (end - start) + " ms");
  }
}


