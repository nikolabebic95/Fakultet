package napredak;

import java.awt.*;

/**
 * Кружни индикатор задатом бојом представља напредовање у облику исечка круга уписаног
 * у целу компоненту. Напредовање се представља одговарајућим процентуалним попуњавањем
 * исечка круга у обрнутом смеру од казаљке часовника.
 */
public class Kruzni extends Indikator {

    public Kruzni(Color boja) {
        super(boja);
    }

    @Override
    public void obavesti(int procenat) {
        Graphics g = getGraphics();
        g.setColor(boja_);
        g.fillArc(0, 0, getWidth(), getHeight(), 0, 360 * procenat / 100);
    }
}
