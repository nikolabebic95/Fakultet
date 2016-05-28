/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z4benzinskastanica;

/**
 *
 * @author Nikola
 */
public class PrepunjenRezervoar extends Exception {
    
    private final double prosuto_;

    public PrepunjenRezervoar(double prosuto) {
        prosuto_ = prosuto;
    }

    @Override
    public String toString() {
        return "Prosuto je " + prosuto_ + " goriva";
    }
}
