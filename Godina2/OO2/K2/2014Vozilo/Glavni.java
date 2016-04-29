import vozila.*;

import java.util.concurrent.TimeUnit;

/**
 * (10 поена) Написати на језику Java програм (класу с главном функцијом) који направи једну улицу
 * и једну раскрсницу, покрене их, после неког врмена их заустави, а затим трајно обустави рад улице
 * и раскрснице. Улица и раскрсница имају: minT=0.1s и maxT=0.3s.
 */
public class Glavni {
    private final static int kapacitet_ = 5;
    private final static double donja_ = 0.1;
    private final static double gornja_ = 0.3;
    private final static int brojSekundi_ = 2;
    public static void main(String[] args) {
        Ulica ulica;
        Raskrsnica raskrsnica;
        try {
            ulica = new Ulica(kapacitet_, donja_, gornja_);
            raskrsnica = new Raskrsnica(donja_, gornja_, ulica);
        } catch (NegativanBroj e) {
            return;
        }
        ulica.start();
        raskrsnica.start();
        ulica.kreni();
        raskrsnica.kreni();
        try {
            TimeUnit.SECONDS.sleep(brojSekundi_);
        } catch (InterruptedException e) {
            // Komentar da se IntelliJ ne buni
        }
        ulica.stani();
        raskrsnica.stani();
        ulica.zaustavi();
        raskrsnica.zaustavi();
    }
}
