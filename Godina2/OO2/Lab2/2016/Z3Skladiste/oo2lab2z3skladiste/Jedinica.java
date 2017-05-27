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
 * Јединица мере има ознаку која може да се дохвати. Дозвољене ознаке су: "kom",
 * "l", "m" и "kg". Грешка је ако се покуша направити јединица мере с другачијом
 * ознаком. Текстуални опис јединица мере садржи ознаку јединице.
 */
public class Jedinica {
    
    private static final int brojDozvoljenih_ = 4;
    //! Paketsko pravo pristupa da bi greska mogla da pristupi
    static final String[] dozvoljene_ = new String[brojDozvoljenih_];
    static {
        dozvoljene_[0] = "kom";
        dozvoljene_[1] = "l";
        dozvoljene_[2] = "m";
        dozvoljene_[3] = "kg";
    }
    
    private final String oznaka_;
    
    public Jedinica(String oznaka) throws PogresnaOznaka {
        boolean dobraOznaka = false;
        for (String s: dozvoljene_) {
            if (oznaka.equals(s)) {
                dobraOznaka = true;
                break;
            }
        }
        if (!dobraOznaka) throw new PogresnaOznaka(oznaka);
        oznaka_ = oznaka;
    }
    @Override 
    public String toString() {
        return oznaka_;
    }
}
