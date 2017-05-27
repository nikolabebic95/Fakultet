/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package avioni;

/**
 *
 * @author Mica
 */
public class Main {
    public static void main(String [] args){
        Aerodrom a=new Aerodrom("Nikola Tesla");
        Putnicki p=new Putnicki('A', 20000, 10000, 200);
        Teretni t=new Teretni('B', 30000, 10000, 300);
        Osoba o1=new Osoba(90, "Nikola");
        Osoba o2=new Osoba(60, "Milica");
        Osoba o3=new Osoba(5, "Strahinja");
        Kontejner k1=new Kontejner(30);
        Kontejner k2=new Kontejner(40); 
        
        try{
        p.stavi(o1, 0);
        p.stavi(o2, 1);
        p.stavi(o3, 5);
        t.stavi(k1, 0);
        t.stavi(k2, 3);
        }
        catch(GPun e) {System.out.println(e);}
        catch(GPopunjeno e) {System.out.println(e);}
        catch(GVrsta e){System.out.println(e);}
        
        a.sleti(t);
        a.sleti(p);
        
        System.out.println(a);
    }
}
