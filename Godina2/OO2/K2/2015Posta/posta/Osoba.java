package posta;

import java.util.concurrent.TimeUnit;

/**
 * (35 поена) Активна особа има име, границе опсега времена (у ms) и придружено сандуче. У
 * случајним временским интервалима, између најкраћег и најдужег времена (задатих пр
 * стварању особе), особа извршава одређену радњу. Грешка је ако су најкраће и најдуже време
 * извршавања неисправно задати. Може да се састави текстуални опис особе наводећи име
 * особе, а у посебном реду придружено сандуче.
 */
public abstract class Osoba implements Runnable {
    private String ime_;
    private int donjaGranica_;
    private int gornjaGranica_;
    private Sanduce sanduce_;

    public Osoba(String ime, int donjaGranica, int gornjaGranica, Sanduce sanduce) throws PogresnoVreme {
        if (donjaGranica < 0) throw new PogresnoVreme();
        if (gornjaGranica < 0) throw new PogresnoVreme();
        if (gornjaGranica <= donjaGranica) throw new PogresnoVreme();
        ime_ = ime;
        donjaGranica_ = donjaGranica;
        gornjaGranica_ = gornjaGranica;
        sanduce_ = sanduce;
    }

    protected abstract void apstraktnaRadnja() throws InterruptedException;

    @Override
    public void run() {
        try {
            while (!Thread.interrupted()) { // IntelliJ kaze da ne valja da se while napusta exceptionom
                int vreme = (int) (Math.random() * (gornjaGranica_ - donjaGranica_) + donjaGranica_);
                apstraktnaRadnja();
                TimeUnit.MILLISECONDS.sleep(vreme);
            }
        } catch (InterruptedException e) {
            // IntelliJ kaze da je prazan catch blok i da ne valja
            // Ali ne kaze kad stavim komentar
            // Pritom u ovo nece nikad uci ali moram da stavim jer java nema pojma
        }
    }

    @Override
    public String toString() {
        return ime_ + "\n" + sanduce_;
    }

    protected Sanduce sanduce() {
        return sanduce_;
    }

}
