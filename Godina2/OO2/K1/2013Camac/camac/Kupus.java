package camac;

/**
 * Вук је биће животињског царства (назив врсте Vu) које се храни храном животињског порекла,
 * коза је биће животињског царства (назив врсте Ko) које се храни храном биљног порекла,
 * а купус је (неживо) биће биљног царства (назив врсте Ku) које се (више) не храни.
 */
public class Kupus extends Bice {
    @Override
    public char oznakaCarstva() {
        return BILJKA;
    }

    @Override
    public String nazivVrste() {
        return "Ku";
    }

    @Override
    public char oznakaHrane() {
        return NISTA;
    }
}
