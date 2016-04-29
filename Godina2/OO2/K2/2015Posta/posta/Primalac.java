package posta;

/**
 * Прималац је особа. У сандучету придруженом примаоцу налазе се пошиљке које прималац
 * узима, по редоследу којeм се у сандучету налазе. Радња примаоца је узимање пошиљке из
 * придруженог сандучета.
 */
public class Primalac extends Osoba {
    public Primalac(String ime, int donjaGranica, int gornjaGranica, Sanduce sanduce) throws PogresnoVreme {
        super(ime, donjaGranica, gornjaGranica, sanduce);
    }

    @Override
    protected void apstraktnaRadnja() throws InterruptedException {
        sanduce().uzmi();
    }
}
