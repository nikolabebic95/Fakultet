/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banke;

/**
 *
 * @author Mica
 */
public class Stranka {
    private final int iznos;
    private static final int MIN=-1000, MAX=1000;
    
    public Stranka() {
        iznos=(int) (Math.random()*(MAX-MIN)+MIN);
    }

    public int getIznos() {
        return iznos;
    }
    
}
