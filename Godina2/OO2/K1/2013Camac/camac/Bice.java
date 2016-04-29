package camac;

/**
 * (20 поена) Бићу могу да се дохвате једнословнa ознакa припадности царству (B – биљном или Z – животињском),
 * ниска назива врсте, као и једнословна ознака царства чијим се јединкама храни (N – за бића која се не хране
 * ни биљном ни животињском храном). Може да се провери да ли биће једе задато биће и да се састави текстуални
 * опис који у угластим заградама садржи ознаку царства којем припада, назив врсте и ознаку царства чијим се
 * јединкама храни, раздвојене двотачком.
 */
public abstract class Bice {
    public static final char ZIVOTINJA = 'Z';
    public static final char BILJKA = 'B';
    public static final char NISTA = 'N';

    abstract public char oznakaCarstva();

    abstract public String nazivVrste();

    abstract public char oznakaHrane();

    public boolean daLiJede(Bice hrana) {
        return oznakaHrane() == hrana.oznakaCarstva();
    }

    @Override
    public String toString() {
        return oznakaCarstva() + ":" + nazivVrste() + ":" + oznakaHrane();
    }
}
