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
public class Razvodnik extends Sluzbenik{
    Red ulazni;
    Red [] salterski;

    public Razvodnik(double minT, double maxT, Red ulazni, Red[] salterski) {
        super('R', minT, maxT);
        this.ulazni = ulazni;
        this.salterski = salterski;
    }
    
    @Override
    protected Klijent radi() throws InterruptedException{
        Klijent k=ulazni.uzmi();
        salterski[k.getKod()].stavi(k);
        return k;
    }
    
}
