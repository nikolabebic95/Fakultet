/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z1izvod;

/**
 *
 * @author Nikola
 */
public class Kolicnik extends Binarni {

    public Kolicnik(Izraz levi, Izraz desni) {
        super(levi, desni);
    }

    @Override
    public char znak() {
        return '/';
    }

    @Override
    public double operacija() throws DeljenjeNulom {
        if (desnaVrednost_ == 0) throw new DeljenjeNulom();
        return levaVrednost_ / desnaVrednost_;
    }

    @Override
    public Izraz izvod(Promenljiva p) {
        return new Kolicnik(new Razlika(new Proizvod(levi().izvod(p), desni()), new Proizvod(levi(), desni().izvod(p))), new Proizvod(desni(), desni()));
    }
}
