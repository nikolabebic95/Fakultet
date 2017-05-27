/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z3skladiste;

/**
 *
 * @author Nikola
 */
public class ZapisVecPostoji extends Exception {

    private final Zapis zapis_;

    public ZapisVecPostoji(Zapis zapis) {
        zapis_ = zapis;
    }

    @Override
    public String toString() {
        return zapis_ + " vec postoji";
    }
}
