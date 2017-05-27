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
 * Низ записа може да садржи задат број записа. Ствара се празан, задатог
 * капацитета, после чега се записи могу додавати један по један (капацитет низа
 * се по потреби аутоматски повећава за 10%, али најмање за 5 места). Може да се
 * дохвати број елемената у низу, да се дохвати елемент са задатим редним бројем
 * (грешка је ако је индекс изван опсега) и да се састави текстуални опис
 * садржаја низа, по један елемент у сваком реду, при чему се текстуални описи
 * елемената састављају конкурентно.
 */
public class Niz {

    private Zapis[] niz_;
    private int brojClanova_ = 0;

    public Niz(int kapacitet) {
        niz_ = new Zapis[kapacitet];
    }

    private void realociraj() {
        int velicina = niz_.length / 10; // Zaokruzujem 10% na nize
        if (velicina < 5) {
            velicina = 5;
        }
        velicina += niz_.length;
        Zapis[] noviNiz = new Zapis[velicina];
        for (int i = 0; i < niz_.length; i++) {
            noviNiz[i] = niz_[i];
        }
        niz_ = noviNiz;
    }

    public Niz dodaj(Zapis z) {
        if (brojClanova_ == niz_.length) {
            realociraj();
        }
        niz_[brojClanova_++] = z;
        return this;
    }

    public int brojElemenata() {
        return brojClanova_;
    }

    public Zapis naMestu(int i) throws IndeksVanOpsega {
        if (i < 0 && i >= brojClanova_) {
            throw new IndeksVanOpsega(i, 0, brojClanova_);
        }
        return niz_[i];
    }

    private static class Nit extends Thread {

        private String opis_;
        private Zapis zapis_;

        public Nit(Zapis zapis) {
            zapis_ = zapis;
        }

        @Override
        public void run() {
            opis_ = zapis_.toString();
        }
    }

    @Override
    public String toString() {
        Nit niti[] = new Nit[niz_.length];
        for (int i = 0; i < niz_.length; i++) {
            niti[i] = new Nit(niz_[i]);
        }
        for (Nit n : niti) {
            n.start();
        }
        for (Nit n : niti) {
            try {
                n.join();
            } catch (InterruptedException e) {
                n.opis_ = "";
            }
        }
        StringBuilder povratna = new StringBuilder();
        for (Nit n : niti) {
            povratna.append(n.opis_);
            povratna.append("\n");
        }
        return povratna.toString();
    }

}
