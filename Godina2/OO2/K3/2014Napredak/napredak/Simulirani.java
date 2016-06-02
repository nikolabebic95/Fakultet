package napredak;

import java.util.concurrent.TimeUnit;

/**
 * Симулирани посао остварује радњу спавањем случајног трајања у задатом опсегу времена у ms.
 */
public class Simulirani extends Posao {
    private final long donja_granica_vremena_u_milisekundama_;
    private final long gornja_granica_vremena_u_milisekundama_;

    public Simulirani(
            int ukupan_broj_izvrsavanja,
            int korak_broja_izvrsavanja,
            long donja_granica_vremena_u_milisekundama,
            long gornja_granica_vremena_u_milisekundama
    ) {
        super(ukupan_broj_izvrsavanja, korak_broja_izvrsavanja);
        donja_granica_vremena_u_milisekundama_ = donja_granica_vremena_u_milisekundama;
        gornja_granica_vremena_u_milisekundama_ = gornja_granica_vremena_u_milisekundama;
    }

    @Override
    protected void izvrsiRadnju() throws InterruptedException {
        long vreme_spavanja_u_milisekundama = (long) (Math.random() * (gornja_granica_vremena_u_milisekundama_ - donja_granica_vremena_u_milisekundama_ + 1) + donja_granica_vremena_u_milisekundama_);
        TimeUnit.MILLISECONDS.sleep(vreme_spavanja_u_milisekundama);
    }
}
