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
 * Променљива је израз који има једнословно име и реалну вредност (подразумевано
 * 0) која може да се промени после иницијализације. Извод променљиве по
 * променљивој са истим именом је константа 1, а по било којој другој
 * променљивој константа 0. Текстуални опис променљиве садржи име променљиве
 */
public class Promenljiva implements Izraz {

    private double vrednost_;
    private char ime_;

    public Promenljiva(char ime) {
        ime_ = ime;
        vrednost_ = 0; // Nepotrebno, nula ce se sama upisati, al nema veze
    }

    public Promenljiva(char ime, double vrednost) {
        ime_ = ime;
        vrednost_ = vrednost;
    }

    public void vrednost(double vrednost) {
        vrednost_ = vrednost;
    }

    @Override
    public double vrednost() {
        return vrednost_;
    }

    @Override
    public Izraz izvod(Promenljiva p) {
        if (p.ime_ == ime_) {
            return new Konstanta(1);
        } else {
            return new Konstanta(0);
        }
    }

    @Override
    public String toString() {
        return "" + ime_;
    }

}
