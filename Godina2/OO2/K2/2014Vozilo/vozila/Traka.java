package vozila;

/**
 * Саобраћајна трака садржи произвољан број возила у реду и камеру. Може да се дода возило
 * на крај реда и да се узме возило са почетка реда (null ако је ред празан). Приликом узимања
 * возила из траке возило се сними камером траке и снимак се памти до следећег снимања. Ако је
 * ред при покушају узимања возила празан, снимак је празан. Може да се дохвати последњи снимак.
 */
public class Traka {
    private static class Element {
        private Vozilo info_;
        private Element sled_;

        private Element(Vozilo info) {
            info_ = info;
            sled_ = null;
        }
    }

    private Element prvi_ = null;
    private Element posl_ = null;

    private Kamera kamera_ = new Kamera();
    private String snimak_ = "";

    public synchronized Traka dodaj(Vozilo vozilo) {
        Element novi = new Element(vozilo);
        if (prvi_ == null) prvi_ = novi;
        else posl_.sled_ = novi;
        posl_ = novi;
        return this;
    }

    public synchronized Vozilo uzmi() {
        snimak_ = "";
        if (prvi_ == null) return null;
        Vozilo povratna = prvi_.info_;
        prvi_ = prvi_.sled_;
        if (prvi_ == null) posl_ = null;
        kamera_.snimi(povratna);
        snimak_ = kamera_.snimak();
        return povratna;
    }

    public String snimak() {
        return snimak_;
    }

}
