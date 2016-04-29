package camac;

/**
 * Вук је биће животињског царства (назив врсте Vu) које се храни храном животињског порекла,
 * коза је биће животињског царства (назив врсте Ko) које се храни храном биљног порекла,
 * а купус је (неживо) биће биљног царства (назив врсте Ku) које се (више) не храни.
 */
public class Koza extends Bice {
    @Override
    public char oznakaCarstva() {
        return ZIVOTINJA;
    }

    @Override
    public String nazivVrste() {
        return "Ko";
    }

    @Override
    public char oznakaHrane() {
        return BILJKA;
    }
}
