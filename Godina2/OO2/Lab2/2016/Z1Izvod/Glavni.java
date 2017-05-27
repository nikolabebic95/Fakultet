/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import oo2lab2z1izvod.*;

/**
 *
 * @author Nikola
 *
 * Написати на језику Java програм који направи објекат за израз
 * (x+3)/((x−2)(x+1)), испише на главном излазу алгебарски облик израза и
 * његовог извода и после табелира вредност израза и његовог извода на главном
 * излазу за свако −2 ≤ x ≤ 3 с кораком 0,25.
 */
public class Glavni {

    private Glavni() {
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Promenljiva x = new Promenljiva('x');
        Konstanta tri = new Konstanta(3);
        Konstanta dva = new Konstanta(2);
        Konstanta jedan = new Konstanta(1);
        Zbir z1 = new Zbir(x, tri);
        Razlika r1 = new Razlika(x, dva);
        Zbir z2 = new Zbir(x, jedan);
        Proizvod p1 = new Proizvod(r1, z2);
        Kolicnik k1 = new Kolicnik(z1, p1);

        Izraz izraz = k1;
        Izraz izvod = k1.izvod(x);
        System.out.println(izraz);
        System.out.println(izvod);
        for (double i = -2; i <= 3; i += 0.25) {
            x.vrednost(i);
            try {
                String stampa = x + " = " + x.vrednost() + ", izraz " + izraz.vrednost() + ", izvod: " + izraz.izvod(x).vrednost();
                System.out.println(stampa);
            } catch (DeljenjeNulom d) {
                System.out.println(d);
            }
        }
    }
}
