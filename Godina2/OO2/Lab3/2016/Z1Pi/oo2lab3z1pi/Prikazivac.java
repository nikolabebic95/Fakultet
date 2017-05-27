/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z1pi;

import java.awt.TextArea;

/**
 *
 * @author Nikola
 *
 * Приказивач на придруженој вишередној текстуалној компоненти графичке
 * корисничке површи може да прикаже један текстуални (String) податак. Може да
 * се постави садржај текста на нову вредност и да се на постојећи садржај
 * додаје још текста.
 */
public class Prikazivac {

    private final TextArea viserednaTekstualnaKomponentaGrafickeKorisnickePovrsi_;

    public Prikazivac(TextArea viserednaTekstualnaKomponentaGrafickeKorisnickePovrsi) {
        viserednaTekstualnaKomponentaGrafickeKorisnickePovrsi_ = viserednaTekstualnaKomponentaGrafickeKorisnickePovrsi;
        viserednaTekstualnaKomponentaGrafickeKorisnickePovrsi_.setEditable(false);
    }

    public Prikazivac postavi(String novi) {
        if (novi == null) {
            viserednaTekstualnaKomponentaGrafickeKorisnickePovrsi_.setText("");
        } else {
            viserednaTekstualnaKomponentaGrafickeKorisnickePovrsi_.setText(novi + '\n');
        }
        return this;
    }

    public Prikazivac dodaj(String novi) {
        viserednaTekstualnaKomponentaGrafickeKorisnickePovrsi_.append(novi + '\n');
        return this;
    }

}
