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
 * Пакет је приоритетна пошиљка задатог приоритета. Грешка је ако тежина прелази
 * 50 kg. Текстуални опис је PKprio[id(tez)].
 */
public class Paket extends PrioritetnaPosiljka {

    private double tezina_;
    static final double NAJVECATEZINA = 50000;

    public Paket(Prioritet prioritet, double tezina) throws PrevelikaTezina {
        super(prioritet);
        if (tezina > NAJVECATEZINA) {
            throw new PrevelikaTezinaPaketa(tezina);
        }
        tezina_ = tezina;
    }

    @Override
    public double tezina() {
        return tezina_;
    }

    @Override
    public String toString() {
        return "PK " + prioritet() + " [" + super.toString() + "]";
    }

}
