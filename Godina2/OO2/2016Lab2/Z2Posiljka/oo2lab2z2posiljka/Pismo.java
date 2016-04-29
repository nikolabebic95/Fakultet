/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z2posiljka;

/**
 *
 * @author Nikola
 *
 * Писмо је приоритетна пошиљка најнижег приоритета. Грешка је ако тежина
 * прелази 500 g. Текстуални опис је Pprio[id(tez)].
 */
public class Pismo extends PrioritetnaPosiljka {

    private final double tezina_;
    static final double NAJVECATEZINA = 500; // Paketsko pravo pristupa da bi Izuzetak mogao da mu pristupi

    public Pismo(double tezina) throws PrevelikaTezina {
        super(Prioritet.najnizi);
        if (tezina > NAJVECATEZINA) throw new PrevelikaTezinaPisma(tezina);
        tezina_ = tezina;
    }

    @Override
    public double tezina() {
        return tezina_;
    }

    @Override
    public String toString() {
        return "P " + prioritet() + " [" + super.toString() + "]";
    }

}
