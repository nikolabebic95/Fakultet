package vozila;

/**
 * Greska za negativan broj traka pri stvaranju saobracajnice
 */
public class NegativanBroj extends Exception {
    private int broj_;

    public NegativanBroj(int broj) {
        broj_ = broj;
    }

    @Override
    public String toString() {
        return "Broj " + broj_ + " je negativan";
    }
}
