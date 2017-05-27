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
public class Traka implements Mehanizam{
    private final Skladiste skladiste;
    private Proizvod poslednjiProizvod=null;

    public Traka(Skladiste skladiste) {
        this.skladiste = skladiste;
    }
    
    @Override
    public synchronized String izvrsenje() throws InterruptedException{
        poslednjiProizvod=skladiste.uzmi();
        return toString();
    }
    
    @Override
    public synchronized String toString(){
        StringBuilder s=new StringBuilder().append("T");
        if(poslednjiProizvod!=null)
            s.append(poslednjiProizvod);
        return s.toString();
    }
}
