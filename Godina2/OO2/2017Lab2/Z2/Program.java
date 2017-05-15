/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sluzba;

import java.util.concurrent.TimeUnit;

/**
 *
 * @author Mica
 */
public class Program {
    public static void main (String [] args){
        try{
            Sluzba sluzba=new Sluzba();
            sluzba.otvori();
            TimeUnit.SECONDS.sleep(5);
            sluzba.zatvori();
            TimeUnit.SECONDS.sleep(3);
            sluzba.unisti();
        }
        catch(InterruptedException e){}
    }
}
