package vozila;

/**
 * Раскрсница је саобраћајница која има задату улицу, нема ни једну траку и чија се активност састоји
 * од дохватања снимка возила (које је управо напустило задату улицу) уз исписивање снимка,
 * ако снимак постоји.
 */
public class Raskrsnica extends Saobracajnica {
    private Ulica ulica_;

    public Raskrsnica(double donja, double gornja, Ulica ulica) throws NegativanBroj {
        super(0, donja, gornja);
        ulica_ = ulica;
    }

    @Override
    protected void aktivnost() {
        String ispis = ulica_.snimak();
        if (!ispis.equals("")) System.out.println(ispis);
    }
}
