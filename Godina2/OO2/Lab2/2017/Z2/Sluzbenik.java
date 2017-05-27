/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sluzba;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Mica
 */
public abstract class Sluzbenik extends Thread {
    private static int identifikator;
    private final int id;
    private final char vrsta;
    private boolean flag;
    private final double minT, maxT;

    public Sluzbenik(char vrsta, double minT, double maxT) {
        this.vrsta = vrsta;
        this.minT = minT;
        this.maxT = maxT;
        id=identifikator++;
        flag=false;
    }
    
    protected abstract Klijent radi () throws InterruptedException;
    
    @Override
    public void run(){
        try{
            while(!interrupted()){
                synchronized(this){
                    while(!flag)wait();
                }
                Klijent k=radi();
                System.out.println(vrsta+"/"+id+"/"+k);
                TimeUnit.SECONDS.sleep((long)(Math.random()*(maxT-minT)+minT));
            }
        }
        catch(InterruptedException e){}
    }
    
    public synchronized void pokreni(){
        flag=true;
        notifyAll();
    }
    
    public void zaustavi(){
        flag=false;
    }
    
    public void unisti(){
        interrupt();
    }
}
