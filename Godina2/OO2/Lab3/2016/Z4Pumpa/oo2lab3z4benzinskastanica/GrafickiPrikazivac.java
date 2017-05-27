/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z4benzinskastanica;

import java.awt.*;

/**
 *
 * @author Nikola
 *
 * Графички приказивач је приказивач и компонента типа Canvas на којој се, према
 * слици, исцртава светлосива трака чија је дужина пропорционална количини
 * горива у придруженом аутомобилу. На почетном делу те траке исцртава се
 * идентификатор аутомобила.
 */
public class GrafickiPrikazivac extends Canvas implements Prikazivac {

    private Automobil automobil_;

    private final static int POMERAJ = 5;

    private final static int X_ID = 25;
    private final static int Y_ID = 25;

    @Override
    public void prikazi(Automobil automobil) {
        automobil_ = automobil;
        repaint();
    }

    @Override
    public void paint(Graphics g) {

        int sirina = getWidth();
        int visina = getHeight();

        g.setColor(Color.WHITE);
        g.fillRect(0, 0, sirina, visina);

        g.setColor(Color.BLACK);
        g.drawRect(POMERAJ, POMERAJ, sirina - POMERAJ, visina - POMERAJ);

        if (automobil_ == null) {
            return;
        }

        g.setColor(Color.LIGHT_GRAY);
        double procenat = automobil_.gorivo() / automobil_.rezervoar();
        int desnaKoordinata = (int) (procenat * (sirina - 2 * POMERAJ) + POMERAJ);
        g.fillRect(POMERAJ, POMERAJ, desnaKoordinata, visina - POMERAJ);

        g.setColor(Color.BLACK);
        g.drawString("" + automobil_.id(), X_ID, Y_ID);
    }

}
