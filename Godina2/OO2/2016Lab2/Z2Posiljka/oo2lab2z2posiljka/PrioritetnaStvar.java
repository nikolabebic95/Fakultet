/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package oo2lab2z2posiljka;

/**
 *
 * @author Nikola
 *
 * Приоритетним стварима може да се одреди целобројан приоритет, који може имати
 * следеће вредности: најнижи, низак, нормалан, висок и највиши.
 */
public interface PrioritetnaStvar {

    enum Prioritet {
        najnizi(1), nizak(2), normalan(3), visok(4), najvisi(5);
        int vrednost_;

        Prioritet(int vrednost) {
            vrednost_ = vrednost;
        }
        
        int vrednost() {
            return vrednost_;
        }
        
        public static Prioritet nasumicni() {
            return values()[(int) (Math.random() * values().length)];
        }
        
    }

    Prioritet prioritet();

}
