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
 * Параметарска крива предвиђа израчунавање тачке у равни на основу задатог
 * реалног параметра t и састављање текстуалног описа који садржи назив врсте
 * криве.
 */
public interface Kriva {

    Tacka izracunaj(double t);

    @Override
    String toString();

}
