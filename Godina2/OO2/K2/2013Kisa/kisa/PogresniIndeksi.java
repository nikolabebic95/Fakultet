package kisa;

/**
 * Treba za Livadu
 */
public class PogresniIndeksi extends Exception {
    @Override
    public String toString() {
        // Mogao bi da kaze i koji opseg i sve al me mrzi
        return "Indeks van opsega";
    }
}
