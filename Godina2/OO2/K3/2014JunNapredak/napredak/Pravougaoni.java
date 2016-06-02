package napredak;

import java.awt.*;

/**
 * Правоугаони индикатор задатом бојом представља напредовање у облику правоугаоника
 * који покрива целу компоненту. Напредовање се представља одговарајућим процентуалним
 * попуњавањем правоугаоника у правцу дуже странице (слева-удесно или одозго-наниже).
 */
public class Pravougaoni extends Indikator {

    public Pravougaoni(Color boja) {
        super(boja);
    }

    @Override
    public void obavesti(int procentualni_napredak) {
        int x_pocetak = 0;
        int y_pocetak = 0;
        int x_kraj = getWidth();
        int y_kraj = getHeight();
        if (x_kraj < y_kraj) {
            x_kraj = (int) ((double) procentualni_napredak / 100.0 * x_kraj);
        } else {
            y_kraj = (int) ((double) procentualni_napredak / 100.0 * y_kraj);
        }
        Graphics g = getGraphics();
        if (x_kraj == 0 || y_kraj == 0) {
            g.setColor(Color.WHITE);
            g.fillRect(x_pocetak, y_pocetak, getWidth(), getHeight());
        } else {
            g.setColor(boja_);
            g.fillRect(x_pocetak, y_pocetak, x_kraj, y_kraj);
        }
    }
}
