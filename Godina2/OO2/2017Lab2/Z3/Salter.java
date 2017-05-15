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
public class Salter extends Thread {
    
    private static class Elem{
        Stranka s;
        Elem sled;

        public Elem(Stranka s) {
            this.s = s;
        }
        
    }
    
    private Elem prvi, posl;
    private int brojStranaka;
    private final Banka banka;
    private static final int MINT=3, MAXT=5;
    private static int identifikator;
    private final int id;

    public Salter(Banka banka) {
        this.banka = banka;
        id=++identifikator;
    }

    public synchronized int getBrojStranaka() {
        return brojStranaka;
    }
    
    @Override
    public void run(){
        try{
            while(!interrupted()){
                Stranka tmp;
                synchronized (this){
                    while(brojStranaka==0)wait();

                System.out.println("Usao");
                    tmp=prvi.s;
                    prvi=prvi.sled;
                    if(prvi==null)posl=null;
                    brojStranaka--;
                }
                
                StringBuilder s=new StringBuilder();
                s.append(id).append("/").append(tmp.getIznos()).append("/");
                if(banka.transfer(tmp))s.append("opsluzena");
                else s.append("odbijena");
                System.out.println(s.toString());
                banka.registrujIzlaz();
                TimeUnit.SECONDS.sleep((long)(Math.random()*(MAXT-MINT)+MINT));
            }
        }
        catch(InterruptedException e){}
    }
    
    public synchronized void dodaj(Stranka s){
        Elem novi=new Elem(s);
        brojStranaka++;
        if(prvi==null)prvi=novi;
        else posl.sled=novi;
        posl=novi;
        notifyAll();
    }
    
}
