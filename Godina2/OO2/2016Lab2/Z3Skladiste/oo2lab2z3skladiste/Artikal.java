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
 * Aртикал има назив и јединицу мере који могу да се дохвате. Два артикла се
 * сматрају истим ако имају исти назив. Текстуални опис артикла садржи назив
 * артикла.
 */
public class Artikal {

    private final String naziv_;
    private final Jedinica jedinica_;

    public Artikal(String naziv, Jedinica jedinica) throws PogresnaOznaka {
        naziv_ = naziv;
        jedinica_ = jedinica;
    }

    @Override
    public boolean equals(Object o) {
        if (o instanceof Artikal) {
            Artikal a = (Artikal) o;
            return (naziv_.equals(a.naziv_));
        } else {
            return false;
        }
    }

    public String naziv() {
        return naziv_;
    }

    public Jedinica jedinica() {
        return jedinica_;
    }

    @Override
    public String toString() {
        return naziv_;
    }
}
