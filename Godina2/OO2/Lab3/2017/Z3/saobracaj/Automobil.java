/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package saobracaj;

/**
 *
 * @author Mica
 */
public class Automobil {
    private static int ID=0;
    private final int id=ID++;
    private final double kapacitet;
    private double kolicina;

    public Automobil(double kapacitet) {
        this.kapacitet = kapacitet;
        this.kolicina=Math.random()*0.2*kapacitet+0.1*kapacitet;
    }

    public int getId() {
        return id;
    }

    public double getKapacitet() {
        return kapacitet;
    }

    public double getKolicina() {
        return kolicina;
    }
    
    public void sipaj(double kolicina) throws GreskaPun{
        if(this.kolicina+kolicina>kapacitet){
            this.kolicina=kapacitet;
            throw new GreskaPun();
        }
        else
            this.kolicina+=kolicina;
    }
}
