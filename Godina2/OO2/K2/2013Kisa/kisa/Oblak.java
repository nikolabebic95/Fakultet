package kisa;

import java.util.concurrent.TimeUnit;

/**
 * (20 поена) Из активног облака може да пада киша на задату ливаду.
 * Када киша пада, сваких 10 до 50 ms падне једна кап на случајно
 * одабрани бусен ливаде. Захтев за почетак кише када киша већ пада,
 * односно престанак кише кад киша не пада је грешка. Облак може да се уништи.
 */
public class Oblak implements Runnable {
    private final static long donja_ = 10;
    private final static long gornja_ = 30;
    private Thread thread_ = new Thread(this);
    private Livada livada_;
    private boolean pada_ = false;

    public Oblak(Livada livada) {
        livada_ = livada;
    }

    public synchronized void pocni() throws KisaPada {
        if (pada_) throw new KisaPada();
        pada_ = true;
        notifyAll();
    }

    public synchronized void prestani() throws KisaNePada {
        if (!pada_) throw new KisaNePada();
        pada_ = false;
    }

    public void unisti() {
        thread_.interrupt();
    }

    public void start() {
        thread_.start();
    }

    @Override
    public void run() {
        try {
            while (!Thread.interrupted()) {
                synchronized (this) {
                    while (!pada_) wait();
                }
                int sirina = (int) (Math.random() * livada_.sirina());
                int visina = (int) (Math.random() * livada_.visina());
                try {
                    livada_.padni(sirina, visina, new Kap());
                } catch (PogresniIndeksi e) {
                    // Nece se desiti
                }
                long brojMilisekndi = (long) (Math.random() * (gornja_ - donja_ + 1) + donja_);
                TimeUnit.MILLISECONDS.sleep(brojMilisekndi);
            }
        } catch (InterruptedException e) {
            // Nece se desiti zbog uslova u while
        }
    }
}
