package proizvod;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Mica
 */
public class Proizvod {
    private static int identifikator;
    private final int id;
    private final double masa;

    public Proizvod(double masa) {
        this.masa = masa;
        id=identifikator++;
    }

    public double getMasa() {
        return masa;
    }
    
    @Override
    public String toString(){
        String s=id+"("+masa+")";
        return s;
    }
    
}
