package vozila;

/**
 * Кaмера има једнозначан аутоматски генерисан целобројан идентификатор. Она на захтев сними
 * задато возило, када памти возило и време снимања (мерено од почетка извршавања програма)
 * и може да испоручи снимак возила (ниска) у облику [идКам:време]регБр.
 */
public class Kamera {
    private static long pocetakPrograma_ = System.currentTimeMillis();
    private static int brojac_ = 0;
    private int id_ = brojac_++;
    private Vozilo vozilo_;
    private long vreme_;

    public void snimi(Vozilo vozilo) {
        vreme_ = System.currentTimeMillis() - pocetakPrograma_;
        vozilo_ = vozilo;
    }

    public String snimak() {
        return "[" + id_ + ":" + vreme_ + "]" + vozilo_.oznaka();
    }
}
