/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z2posiljka;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 */
public class Primalac implements Runnable {

    private PrioritetniRed red_;
    private static final double donjaGranica_ = 800;
    private static final double gornjaGranica_ = 1200;

    public Primalac(PrioritetniRed red) {
        red_ = red;
    }

    @Override
    public void run() {
        try {
            while (!Thread.interrupted()) {
                PrioritetnaPosiljka p = red_.uzmi();
                System.out.println(p);
                TimeUnit.MILLISECONDS.sleep((int) (Math.random() * (gornjaGranica_ - donjaGranica_) + donjaGranica_));
            }
        } catch (InterruptedException e) {
        }
    }
}
