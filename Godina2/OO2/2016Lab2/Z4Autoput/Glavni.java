/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.concurrent.TimeUnit;
import oo2lab2z4autoput.*;

/**
 *
 * @author Nikola
 *
 * Написати на језику Java програм који направи једну бензинску станицу, отвори
 * станицу, сваке 3 s испише станицу, после 6 исписа затвори станицу и на крају
 * је уништи. Користити константне податке (не треба ништа учитавати).
 */
public class Glavni {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Stanica s = new Stanica();
        s.otvori();
        Autoput a = new Autoput(s);
        a.start();
        try {
            for (int i = 0; i < 6; i++) {
                System.out.println(s);
                TimeUnit.SECONDS.sleep(3);
            }
        } catch (InterruptedException e) {
            System.out.println(e);
        }
        s.prekiniRad();
        a.interrupt();
        System.out.println("Kraj");
    }
}
