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
public abstract class Avion {
    private final char oznaka;
    private final double maxTezina;
    private double sadrzi;
    private final double tezina;
    private final Merljiv [] niz;

    public Avion(char oznaka, double maxTezina, double tezina, int kapacitet) {
        this.oznaka = oznaka;
        this.maxTezina = maxTezina;
        this.tezina = tezina;
        niz=new Merljiv [kapacitet];
    }

    public double getTezina() {
        return tezina+sadrzi;
    }
    
    protected abstract boolean vrsta(Merljiv m);
    
    public void stavi(Merljiv m, int i)throws GPun, GPopunjeno, GVrsta{
        if(!vrsta(m))throw new GVrsta();
        if (m.getTezina()+tezina+sadrzi>maxTezina) throw new GPun();
        if(niz[i]!=null) throw new GPopunjeno();
        niz[i]=m;
    }
    
    public Merljiv uzmi(int i)throws GPrazno{
        if (niz[i]==null) throw new GPrazno();
        Merljiv tmp=niz[i];
        niz[i]=null;
        return tmp;
    }
    
    @Override
    public String toString(){
        StringBuilder s=new StringBuilder(oznaka+"("+getTezina()+")[");
        boolean prvi=true;
        
        for(Merljiv m:niz){
            if (m!=null){
                if (prvi) prvi=false;
                else s.append(",");
                s.append(m);
            }
        }
        s.append("]");
        return s.toString();
    }
    
    
}
