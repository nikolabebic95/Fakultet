package camac;

/**
 * Чамац може да садржи највише једно биће. Биће се може ставити у чамац и извадити из чамца.
 * Може да се састави текстуални опис у облику C{биће}.
 */
public class Camac {
    private Bice bice_;

    public boolean stavi(Bice bice) {
        if (bice_ != null) return false;
        bice_ = bice;
        return true;
    }

    public Bice uzmi() {
        Bice povratna = bice_;
        bice_ = null;
        return povratna;
    }

    @Override
    public String toString() {
        if (bice_==null) return "C()";
        return "C{"+bice_+"}";
    }
}
