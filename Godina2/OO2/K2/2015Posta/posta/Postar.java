package posta;

/**
 * Поштар је особа која има листу сандучића у које доставља пошиљке. Ствара се са празном
 * листом сандучића, после чега се сандучићи могу додавати појединачно. У сандучету
 * придруженом поштару налазе се пошиљке које поштар разноси. Радња поштара је достава
 * пошиљки на неку адресу. Адреса доставе је адреса прве пошиљке из придруженог сандучета,
 * а достављају се (у оквиру исте радње) све пошиљке са том адресом слања.
 */
public class Postar extends Osoba {
    private static class Element {
        private Sanduce info_;
        private Element sled_;
    }

    private Element prvi_;
    private Element posl_;

    public Postar(String ime, int donjaGranica, int gornjaGranica, Sanduce sanduce) throws PogresnoVreme {
        super(ime, donjaGranica, gornjaGranica, sanduce);
    }

    public synchronized void dodaj(Sanduce sanduce) {
        Element novi = new Element();
        novi.info_ = sanduce;
        novi.sled_ = null;
        if (prvi_ == null) prvi_ = novi;
        else posl_.sled_ = novi;
        posl_ = novi;
    }

    private synchronized Element pretrazi(String adresa) {
        for (Element tek = prvi_; tek != null; tek = tek.sled_) if (tek.info_.adresa().equals(adresa)) return tek;
        return null;
    }

    @Override
    protected void apstraktnaRadnja() throws InterruptedException {
        Posiljka p = sanduce().uzmi();
        String s = p.adresa();
        Element e = pretrazi(s);
        if (e==null) sanduce().stavi(p);
        else {
            while (p!=null) {
                e.info_.stavi(p);
                p = sanduce().uzmi(s);
            }
        }
    }

}
