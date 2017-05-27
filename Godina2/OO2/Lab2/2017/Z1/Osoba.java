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
public class Osoba implements Merljiv{
    private final double tezina;
    private final String ime;

    public Osoba(double tezina, String ime) {
        this.tezina = tezina;
        this.ime = ime;
    }

    @Override
    public double getTezina() {
        return tezina;
    }

    public String getIme() {
        return ime;
    }
    
    @Override
    public String toString(){
        String s=ime+"("+tezina+")";
        return s;
    }
    
}
