/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import oo2lab3z3prenos.*;
import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author Nikola
 *
 * Програм на графичкој корисничкој површи према слици приказује пренос
 * текстуалних порука од предајника до пријемника уз помоћ преносне линије.
 */
public final class Program extends Frame {

    private final static int VISINA_TEKSTA = 5;
    
    private final TextArea predajniTekst_ = new TextArea("", VISINA_TEKSTA, 1, TextArea.SCROLLBARS_VERTICAL_ONLY);
    private final TextArea prijemniTekst_ = new TextArea("", VISINA_TEKSTA, 1, TextArea.SCROLLBARS_VERTICAL_ONLY);
    
    private final Prikazivac predajniPrikazivac_ = new Prikazivac(predajniTekst_);
    private final Prikazivac prijemniPrikazivac_ = new Prikazivac(prijemniTekst_);
    
    private final Bafer predajni_ = new Bafer(predajniPrikazivac_);
    private final Bafer prijemni_ = new Bafer(prijemniPrikazivac_);

    private final Predajnik predajnik_ = new Predajnik(predajni_);
    private final Prijemnik prijemnik_ = new Prijemnik(prijemni_);
    private final Linija linija_ = new Linija(predajni_, prijemni_);

    private final int SIRINA_EKRANA = 500;
    private final int VISINA_EKRANA = 300;

    private Program() {
        super("Prenos");

        setSize(SIRINA_EKRANA, VISINA_EKRANA);

        postaviProzor();
        
        predajnik_.zapocni();
        prijemnik_.zapocni();
        linija_.zapocni();
        
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                predajnik_.zavrsi();
                prijemnik_.zavrsi();
                linija_.zavrsi();
                dispose();
            }
        });

        setVisible(true);
    }

    private void postaviProzor() {
        Panel predajnikPrijemnik = new Panel(new GridLayout(1, 2));
        predajnikPrijemnik.add(new KomandnaPloca(predajnik_));
        predajnikPrijemnik.add(new KomandnaPloca(prijemnik_));
        
        Panel tekstovi = new Panel(new GridLayout(1, 2));
        tekstovi.add(predajniTekst_);
        tekstovi.add(prijemniTekst_);
        
        Panel linija = new Panel(new FlowLayout());
        linija.add(new KomandnaPloca(linija_));
        
        add(predajnikPrijemnik, "North");
        add(tekstovi, "Center");
        add(linija, "South");
        
        
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        new Program();
    }

}
