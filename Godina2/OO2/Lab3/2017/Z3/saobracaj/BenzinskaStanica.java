/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package saobracaj;

/**
 *
 * @author Mica
 */
public class BenzinskaStanica{
    private static final int KAPACITET=20;
    protected final Pumpa[] pumpe=new Pumpa [4];
    private final Automobil[] automobili=new Automobil[KAPACITET];
    private int prvi, poslednji, popunjeno;
    private boolean otvorena;
    private int radi = 0;
    
    public BenzinskaStanica() {
        prvi=poslednji=popunjeno=0;
        for(int i=0; i<4; i++)
            pumpe[i]=new Pumpa(this);
    }
    
    public void pokreni(){
        for(Pumpa p:pumpe)
            p.start();
    }
    
    public void otvori(){
        for(Pumpa p:pumpe)
            p.otvori();
        otvorena=true;
    }
    
    public synchronized void zatvori(){
        otvorena=false;
        for(Pumpa p:pumpe)
            p.zatvori();
        
        while (popunjeno > 0) {
            dohvati();
            radi--;
        }
        
        /*try{
            while(radi>0) wait();
        }
        catch(InterruptedException e){}*/
    }
    
    public void unisti(){
        for(Pumpa p:pumpe)
            p.interrupt();
    }
    
    public synchronized void dodaj(Automobil auto){
        if(popunjeno<KAPACITET && otvorena){
            automobili[poslednji]=auto;
            poslednji=(poslednji+1)%KAPACITET;
            popunjeno++;
            notifyAll();
        }
    }
    
    public synchronized void zavrseno(){
        radi--;
        notifyAll();
    }
    
    public synchronized Automobil dohvati(){
        try{
            while(popunjeno==0)wait();
            Automobil ret=automobili[prvi];
            prvi=(prvi+1)%KAPACITET;
            popunjeno--;
            radi++;
            return ret;
        }
        catch(InterruptedException e){
            return null;
        }
    }
    
    protected String prikazReda(){
        StringBuilder s=new StringBuilder();
        int tmp=prvi;
        boolean first=true;
        
        for(int i=0; i<popunjeno; i++){
            if(first)
                first=false;
            else
                s.append('\n');
            s.append(automobili[tmp].getId());
            tmp=(tmp+1)%KAPACITET;
        }
            return s.toString();
    }
}
