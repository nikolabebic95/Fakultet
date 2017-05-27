/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z1pi;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 *
 * Активан апстрактан актер одређује вредност броја пи у задатом броју
 * итерација. После сваког задатог броја итерација, придруженом приказивачу се
 * додаје један ред текста који садржи укупан број итерација, тренутну приближну
 * вредност и апсолутну вредност разлике у односу на претходну итерацију. Рад
 * актера може да се прекине и превремено.
 */
public abstract class Akter implements Runnable {

    private final Thread nit_ = new Thread(this);
    private final Prikazivac prikazivac_;
    private final int brojIteracija_;
    private final int korak_;

    private final static long SLEEP_TIME_MILLISECONDS = 10;

    public void prekiniPrevremeno() {
        nit_.interrupt();
    }

    public Akter(Prikazivac prikazivac, int brojIteracija, int korak) {
        prikazivac_ = prikazivac;
        brojIteracija_ = brojIteracija;
        korak_ = korak;
        nit_.start();
    }

    abstract protected void pocni();

    abstract protected double izracunaj(int brojIteracija);

    private void stampaj(int iteracije, double vrednost, double razlika) {
        prikazivac_.dodaj("Broj iteracija: " + String.format("%6d", iteracije) + " | Trenutna vrednost: " + String.format("%.09f", vrednost) + " | Razlika: " + String.format("%.09f", razlika));
    }

    @Override
    public void run() {
        prikazivac_.postavi(null);
        double trenutna = 0;
        double prethodna = 0;
        double razlika;
        pocni();
        int i;
        try {
            for (i = korak_; i < brojIteracija_; i += korak_) {
                prethodna = trenutna;
                trenutna = izracunaj(i);
                razlika = Math.abs(trenutna - prethodna);
                stampaj(i, trenutna, razlika);
                TimeUnit.MILLISECONDS.sleep(SLEEP_TIME_MILLISECONDS);
            }
        } catch (InterruptedException e) {
        }
        trenutna = izracunaj(brojIteracija_);
        razlika = Math.abs(trenutna - prethodna);
        stampaj(brojIteracija_, trenutna, razlika);
    }

}
