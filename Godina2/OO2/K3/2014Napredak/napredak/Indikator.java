package napredak;

import java.awt.*;

/**
 * Индикатор напретка је обавестиво платно (Canvas) које служи за графички
 * приказ напредовања одговарајућег посла задатом бојом.
 */
public abstract class Indikator extends Canvas implements Obavestiva {
    protected Color boja_;

    private final static int SIRINA = 400;
    private final static int VISINA = 400;

    public Indikator(Color boja) {
        boja_ = boja;
        setSize(SIRINA, VISINA);
    }
}
