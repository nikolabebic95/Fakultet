/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z4benzinskastanica;

/**
 *
 * @author Nikola
 *
 * Аутомобил има јединствен, аутоматски генерисан целобројан идентификатор,
 * задат капацитет резервоара и тренутну количину горива. Сви подаци могу да се
 * дохвате. Почетна количина горива је случајна вредност између 10% и 30%
 * капацитета резервоара. У аутомобил може да се сипа задата количина горива.
 * Грешка је ако се резервоар препуни (тада се резервоар напуни и пријави
 * грешка).
 */
public class Automobil {
    private static final double DONJI_PROCENAT = 0.1;
    private static final double GORNJI_PROCENAT = 0.3;

    private static int brojac_ = 0;
    private final int id_ = brojac_++;
    private final double rezervoar_;
    private double gorivo_;

    public Automobil(double rezervoar) {
        rezervoar_ = rezervoar;
        double donja = rezervoar * DONJI_PROCENAT;
        double gornja = rezervoar * GORNJI_PROCENAT;
        gorivo_ = Math.random() * (gornja - donja) + donja;
    }

    public Automobil sipaj(double gorivo) throws PrepunjenRezervoar {
        if (gorivo_ + gorivo > rezervoar_) {
            gorivo_ = rezervoar_;
            throw new PrepunjenRezervoar(gorivo_ + gorivo - rezervoar_);
        }
        gorivo_ += gorivo;
        return this;
    }

    public int id() {
        return id_;
    }
    
    public double rezervoar() {
        return rezervoar_;
    }
    
    public double gorivo() {
        return gorivo_;
    }
    
}
