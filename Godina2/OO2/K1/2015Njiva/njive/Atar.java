package njive;

/**
 * (30 поена) Атар је парцела која садржи произвољан број других парцела. Ствара се празан
 * или са задатим низом парцела, након чега му се парцеле могу додавати појединачно. Ознака
 * врсте је А. Текстуални опис садржи опис самог атара као парцеле, а затим описе садржаних
 * парцела у одговарајућем броју редова.
 */
public class Atar extends Parcela {
    private static class Element {
        private Parcela info_;
        private Element sled_;

        public Element(Parcela info) {
            info_ = info;
            sled_ = null;
        }
    }

    private Element prvi_;
    private Element posl_;

    public Atar(double povrsina) {
        super(povrsina);
        prvi_ = null;
        posl_ = null;
    }

    public Atar(double povrsina, Parcela[] niz) {
        super(povrsina);
        prvi_ = null;
        for (Parcela p : niz) {
            Element novi = new Element(p);
            if (prvi_ == null) prvi_ = novi;
            else posl_.sled_ = novi;
            posl_ = novi;
        }
    }

    public void dodaj(Parcela info) {
        Element novi = new Element(info);
        if (prvi_ == null) prvi_ = novi;
        else posl_.sled_ = novi;
        posl_ = novi;
    }

    @Override
    public char vrsta() {
        return 'A';
    }

    @Override
    public double prinos(int godine) {
        double povratna = 0;
        Element tek = prvi_;
        while (tek != null) {
            Parcela p = tek.info_;
            povratna += p.prinos(godine);
            tek = tek.sled_;
        }
        return povratna;
    }

    @Override
    public String toString() {
        String povratna = super.toString() + "\n";
        Element tek = prvi_;
        while (tek != null) {
            Parcela p = tek.info_;
            povratna += p.toString() + "\n";
            tek = tek.sled_;
        }
        return povratna;
    }
}
