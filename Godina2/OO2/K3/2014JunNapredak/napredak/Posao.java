package napredak;

/**
 * Активан посао извршава неку радњу N пута. Понављање радње може привремено да се
 * заустави и настави, као и да се трајно прекине. Може да се дохвати стање
 * (заустављен/извршава се). Послу може да се пријави највише једна обавестива
 * ствар (више од једне је грешка).После сваких K извршавања радње посао шаље
 * пријављеној обавестивој ствари обавештење о процентуалном напредовању посла.
 */
public abstract class Posao implements Runnable {

    private Thread nit_;
    private Obavestiva stvar_;
    private boolean radi_;
    private final int ukupan_broj_izvrsavanja_;
    private final int korak_broja_izvrsavanja_;

    public Posao(int ukupan_broj_izvrsavanja, int korak_broja_izvrsavanja) {
        ukupan_broj_izvrsavanja_ = ukupan_broj_izvrsavanja;
        korak_broja_izvrsavanja_ = korak_broja_izvrsavanja;
    }

    public void zaustavi() {
        radi_ = false;
    }

    public synchronized void nastavi() {
        if (nit_ == null) {
            nit_ = new Thread(this);
            nit_.start();
        }
        radi_ = true;
        notify();
    }

    public void zavrsi() {
        if (nit_ != null) nit_.interrupt();
    }

    public boolean stanje() {
        return radi_;
    }

    public void prijavi(Obavestiva stvar) throws ViseOdJedneObavestive {
        if (stvar_ != null) throw new ViseOdJedneObavestive();
        stvar_ = stvar;
    }

    protected abstract void izvrsiRadnju() throws InterruptedException;

    @Override
    public void run() {
        try {
            for (int i = 1; i <= ukupan_broj_izvrsavanja_; i++) {
                synchronized (this) {
                    while (!radi_) wait();
                }
                izvrsiRadnju();
                if (i % korak_broja_izvrsavanja_ == 0 && stvar_ != null)
                    stvar_.obavesti(i * 100 / ukupan_broj_izvrsavanja_);
            }
        } catch (InterruptedException e) {
        }
        nit_ = null;
    }
}
