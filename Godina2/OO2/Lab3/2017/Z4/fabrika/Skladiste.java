/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fabrika;

/**
 *
 * @author Mica
 */
public class Skladiste {
    private final Proizvod[] proizvodi;
    private int ubaceno;

    public Skladiste(int kapacitet) {
        proizvodi=new Proizvod[kapacitet];
    }
    
    public synchronized void dodaj(Proizvod proizvod)throws InterruptedException{
        while(ubaceno==proizvodi.length)
            wait();
        proizvodi[ubaceno++]=proizvod;
        notifyAll();
    }
    
    public synchronized Proizvod uzmi() throws InterruptedException {
        while(ubaceno==0)
            wait();
        ubaceno--;
        Proizvod ret=proizvodi[ubaceno];
        proizvodi[ubaceno]=null;
        notifyAll();
        return ret;
    }
    
    @Override
    public String toString(){
        StringBuilder s=new StringBuilder();
        boolean prvi=true;
        
        for(int i=0; i<ubaceno; i++){
            if(prvi)
                prvi=false;
            else
                s.append('\n');
            s.append(proizvodi[i].toString());
        }
        
        return s.toString();
    }
}
