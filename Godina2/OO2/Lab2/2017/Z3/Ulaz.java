/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banke;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Mica
 */
public class Ulaz extends Thread {
    private static final int MINT=1, MAXT=3;
    private boolean flag=false;
    private final Banka banka;

    public Ulaz(Banka banka) {
        this.banka = banka;
    }
    
    @Override
    public void run(){
        try{
            while(!interrupted()){
                synchronized (this){
                    while(!flag)wait();
                }
                
                banka.registruj(new Stranka());
                TimeUnit.SECONDS.sleep((long)(Math.random()*(MAXT-MINT)+MAXT));
            }
        }
        catch(InterruptedException e){}
    }
    
    public synchronized void otvori(){
        flag=true;
        notifyAll();
    }
    
    public void zatvori(){
        flag=false;
    }
    
    public void unisti(){
        interrupt();
    }
}
