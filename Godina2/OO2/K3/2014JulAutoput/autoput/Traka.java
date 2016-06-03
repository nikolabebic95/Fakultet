package autoput;

import java.util.concurrent.TimeUnit;

/**
 * (30 поена) Активном траком може да се креће произвољан број аута. На свом почетку
 * има једну рампу. Има задату дужину и дозвољену брзину кретања аута по траци.
 * Дозвољена брзина касније може да се промени. Сваких задатих Δt времена
 * (подразумевано 20 ms) саопштава аутима тренутно време и уклања аута која су
 * стигла до краја. Може да се затражи покретање и привремено заустављање садржане
 * рампе, као и трајно прекидање рада траке заједно са рампом.
 */
public class Traka implements Runnable {
    protected static class ElementListe {
        public Auto auto_;
        public ElementListe sled_;

        public ElementListe(Auto auto) {
            auto_ = auto;
        }
    }

    private final static long KVANT_VREMENA_MILISEKUNDI = 20;

    private final long kvant_vremena_milisekundi_;

    protected final double duzina_;
    protected double dozvoljena_brzina_;

    private Thread nit_ = new Thread(this);
    private boolean radi_;

    private Rampa rampa_;

    protected ElementListe prvi_;
    protected ElementListe posl_;

    public Traka(double duzina, double dozvoljena_brzina, long kvant_vremena_milisekundi) {
        duzina_ = duzina;
        dozvoljena_brzina_ = dozvoljena_brzina;
        kvant_vremena_milisekundi_ = kvant_vremena_milisekundi;
    }

    public Traka(double duzina, double dozvoljena_brzina) {
        this(duzina, dozvoljena_brzina, KVANT_VREMENA_MILISEKUNDI);
    }

    public void promeniDozvoljenuBrzinu(double dozvoljena_brzina) {
        dozvoljena_brzina_ = dozvoljena_brzina;
    }

    public Traka ubaci(Auto auto) {
        ElementListe novi = new ElementListe(auto);
        if (prvi_ == null) prvi_ = novi;
        else posl_.sled_ = novi;
        posl_ = novi;
        return this;
    }

    protected void izbaciAutomobile() {
        ElementListe tek = prvi_;
        ElementListe pret = null;
        while (tek != null) {
            tek.auto_.saopsti(System.currentTimeMillis());
            if (tek.auto_.predjeniPut() > duzina_) {
                if (pret == null) prvi_ = tek.sled_;
                else pret.sled_ = tek.sled_;
            } else pret = tek;
            tek = tek.sled_;
        }
        if (prvi_ == null) posl_ = null;
    }

    public void rampa(Rampa rampa) {
        rampa_ = rampa;
    }

    public void pocni() {
        if (rampa_ != null) rampa_.pocni();
        nit_.start();
    }

    public void zaustavi() {
        radi_ = false;
        if (rampa_ != null) rampa_.zaustavi();
    }

    public synchronized void nastavi() {
        radi_ = true;
        notify();
        if (rampa_ != null) rampa_.nastavi();
    }

    public synchronized void zavrsi() {
        nit_.interrupt();
        if (rampa_ != null) rampa_.zavrsi();
    }

    public double duzina() {
        return duzina_;
    }

    @Override
    public void run() {
        try {
            synchronized (this) {
                while (!radi_) wait(); // Da ne pocne pre vremena prvi put
            }
            while (!Thread.interrupted()) {
                izbaciAutomobile();
                TimeUnit.MILLISECONDS.sleep(kvant_vremena_milisekundi_);
            }
        } catch (InterruptedException e) {
        }
    }
}
