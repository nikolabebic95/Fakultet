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
 * За израз може да се израчуна вредност реалног типа, да се створи израз који
 * представља његов извод по задатој променљивој и да се састави текстуални опис
 * израза.
 */
public interface Izraz {

    double vrednost() throws DeljenjeNulom;

    Izraz izvod(Promenljiva p);

    @Override
    String toString();
}
