package pozoriste;

/**
 * Глумац, редитељ и костимограф су запослени у позоришту (ознака врсте посла је G, R и K,
 * респективно).
 */
public class Kostimograf extends Zaposleni {
    public Kostimograf(String ime, Pozoriste pozoriste) {
        super(ime, pozoriste);
    }

    @Override
    public char oznakaPosla() {
        return 'K';
    }
}
