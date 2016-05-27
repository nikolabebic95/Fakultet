/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z1pi;

/**
 *
 * @author Nikola
 *
 * Круг је актер који вредност броја пи одређује тако што генерише тачке са
 * случајним координатама у опсегу од 0 до 1 и броји колико њих пада унутар
 * четвртине круга, са центром у координатном почетку и јединичним
 * полупречником, у првом квадранту. Ако од укупно n тачака m пада унутар тог
 * исечка, узима се да је пи ≈ 4 m / n.
 */
public class Krug extends Akter {

    private int iteracija;
    private int unutra;

    public Krug(Prikazivac prikazivac, int brojIteracija, int korak) {
        super(prikazivac, brojIteracija, korak);
    }

    @Override
    protected void pocni() {
        iteracija = 0;
        unutra = 0;
    }

    @Override
    protected double izracunaj(int brojIteracija) {
        for (int i = iteracija; i < brojIteracija; i++) {
            double x = Math.random();
            double y = Math.random();
            if (x * x + y * y < 1) {
                unutra++;
            }
        }
        iteracija = brojIteracija;
        return 4.0 * unutra / brojIteracija;
    }

}
