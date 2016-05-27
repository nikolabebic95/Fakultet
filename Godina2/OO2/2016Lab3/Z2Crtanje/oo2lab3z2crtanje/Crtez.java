/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z2crtanje;

import java.awt.*;
import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 *
 * Цртеж је графичка компонента по којој може да се црта задата крива задатом
 * бојом мењајући параметар t од tmin до tmax са кораком Δt. Приликом стварања
 * цртежа задају се опсези координата који се пресликају на целу компоненту и
 * који касније не могу да се промене, тако да изглед криве зависи од актуелне
 * величине компоненте.
 */
public class Crtez extends Canvas {

    private final int gore_;
    private final int dole_;
    private final int levo_;
    private final int desno_;

    private final static long SLEEP_TIME_MILLISECONDS = 5;

    public Crtez(int gore, int dole, int levo, int desno) {
        gore_ = gore;
        dole_ = dole;
        levo_ = levo;
        desno_ = desno;

    }

    Tacka skaliraj(Tacka tacka) {
        double x = tacka.x() - levo_;
        double y = tacka.y() - gore_;
        x *= getWidth();
        y *= getHeight();
        x /= desno_ - levo_;
        y /= dole_ - gore_;
        y = getHeight() - 1 - y;
        return new Tacka(x, y);
    }

    public void crtaj(Kriva kriva, Color boja, double donjaGranica, double gornjaGranica, double korak) {
        // Mozda staviti u posebnu nit
        Graphics olovka = getGraphics();
        olovka.clearRect(0, 0, getWidth(), getHeight());
        olovka.setColor(boja);
        for (double i = donjaGranica; i <= gornjaGranica; i += korak) {
            double sledeci = i + korak;
            if (sledeci > gornjaGranica) {
                sledeci = gornjaGranica;
            }
            Tacka t1 = kriva.izracunaj(i);
            Tacka t2 = kriva.izracunaj(sledeci);
            t1 = skaliraj(t1);
            t2 = skaliraj(t2);
            olovka.drawLine((int) t1.x(), (int) t1.y(), (int) t2.x(), (int) t2.y());
            try {
                TimeUnit.MILLISECONDS.sleep(SLEEP_TIME_MILLISECONDS);
            } catch (InterruptedException e) {
            }
        }
    }

}
