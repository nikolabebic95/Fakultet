/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z4benzinskastanica;

import java.awt.*;

/**
 *
 * @author Nikola
 *
 * Графичка станица је станица која садржи графичку плочу (Panel) која може да
 * се дохвата. Уз леву ивицу, према слици, приказује идентификаторе аутомобила
 * који чекају у реду за чекање после сваке промене садржаја реда. Преостали део
 * плоче попуњава са по једним графичким приказивачем за за сваку садржану
 * бензинску пумпу
 */
public class GrafickaStanica extends Stanica {
    private final Panel grafickaPloca_ = new Panel(new BorderLayout());
    
    private final List redZaCekanje_ = new List();
    
    public Panel grafickaPloca() {
        return grafickaPloca_;
    }
    
    public GrafickaStanica() {
        super();
        grafickaPloca_.add(redZaCekanje_, "West");
        
        Panel pumpe = new Panel(new GridLayout(BROJ_PUMPI, 1));
        
        for (int i = 0; i < BROJ_PUMPI; i++) {
            GrafickiPrikazivac gp = new GrafickiPrikazivac();
            pumpe_[i].pridruzi(gp);
            pumpe.add(gp);
        }
        
        grafickaPloca_.add(pumpe, "Center");       
    }
    
    private synchronized void srediListu() {
        redZaCekanje_.removeAll();
        for (int i = 0; i < brojClanova_; i++) {
            redZaCekanje_.add(red_[(prvi_ + i) % KAPACITET].id() + "");
        }
    }
    
    @Override
    public synchronized Automobil uzmi() throws InterruptedException {
        Automobil ret = super.uzmi();
        srediListu();
        return ret;
    }
    
    @Override
    public synchronized GrafickaStanica dodaj(Automobil automobil) {
        super.dodaj(automobil);
        srediListu();
        notifyAll();
        return this;
    }
    
}
