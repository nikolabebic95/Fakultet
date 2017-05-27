/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z4autoput;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 *
 * Бензинска станица има четири пумпе и ред за чекање за највише 20 аутомобила.
 * Станица може да се отвори и затвори, може да се прекине њен рад, да јој се
 * дода задати аутомобил на крај реда, да се извади први аутомобил из њеног реда
 * и да јој се дојави завршетак пуњења једног аутомобила. Ако је станица
 * затворена или је ред пун, додавање аутомобила се занемари. Ако је ред празан,
 * при узимању се сачека да се појави неки аутомобил. Приликом затварања,
 * прекида се чекање возила у реду и чека се да се заврши сипање горива које је
 * у току. Приликом прекидања рада станице прекида се и рад свих њених пумпи.
 * Текстуални опис станице садржи текстуалне описе њених пумпи и низ
 * идентификатора аутомобила који чекају на пумпе.
 */
public class Stanica {

    private final static int brojPumpi_ = 4;
    private final static int kapacitet_ = 20;
    private boolean[] radi_ = new boolean[brojPumpi_];
    private final Pumpa[] pumpe_ = new Pumpa[brojPumpi_];
    private final Automobil[] red_ = new Automobil[kapacitet_];
    private int prvi_ = 0;
    private int posl_ = 0;
    private int brojClanova_ = 0;
    private boolean otvorena_ = false;

    {
        for (int i = 0; i < brojPumpi_; i++) {
            pumpe_[i] = new Pumpa(i);
        }
        for (int i = 0; i < brojPumpi_; i++) {
            pumpe_[i].start();
        }
    }

    private boolean nekoPuni() {
        boolean povratna = false;
        for (boolean b : radi_) {
            if (b) {
                povratna = true;
                break;
            }
        }
        return povratna;
    }

    public synchronized void otvori() {
        otvorena_ = true;
        notifyAll();
    }

    public synchronized void zatvori() {
        while (!nekoPuni()) {
            try {
                wait();
            } catch (InterruptedException e) {
                return;
            }
        }
        otvorena_ = false;
        for (int i = 0; i < kapacitet_; i++) {
            red_[i] = null;
        }
        prvi_ = 0;
        posl_ = 0;
        brojClanova_ = 0;
    }

    public void prekiniRad() {
        for (Pumpa p : pumpe_) {
            p.interrupt();
        }
        zatvori();
    }

    public synchronized Stanica dodaj(Automobil a) {
        if (!otvorena_ || brojClanova_ == kapacitet_) {
            return this;
        }
        red_[posl_] = a;
        posl_++;
        posl_ %= kapacitet_;
        brojClanova_++;
        notifyAll();
        return this;
    }

    public synchronized Automobil uzmi() {
        while (brojClanova_ == 0) {
            try {
                wait();
            } catch (InterruptedException e) {
                return null;
            }
        }
        Automobil povratna = red_[prvi_];
        prvi_++;
        prvi_ %= kapacitet_;
        brojClanova_--;
        return povratna;
    }

    @Override
    public String toString() {
        StringBuilder povratna = new StringBuilder();
        for (Pumpa p : pumpe_) {
            povratna.append(p.toString());
            povratna.append(" ");
        }
        for (int i = 0; i < brojClanova_; i++) {
            int indeks = prvi_ + i;
            indeks %= kapacitet_;
            povratna.append(red_[indeks].id());
            povratna.append(" ");
        }
        return povratna.toString();
    }

    /**
     *
     * @author Nikola
     *
     * Активна пумпа се ствара за задату бензинску станицу. Пумпа циклички
     * дохвата по један аутомобил из реда своје станице и сипа му потребну
     * количину горива до пуног резервоара, брзином од 1 l на сваких 100 ms.
     * Завршетак сипања дојави бензинској станици. Текстуални опис садржи
     * текстуални опис аутомобила којег управо опслужује.
     */
    private class Pumpa extends Thread {

        private int indeks_;
        private static final double kvantGoriva_ = 1;
        private static final long vreme_ = 100;
        private Automobil automobil_ = null;

        public Pumpa(int indeks) {
            indeks_ = indeks;
        }

        private void poceo() {
            radi_[indeks_] = true;
        }

        private synchronized void dojava() {
            automobil_ = null;
            radi_[indeks_] = false;
            notifyAll();
        }

        @Override
        public void run() {
            try {
                while (!interrupted()) {
                    while (!otvorena_) {
                        synchronized (this) {
                            wait();
                        }
                    }
                    poceo();
                    automobil_ = uzmi();
                    if (automobil_ == null) {
                        dojava();
                        continue;
                    }
                    try {
                        while (true) {
                            automobil_.sipaj(kvantGoriva_);
                            TimeUnit.MILLISECONDS.sleep(vreme_);
                        }
                    } catch (PrepunjenRezervoar pr) {
                    }
                    dojava();
                }
            } catch (InterruptedException e) {
            }

        }

        @Override
        public String toString() {
            if (automobil_ == null) {
                return "Prazna pumpa";
            }
            return automobil_.toString();
        }
    }
}
