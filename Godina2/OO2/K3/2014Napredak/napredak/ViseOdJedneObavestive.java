package napredak;

/**
 * Greska
 */
public class ViseOdJedneObavestive extends Exception {
    @Override
    public String toString() {
        return "Moze je prijaviti samo jedna obavestiva stvar";
    }
}
