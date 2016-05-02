import kisa.*;

import java.util.concurrent.TimeUnit;

/**
 * (10 поена) Написати на језику Java програм који направи једну
 * ливаду величине 4×5 бусена и један облак, покрене падање кише,
 * после 5 s испише ливаду на главном излазу, после још 3 s заустави
 * кишу, испише ливаду, испари воду са ливаде, испише ливаду и још
 * једном заустави кишу. Користити константне параметре (не треба
 * ништа учитавати с главног улаза).
 */
final public class Glavni {
    private Glavni() {
    }

    public static void main(String[] args) {
        Livada livada = new Livada(4, 5, new Busen());
        Oblak oblak = new Oblak(livada);
        oblak.start();
        try {
            oblak.pocni();
            TimeUnit.SECONDS.sleep(5);
            System.out.println(livada);
            TimeUnit.SECONDS.sleep(3);
            oblak.prestani();
            System.out.println(livada);
            livada.ispari();
            System.out.println(livada);
            oblak.prestani();
        } catch (Exception e) {
            System.out.println(e);
        }
        oblak.unisti();
    }
}
