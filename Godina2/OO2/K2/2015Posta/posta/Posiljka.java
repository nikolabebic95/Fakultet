package posta;

/**
 * (25 поена) Пошиљка има једнозначан аутоматски генерисан целобројан идентификатор и
 * адресу (ниска) на коју се шаље. Може да се дохвати адреса слања, да се направи копија
 * пошиљке и да се састави текстуални опис у облику p_идентификатор[адреса].
 */
public class Posiljka implements Cloneable {
    private static int brojac_ = 0;
    private int id_ = brojac_++;
    private String adresa_;

    public Posiljka(String adresa) {
        adresa_ = adresa;
    }

    String adresa() {
        return adresa_;
    }

    @Override
    public Posiljka clone() throws CloneNotSupportedException {
        Posiljka p = (Posiljka) super.clone();
        p.id_=brojac_++;
        return p;
    }

    @Override
    public String toString() {
        return "p_"+id_+"["+adresa_+"]";
    }
}
