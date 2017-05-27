/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z3prenos;

/**
 *
 * @author Nikola
 *
 * Бафер може да садржи призвољан број једноредних порука типа String. Ствара се
 * празан после чега могу да се додају поруке једна по једна, да се поруке
 * узимају једна по једна (по редоследу додавања) и да се састави текстуални
 * опис садржаја бафера. Ако при узимању у баферу нема поруке, нит читаоца се
 * привремено зауставља. Текстуални опис бафера садржи све тренутне поруке, по
 * једну поруку у сваком реду. После сваке промене садржаја бафера исти се
 * приказује на вишередном приказивачу који се задаје приликом стварања бафера.
 */
public class Bafer {

    private static class Element {

        String poruka_;
        Element sled_;

        Element(String poruka) {
            poruka_ = poruka;
        }
    }

    private Element prvi_;
    private Element posl_;

    private final Prikazivac viseredniPrikazivac_;

    public Bafer(Prikazivac viseredniPrikazivac) {
        viseredniPrikazivac_ = viseredniPrikazivac;
    }

    public synchronized Bafer dodaj(String poruka) {
        Element novi = new Element(poruka);
        if (prvi_ == null) {
            notify();
            prvi_ = novi;
        } else {
            posl_.sled_ = novi;
        }
        posl_ = novi;
        viseredniPrikazivac_.prikazi(toString());
        return this;
    }

    public synchronized String uzmi() {
        try {
            if (prvi_ == null) {
                wait();
            }
        } catch (InterruptedException e) {
        }
        String ret = prvi_.poruka_;
        prvi_ = prvi_.sled_;
        if (prvi_ == null) {
            posl_ = null;
        }
        viseredniPrikazivac_.prikazi(toString());
        return ret;
    }

    @Override
    public synchronized String toString() {
        StringBuilder ret = new StringBuilder();
        Element tek = prvi_;
        while (tek != null) {
            ret.append(tek.poruka_).append("\n");
            tek = tek.sled_;
        }
        return ret.toString();
    }

}
