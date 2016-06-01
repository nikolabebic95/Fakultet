package proizvodnja;

/**
 * Троугаони генератор је генератор низа целих бројева, који генерише бројеве Троугаоног
 * низа. Почетне клице су {0, 1, 1}. Нова вредност Троугаоног низа се добија сабирањем klice[0]
 * + klice[1]. Приликом сваког генерисања потребно је ажурирати низ клица тако да вредности у
 * новом низу клица буду {nova_generisana_vrednost, klice[1] + klice[2], klice[2]}.
 */
public class Trougaoni extends Generator {

    public Trougaoni() {
        super(new int[]{0, 1, 1});
    }

    @Override
    public int proizvedi() {
        int povratna = niz_klica_[0] + niz_klica_[1];
        niz_klica_[0] = povratna;
        niz_klica_[1] += niz_klica_[2];
        return povratna;
    }
}
