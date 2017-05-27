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
public class Sluzba {
    private static final int BR=3;
    Red ulaz;
    Red [] salter;
    Portir portir;
    Razvodnik razvodnik;
    Salterski [] salterski;
    
    private void pokreni(){
        portir.start();
        razvodnik.start();
        for(Salterski r:salterski)r.start();
    }

    public Sluzba() {
        salter=new Red[BR];
        salterski=new Salterski[BR];
        ulaz=new Red();
        for(int i=0; i<salter.length; i++) 
            salter[i]=new Red();
        portir=new Portir(0.1, 0.3, ulaz);
        razvodnik=new Razvodnik(0.15, 0.25, ulaz, salter);
        for(int i=0; i<salterski.length; i++) 
            salterski[i]=new Salterski(0.2, 1, salter[i]);
        pokreni();
    }
    
    public void otvori(){
        portir.pokreni();
        razvodnik.pokreni();
        for(int i=0; i<salterski.length; i++)
            salterski[i].pokreni();
    }
    
    public void zatvori(){
        portir.zaustavi();
        /*try{
            razvodnik.join();
            for(int i=0; i<salterski.length; i++)
                salterski[i].join();
        }
        catch(InterruptedException e){}
        razvodnik.zaustavi();
        for(int i=0; i<salterski.length; i++)
            salterski[i].zaustavi();*/
    }
    
    public void unisti(){
        portir.unisti();
        razvodnik.unisti();
        for(int i=0; i<salterski.length; i++)
            salterski[i].unisti();
    }
}
