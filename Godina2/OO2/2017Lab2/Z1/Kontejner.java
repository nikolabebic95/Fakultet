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
public class Kontejner implements Merljiv{
    private static int identifikator;
    private final int id;
    private final double tezina;
    private double sadrzi;

    public Kontejner(double tezina) {
        this.tezina = tezina;
        id=identifikator++;
    }

    @Override
    public double getTezina() {
        return tezina;
    }

    public int getId() {
        return id;
    }
    
    public void ubaci(double m){
        sadrzi++;
    }
    
    public void izvadi(double m){
        sadrzi--;
    }
    
    @Override
    public String toString(){
        String s=id+"("+(tezina+sadrzi)+")";
        return s;
    }
    
}
