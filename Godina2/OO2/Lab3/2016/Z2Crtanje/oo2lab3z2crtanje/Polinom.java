/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z2crtanje;

/**
 *
 * @author Nikola
 *
 * Полином је крива задата формулама x=t и y=poli(t). При стварању се задаје низ
 * коефицијената.
 */
public class Polinom implements Kriva {

    private final double[] koeficijenti_;

    public Polinom(double[] koeficijenti) {
        koeficijenti_ = koeficijenti;
    }

    @Override
    public Tacka izracunaj(double t) {
        // Hornerova sema
        double resenje = koeficijenti_[0];
        for (int i = 1; i < koeficijenti_.length; i++) {
            resenje = resenje * t + koeficijenti_[i];
        }
        return new Tacka(t, resenje);
    }

    @Override
    public String toString() {
        return "Polinom";
    }

}
