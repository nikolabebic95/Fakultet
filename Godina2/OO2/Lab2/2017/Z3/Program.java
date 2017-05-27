/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package banke;

import java.util.Scanner;
import java.util.concurrent.TimeUnit;

/**
 *
 * @author Mica
 */
public class Program {
    public static void main(String [] args){
            Scanner scanner=new Scanner(System.in);
            Banka b=new Banka();
            b.startuj();
            
        while(true){
            
            System.out.println("Uneti pocetnu sumu novca i duzinu radnog vremena:");
            double suma=scanner.nextDouble();
            double radnoVreme=scanner.nextDouble();
            if(radnoVreme<0) break;
            
            b.otvori(suma);
            
            try{
                TimeUnit.SECONDS.sleep((long)radnoVreme);
            }
            catch(InterruptedException e){}
            b.zatvori();
        }
        
        b.unisti();
    }
}
