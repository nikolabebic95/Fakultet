import njive.*;

/**
 * (10 поена) Написати на језику Java програм који направи два атара, пар шума и њива које
 * припадају овим атарима, а затим трећи атар који садржи претходна два и једну шуму. Затим
 * испише трећи атар и његов принос за неки период. Користити константне параметре (не треба
 * ништа учитавати).
 */
public class Glavni {
    public static void main(String[] args) {
        Atar a1 = new Atar(500);
        Atar a2 = new Atar(200);
        Suma s1 = new Suma(100, 50, 10, 2);
        Njiva n1 = new Njiva(100, 100);
        a1.dodaj(s1);
        a2.dodaj(n1);
        Atar a3 = new Atar(1000);
        a3.dodaj(a1);
        a3.dodaj(a2);
        Suma s2 = new Suma(200, 150, 5, 1);
        a3.dodaj(s2);
        System.out.println(a3);
        System.out.println(a3.prinos(5));
    }
}
