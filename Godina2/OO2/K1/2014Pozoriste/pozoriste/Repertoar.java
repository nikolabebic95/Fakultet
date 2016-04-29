package pozoriste;

/**
 * (20 поена) Позоришни репертоар садржи позориште којем припада и може садржати про-
 * извољан број представа. Може да се дода представа на репертоар, да се уклони представа
 * задатог назива са репертоара и да се састави текстуални опис репертоара (свака представа у
 * засебном реду).
 */
public class Repertoar {
    private static class Element {
        private Predstava info_;
        private Element sled_;

        public Element(Predstava info) {
            info_ = info;
        }
    }

    private Pozoriste pozoriste_;
    private Element prvi_;
    private Element posl_;

    public Repertoar(Pozoriste pozoriste) {
        pozoriste_ = pozoriste;
    }

    public void dodaj(Predstava predstava) {
        if (predstava.pozoriste() != pozoriste_) return;
        Element tek = prvi_;
        while (tek != null) {
            if (tek.info_.naziv().equals(predstava.naziv())) return;
            tek = tek.sled_;
        }
        Element novi = new Element(predstava);
        if (prvi_ == null) prvi_ = novi;
        else posl_.sled_ = novi;
        posl_ = novi;
    }

    public void ukloni(String naziv) {
        Element tek = prvi_;
        Element pret = null; // Nepotrebna inicijalizacija, ali volim da vidim šta je
        while (tek != null) {
            if (tek.info_.naziv().equals(naziv)) {
                if (pret == null) prvi_ = tek.sled_;
                else pret.sled_ = tek.sled_;
                if (posl_ == tek) posl_ = pret;
                return;
            }
            pret = tek;
            tek = tek.sled_;
        }
    }

    @Override
    public String toString() {
        String povratna = "";
        Element tek = prvi_;
        while (tek != null) {
            povratna += tek.info_ + "\n";
            tek = tek.sled_;
        }
        return povratna;
    }
}
