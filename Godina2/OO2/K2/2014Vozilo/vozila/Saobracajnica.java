package vozila;

import java.util.concurrent.TimeUnit;

/**
 * (30 поена) Активна саобраћајница ствара задат број саобраћајних трака (може и 0). Негативан
 * број трака је грешка. На сваких T sec, где је T случајно време између задатих minT и maxT, извршава
 * се нека активност. Рад саобраћајнице може да се привремено обустави, поново покрене
 * или трајно заустави.
 */
public abstract class Saobracajnica extends Thread {
    private int donja_; // Ovde su milisekunde
    private int gornja_; // A u konsturktoru sekunde
    private boolean radi_ = false;
    protected Traka[] niz_;

    public Saobracajnica(int kapacitet, double donja, double gornja) throws NegativanBroj {
        if (kapacitet<0) throw new NegativanBroj(kapacitet);
        niz_ = new Traka[kapacitet];
        for (int i = 0; i < kapacitet; i++) niz_[i] = new Traka();
        donja_ = (int) (donja * 1000);
        gornja_ = (int) (gornja * 1000);
    }

    protected abstract void aktivnost();

    public synchronized void kreni() {
        radi_ = true;
        notifyAll();
    }

    public void stani() {
        radi_ = false;
    }

    public void zaustavi() {
        interrupt();
    }

    @Override
    public void run() {
        try {
            while (!interrupted()) {
                while (!radi_) wait();
                aktivnost();
                int vreme = (int) (Math.random() * (gornja_ - donja_) + donja_);
                TimeUnit.MILLISECONDS.sleep(vreme);
            }
        } catch (InterruptedException e) {
            // Komentar da se IntelliJ ne buni za empty catch block
        }
    }
}
