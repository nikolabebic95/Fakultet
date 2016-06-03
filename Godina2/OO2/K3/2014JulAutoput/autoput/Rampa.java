package autoput;

import java.util.concurrent.TimeUnit;

/**
 * Кроз активну рампу, док ради, у случајним временским интервалима у задатом
 * интервалу између tmin и tmax (подразумевано од 100 до 400 ms) улази по један
 * ауто у траку која се задаје приликом стварања рампе. Рампа може да ради, буде
 * привремено заустављена и да трајно прекине са радом.
 */
public class Rampa implements Runnable {

    private static final long DONJA_GRANICA_MILISEKUNDI = 100;
    private static final long GORNJA_GRANICA_MILISEKUNDI = 400;

    private final long donja_granica_milisekundi_;
    private final long gornja_granica_milisekundi_;
    private final Traka traka_;

    private final Thread nit_ = new Thread(this);
    private boolean radi_;

    public void pocni() {
        nit_.start();
    }

    public void zaustavi() {
        radi_ = false;
    }

    public synchronized void nastavi() {
        radi_ = true;
        notify();
    }

    public void zavrsi() {
        nit_.interrupt();
    }

    public Rampa(long donja_granica_milisekundi, long gornja_granica_milisekundi, Traka traka) {
        donja_granica_milisekundi_ = donja_granica_milisekundi;
        gornja_granica_milisekundi_ = gornja_granica_milisekundi;
        traka_ = traka;
        traka_.rampa(this);
    }

    public Rampa(Traka traka) {
        this(DONJA_GRANICA_MILISEKUNDI, GORNJA_GRANICA_MILISEKUNDI, traka);
    }

    @Override
    public void run() {
        try {
            while (!Thread.interrupted()) {
                synchronized (this) {
                    while (!radi_) wait();
                }
                traka_.ubaci(new Auto());
                long vreme_spavanja_milisekundi = (long) (Math.random() * (gornja_granica_milisekundi_ - donja_granica_milisekundi_ + 1) + donja_granica_milisekundi_);
                TimeUnit.MILLISECONDS.sleep(vreme_spavanja_milisekundi);
            }
        } catch (InterruptedException e) {
        }
    }
}
