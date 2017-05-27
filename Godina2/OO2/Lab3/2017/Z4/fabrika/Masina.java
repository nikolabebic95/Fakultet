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
public class Masina implements Mehanizam{
    private final Skladiste skladiste;
    private Proizvod poslednjiProizvod=null;

    public Masina(Skladiste skladiste) {
        this.skladiste = skladiste;
    }
    
    @Override
    public synchronized String izvrsenje() throws InterruptedException{
        poslednjiProizvod=new Proizvod();
        skladiste.dodaj(poslednjiProizvod);
        return toString();
    }
    
    @Override
    public synchronized String toString(){
        StringBuilder s=new StringBuilder().append("M");
        if(poslednjiProizvod!=null)
            s.append(poslednjiProizvod);
        return s.toString();
    }
}
