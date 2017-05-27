/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import figure.Strela;
import figure.Balon;
import figure.Figura;
import java.awt.*;
import java.util.concurrent.TimeUnit;

/**
 *
 * @author Mica
 */
public class Scena extends Canvas implements Runnable{
    private final Thread nit=new Thread(this);
    private static final long VREME_SPAVANJA=100;
    
    private static class Elem{
        Figura figura;
        Elem sled;

        public Elem(Figura figura) {
            this.figura = figura;
            this.sled=null;
        }
    }
    Elem prvi, posl;
    
    public void initialize(){
        nit.start();
    }

    @Override
    public void run() {
        try{
            while(!nit.isInterrupted()){
                TimeUnit.MICROSECONDS.sleep(VREME_SPAVANJA);
                iscrtaj();
                pomeri();
                izbaci();
                probusi();
            }
        }
        catch(InterruptedException e){}
    }
    
    public void iscrtaj(){
        Graphics graphics=this.getGraphics();
        graphics.clearRect(0, 0, getWidth(), getHeight());
        Elem tmp=prvi;
        while(tmp!=null){
            tmp.figura.iscrtaj(graphics);
            tmp=tmp.sled;
        }
    }
    
    public void pomeri(){
        Elem tmp=prvi;
        while(tmp!=null){
            if(tmp.figura instanceof Strela){
                ((Strela)tmp.figura).pomeri();
            }
            else if(tmp.figura instanceof Balon){
                ((Balon)tmp.figura).pomeri();
            }
            tmp=tmp.sled;
        }  
    }
    
    public void izbaci(){
        Elem tmp=prvi;
        while(tmp!=null){
            if(tmp.figura instanceof Strela){
                Strela strela=(Strela)tmp.figura;
                if(strela.getDuzina()+strela.getX()>=getWidth())
                    izbaci(strela);
            }
            else if(tmp.figura instanceof Balon){
                Balon balon=(Balon)tmp.figura;
                if(balon.getY()<0){
                    if(balon.isProbusen())
                        izbaci(balon);
                    else{
                        balon.setY(getHeight());
                    }
                }
            }
            tmp=tmp.sled;
        }
    }
    
    public void probusi(){
        Elem i=prvi;
        while(i!=null){
            Elem j=prvi;
            while(j!=null){
                if((i.figura instanceof Strela) && (j.figura instanceof Balon)){
                    double x1, x2, y1, y2, x, y;
                    x1=i.figura.getX();
                    y1=i.figura.getY();
                    x2=j.figura.getX();
                    y2=j.figura.getY();
                    x=x1-x2;
                    y=y1-y2;
                    Balon balon=(Balon)j.figura;
                    
                    if(Math.sqrt(x*x+y*y)<balon.getPrecnik()/2)
                        balon.probusi();
                }
                j=j.sled;
            }
            i=i.sled;
        }
    }
    
    public void dodaj(Figura f){
        Elem novi=new Elem(f);
        if(prvi==null)
            prvi=novi;
        else
            posl.sled=novi;
        posl=novi;
    }
    
    public Figura dohvati(){
        Elem ret=prvi;
        prvi=prvi.sled;
        return ret.figura;
    }
    
    public void izbaci(Figura f){
        Elem tek=prvi;
        Elem pret=null;
        
        while(tek!=null && tek.figura!=f){
            pret=tek;
            tek=tek.sled;
        }
        
        if(tek!=null){
            if(pret==null)
                prvi=tek.sled;
            else
                pret.sled=tek.sled;
            if(tek==posl)
                posl=pret;
        } 
    }
    
    public void zaustavi(){
        nit.interrupt();
    }
}
