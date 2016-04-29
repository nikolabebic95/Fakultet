package pozoriste;

/**
 * Запослени у позоришту је описан именом и позориштем у којем је запослен. Сви подаци могу
 * да се дохвате. Може да се дохвати једнословна ознака врсте посла коју обавља, да се састави
 * текстуални опис у облику име[ознака_посла,назив_позоришта].
 */
public abstract class Zaposleni {
    private String ime_;
    private Pozoriste pozoriste_;

    public Zaposleni(String ime, Pozoriste pozoriste) {
        ime_ = ime;
        pozoriste_ = pozoriste;
    }

    public abstract char oznakaPosla();

    @Override
    public String toString() {
        return ime_ + "[" + oznakaPosla() + "," + pozoriste_.naziv() + "]";
    }
}
