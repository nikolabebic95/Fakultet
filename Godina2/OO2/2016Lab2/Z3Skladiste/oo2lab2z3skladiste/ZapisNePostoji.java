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
public class ZapisNePostoji extends Exception {

    private final String zapis_;

    public ZapisNePostoji(String zapis) {
        zapis_ = zapis;
    }

    @Override
    public String toString() {
        return zapis_ + " vec postoji";
    }
}
