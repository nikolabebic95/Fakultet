package proizvodnja;

/**
 * Фибоначијев генератор је генератор низа целих бројева, који генерише бројеве
 * Фибоначијевог низа (почев од вредности 1). Почетне клице су {0, 1}. Нова вредност
 * Фибоначијевог низа се добија сабирањем клица (klice[0] + klice[1]). Приликом сваког
 * генерисања потребно је ажурирати низ клица тако да вредности у новом низу клица буду
 * буду {klice[1], nova_generisana_vrednost}.
 */
public class Fibonacijev extends Generator {

    public Fibonacijev() {
        super(new int[]{0, 1});
    }

    @Override
    public int proizvedi() {
        int povratna = niz_klica_[0] + niz_klica_[1];
        niz_klica_[0] = niz_klica_[1];
        niz_klica_[1] = povratna;
        return povratna;
    }
}
