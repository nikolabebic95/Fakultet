/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z4autoput;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 *
 * Активан аутопут има задату бензинску станицу која може да се дохвати. У
 * случајним временским интервалима од 0,5 s до 1 s ствара по један аутомобил
 * капацитета резервоара 50 l који додаје тој станици. Може да се прекине рад
 * аутопута када се прекида и рад његове станице.
 */
public class Autoput extends Thread {

    private static final double donja_ = 500;
    private static final double gornja_ = 1000;
    private static final double kapacitetAutomobila_ = 50;
    private Stanica stanica_;
    
    public Autoput(Stanica stanica) {
        stanica_ = stanica;
    }
    
    public void prekini() {
        interrupt();
        
    }
    
    @Override
    public void run() {
        try {
            while (!interrupted()) {
                stanica_.dodaj(new Automobil(kapacitetAutomobila_));
                TimeUnit.MILLISECONDS.sleep((long) (Math.random() * (gornja_ - donja_) + donja_));
            }
        } catch (InterruptedException e) {            
        }
    }
}
