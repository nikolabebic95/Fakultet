/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z4benzinskastanica;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 *
 * Бензинска станица има четири пумпе и ред за чекање за највише 20 аутомобила.
 * Станица може да се отвори и затвори, може да се прекине њен рад, да јој се
 * дода задати аутомобил, да се извади један аутомобил из њеног реда и да јој се
 * дојави завршетак пуњења једног аутомобила. Ако је станица затворена или је
 * ред пун, додавање аутомобила се занемари. Ако је ред празан, при узимању се
 * сачека да се појави неки аутомобил. Приликом затварања, прекида се чекање
 * возила у реду и чека се да се заврши сипање горива које је у току. Приликом
 * прекидања прекида се и рад свих пумпи станице.
 */
public class Stanica {

    protected final static int BROJ_PUMPI = 4;
    protected final static int KAPACITET = 20;

    protected final Pumpa[] pumpe_ = new Pumpa[BROJ_PUMPI];
    protected final Automobil[] red_ = new Automobil[KAPACITET];
    protected int prvi_ = 0;
    protected int posl_ = 0;
    protected int brojClanova_ = 0;
    private boolean otvorena_ = false;

    public Stanica() {
        for (int i = 0; i < BROJ_PUMPI; i++) {
            pumpe_[i] = new Pumpa(this);
        }
        for (int i = 0; i < BROJ_PUMPI; i++) {
            pumpe_[i].start();
        }
    }

    
    public synchronized void otvori() {
        otvorena_ = true;
        for (Pumpa p: pumpe_) {
            p.otvori();
        }
    }

    public synchronized void zatvori() {
        otvorena_ = false;
        for (Pumpa p: pumpe_) {
            p.zatvori();
        }
        for (int i = 0; i < KAPACITET; i++) {
            red_[i] = null;
        }
        prvi_ = 0;
        posl_ = 0;
        brojClanova_ = 0;
    }

    public void prekiniRad() {
        for (Pumpa p : pumpe_) {
            p.interrupt();
        }
        zatvori();
    }

    public synchronized Stanica dodaj(Automobil a) {
        if (!otvorena_ || brojClanova_ == KAPACITET) {
            return this;
        }
        red_[posl_] = a;
        posl_++;
        posl_ %= KAPACITET;
        brojClanova_++;
        notifyAll();
        return this;
    }

    public synchronized Automobil uzmi() throws InterruptedException {
        while (brojClanova_ == 0) {
            wait();
        }
        Automobil povratna = red_[prvi_];
        prvi_++;
        prvi_ %= KAPACITET;
        brojClanova_--;
        return povratna;
    }

   
}
