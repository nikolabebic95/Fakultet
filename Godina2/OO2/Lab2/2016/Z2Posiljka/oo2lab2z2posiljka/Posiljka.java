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
 * Апстрактна пошиљка има јединствен, аутоматски генерисан целобројан
 * идентификатор и реалну тежину који могу да се дохвате. Може да се састави
 * текстуални опис пошиљке у облику id(tez).
 */
public abstract class Posiljka {

    private static int brojac_ = 0;
    private final int id_ = brojac_++;

    public Posiljka() throws PrevelikaTezina {
    }

    public int id() {
        return id_;
    }

    public abstract double tezina();

    @Override
    public String toString() {
        return id_ + "(" + tezina() + ")";
    }
}
