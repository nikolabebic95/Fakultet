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
 * Апстрактан актер у петљи извршава неку апстрактну акцију. Може да се дохвати
 * назив врсте актера, да се постави једноредни приказивач за приказ стања, да
 * се рад актера започне, привремено заустави, настави даље и заврши
 */
public abstract class Akter implements Runnable {

    private Prikazivac jednoredniPrikazivacZaPrikazStanja_;
    private boolean radi_ = false;
    private final Thread nit_ = new Thread(this);

    // Ovo vraca poruku a to nigde ne pise u ovoj klasi
    // nego mora da se gledaju ove sto je prosiruju pa da se skapira
    public abstract String izvrsiNekuApstraktnuAkciju();

    public abstract String nazivVrste();

    public void postavi(Prikazivac jednoredniPrikazivacZaPrikazStanja) {
        jednoredniPrikazivacZaPrikazStanja_ = jednoredniPrikazivacZaPrikazStanja;
    }

    public void zapocni() {
        nit_.start();
    }

    public synchronized void privremenoZaustavi() {
        radi_ = false;
    }

    public synchronized void nastaviDalje() {
        radi_ = true;
        notify();
    }

    public void zavrsi() {
        nit_.interrupt();
    }

    @Override
    public void run() {
        try {
            while (!Thread.interrupted()) {
                synchronized (this) {
                    while (!radi_) {
                        wait();
                    }
                }
                jednoredniPrikazivacZaPrikazStanja_.prikazi(izvrsiNekuApstraktnuAkciju());
            }
        } catch (InterruptedException e) {
        }
    }
}
