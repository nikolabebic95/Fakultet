/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z1izvod;

/**
 *
 * @author Nikola
 *
 * Бинарни израз је израз који садржи два израза (a и b). При рачунању вредности
 * израза вредности операнада се израчунавају конкурентно. Текстуални опис је
 * облика (a#b), где је # симбол реализоване операције.
 *
 */
public abstract class Binarni implements Izraz {

    private final Izraz levi_;
    private final Izraz desni_;
    protected double desnaVrednost_;
    protected double levaVrednost_;
    private boolean desniDelioNulom_ = false;

    protected Izraz levi() {
        return levi_;
    }

    protected Izraz desni() {
        return desni_;
    }

    public Binarni(Izraz levi, Izraz desni) {
        levi_ = levi;
        desni_ = desni;
    }

    public abstract double operacija() throws DeljenjeNulom;

    public abstract char znak();

    @Override
    public double vrednost() throws DeljenjeNulom {
        Thread desnaNit = new Thread(() -> {
            try {
                desnaVrednost_ = desni_.vrednost();
            } catch (DeljenjeNulom d) {
                desniDelioNulom_ = true;
            }
        });
        if (desniDelioNulom_) throw new DeljenjeNulom();
        desnaNit.start();
        levaVrednost_ = levi_.vrednost();
        try {
            desnaNit.join();
        } catch (InterruptedException e) {
            return Double.NaN;
        }
        return operacija();
    }

    @Override
    public String toString() {
        return "(" + levi_ + znak() + desni_ + ")";
    }

}
