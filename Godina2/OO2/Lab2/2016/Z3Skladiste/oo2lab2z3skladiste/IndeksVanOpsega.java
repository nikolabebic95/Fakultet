/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z3skladiste;

/**
 *
 * @author Nikola
 */
public class IndeksVanOpsega extends Exception {
    private int indeks_;
    private int donja_;
    private int gornja_;
    
    public IndeksVanOpsega(int indeks, int donja, int gornja) {
        indeks_ = indeks;
        donja_ = donja;
        gornja_ = gornja;
    }
    
    @Override    
    public String toString() {
        return indeks_ + " nije u opsegu [" + donja_ + "," + gornja_ + "]";
    }
}
