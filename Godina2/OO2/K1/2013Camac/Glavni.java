import camac.*;

/**
 * (15 поена) Написати на језику Java програм (класу са главном функцијом) у којем се стварају један вук,
 * једна коза и један купус, смештају у дружину на једној обали реке, а затим неколико пута чамцем пребацују
 * из дружине на једној обали у дружину на другој обали (у оба смера), уз исписивање дружина на обе обале и
 * чамца после сваке акције над дружином на обали. Није потребно водити рачуна о логичкој исправности редоследа
 * пребацивања, односно избора бића, нити је потребно проверавати статус успеха после операција над дружинама.
 */
public class Glavni {
    public static void main(String[] args) {

        Vuk vuk = new Vuk();
        Koza koza  = new Koza();
        Kupus kupus = new Kupus();
        Druzina levo = new Druzina();
        Druzina desno = new Druzina();
        Camac camac = new Camac();
        levo.dodaj(vuk);
        levo.dodaj(kupus);
        levo.dodaj(koza);
        System.out.println("Levo: "+levo+", Camac: "+camac+", Desno: "+desno);

        camac.stavi(levo.uzmi("Ko"));
        System.out.println("Levo: "+levo+", Camac: "+camac+", Desno: "+desno);

        desno.dodaj(camac.uzmi());
        System.out.println("Levo: "+levo+", Camac: "+camac+", Desno: "+desno);

        camac.stavi(levo.uzmi("Ku"));
        System.out.println("Levo: "+levo+", Camac: "+camac+", Desno: "+desno);

        camac.stavi(desno.zameni("Ko", camac.uzmi()));
        System.out.println("Levo: "+levo+", Camac: "+camac+", Desno: "+desno);

        camac.stavi(levo.zameni("Vu", camac.uzmi()));
        System.out.println("Levo: "+levo+", Camac: "+camac+", Desno: "+desno);

        desno.dodaj(camac.uzmi());
        System.out.println("Levo: "+levo+", Camac: "+camac+", Desno: "+desno);

        camac.stavi(levo.uzmi("Ko"));
        System.out.println("Levo: "+levo+", Camac: "+camac+", Desno: "+desno);

        desno.dodaj(camac.uzmi());
        System.out.println("Levo: "+levo+", Camac: "+camac+", Desno: "+desno);
    }
}
