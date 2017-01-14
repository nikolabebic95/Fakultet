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

    public MySemaphore() {
        this.MySemaphore(0); // Default value
    }

    public MySemaphore(int value) {
        this.value = value;
    }

    public synchronized void semaphoreWait() {
        value--;
        while (value < 0) {
            wait();
        }
    }

    public synchronized void semaphoreSignal() {
        if (++value <= 0) {
            notify();
        }
    }
}
