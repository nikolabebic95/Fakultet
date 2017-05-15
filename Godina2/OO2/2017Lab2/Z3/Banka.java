/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banke;

/**
 *
 * @author Mica
 */
public class Banka {
    private double suma;
    private final Ulaz ulaz;
    private final Salter salter1, salter2;

    public Banka() {
        ulaz=new Ulaz(this);
        salter1=new Salter(this);
        salter2=new Salter(this);
    }
    
    public void startuj(){
        ulaz.start();
        salter1.start();
        salter2.start();
    }
    
    public int brojStranaka(){
        return salter1.getBrojStranaka() + salter2.getBrojStranaka();
    }

    public synchronized double getSuma() {
        return suma;
    }
    
    public void registruj(Stranka s){
        if(salter1.getBrojStranaka()<salter2.getBrojStranaka())
            salter1.dodaj(s);
        else
            salter2.dodaj(s);
    }
    public synchronized boolean transfer(Stranka s){
        int iznos=s.getIznos();
        if(suma+iznos<0)
            return false;
        else{
            suma+=iznos;
            return true;
        }
    
    }
    public synchronized void registrujIzlaz(){
        notifyAll();
    }
    
    public void otvori(double suma){
        this.suma=suma;
        System.out.println("Pocetna suma iznosi "+suma+".");
        ulaz.otvori();
    }
    
    public void zatvori(){
        ulaz.zatvori();
        try{
            while(salter1.getBrojStranaka()!=0 || salter2.getBrojStranaka()!=0) wait();
        }
        catch(InterruptedException e){}
        System.out.println("Preostala suma novca u banci iznosi "+suma+".");
    }
    
    public void unisti(){
        ulaz.unisti();
        salter1.interrupt();
        salter2.interrupt();
    }
}
