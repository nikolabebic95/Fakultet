import posta.*;

import java.util.concurrent.TimeUnit;

/**
 * (10 поена) Написати на језику Java програм који направи једног поштара са придруженим
 * сандучетом са неколико пошиљки, испише поштара, потом направи примаоца у чије
 * придружено сандуче направљени поштар доставља пошиљке, после неког времена заустави
 * поштара и примаоца и испише их. При писању програма користити константне параметре (не
 * треба ништа учитавати).
 */
public class Glavni {
    public static void main(String[] args) {
        try {
            Sanduce postarovo = new Sanduce("Posta", 10);
            Posiljka p1 = new Posiljka("Kuca");
            Posiljka p2 = new Posiljka("Faks");
            Posiljka p3 = new Posiljka("Faks");
            postarovo.stavi(p1);
            postarovo.stavi(p2);
            postarovo.stavi(p3);
            Postar postar = new Postar("Pera Peric", 100, 1000, postarovo);
            System.out.println(postar);
            Sanduce primaocevo = new Sanduce("Faks", 5);
            Primalac primalac = new Primalac("Mika Mikic", 100, 1000, primaocevo);
            postar.dodaj(primaocevo);
            Thread po = new Thread(postar);
            Thread pr = new Thread(primalac);
            po.start();
            pr.start();
            TimeUnit.SECONDS.sleep(1);
            po.interrupt();
            pr.interrupt();
            System.out.println(postar);
            System.out.println(primalac);
        }
        catch (Exception e) {
            System.out.println(e);
        }
    }
}
