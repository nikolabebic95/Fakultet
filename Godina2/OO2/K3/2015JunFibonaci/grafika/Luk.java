package grafika;

import java.awt.*;
import java.util.concurrent.TimeUnit;

/**
 * Кружни лук садржи тачку која представља центар лука, дужину полупречника, почетни угао,
 * крајњи угао и графичку компоненту за цртање. Угао се мери у односу на смер позитивне X
 * осе, насупрот кретања казаљке часовника. За задати угао, може да се дохвати тачка на луку
 * чије се координате рачунају по формулама x = xC + r*Math.cos(u) и y = yC -
 * r*Math.sin(u) (r – полупречник лука, u - угао, xC и yC – координате центра лука).
 * Грешка је ако је угао изван опсега од почетног до крајњег угла лука. Лук се црта
 * надовезивањем (кратких) правих линија на придруженој компоненти, са кораком
 * 2*Math.PI/1000 и паузом од 3ms после сваког корака. Боја лука треба да буде случајна
 * комбинација RGB компоненти.
 */
public class Luk {
    private final Tacka centar_;
    private final double poluprecnik_;
    private final double pocetni_ugao_;
    private final double krajnji_ugao_;
    private final Graphics graficka_komponenta_za_crtanje_;

    private final static long VREME_SPAVANJA_U_MILISEKUNDAMA = 3;
    private final static double KORAK = 2 * Math.PI / 1000;

    public Luk(Tacka centar, double poluprecnik, double pocetni_ugao, double krajnji_ugao, Graphics graficka_komponenta_za_crtanje) {
        centar_ = centar;
        poluprecnik_ = poluprecnik;
        pocetni_ugao_ = pocetni_ugao;
        krajnji_ugao_ = krajnji_ugao;
        graficka_komponenta_za_crtanje_ = graficka_komponenta_za_crtanje;
    }

    public Tacka tackaNaLuku(double ugao) throws UgaoVanOpsega {
        if (ugao < pocetni_ugao_ || ugao > krajnji_ugao_) throw new UgaoVanOpsega();
        double x = centar_.x() + poluprecnik_ * Math.cos(ugao);
        double y = centar_.y() - poluprecnik_ * Math.sin(ugao);
        return new Tacka(x, y);
    }

    public void crtaj() throws InterruptedException {
        double pocetak = pocetni_ugao_;
        double kraj = pocetni_ugao_ + KORAK;
        float crveni_deo = (float) Math.random();
        float zeleni_deo = (float) Math.random();
        float plavi_deo = (float) Math.random();
        Color boja = new Color(crveni_deo, zeleni_deo, plavi_deo);
        graficka_komponenta_za_crtanje_.setColor(boja);
        while (kraj < krajnji_ugao_) {
            try {
                Tacka pocetna_tacka = tackaNaLuku(pocetak);
                Tacka krajnja_tacka = tackaNaLuku(kraj);
                graficka_komponenta_za_crtanje_.drawLine((int) pocetna_tacka.x(), (int) pocetna_tacka.y(), (int) krajnja_tacka.x(), (int) krajnja_tacka.y());
                pocetak = kraj;
                kraj += KORAK;
                TimeUnit.MILLISECONDS.sleep(VREME_SPAVANJA_U_MILISEKUNDAMA);
            } catch (UgaoVanOpsega e) {
                // Nece se desiti nikad
            }
        }
    }

}
