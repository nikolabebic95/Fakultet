/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import oo2lab2z2posiljka.*;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

/**
 *
 * @author Nikola
 *
 * Написати на језику Java програм који с главног улаза учита трајање симулације
 * и капацитет приоритетног реда, направи један приоритетни ред, пошиљаоца и
 * примаоца и покрене симулацију
 */
public class Glavni {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in); // Ne svidja mi se klasa Citaj
        System.out.println("Unesite trajanje u sekundama i kapacitet");
        int trajanje = input.nextInt();
        int kapacitet = input.nextInt();

        PrioritetniRed prioritetni = new PrioritetniRed(kapacitet);
        Thread posiljalac = new Thread(new Posiljalac(prioritetni));
        Thread primalac = new Thread(new Primalac(prioritetni));
        posiljalac.start();
        primalac.start();
        try {
            TimeUnit.SECONDS.sleep(trajanje);
        } catch (InterruptedException e) {
            System.out.println(e);
        }
        posiljalac.interrupt();
        primalac.interrupt();
    }

}
