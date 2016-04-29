package njive;

/**
 * (30 поена) Парцела има једнозначан аутоматски генерисан целобројан идентификатор и
 * задату површину (у квадратним метрима). Могу да јој се дохвате садржани подаци, као и
 * једнословна врста. Може да јој се одреди принос у периоду задатом бројем година. Може да
 * се састави текстуални опис у облику врста-идент[површ].
 */
public abstract class Parcela {
    private static int brojac_ = 0;
    private int id_ = brojac_++;
    private double povrsina_;

    public Parcela(double povrsina) {
        povrsina_ = povrsina;
    }

    public int id() {
        return id_;
    }

    public double povrsina() {
        return povrsina_;
    }

    public abstract char vrsta();

    public abstract double prinos(int godine);

    @Override
    public String toString() {
        return vrsta() + "-" + id_ + "[" + povrsina_ + "]";
    }
}
