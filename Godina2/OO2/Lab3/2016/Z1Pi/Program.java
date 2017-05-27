/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import oo2lab3z1pi.*;
import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author Nikola
 *
 * Програм коришћењем графичке корисничке површи према слици приказује рад
 * претходних класа. У менију Komande налазе се команде Kreni, Prekini и Zavrsi.
 */
final public class Program extends Frame {

    private final static int TEXT_FIELD_WIDTH = 20;

    private final TextField brojIteracija_ = new TextField("", TEXT_FIELD_WIDTH);
    private final TextField korak_ = new TextField("", TEXT_FIELD_WIDTH);

    private final static String OJLER = "Ojler";
    private final static String KRUG = "Krug";

    private final CheckboxGroup grupa_ = new CheckboxGroup();
    private final Checkbox ojler_ = new Checkbox(OJLER, grupa_, true);
    private final Checkbox krug_ = new Checkbox(KRUG, grupa_, false);

    private final static String BROJ_ITERACIJA = "Broj iteracija: ";
    private final static String KORAK = "Korak: ";

    private final static int TEXT_AREA_HEIGHT = 7;

    private final TextArea tekst_ = new TextArea("", TEXT_AREA_HEIGHT, 1, TextArea.SCROLLBARS_VERTICAL_ONLY);

    private final Prikazivac prikazivac_;
    private Akter akter_;

    private final static int BOUND_X = 200;
    private final static int BOUND_Y = 200;
    private final static int BOUND_WIDTH = 500;
    private final static int BOUND_HEIGHT = 300;

    private Program() {
        super("Racunanje PI");

        setBounds(BOUND_X, BOUND_Y, BOUND_WIDTH, BOUND_HEIGHT);

        tekst_.setBackground(Color.WHITE);
        prikazivac_ = new Prikazivac(tekst_);

        postaviProzor();
        postaviMeni();

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                if (akter_ != null) {
                    akter_.prekiniPrevremeno();
                }
                dispose();
            }
        });

        setVisible(true);
    }

    private void postaviProzor() {

        Panel panelSaTekstom = new Panel(new BorderLayout());
        panelSaTekstom.add(tekst_, "Center");
        add(panelSaTekstom, "North");

        Panel panelSaIzborima = new Panel(new BorderLayout());
        panelSaIzborima.setBackground(Color.LIGHT_GRAY);

        Panel izborParametara = new Panel(new FlowLayout());

        Panel izborIteracija = new Panel(new BorderLayout());
        izborIteracija.add(new Label(BROJ_ITERACIJA), "West");
        izborIteracija.add(brojIteracija_, "East");

        Panel izborKoraka = new Panel(new BorderLayout());
        izborKoraka.add(new Label(KORAK), "West");
        izborKoraka.add(korak_, "East");

        izborParametara.add(izborIteracija, "West");
        izborParametara.add(izborKoraka, "East");

        Panel izborAktera = new Panel(new FlowLayout());
        izborAktera.add(ojler_, "West");
        izborAktera.add(krug_, "East");

        panelSaIzborima.add(izborParametara, "North");
        panelSaIzborima.add(izborAktera, "South");

        add(panelSaIzborima, "South");
    }

    private void postaviMeni() {
        MenuBar traka = new MenuBar();
        Menu komande = new Menu("Komande");

        MenuItem kreni = new MenuItem("Kreni");
        kreni.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                int iteracije = Integer.parseInt(brojIteracija_.getText());
                int koraci = Integer.parseInt(korak_.getText());
                if (ojler_.getState()) {
                    akter_ = new Ojler(prikazivac_, iteracije, koraci);
                } else {
                    akter_ = new Krug(prikazivac_, iteracije, koraci);
                }
            }
        });

        MenuItem prekini = new MenuItem("Prekini");
        prekini.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                if (akter_ != null) {
                    akter_.prekiniPrevremeno();
                }
            }
        });

        MenuItem zavrsi = new MenuItem("Zavrsi");
        zavrsi.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                if (akter_ != null) {
                    akter_.prekiniPrevremeno();
                }
                dispose();
            }
        });

        komande.add(kreni);
        komande.add(prekini);
        komande.add(zavrsi);

        traka.add(komande);
        setMenuBar(traka);

    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        new Program();
    }

}
