/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z3prenos;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 *
 * Пријемник је актер који у случајним временским интервалима између 120 и 360
 * ms из пријемног бафера узима по једну поруку и приказује на придруженом
 * приказивачу.
 */
public class Prijemnik extends Akter {

    private final static long DONJA_GRANICA_SPAVANJA_U_MILISEKUNDAMA = 120;
    private final static long GORNJA_GRANICA_SPAVANJA_U_MILISEKUNDAMA = 360;

    private final Bafer bafer_;

    public Prijemnik(Bafer bafer) {
        bafer_ = bafer;
    }

    @Override
    public String nazivVrste() {
        return "Prijemnik";
    }

    @Override
    public String izvrsiNekuApstraktnuAkciju() {
        long vremeSpavanja = (long) (Math.random() * (GORNJA_GRANICA_SPAVANJA_U_MILISEKUNDAMA - DONJA_GRANICA_SPAVANJA_U_MILISEKUNDAMA + 1) + DONJA_GRANICA_SPAVANJA_U_MILISEKUNDAMA);
        try {
            TimeUnit.MILLISECONDS.sleep(vremeSpavanja);
        } catch (InterruptedException e) {
        }
        return bafer_.uzmi();
    }

}
