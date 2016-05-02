package kisa;

/**
 * (20 поена) Ливада је матрица бусена задатих димензија која се
 * попуњава копијама задатог бусена. Могу да се дохвате димензије
 * ливаде, да падне задата кап кише на бусен са задатим индексима.
 * Грешка је ако је индекс изван опсега. Вода са ливаде може да
 * испари. Текстуални приказ ливаде садржи текстуалне приказе
 * садржаних бусена, једна врста по реду.
 */
public class Livada {
    private final Busen[][] matrica_;

    public Livada(int visina, int sirina, Busen busen) {
        matrica_ = new Busen[visina][sirina];
        for (Busen[] red : matrica_) for (int i = 0; i < red.length; i++) red[i] = busen.clone();
    }

    public int sirina() {
        if (matrica_.length > 0) return matrica_[0].length;
        else return 0;
    }

    public int visina() {
        return matrica_.length;
    }

    public synchronized void padni(int sirina, int visina, Kap kap) throws PogresniIndeksi {
        if (sirina >= sirina() || visina >= visina()) throw new PogresniIndeksi();
        matrica_[visina][sirina].padni(kap);
    }

    public synchronized void ispari() {
        for (Busen[] red : matrica_) for (Busen b : red) b.ispari();
    }

    @Override
    public synchronized String toString() {
        StringBuilder povratna = new StringBuilder();
        for (Busen[] red : matrica_) {
            for (Busen b : red) povratna.append(b).append(' ');
            povratna.append('\n');
        }
        return povratna.toString();
    }
}
