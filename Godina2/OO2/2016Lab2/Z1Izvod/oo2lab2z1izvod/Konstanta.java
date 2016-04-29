/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z1izvod;

/**
 *
 * @author Nikola
 *
 * Константа је израз који има реалну вредност која не може да се промени после
 * иницијализације. Извод константе је константа 0. Текстуални опис садржи
 * вредност константе.
 */
public class Konstanta implements Izraz {

    private final double vrednost_;

    public Konstanta(double vrednost) {
        vrednost_ = vrednost;
    }

    @Override
    public double vrednost() {
        return vrednost_;
    }

    @Override
    public Izraz izvod(Promenljiva p) {
        return new Konstanta(0);
    }

    @Override
    public String toString() {
        return "" + vrednost_;
    }
}
