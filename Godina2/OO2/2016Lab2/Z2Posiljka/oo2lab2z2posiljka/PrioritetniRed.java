/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z2posiljka;

/**
 *
 * @author Nikola
 *
 * Приоритетни ред приоритетних пошиљки се ствара празан, задатог капацитета,
 * после чега се пошиљке додају и узимају једна по једна по нерастућем
 * приоритету. Може да се дохвати број пошиљки у реду, да се одреди укупна
 * тежина свих пошиљки у реду и да се састави текстуални опис реда који садржи
 * текстуалне описе садржаних пошиљки, једна пошиљка по реду. Ако се ред препуни
 * или ако се покуша извадити из празног реда нит извршиоца операције се
 * привремено блокира.
 */
public class PrioritetniRed {

    private int brojClanova_ = 0;
    private PrioritetnaPosiljka[] niz_;

    public PrioritetniRed(int kapacitet) {
        niz_ = new PrioritetnaPosiljka[kapacitet];
    }

    public synchronized PrioritetniRed dodaj(PrioritetnaPosiljka p) throws InterruptedException {
        while (brojClanova_ == niz_.length) {
            wait();
        }
        niz_[brojClanova_++] = p;
        if (brojClanova_ == 1) {
            notifyAll();
        }
        return this;
    }

    private int indeksMaksimuma() {
        int indeks = 0;
        for (int i = 1; i < brojClanova_; i++) {
            if (niz_[i].prioritet().vrednost() > niz_[indeks].prioritet().vrednost()) {
                indeks = i;
            }
        }
        return indeks;
    }

    public synchronized PrioritetnaPosiljka uzmi() throws InterruptedException {
        while (brojClanova_ == 0) {
            wait();
        }
        int indeks = indeksMaksimuma();
        PrioritetnaPosiljka povratna = niz_[indeks];
        for (int i = indeks; i < brojClanova_ - 1; i++) {
            niz_[i] = niz_[i + 1];
        }
        niz_[--brojClanova_] = null;
        if (brojClanova_ == niz_.length - 1) {
            notifyAll();
        }
        return povratna;
    }

    public double ukupnaTezina() {
        double tezina = 0;
        for (int i = 0; i < brojClanova_; i++) {
            tezina += niz_[i].tezina();
        }
        return tezina;
    }

    @Override
    public String toString() {
        StringBuilder povratna = new StringBuilder();
        for (int i = 0; i < brojClanova_; i++) {
            povratna.append(niz_[i].toString());
            povratna.append("\n");
        }
        return povratna.toString();
    }
}
