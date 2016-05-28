/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z4benzinskastanica;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 *
 * Активан аутопут има задату бензинску станицу. У случајним временским
 * интервалима од 0,5 s до 1 s ствара по један аутомобил капацитета резервоара
 * 50 l који додаје тој станици. Може да се прекине рад аутопута када се прекида
 * и рад његове станице.
 */
public class Autoput implements Runnable {

    private static final double DONJA_GRANICA_MILISEKUNDI = 500;
    private static final double GORNJA_GRANICA_MILISEKUNDI = 1000;
    private static final double KAPACITET_AUTOMOBILA = 50;
    private final Stanica stanica_;
    private final Thread nit_ = new Thread(this);
    
    public Autoput(Stanica stanica) {
        stanica_ = stanica;
    }
    
    public void start() {
        nit_.start();
    }
    
    public void prekini() {
        nit_.interrupt();
        stanica_.prekiniRad();
    }
    
    @Override
    public void run() {
        try {
            while (!Thread.interrupted()) {
                stanica_.dodaj(new Automobil(KAPACITET_AUTOMOBILA));
                TimeUnit.MILLISECONDS.sleep((long) (Math.random() * (GORNJA_GRANICA_MILISEKUNDI - DONJA_GRANICA_MILISEKUNDI) + DONJA_GRANICA_MILISEKUNDI));
            }
        } catch (InterruptedException e) {            
        }
    }
}
