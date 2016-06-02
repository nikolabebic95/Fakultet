package napredak;

/**
 * Напредак је обавестива ствар која садржи индикатор напретка. Може да се пријави код
 * задатог посла, како би пратила његов напредак. Неуспех
 * пријаве се игнорише. Обавештење о напретку прослеђује
 * садржаном индикатору.
 */
public class Napredak implements Obavestiva {
    private final Indikator indikator_;
    private final Posao posao_;

    public Napredak(Indikator indikator, Posao posao) {
        indikator_ = indikator;
        posao_ = posao;
    }

    public void prijavi() {
        try {
            posao_.prijavi(this);
        } catch (ViseOdJedneObavestive e) {
            // Ignorise se
        }
    }

    @Override
    public void obavesti(int procenat) {
        indikator_.obavesti(procenat);
    }
}
