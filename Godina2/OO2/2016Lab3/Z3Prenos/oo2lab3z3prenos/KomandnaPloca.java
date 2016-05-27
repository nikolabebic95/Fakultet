/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z3prenos;

import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author Nikola
 *
 * Графичка командна плоча је компонента типа Panel која садржи једног актера,
 * коме придружује приказивач и која може да покреће и зауставља рад актера
 * пољем за потврду.
 */
public class KomandnaPloca extends Panel {
    private final static int SIRINA_POLJA = 10;
    
    private final Akter akter_;
    
    private final TextField polje_ = new TextField("", SIRINA_POLJA);
    
    private final Prikazivac prikazivac_ = new Prikazivac(polje_);
    
    private final Checkbox poljeZaPotvrdu_;
    
    public KomandnaPloca(Akter akter) {
        akter_ = akter;
        akter_.postavi(prikazivac_);
        poljeZaPotvrdu_ = new Checkbox(akter.nazivVrste());
        add(poljeZaPotvrdu_);
        add(polje_);
        poljeZaPotvrdu_.addItemListener(new ItemListener() {
            @Override
            public void itemStateChanged(ItemEvent ie) {
                if (poljeZaPotvrdu_.getState()) akter_.nastaviDalje();
                else akter_.privremenoZaustavi();
            }
        });
    }
    
    
    
}
