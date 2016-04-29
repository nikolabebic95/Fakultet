package camac;

/**
 * (35 поена) Дружина садржи највише три бића и то различите врсте. Ако су само два бића у дружини,
 * она узајамно не смеју бити храна једно другом. Такво ограничење не важи ако су у дружини сва три бића.
 * Бића се додају дружини појединачно (резултат је статус успеха) и из дружине се узимају бића појединачно
 * задавањем врсте бића. Могуће је и заменити једно биће у дружини (једно узети, а друго додати),
 * при чему се замена врши само ако дружина није попуњена. Приликом покушаја додавања и узимања бића
 * у дружини врши се провера дозвољеног састава дружине (провера носи 10 од 35 поена).
 * Може да се састави текстуални опис дружине наводећи у витичастим заградама садржана бића раздвојена зарезом.
 */
public class Druzina {
    private static final int KAPACITET = 3;
    private Bice[] niz_ = new Bice[KAPACITET]; // Svi ce da budu null na pocetku, ne mora eksplicitno da se popunjava

    public boolean dodaj(Bice bice) {
        int mesto = -1;
        for (int i = 0; i < KAPACITET; i++) {
            if (niz_[i] == null) {
                mesto = i;
                break;
            }
        }
        if (mesto == -1) return false;
        int brojClanova = 0;
        int mestoClana = 0; // Kompajler se buni ako ne inicijalizujem
        for (int i = 0; i < KAPACITET; i++) {
            if (niz_[i] != null) {
                brojClanova++;
                mestoClana = i;
                if (niz_[i].nazivVrste().equals(bice.nazivVrste())) return false;
            }
        }
        if ((brojClanova == 1) && ((niz_[mestoClana].oznakaCarstva() == (bice.oznakaHrane())) || (niz_[mestoClana].oznakaHrane() == bice.oznakaCarstva())))
            return false;
        niz_[mesto] = bice;
        return true;
    }

    public Bice uzmi(String vrsta) {
        int mesto = -1;
        int brojClanova = 0;
        for (int i = 0; i < KAPACITET; i++) {
            if (niz_[i] != null && niz_[i].nazivVrste().equals(vrsta)) {
                mesto = i;
                brojClanova++;
            }
        }
        if (mesto == -1) return null;
        if (brojClanova < KAPACITET) {
            Bice povratna = niz_[mesto];
            niz_[mesto] = null;
            return povratna;
        }
        int druga = -1;
        int treca = -1;
        for (int i = 0; i < KAPACITET; i++) {
            if (i == mesto) continue;
            if (druga == -1) druga = i;
            else treca = i;
        } // Hardkodovano da bude glupo al mrzi me stvarno da pravim opsti slucaj kad kaze da ima 3 zivotinje
        if ((niz_[druga].oznakaCarstva() == niz_[treca].oznakaHrane()) || (niz_[druga].oznakaHrane() == niz_[treca].oznakaCarstva()))
            return null;
        Bice povratna = niz_[mesto];
        niz_[mesto] = null;
        return povratna;
    }

    public Bice zameni(String vrstaUzetog, Bice stavljeno) {
        boolean moze = false;
        for (int i = 0; i < KAPACITET; i++) {
            if (niz_[i] == null) {
                moze = true;
                break;
            }
        }
        Bice povratna;
        if (moze) {
            povratna = uzmi(vrstaUzetog);
            boolean stavljanje = dodaj(stavljeno);
            if (!stavljanje) {
                dodaj(povratna);
                return null;
            }
            return povratna;
        }
        return null;
    }

    @Override
    public String toString() {
        boolean prvi = true;
        String povratna = "{";
        for (int i = 0; i < KAPACITET; i++) {
            if (niz_[i] != null) {
                if (!prvi) povratna += ",";
                prvi = false;
                povratna += "[" + niz_[i] + "]";
            }
        }
        povratna+="}";
        return povratna;
    }
}
