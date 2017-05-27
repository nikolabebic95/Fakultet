/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package funkcije;

/**
 *
 * @author Mica
 */
public class Sinusoida implements Funkcija{
    private final double a, b, c;

    public Sinusoida(double a, double b, double c) {
        this.a = a;
        this.b = b;
        this.c = c;
    }
    
    @Override
    public double f(double x) {
        return a*Math.sin(b*x+c);
    }
    
    @Override
    public String toString(){
        return a+"*sin("+b+"*x+"+c+")";
    }
}
