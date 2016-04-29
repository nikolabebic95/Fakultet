package pozoriste;

/**
 * (20 поена) Позориште има једнозначан аутоматски генерисан целобројан идентификатор и
 * назив који могу да се дохвате. Може да се састави текстуални опис у облику назив[идент].
 */
public class Pozoriste {
    private static int brojac_ = 0;
    private int id_ = brojac_++;
    private String naziv_;

    public Pozoriste(String naziv) {
        naziv_ = naziv;
    }

    public int id() {
        return id_;
    }

    public String naziv() {
        return naziv_;
    }

    @Override
    public String toString() {
        return naziv_ + "[" + id_ + "]";
    }
}
