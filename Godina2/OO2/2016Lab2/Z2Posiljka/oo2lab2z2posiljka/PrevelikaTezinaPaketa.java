/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z2posiljka;

/**
 *
 * @author Nikola
 */
public class PrevelikaTezinaPaketa extends PrevelikaTezina {
    
    private final double tezina_;

    public PrevelikaTezinaPaketa(double tezina) {
        tezina_ = tezina;
    }

    @Override
    protected double maksimalnaTezina() {
        return Paket.NAJVECATEZINA;
    }

    @Override
    protected double pogresnaTezina() {
        return tezina_;
    }
}
