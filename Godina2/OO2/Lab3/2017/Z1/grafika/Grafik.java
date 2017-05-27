/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import funkcije.Funkcija;
import java.awt.*;
import java.util.concurrent.TimeUnit;

/**
 *
 * @author Mica
 */
public class Grafik extends Canvas implements Runnable {
    private final Thread nit=new Thread(this);
    private static final long VREME_SPAVANJA=100;
    private int brojTacaka;
    private final Funkcija funkcija;
    private double v;
    private boolean radi=false;
    private final double xDonjaGranica, xGornjaGranica;
    private final double yDonjaGranica, yGornjaGranica;
    private double pocetnoVreme=0, vremeCekanja=0;
    private double vremeStajanja;
    
    public Grafik(Funkcija funkcija, double xDonjaGranica, double xGornjaGranica, double yDonjaGranica, double yGornjaGranica) {
        this.funkcija = funkcija;
        this.xDonjaGranica = xDonjaGranica;
        this.xGornjaGranica = xGornjaGranica;
        this.yDonjaGranica = yDonjaGranica;
        this.yGornjaGranica = yGornjaGranica;
    }
    
    public void start(){
        nit.start();
        pocetnoVreme=System.currentTimeMillis()/1000.0;
        vremeStajanja=pocetnoVreme;
    }
    
    @Override
    public void run() {
        try{
            while(!Thread.interrupted()){
                synchronized(this){while(!radi) wait();}
                crtaj();
                TimeUnit.MILLISECONDS.sleep(VREME_SPAVANJA);
            }
        }
        catch(InterruptedException e){}
    }
    
    public void crtaj(){
        Graphics graphics=getGraphics();
        graphics.setColor(Color.white);
        graphics.fillRect(0, 0, getWidth(), getHeight());
        graphics.setColor(Color.black);
        double sirina=xGornjaGranica-xDonjaGranica;
        double korak=sirina/brojTacaka;
        double xPrethodno=0, yPrethodno=0;
        for(int i=0; i<brojTacaka; i++){
            double x=i*korak+xDonjaGranica;
            double t=System.currentTimeMillis()/1000.0-pocetnoVreme-vremeCekanja;
            double y=funkcija.f(x+v*t);
            double xZaCrtanje=(x-xDonjaGranica)/(xGornjaGranica-xDonjaGranica)*getWidth();
            double yZaCrtanje=(y-yDonjaGranica)/(yGornjaGranica-yDonjaGranica)*getHeight();
            if(i>0){
                graphics.drawLine((int)xPrethodno, (int)yPrethodno, (int)xZaCrtanje, (int)yZaCrtanje);
            }
            xPrethodno=xZaCrtanje;
            yPrethodno=yZaCrtanje;
        }
            
    }

    public void setBrojTacaka(int brojTacaka) {
        this.brojTacaka = brojTacaka;
    }

    public void setV(double v) {
        this.v = v;
    }
    
    public synchronized void zaustavi(){
        radi=false;
        vremeStajanja=System.currentTimeMillis()/1000.0;
    }
    
    public synchronized void nastavi(){
        vremeCekanja+=System.currentTimeMillis()/1000.0-vremeStajanja;
        radi=true;
        notifyAll();
    }
    
    public void prekini(){
        if(pocetnoVreme!=0)
            nit.interrupt();
    }
}
