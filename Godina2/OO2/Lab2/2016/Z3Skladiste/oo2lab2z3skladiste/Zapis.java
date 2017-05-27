/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z3skladiste;

/**
 *
 * @author Nikola
 *
 * Вредносни запис о артиклу има артикал, количину и јединичну цену артикла.
 * Могу да се дохвате поља записа, да се промени количина, да се промени
 * јединична цена и да се израчуна вредност укупне количине артикла у запису.
 * Текстуални опис записа садржи артикал, количину, јединицу мере, јединичну
 * цену и вредност артикла.
 */
public class Zapis implements Vrednosno {

    private final Artikal artikal_;
    private double kolicina_;
    private double cena_;

    public Zapis(Artikal artikal, double kolicina, double cena) {
        artikal_ = artikal;
        kolicina_ = kolicina;
        cena_ = cena;
    }

    public Artikal artikal() {
        return artikal_;
    }

    public double kolicina() {
        return kolicina_;
    }

    public void kolicina(double kolicina) {
        kolicina_ = kolicina;
    }

    public double cena() {
        return cena_;
    }

    public void cena(double cena) {
        cena_ = cena;
    }

    @Override
    public double vrednost() {
        return cena_ * kolicina_;
    }

    @Override
    public String toString() {
        return artikal_ + " " + kolicina_ + artikal_.jedinica() + " " + cena_ + " " + vrednost();
    }

}
