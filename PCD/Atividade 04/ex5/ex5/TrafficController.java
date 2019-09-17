package ex5;

import java.util.concurrent.Semaphore;

public class TrafficController {

    Semaphore sem = new Semaphore(1);

    public void enterLeft() {
        try {
            sem.acquire();
        } catch (InterruptedException ex) {}
    }

    public void enterRight() {
        try {
            sem.acquire();
        } catch (InterruptedException ex) {}
    }

    public void leaveLeft() {
        sem.release();
    }

    public void leaveRight() {
        sem.release();
    }

}