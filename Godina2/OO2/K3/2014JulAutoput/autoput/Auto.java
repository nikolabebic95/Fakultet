package autoput;

/**
 * Покретан ауто има случајну, аутоматски генерисану регистарску ознаку која
 * се састоји од једног слова и три цифре. Креће се случајном целобројном
 * брзином у задатом интервалу између vmin и vmax (подразумевано од 60 до 200).
 * Може да се дохвати брзина којом се ауто креће, пут који је прешао од тренутка
 * стварања и да се састави текстуални опис у облику ознака(брзина).
 */
public class Auto implements Pokretna {
    private final char slovo_;
    private final static int BROJ_CIFARA = 3;
    private final char[] cifre_ = new char[BROJ_CIFARA];

    {
        slovo_ = (char) (Math.random() * ('Z' - 'A' + 1) + 'A');
        for (int i = 0; i < BROJ_CIFARA; i++) cifre_[i] = (char) (Math.random() * ('9' - '0' + 1) + '0');
    }

    private final static double DONJA_GRANICA_BRZINE = 60;
    private final static double GORNJA_GRANICA_BRZINE = 200;

    private final double brzina_;

    private final long pocetno_vreme_ = System.currentTimeMillis();
    private double predjeni_put_ = 0;

    public Auto(double donja_granica_brzine, double gornja_granica_brzine) {
        brzina_ = Math.random() * (gornja_granica_brzine - donja_granica_brzine) + donja_granica_brzine;
    }

    public Auto() {
        this(DONJA_GRANICA_BRZINE, GORNJA_GRANICA_BRZINE);
    }

    public double brzina() {
        return brzina_;
    }

    public double predjeniPut() {
        return predjeni_put_;
    }

    @Override
    public void saopsti(long trenutno_vreme_u_milisekundama) {
        long vreme = trenutno_vreme_u_milisekundama - pocetno_vreme_;
        predjeni_put_ = vreme * brzina_;
    }

    @Override
    public String toString() {
        StringBuilder povratna = new StringBuilder();
        povratna.append(slovo_);
        for (char cifra : cifre_) povratna.append(cifra);
        povratna.append('(').append(String.format("%.0f", brzina())).append(')');
        return povratna.toString();
    }
}
