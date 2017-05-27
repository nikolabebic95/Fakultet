/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sluzba;

/**
 *
 * @author Mica
 */
public class Salterski extends Sluzbenik{
    Red salterski;

    public Salterski(double minT, double maxT, Red salterski) {
        super('S', minT, maxT);
        this.salterski = salterski;
    }

    @Override
    protected Klijent radi() throws InterruptedException{
        return salterski.uzmi();
    }
    
}
