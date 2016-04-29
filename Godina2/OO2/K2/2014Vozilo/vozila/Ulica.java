package vozila;

/**
 * Улица је саобраћајница са неколико трака чија је активност додавање возила у случајно изабрану
 * траку. Може да се дохвати снимак возила које се том приликом узима из случајно одабране
 * траке улице, при чему се узето возило одбацује.
 */
public class Ulica extends Saobracajnica {
    public Ulica(int kapacitet, double donja, double gornja) throws NegativanBroj {
        super(kapacitet, donja, gornja);
    }

    @Override
    protected void aktivnost() {
        niz_[(int) (Math.random() * niz_.length)].dodaj(new Vozilo());
    }

    public String snimak() {
        int indeksTrake = (int) (Math.random() * niz_.length);
        niz_[indeksTrake].uzmi();
        return niz_[indeksTrake].snimak();
    }
}
