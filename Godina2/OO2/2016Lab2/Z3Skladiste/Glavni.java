/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import oo2lab2z3skladiste.*;

/**
 *
 * @author Nikola
 *
 * Написати на језику Java програм који направи једно складиште, стави у њега
 * неколико артикала и испише на главном излазу укупну вредност артикала у
 * складишту. Користити константне податке (не треба ништа учитавати).
 */
public class Glavni {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Skladiste s = new Skladiste("Naziv", "Adresa");
        try {
            // Ovo nece napraviti vise niti uopste, jer nije pokrenut ispis niza
            s.dodaj(new Zapis(new Mleko(), 3, 100));
            s.dodaj(new Zapis(new Secer(), 5, 50));
            System.out.println("Ukupna vrednost je " + s.vrednost());
        } catch (Exception e) {
            System.out.println(e);
        }
    }

}
