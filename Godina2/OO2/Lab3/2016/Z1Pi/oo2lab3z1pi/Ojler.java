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
 * Ојлер је актер који за рачунање броја пи користи приложену Ојлерову формулу.
 */
public class Ojler extends Akter {

    private double suma;
    private int iteracija;

    public Ojler(Prikazivac prikazivac, int brojIteracija, int korak) {
        super(prikazivac, brojIteracija, korak);
    }

    @Override
    protected void pocni() {
        suma = 0;
        iteracija = 0;
    }

    @Override
    protected double izracunaj(int brojIteracija) {
        for (int i = iteracija; i < brojIteracija; i++) {
            suma += 1.0 / ((i + 1) * (i + 1));
        }
        iteracija = brojIteracija;
        return Math.sqrt(6 * suma);
    }

}
