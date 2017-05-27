/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package figure;

import figure.Figura;
import grafika.Scena;
import java.awt.Color;
import java.awt.Graphics;

/**
 *
 * @author Mica
 */
public class Luk extends Figura{
    private final Color boja;
    private final double duzinaIvica;
    private final double korak;

    public Luk(Color boja, double duzinaIvica, double korak, double x, double y) {
        super(x, y);
        this.boja = boja;
        this.duzinaIvica = duzinaIvica;
        this.korak = korak;
    }
    
    public void pomeriGore(){
        y-=korak;
    }
    
    public void pomeriDole(){
        y+=korak;
    }
    
    @Override
    public void iscrtaj(Graphics graphics) {
        Color old=graphics.getColor();
        graphics.setColor(boja);
        graphics.drawLine((int)x, (int)(y-duzinaIvica/2), (int)x, (int)(y+duzinaIvica/2));
        graphics.drawLine((int)x, (int)(y-duzinaIvica/2), (int)(x+duzinaIvica), (int)y);
        graphics.drawLine((int)x, (int)(y+duzinaIvica/2), (int)(x+duzinaIvica), (int)y);
        graphics.setColor(old);
    }
    
    public void ispali(double duzina, Color boja, double brzina, Scena scena){
        scena.dodaj(new Strela(brzina, boja, duzina, x+duzinaIvica+duzina, y));
    }

    public double getDuzinaIvica() {
        return duzinaIvica;
    }

    public double getKorak() {
        return korak;
    }
}
