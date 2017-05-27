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
 * Линија је актер који поруке из предајног бафера преноси у пријемни бафер.
 * Пренос сваке поруке траје 240 ms. Управо пренета порука се приказује на
 * придруженом приказивачу.
 */
public class Linija extends Akter {

    private final Bafer predajni_;
    private final Bafer prijemni_;

    private final static long VREME_SPAVANJA_U_MILISEKUNDAMA = 240;

    public Linija(Bafer predajni, Bafer prijemni) {
        predajni_ = predajni;
        prijemni_ = prijemni;
    }

    @Override
    public String nazivVrste() {
        return "Linija";
    }

    @Override
    public String izvrsiNekuApstraktnuAkciju() {
        String poruka = predajni_.uzmi();
        prijemni_.dodaj(poruka);
        try {
            TimeUnit.MILLISECONDS.sleep(VREME_SPAVANJA_U_MILISEKUNDAMA);
        } catch (InterruptedException e) {
        }
        return poruka;
    }

}
