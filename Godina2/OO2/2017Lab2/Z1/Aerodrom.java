/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package avioni;

/**
 *
 * @author Mica
 */
public class Aerodrom {
    private final String ime;
    
    private static class Elem{
        Avion avion;
        Elem sled;
        Nit nit;

        public Elem(Avion avion) {
            this.avion = avion;
            sled=null;
        }
        
    }
    
    private static class Nit extends Thread{
        Avion a;
        String s;

        public Nit(Avion a) {
            this.a = a;
        }
        
        @Override
        public void run(){
            s=a.toString();
        }
    }
    
    Elem prvi, posl;

    public Aerodrom(String ime) {
        this.ime = ime;
    }
    
    public void sleti(Avion a){
        Elem novi=new Elem(a);
        if(prvi==null)prvi=novi;
        else posl.sled=novi;
        posl=novi;
    }
    
    public Avion odleti(){
        Avion tmp=prvi.avion;
        prvi=prvi.sled;
        if(prvi==null)posl=null;
        return tmp;
    }
    
    @Override
    public String toString(){
        StringBuilder s=new StringBuilder(ime+"\n");
        Elem tmp=prvi;
        while(tmp!=null){
            tmp.nit=new Nit(tmp.avion);
            tmp.nit.start();
            tmp=tmp.sled;
        }
        
        tmp=prvi;
        while(tmp!=null){
            try{
                tmp.nit.join();
            }
            catch(InterruptedException e){}
            s.append(tmp.nit.s+"\n");
            tmp=tmp.sled;
        }
        return s.toString();
    }
    
}
