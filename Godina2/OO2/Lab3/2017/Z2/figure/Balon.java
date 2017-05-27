/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package figure;

import figure.Figura;
import java.awt.Color;
import java.awt.Graphics;

/**
 *
 * @author Mica
 */
public class Balon extends Figura{
    private Color boja;
    private final Color drugaBoja;
    private final double precnik;
    private final double brzina;
    private boolean probusen=false;

    public Balon(Color boja, Color drugaBoja, double precnik, double brzina, double x, double y) {
        super(x, y);
        this.boja = boja;
        this.drugaBoja=drugaBoja;
        this.precnik = precnik;
        this.brzina = brzina;
    }
    
    public void pomeri(){
        y-=brzina;
    }
    
    public void probusi(){
        boja=drugaBoja;
        probusen=true;
    }

    public boolean isProbusen() {
        return probusen;
    }

    public void setY(double y) {
        this.y = y;
    }

    public double getPrecnik() {
        return precnik;
    }
    
    @Override
    public void iscrtaj(Graphics graphics) {
        Color old=graphics.getColor();
        graphics.setColor(boja);
        graphics.fillOval((int)(x-precnik/2), (int)(y-precnik/2), (int)precnik, (int)precnik);
        graphics.setColor(old);
    }
}
