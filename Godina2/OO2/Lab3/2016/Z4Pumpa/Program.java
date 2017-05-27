/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import oo2lab3z4benzinskastanica.*;
import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author Nikola
 *
 * Програм на графичкој корисничкој површи према слици приказује стање једне
 * бензинске станице. Не сме да се отвори отворена, односно затвори затворена
 * станица.
 */
public final class Program extends Frame implements ActionListener {

    private final static int SIRINA = 600;
    private final static int VISINA = 400;

    private final GrafickaStanica stanica_ = new GrafickaStanica();
    private final Autoput autoput_ = new Autoput(stanica_);

    private final Button otvori_ = new Button("Otvori");
    private final Button zatvori_ = new Button("Zatvori");

    private Program() {
        super("Benzinska stanica");
        setSize(SIRINA, VISINA);

        postaviProzor();
        
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                autoput_.prekini();
                dispose();
            }
        });

        autoput_.start();
        
        setVisible(true);

    }

    private void postaviProzor() {
        setLayout(new BorderLayout());
        otvori_.addActionListener(this);
        zatvori_.addActionListener(this);
        otvori_.setEnabled(true);
        zatvori_.setEnabled(false);

        Panel dugmici = new Panel(new FlowLayout());
        dugmici.add(otvori_);
        dugmici.add(zatvori_);
        dugmici.setBackground(Color.GRAY);
        
        add(dugmici, "South");
        add(stanica_.grafickaPloca(), "Center");
    }

    @Override
    public void actionPerformed(ActionEvent ae) {
        if (ae.getActionCommand().equals("Otvori")) {
            otvori_.setEnabled(false);
            zatvori_.setEnabled(true);
            stanica_.otvori();
        } else {
            zatvori_.setEnabled(false);
            otvori_.setEnabled(true);
            stanica_.zatvori();
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        new Program();
    }

}
