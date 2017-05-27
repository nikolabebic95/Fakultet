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
public class Putnicki extends Avion{

    public Putnicki(char oznaka, double maxTezina, double tezina, int kapacitet) {
        super(oznaka, maxTezina, tezina, kapacitet);
    }
    
    @Override
    protected boolean vrsta(Merljiv m){
        if (m instanceof Osoba)return true;
        else return false;
    }
}
