import pozoriste.*;

/**
 * (10 поена) Написати на језику Java програм који направи једно позориште и репертоар за њега,
 * на позоришни репертоар дода представу са једним костимографом и једним глумцем и предста-
 * ву са једним костимографом и три глумца, и испише позоришни репертоар. Користити кон-
 * стантне параметре (не треба ништа учитавати).
 */
public class Glavni {
    public static void main(String[] args) {
        Pozoriste p = new Pozoriste("Pozoristance Puz");
        Repertoar r = new Repertoar(p);
        Reditelj r1 = new Reditelj("Pera Peric", p);
        Predstava p1 = new Predstava("Brankov urnebes", p, r1);
        Kostimograf k1 = new Kostimograf("Mika Mikic", p);
        Glumac g1 = new Glumac("Branko Kockica", p);
        p1.dodaj(k1);
        p1.dodaj(g1);
        r.dodaj(p1);
        Reditelj r2 = new Reditelj("Zika Zikic", p);
        Predstava p2 = new Predstava("Robin Hud", p, r2);
        Kostimograf k2 = new Kostimograf("Marko Markovic", p);
        Glumac g2 = new Glumac("Sergej Trifunovic", p);
        Glumac g3 = new Glumac("Petar Strugar", p);
        Glumac g4 = new Glumac("Andrija Milosevic", p);
        p2.dodaj(k2);
        p2.dodaj(g2);
        p2.dodaj(g3);
        p2.dodaj(g4);
        r.dodaj(p2);
        System.out.println(r);
    }
}
