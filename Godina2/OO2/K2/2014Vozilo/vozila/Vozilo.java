package vozila;

/**
 * Регистровано возило има аутоматски генерисану регистарску ознаку која може да се дохвати.
 * Регистарска ознака садржи једно од "BG", "NS" и "NI" иза чега стоји случајан троцифрен
 * број.
 */
public class Vozilo implements Registrovano {
    private static final int brojOznaka_ = 3;
    private static String[] oznake_ = new String[brojOznaka_];

    static {
        oznake_[0] = "BG";
        oznake_[1] = "NS";
        oznake_[2] = "NI";
    }

    private String registracija_ = oznake_[(int) (Math.random() * brojOznaka_)] + (int)(Math.random()*10) + (int)(Math.random()*10) + (int)(Math.random()*10);

    @Override
    public String oznaka() {
        return registracija_;
    }
}
