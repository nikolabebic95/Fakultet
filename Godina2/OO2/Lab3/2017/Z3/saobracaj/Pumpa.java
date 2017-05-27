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
public class Pumpa extends Thread{
    private final BenzinskaStanica stanica;
    private Prikazivac prikazivac;
    private boolean radi;

    public Pumpa(BenzinskaStanica stanica) {
        this.stanica = stanica;
    }

    public void setPrikazivac(Prikazivac prikazivac) {
        this.prikazivac = prikazivac;
    }
    
    @Override
    public void run(){
        try{
            while(!interrupted()){
                synchronized(this){while(!radi)wait();}
                
                Automobil auto=stanica.dohvati();
                if(auto==null)
                    continue;
                try{
                    while(true) {
                        auto.sipaj(1);
                        if(prikazivac!=null)
                            prikazivac.prikaziAuto(auto);
                        TimeUnit.MILLISECONDS.sleep(100);
                    }
                }
                catch(GreskaPun g){
                    stanica.zavrseno();
                }
                
            }
        }
        catch(InterruptedException e){}
    }
    
    public synchronized void otvori(){
        radi=true;
        notifyAll();
    }
    
    public void zatvori(){
        radi=false;
    }
    
    public void zavrsiRad(){
        interrupt();
    }
}
