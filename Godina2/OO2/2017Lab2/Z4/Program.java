/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package proizvod;

import java.util.Scanner;

/**
 *
 * @author Mica
 */
public class Program {
    public static void main(String [] args){
        Scanner scanner=new Scanner(System.in);
        int i;
        Radnik radnik=null;
        
        while(true){
            System.out.println("Odabrati jednu od opcija:");
            System.out.println("1. Napraviti radnika(ime i produktivnost)");
            System.out.println("2. Napraviti predmet (masa)");
            System.out.println("3. Ispitati da li radnik ima gotov proizvod");
            System.out.println("4. Preuzeti proizvod i ispisati ga");
            System.out.println("5. Ispisati radnika");
            System.out.println("6. Zavrsiti program");
            i=scanner.nextInt();
            switch(i){
                case 1:
                    String ime=scanner.next();
                    double pro=scanner.nextInt();
                    radnik=new Radnik(ime,pro);
                    radnik.start();
                    break;
                case 2:
                    double masa=scanner.nextDouble();
                    try{
                        radnik.proizvedi(masa);
                    }
                    catch(InterruptedException e){}
                    break;
                case 3:
                    if(radnik.isGotov())
                        System.out.println("Radnik ima gotov proizvod");
                    else
                        System.out.println("Radnik nema gotov proizvod");
                    break;
                case 4:
                    Proizvod p=null;
                    try{
                        p=radnik.preuzmi();
                    }
                    catch(InterruptedException e){}
                    System.out.println("Proizvod:"+p);
                    break;
                case 5:
                    System.out.println("Radnik:"+radnik);
                    break;
                case 6:
                    radnik.interrupt();
                    return;
                default:
                    System.out.println("Pogresan unos!");
                    break;
            }
        }
    }
}
