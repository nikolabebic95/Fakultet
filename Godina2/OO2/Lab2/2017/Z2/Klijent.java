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
public class Klijent {
    private static int identifikator;
    private final int id;
    private final int kod;

    public Klijent(int kod) {
        this.kod = kod;
        id=identifikator++;
    }

    public int getId() {
        return id;
    }

    public int getKod() {
        return kod;
    }
    
    @Override
    public String toString(){
        String s=id+"("+kod+")";
        return s;
    }
    
}
