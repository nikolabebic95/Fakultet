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
public class Strela extends Figura{
    private final double brzina;
    private final Color boja;
    private final double duzina;

    public Strela(double brzina, Color boja, double duzina, double x, double y) {
        super(x, y);
        this.brzina = brzina;
        this.boja = boja;
        this.duzina = duzina;
    }
    
    public void pomeri(){
        x+=brzina;
    }

    public double getDuzina() {
        return duzina;
    }
    
    @Override
    public void iscrtaj(Graphics graphics) {
        Color old=graphics.getColor();
        graphics.setColor(boja);
        graphics.drawLine((int)(x-duzina), (int)y, (int)x, (int)y);
        graphics.setColor(old);
    }    
}
