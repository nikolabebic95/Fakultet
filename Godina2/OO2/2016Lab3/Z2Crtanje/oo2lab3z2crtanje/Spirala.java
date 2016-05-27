/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z2crtanje;

/**
 *
 * @author Nikola
 *
 * Спирала је крива задата формулама x=a·t·cos(b·t+c) и y=a·t·sin(b·t+c).
 * Коефицијенти a, b и c се задају приликом стварања спирале.
 */
public class Spirala implements Kriva {
    
    private final double a_;
    private final double b_;
    private final double c_;
    
   public Spirala(double a, double b, double c) {
       a_ = a;
       b_ = b;
       c_ = c;
   }
    
   @Override
   public Tacka izracunaj(double t) {
       double x = a_ * t * Math.cos(b_ * t + c_);
       double y = a_ * t * Math.sin(b_ * t + c_);
       return new Tacka(x, y);
   }
   
   @Override
   public String toString() {
       return "Spirala";
   }
   
}
