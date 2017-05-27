/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package saobracaj;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Mica
 */
public class Autoput extends Thread{
    private final BenzinskaStanica stanica;

    public Autoput(BenzinskaStanica stanica) {
        this.stanica = stanica;
    }
    
    public void pokreni(){
        start();
    }
    
    @Override
    public void run(){
        try{
            while(!interrupted()){
                stanica.dodaj(new Automobil(50));
                TimeUnit.MILLISECONDS.sleep((long)(Math.random()*500+500));
            }
        }
        catch(InterruptedException e){}
    }
    
    public void prekiniRad(){
        stanica.unisti();
        interrupt();
    }
}
