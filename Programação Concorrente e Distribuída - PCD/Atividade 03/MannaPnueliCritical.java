public class MannaPnueliCritical {
  static final int MAX_THREADS = 8;
  static volatile int request = 0;
  static volatile int respond = 0;
  static volatile int count = 0;

  public static void main(String[] args) {
    Client[] clientes = new Client[MAX_THREADS];
    Thread[] threads = new Thread[MAX_THREADS];
    Server server = new Server();
    Thread t_server = new Thread(server);
    t_server.start();

    for (int i = 0; i < MAX_THREADS; i++) {
      (threads[i] = new Thread(clientes[i] = new Client(i + 1))).start();
    }
  }

  public static class Client implements Runnable {
    private final int i;

    public Client(int value) {
      i = value;
    }

    @Override
    public void run() {
      while (true) {
        while (respond != i) {
          request = i;
        }
        System.out.println("Thread ID: " + i + ", soma: " + count++);
        respond = 0;
        try {
          Thread.sleep(1000);
        } catch (Exception ex) { }
      }
    }
  }

  public static class Server implements Runnable {

    @Override
    public void run() {
      while (true) {
        while (request == 0) {
          Thread.yield();
        }
        respond = request;
        while (respond != 0) {
          Thread.yield();
        }
        request = 0;
      }
    }
  }
}
