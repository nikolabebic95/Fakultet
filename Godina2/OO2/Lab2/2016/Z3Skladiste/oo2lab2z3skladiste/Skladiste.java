/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z3skladiste;

/**
 *
 * @author Nikola
 *
 * Складиште има назив и адресу и садржи низ записа о артиклима. Ствара се пра-
 * зно, почетног капацитета од 5 записа, после чега се записи додају један по
 * један. Грешка је ако већ постоји запис за исти артикал. Може да се дохвати
 * запис за артикал задат по називу (грешка је ако такав запис не постоји) и да
 * се израчуна укупна вредност артикала у складишту.
 */
public class Skladiste implements Vrednosno {

    private final static int pocetniKapacitet_ = 5;

    private String naziv_;
    private String adresa_;
    private Niz niz_ = new Niz(pocetniKapacitet_);

    public Skladiste(String naziv, String adresa) {
        naziv_ = naziv;
        adresa_ = adresa;
    }

    public Skladiste dodaj(Zapis zapis) throws ZapisVecPostoji {
        for (int i = 0; i < niz_.brojElemenata(); i++) {
            try {
                if (zapis.artikal().equals(niz_.naMestu(i).artikal())) {
                    throw new ZapisVecPostoji(niz_.naMestu(i));
                }
            } catch (IndeksVanOpsega e) {
                // Nece se nikad desiti
            }
        }
        niz_.dodaj(zapis);
        return this;
    }

    public Zapis uzmi(String naziv) throws ZapisNePostoji {
        boolean nasao = false;
        int indeks = 0;
        for (int i=0;i<niz_.brojElemenata();i++) {
            try {
                if (niz_.naMestu(i).artikal().naziv().equals(naziv)) {
                    indeks = i;
                    nasao = true;
                    break;
                }
            } catch (IndeksVanOpsega e) {
                // Nece se nikad desiti
            }
        }
        if (!nasao) throw new ZapisNePostoji(naziv);
        try {
            return niz_.naMestu(indeks);
        }
        catch (IndeksVanOpsega e){
            // Nece se nikad desiti
            return null;
        }
    }
    
    @Override
    public double vrednost() {
        double povratna = 0;
        for (int i = 0; i<niz_.brojElemenata();i++) {
            try {
                povratna+=niz_.naMestu(i).vrednost();
            }
            catch (IndeksVanOpsega e) {
                // Nece se nikad desiti
            }
        }
        return povratna;
    }
}
