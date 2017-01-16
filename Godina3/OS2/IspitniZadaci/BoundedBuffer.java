//==========================================================================================================//
//==========================================================================================================//
//
//  Nikola Bebic - bn140314d@student.etf.rs
//
//  OS2
//  BoundedBuffer
//  Implementacija preko monitora
//
//==========================================================================================================//
//==========================================================================================================//
//
//  Zadatak:
//
//  Januar 2015.
//  Na jeziku Java napisati kod monitora koji realizuje ograničeni bafer (bounded buffer).
//
//==========================================================================================================//
//==========================================================================================================//

public class BoundedBuffer<T> {

    private Object[] vect;

    private int front;
    private int back;

    private int num_of_elements;

    public BoundedBuffer(int capacity) {
        vect = new Object[capacity];
    }

    public synchronized void put(T element) throws InterruptedException {
        while (num_of_elements == vect.length) {
            wait();
        }

        vect[back] = element;
        back = (back + 1) % vect.length;
        num_of_elements++;

        if (num_of_elements == 1) {
            notify();
        }
    }

    public synchronized T get() throws InterruptedException {
        while (num_of_elements == 0) {
            wait();
        }

        @SuppressWarnings("unchecked")
        final T ret = (T)vect[front];
        front = (front + 1) % vect.length;
        num_of_elements--;

        if (num_of_elements == vect.length - 1) {
            notify();
        }

        return ret;
    }
}
