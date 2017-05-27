/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import oo2lab3z2crtanje.*;
import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author Nikola
 *
 * Програм на графичкој корисничкој површи црта одабрану криву с одабраним
 * параметрима. Опсег координата на цртежу дуж обе осе је ±10. Садржај податка s
 * типа String може да се разложи на редове методом String[] s.split("\n").
 */
public class Program extends Frame {

    private final static int BOUND_X = 200;
    private final static int BOUND_Y = 200;
    private final static int BOUND_WIDTH = 500;
    private final static int BOUND_HEIGHT = 500;

    private final static int TEXT_FIELD_WIDTH = 10;

    private final TextField donjaGranica_ = new TextField("", TEXT_FIELD_WIDTH);
    private final TextField gornjaGranica_ = new TextField("", TEXT_FIELD_WIDTH);
    private final TextField korak_ = new TextField("", TEXT_FIELD_WIDTH);

    private final Label labele_ = new Label("tMin, tMax, dT: ");

    private final static int TEXT_AREA_HEIGHT = 10;

    private final TextArea unos_ = new TextArea("", TEXT_AREA_HEIGHT, 1, TextArea.SCROLLBARS_BOTH);

    private final Color[] boje_ = {Color.BLACK, Color.GRAY, Color.RED, Color.YELLOW, Color.GREEN, Color.BLUE};
    private final String[] imenaBoja_ = {"Crna", "Siva", "Crvena", "Zuta", "Zelena", "Plava"};

    private final static int CRTEZ_GORE = -10;
    private final static int CRTEZ_DOLE = 10;
    private final static int CRTEZ_LEVO = -10;
    private final static int CRTEZ_DESNO = 10;

    private final Crtez crtez_ = new Crtez(CRTEZ_GORE, CRTEZ_DOLE, CRTEZ_LEVO, CRTEZ_DESNO);

    private final static String SPIRALA = "Spirala";
    private final static String POLINOM = "Polinom";

    private final CheckboxGroup grupa_ = new CheckboxGroup();
    private final Checkbox spirala_ = new Checkbox(SPIRALA, grupa_, true);
    private final Checkbox polinom_ = new Checkbox(POLINOM, grupa_, false);

    private final Button dugme_ = new Button("Crtaj");

    private Program() {
        super("Crtanje krivih");

        setBounds(BOUND_X, BOUND_Y, BOUND_WIDTH, BOUND_HEIGHT);

        postaviProzor();

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                crtez_.prekini();
                dispose();
            }
        });

        setVisible(true);

    }

    private void postaviProzor() {
        Panel izborTacaka = new Panel(new FlowLayout());
        izborTacaka.add(labele_);
        izborTacaka.add(donjaGranica_);
        izborTacaka.add(gornjaGranica_);
        izborTacaka.add(korak_);

        add(izborTacaka, "North");

        Panel sredina = new Panel(new GridLayout(1, 3));

        sredina.add(unos_);
        sredina.add(crtez_);

        List lista = new List(imenaBoja_.length);
        for (String ime : imenaBoja_) {
            lista.add(ime);
        }
        lista.select(0);
        lista.setMultipleMode(false);
        sredina.add(lista);

        add(sredina, "Center");

        Panel izborKrive = new Panel(new FlowLayout());

        izborKrive.add(spirala_);
        izborKrive.add(polinom_);
        izborKrive.add(dugme_);

        dugme_.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ae) {
                String[] koeficijentiStringovi = unos_.getText().trim().split("\n");
                double[] koeficijenti = new double[koeficijentiStringovi.length];
                for (int i = 0; i < koeficijenti.length; i++) {
                    koeficijenti[i] = Double.parseDouble(koeficijentiStringovi[i]);
                }
                Kriva kriva;
                if (spirala_.getState()) {
                    kriva = new Spirala(koeficijenti[0], koeficijenti[1], koeficijenti[2]);
                }
                else {
                    kriva = new Polinom(koeficijenti);
                }
                int kkk = lista.getSelectedIndex();
                crtez_.crtaj(kriva, boje_[lista.getSelectedIndex()], Double.parseDouble(donjaGranica_.getText()), Double.parseDouble(gornjaGranica_.getText()), Double.parseDouble(korak_.getText()));
            }
        });
        
        add(izborKrive, "South");
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        new Program();
    }

}
