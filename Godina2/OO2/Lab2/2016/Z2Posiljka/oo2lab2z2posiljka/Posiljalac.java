/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z2posiljka;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 *
 * Активан пошиљалац сваке секунде генерише пошиљку случајне врсте и смешта је у
 * задати приоритетни ред. У 20% случајева пошиљка је писмо случајне тежине од
 * 20 g до 550 g. У осталим случајевима пошиљка је пакет случајне тежине од 1 kg
 * до 55 kg и случајног приоритета од ниског до највишег.
 */
public class Posiljalac implements Runnable {

    private PrioritetniRed red_;
    private static final double donjaGranicaPisma_ = 20;
    private static final double gornjaGranicaPisma_ = 550;
    private static final double donjaGranicaPaketa_ = 1000;
    private static final double gornjaGranicaPaketa_ = 55000;

    public Posiljalac(PrioritetniRed red) {
        red_ = red;
    }

    @Override
    public void run() {
        try {
            while (!Thread.interrupted()) {
                double slucajanBroj = Math.random();
                if (slucajanBroj < 0.2) {
                    double tezina = Math.random() * (gornjaGranicaPisma_ - donjaGranicaPisma_) + donjaGranicaPisma_;
                    try {
                        red_.dodaj(new Pismo(tezina));
                    } catch (PrevelikaTezina e) {
                    }
                } else {
                    double tezina = Math.random() * (gornjaGranicaPaketa_ - donjaGranicaPaketa_) + donjaGranicaPaketa_;
                    PrioritetnaStvar.Prioritet prioritet = PrioritetnaStvar.Prioritet.nasumicni();
                    try {
                        red_.dodaj(new Paket(prioritet, tezina));
                    } catch (PrevelikaTezina e) {
                    }
                }
                TimeUnit.SECONDS.sleep(1);
            }
        } catch (InterruptedException e) {
        }
    }
}
