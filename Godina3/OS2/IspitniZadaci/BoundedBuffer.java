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

    private T[] vect;

    private int front;
    private int back;

    private int num_of_elements;

    public BoundedBuffer(int capacity) {
        vect = new T[capacity];
    }

    public synchronized void put(T element) {
        if (num_of_elements == vect.length) {
            wait();
        }

        vect[back] = element;
        back = (back + 1) % vect.length;
        num_of_elements++;

        if (num_of_elements == 1) {
            notifyAll();
        }
    }

    public synchronized T get() {
        if (num_of_elements == 0) {
            wait();
        }

        T ret = vect[front];
        front = (front + 1) % vect.length;
        num_of_elements--;

        if (num_of_elements == vect.length - 1) {
            notifyAll();
        }

        return ret;
    }
}
