/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proizvod;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Mica
 */
public class Radnik extends Thread {
    private final String ime;
    private final double produktivnost;
    private Proizvod proizvod;
    private boolean radi, gotov;
    private double masa;

    public Radnik(String ime, double produktivnost) {
        this.ime = ime;
        this.produktivnost = produktivnost;
    }
    
    public synchronized void proizvedi(double m)throws InterruptedException{
        if(radi || gotov) wait();
        masa=m;
        radi=true;
        notifyAll();
    }
    
    public synchronized Proizvod preuzmi()throws InterruptedException {
        System.out.println(radi+" "+gotov);
        if(radi || !gotov) wait();
        System.out.println("drugi");
        gotov=false;
        notifyAll();
        return proizvod;
    }

    public synchronized boolean isGotov() {
        return gotov;
    }
    
    @Override
    public void run(){
        
        try{
            while(!interrupted()){
                synchronized(this){
                    while(!radi)wait();

                    proizvod=new Proizvod(masa);
                    radi=false;
                    gotov=true;
                    notifyAll();
                }
                
                TimeUnit.SECONDS.sleep((long)(masa/produktivnost));                
            }
        }
        catch(InterruptedException e){}
    }
    
    @Override
    public synchronized String toString(){
        StringBuilder s=new StringBuilder();
        s.append(ime).append("/");
        if(!radi && !gotov)s.append("ceka");
        else if(!gotov)s.append("radi");
        else s.append(proizvod);
        return s.toString();
    }
}
