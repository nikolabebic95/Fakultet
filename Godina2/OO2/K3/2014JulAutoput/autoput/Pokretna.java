package autoput;

/**
 * (20 поена) Покретним стварима може да се саопшти тренутно време у ms.
 */
@FunctionalInterface
public interface Pokretna {
    void saopsti(long trenutno_vreme_u_milisekundama);
}
