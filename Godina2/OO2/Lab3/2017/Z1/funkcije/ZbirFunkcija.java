/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package funkcije;

/**
 *
 * @author Mica
 */
public class ZbirFunkcija implements Funkcija{

    private static class Elem{
        Funkcija funkcija;
        Elem sled;

        public Elem(Funkcija funkcija) {
            this.funkcija = funkcija;
            this.sled=null;
        }
    }
    
    private Elem prvi, posl;
    
    public void dodaj(Funkcija funkcija){
        Elem novi=new Elem(funkcija);
        if(prvi==null)
            prvi=novi;
        else posl.sled=novi;
        posl=novi;
    }
    
    public void izbaci(){
        prvi=posl=null;
    }
    
    @Override
    public double f(double x) {
        Elem tmp=prvi;
        double vrednost=0;
        while (tmp!=null){
            vrednost+=tmp.funkcija.f(x);
            tmp=tmp.sled;
        }
        return vrednost;
    }
    
    @Override
    public String toString(){
        StringBuilder s=new StringBuilder();
        Elem tmp=prvi;
        while(tmp!=null){
            s.append(tmp.funkcija.toString()).append('\n');
            tmp=tmp.sled;
        }
        return s.toString();
    }
}
