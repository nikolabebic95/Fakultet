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
 * Млеко и шећер су артикли који се мере у литрима, односно у килограмима
 */
public class Mleko extends Artikal {

    public Mleko() throws PogresnaOznaka {
        super("Mleko", new Jedinica("l"));
    }
}
