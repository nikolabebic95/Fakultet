/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fabrika;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Mica
 */
abstract public class Motor extends Thread{
    protected Mehanizam mehanizam=null;
    private double vreme=100;
    private boolean radi=false;
    
    public Motor(Mehanizam mehanizam) {
        this.mehanizam = mehanizam;
    }

    public synchronized void setVreme(double vreme) {
        this.vreme = vreme;
    }
    
    abstract public void podesiLabelu(String string);
    
    @Override
    public void run(){
        try{
            while(!interrupted()){
                synchronized(this){
                    while(!radi)wait();
                }
                podesiLabelu(mehanizam.izvrsenje());
                TimeUnit.MILLISECONDS.sleep((long)(0.4*vreme+0.8*vreme));
            }
        }
        catch(InterruptedException e){}
    }
    
    public void zaustavi(){
        radi=false;
    }
    public synchronized void nastavi(){
        radi=true;
        notifyAll();
    }
    
    public void prekini(){
        interrupt();
    }
}
