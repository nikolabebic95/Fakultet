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
public class Portir extends Sluzbenik{
    Red ulazni;
    
    public Portir(double minT, double maxT, Red ulazni) {
        super('P', minT, maxT);
        this.ulazni=ulazni;
    }
    
    @Override
    protected Klijent radi()throws InterruptedException{
        Klijent k=new Klijent((int)(Math.random()*2+1));
        ulazni.stavi(k);
        return k;
    }
    
}
