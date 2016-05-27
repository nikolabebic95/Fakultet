/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z3prenos;

import java.awt.TextComponent;
/**
 *
 * @author Nikola
 *
 * Графички приказивач садржи графичку компоненту типа TextComponent на којој
 * може да прикаже задати текст.
 */
public class Prikazivac {
    private final TextComponent grafickaKomponentaTipaTextComponent_;
    
    public Prikazivac(TextComponent grafickaKomponentaTipaTextComponent) {
        grafickaKomponentaTipaTextComponent_ = grafickaKomponentaTipaTextComponent;
    }
    
    public Prikazivac prikazi(String zadatiTekst) {
        grafickaKomponentaTipaTextComponent_.setText(zadatiTekst);
        return this;
    }
    
}
