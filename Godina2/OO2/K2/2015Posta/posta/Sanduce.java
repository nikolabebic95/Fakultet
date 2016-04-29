package posta;

/**
 * Поштанско сандуче има адресу и садржи низ пошиљки задатог капацитета. Ствара се празно,
 * после чега се пошиљке могу додавати појединачно. Може да се из сандучета извади прва
 * пошиљка и да се извади пошиљка са задатом адресом примаоца (у случају да постоји више
 * пошиљки које се шаљу на исту адресу, из сандучета се вади прва која се пронађе; при вађењу
 * неке пошиљке, наредне се померају). При покушају узимања пошиљке из празног сандучета
 * или покушаја додавања пошиљке у пуно сандуче, нит извршиоца радње се привремено
 * блокира. Може да се дохвати адреса сандучета. Може да се састави текстуални опис
 * сандучета наводећи пошиљке које се у њему налазе (сваку пошиљку у засебном реду).
 */
public class Sanduce {
    private String adresa_;
    private Posiljka[] niz_;
    private int brojPopunjenih_ = 0;

    public Sanduce(String adresa, int kapacitet) {
        adresa_ = adresa;
        niz_ = new Posiljka[kapacitet];
    }

    public synchronized void stavi(Posiljka p) throws InterruptedException {
        while (brojPopunjenih_==niz_.length) wait();
        niz_[brojPopunjenih_++] = p;
        notifyAll();
    }

    public synchronized Posiljka uzmi() throws InterruptedException {
        while (brojPopunjenih_==0) wait();
        Posiljka p = niz_[0];
        brojPopunjenih_--;
        System.arraycopy(niz_, 1, niz_, 0, brojPopunjenih_);
        niz_[brojPopunjenih_+1] = null;
        notifyAll();
        return p;
    }

    public synchronized Posiljka uzmi(String adresa) throws InterruptedException {
        while (brojPopunjenih_==0) wait();
        for (int i=0;i<brojPopunjenih_;i++) {
            if (niz_[i].adresa().equals(adresa)) {
                Posiljka p = niz_[i];
                brojPopunjenih_--;
                System.arraycopy(niz_, i+1, niz_, i, brojPopunjenih_-i);
                niz_[brojPopunjenih_+1] = null;
                notifyAll();
                return p;
            }
        }
        return null;
    }

    public String adresa() {
        return adresa_;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i=0;i<brojPopunjenih_;i++) {
            sb.append(niz_[i].toString());
            sb.append('\n');
        }
        return sb.toString();
    }

}
