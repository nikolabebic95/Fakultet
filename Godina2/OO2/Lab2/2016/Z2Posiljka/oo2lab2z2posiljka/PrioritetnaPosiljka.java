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
 * Апстрактна приоритетна пошиљка је пошиљка с приоритетом
 */
public abstract class PrioritetnaPosiljka extends Posiljka implements PrioritetnaStvar {

    private final Prioritet prioritet_;

    public PrioritetnaPosiljka(Prioritet prioritet) throws PrevelikaTezina {
        prioritet_ = prioritet;
    }

    @Override
    public Prioritet prioritet() {
        return prioritet_;
    }
}
