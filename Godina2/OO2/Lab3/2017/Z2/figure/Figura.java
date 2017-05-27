/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package figure;

import java.awt.Graphics;

/**
 *
 * @author Mica
 */
public abstract class Figura {
    protected double x, y;

    public Figura(double x, double y) {
        this.x = x;
        this.y = y;
    }
    
    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }
    
    public abstract void iscrtaj(Graphics graphics);
}
