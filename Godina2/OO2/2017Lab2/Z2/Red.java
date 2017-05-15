/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sluzba;

/**
 *
 * @author Mica
 */
public class Red {
    private final int MAX=10;
    private final Klijent [] niz;
    private int prvi, sadrzi;

    public Red() {
        niz=new Klijent [MAX];
    }
    
    public synchronized Red stavi(Klijent k) throws InterruptedException {
        while(sadrzi==MAX)wait();
        niz[(prvi+sadrzi)%MAX]=k;
        sadrzi++;
        System.out.println(this);
        notifyAll();
        return this;
    }
    
    public synchronized Klijent uzmi() throws InterruptedException {
        while(sadrzi==0)wait();
        Klijent tmp=niz[prvi];
        prvi=(prvi+1)%MAX;
        sadrzi--;
        System.out.println(this);
        notifyAll();
        return tmp;
    }
    
    @Override
    public synchronized String toString(){
        StringBuilder s=new StringBuilder();
        boolean first=true;
        for(int i=0; i<sadrzi; i++){
            if(first)first=false;
            else s.append(",");
            s.append(niz[(prvi+i)%MAX]);
        }
        return s.toString();
    }
}
