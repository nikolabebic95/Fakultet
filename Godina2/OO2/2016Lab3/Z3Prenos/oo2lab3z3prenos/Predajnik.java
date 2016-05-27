/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z3prenos;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 *
 * Предајник је актер који генерише поруке случајне дужине од 2 до 10 знакова
 * састављене само од великих слова. Генерисање сваког слова траје 40 ms. Поруке
 * ставља у предајни бафер и на придруженом приказивачу приказује управо послату
 * поруку.
 */
public class Predajnik extends Akter {

    private static final int DONJA_GRANICA_DUZINE = 2;
    private static final int GORNJA_GRANICA_DUZINE = 10;

    private static final long VREME_SPAVANJA_U_MILISEKUNDAMA = 40;
    
    private final Bafer bafer_;
    
    public Predajnik(Bafer bafer) {
        bafer_ = bafer;
    }
    
    @Override
    public String nazivVrste() {
        return "Predajnik";
    }

    @Override
    public String izvrsiNekuApstraktnuAkciju() {
        int duzina = (int) (Math.random() * (GORNJA_GRANICA_DUZINE - DONJA_GRANICA_DUZINE + 1) + DONJA_GRANICA_DUZINE);
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < duzina; i++) {
            char slovo = (char) (Math.random() * ('Z' - 'A' + 1) + 'A');
            sb.append(slovo);
            try {
                TimeUnit.MILLISECONDS.sleep(VREME_SPAVANJA_U_MILISEKUNDAMA);
            } catch (InterruptedException e) {
            }
        }
        bafer_.dodaj(sb.toString());
        return sb.toString();
    }

}
