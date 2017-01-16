//==========================================================================================================//
//==========================================================================================================//
//
//  Nikola Bebic - bn140314d@student.etf.rs
//
//  OS2 
//  Semafor
//  Implementacija preko monitora
//
//==========================================================================================================//
//==========================================================================================================//
//
//  Zadatak:
//
//  Januar 2016.
//  Na jeziku Java napisati kod za monitor koji realizuje standardni brojački semafor. 
// 
//==========================================================================================================//
//==========================================================================================================//

public class MySemaphore {

    private int value;

    private boolean should_unblock;

    public MySemaphore() {
        this(0); // Default value
    }

    public MySemaphore(int value) {
        this.value = value;
    }

    public synchronized void semaphoreWait() throws InterruptedException {
        value--;
        while (value < 0) {
            wait();
            if (should_unblock) {
                should_unblock = false;
                break;
            }
        }
    }

    public synchronized void semaphoreSignal() {
        if (++value <= 0) {
            should_unblock = true;
            notify();
        }
    }
}
