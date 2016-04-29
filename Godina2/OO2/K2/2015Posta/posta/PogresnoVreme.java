package posta;

/**
 * Klasa izuzetka koja se koristi u klasi Osoba
 */
public class PogresnoVreme extends Exception {
    public String toString() {
        return "Pogresan opseg vremena";
    }
}
