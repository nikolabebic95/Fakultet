package pozoriste;

/**
 * (20 поена) Представа је описана називом, позориштем у којем се одржава и садржи произво-
 * љан број запослених који учествују у реализацији представе. У реализацији представе могу
 * учествовати само запослени у позоришту у коме се представа одржава, при чему тачно један
 * редитељ, највише два костимографа и произвољан број глумаца. Представа се ствара са ре-
 * дитељем, након чега се костимографи и глумци додају појединачно. Повратна вредност при
 * додавању запосленог је индикатор успеха. Може да се дохвати назив представе, да се дохва-
 * ти позориште у којем се одржава представа и да се састави текстуални опис представе наво-
 * дећи назив представе и назив позоришта у којем се представа одржава раздвојене зарезом, а
 * потом запослене који учествују у реализацији представе (сваког запосленог у засебном реду).
 */
public class Predstava {
    private static final int BROJ_KOSTIMOGRAFA = 2;

    private static class Element {
        private Glumac info_;
        private Element sled_;

        public Element(Glumac info) {
            info_ = info;
        }
    }

    private String naziv_;
    private Pozoriste pozoriste_;

    private Reditelj reditelj_;
    private Kostimograf[] kostimografi_ = new Kostimograf[BROJ_KOSTIMOGRAFA];
    private Element prvi_;
    private Element posl_;

    public Predstava(String naziv, Pozoriste pozoriste, Reditelj reditelj) {
        naziv_ = naziv;
        pozoriste_ = pozoriste;
        reditelj_ = reditelj;
    }

    public boolean dodaj(Zaposleni zaposleni) {
        if (zaposleni.oznakaPosla() == 'K') {
            for (int i = 0; i < BROJ_KOSTIMOGRAFA; i++) {
                if (kostimografi_[i] == null) {
                    kostimografi_[i] = (Kostimograf) zaposleni; // Ocajan je zadatak
                    return true;
                }
            }
            return false;
        } else if (zaposleni.oznakaPosla() == 'G') {
            Element novi = new Element((Glumac) zaposleni); // I ovde je ocajan zadatak
            if (prvi_ == null) prvi_ = novi;
            else posl_.sled_ = novi;
            posl_ = novi;
            return true;
        } else return false;
    }

    public String naziv() {
        return naziv_;
    }

    public Pozoriste pozoriste() {
        return pozoriste_;
    }

    @Override
    public String toString() {
        String povratna = naziv_ + ", " + pozoriste_.naziv() + "\n" + reditelj_ + "\n";
        for (int i = 0; i < BROJ_KOSTIMOGRAFA; i++) {
            if (kostimografi_[i] == null) break;
            povratna += kostimografi_[i] + "\n";
        }
        Element tek = prvi_;
        while (tek != null) {
            Zaposleni info = tek.info_;
            povratna += info + "\n";
            tek = tek.sled_;
        }
        return povratna;
    }
}
