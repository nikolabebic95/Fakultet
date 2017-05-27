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
     * Активна пумпа се ствара за задату бензинску станицу. Пумпи може да се
     * придружи задати приказивач у произвољном тренутку. Пумпа циклички дохвата
     * по један аутомобил из реда своје станице и сипа му потребну количину
     * горива до пуног резервоара, брзином од 1 l на сваких 100 ms. Завршетак
     * сипања дојави бензинској станици. Стање аутомобила приказује на
     * придруженом приказивачу после сваке промене количине горива.
     */
    public class Pumpa implements Runnable {

        private static final double KVANT_GORIVA = 1;
        private static final long VREME_SPAVANJA_U_MILISEKUNDAMA = 100;
        private Automobil automobil_ = null;
        private Prikazivac prikazivac_;
        private final Thread nit_ = new Thread(this);
        private final Stanica stanica_;
        private boolean otvorena_ = false;
        
        public Pumpa(Stanica stanica) {
            stanica_ = stanica;
        }
        
        public void start() {
            nit_.start();
        }

        public void interrupt() {
            nit_.interrupt();
        }

        public void pridruzi(Prikazivac prikazivac) {
            prikazivac_ = prikazivac;
        }
        
        public void zatvori() {
            otvorena_ = false;
        }
        
        public synchronized void otvori() {
            otvorena_ = true;
            notify();
        }
        
        @Override
        public void run() {
            try {
                while (!Thread.interrupted()) {
                    synchronized (this) {
                        while (!otvorena_) {
                            wait();
                        }
                    }
                    automobil_ = stanica_.uzmi();
                    try {
                        while (true) {
                            automobil_.sipaj(KVANT_GORIVA);
                            if (prikazivac_ != null) {
                                prikazivac_.prikazi(automobil_);
                            }
                            TimeUnit.MILLISECONDS.sleep(VREME_SPAVANJA_U_MILISEKUNDAMA);
                        }
                    } catch (PrepunjenRezervoar pr) {
                    }
                }
            } catch (InterruptedException e) {
            }

        }
    }
