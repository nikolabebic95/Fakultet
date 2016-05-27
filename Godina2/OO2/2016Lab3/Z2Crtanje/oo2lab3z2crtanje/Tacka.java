/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab3z2crtanje;

/**
 *
 * @author Nikola
 *
 * Тачка у равни се задаје реалним координатама које могу да се дохвате.
 */
public class Tacka {

    private final double x_;
    private final double y_;

    public Tacka(double x, double y) {
        x_ = x;
        y_ = y;
    }

    public double x() {
        return x_;
    }

    public double y() {
        return y_;
    }

}
