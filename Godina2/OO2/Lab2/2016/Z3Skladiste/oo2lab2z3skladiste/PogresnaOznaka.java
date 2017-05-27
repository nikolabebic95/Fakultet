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
public class PogresnaOznaka extends Exception {
    String oznaka_;
    PogresnaOznaka(String oznaka) {
        oznaka_ = oznaka;
    }
    @Override
    public String toString() {
        StringBuilder povratna = new StringBuilder();
        povratna.append(oznaka_);
        povratna.append(" nije moguca oznaka. Moguce su: ");
        for (String s: Jedinica.dozvoljene_) {
            povratna.append(s);
            povratna.append(" ");
        }
        return povratna.toString();
    }
}
