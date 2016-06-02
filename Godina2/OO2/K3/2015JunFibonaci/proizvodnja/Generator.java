package proizvodnja;

/**
 * Генератор низа целих бројева је произвођач који садржи низ целобројних клица који се
 * задаје при стварању.
 */
public abstract class Generator implements Proizvodjac {
    protected int[] niz_klica_;

    protected Generator(int[] niz_klica) {
        niz_klica_ = niz_klica;
    }
}
