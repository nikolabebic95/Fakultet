/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import java.awt.*;
import saobracaj.*;

/**
 *
 * @author Mica
 */
public class GrafickiPrikazivac extends Canvas implements Prikazivac{
    private Automobil auto;
    
    @Override
    public void prikaziAuto(Automobil auto) {
        this.auto=auto;
        repaint();
    }
    
    @Override
    public void paint(Graphics graphics){
        Color old=graphics.getColor();
        graphics.clearRect(0, 0, getWidth(), getHeight());
        double procenat=0;
        if(auto!=null)
            procenat=auto.getKolicina()/auto.getKapacitet();
        graphics.setColor(Color.LIGHT_GRAY);
        graphics.fillRect(0, 0, (int)(getWidth()*procenat), getHeight());
        graphics.setColor(Color.BLACK);
        if(auto!=null)
            graphics.drawString(""+auto.getId(), 25, 25);
        graphics.drawRect(0, 0, getWidth(), getHeight());
        graphics.setColor(old);
    }
}
