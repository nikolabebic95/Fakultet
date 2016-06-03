package autoput;

import java.awt.*;
import java.awt.event.*;

/**
 * (20 поена) Аутопут с једном графичком траком на графичкој корисничкој површи према
 * слици приказује стање на траци. Промена дозвољене брзине делује чим се унесе нова
 * вредност и притисне тастер Enter у одговарајућем пољу за текст. При покретању траке
 * текст у приказивачу се брише.
 */
public class Autoput extends Frame {
    private final static double PODRAZUMEVANA_DUZINA = 200000;
    private final static double PODRAZUMEVANA_DOZVOLJENA_BRZINA = 120;

    private final static int DUZINA_POLJA_ZA_TEKST = 10;

    private final static int SIRINA_PROZORA = 300;
    private final static int VISINA_PROZORA = 500;

    private GrafickaTraka traka_ = new GrafickaTraka(PODRAZUMEVANA_DUZINA, PODRAZUMEVANA_DOZVOLJENA_BRZINA);
    {
        new Rampa(traka_);
    }
    private TextField polje_ = new TextField(DUZINA_POLJA_ZA_TEKST);

    private Button kreni_ = new Button("Kreni");
    private Button stani_ = new Button("Stani");

    public Autoput() {
        super("Autoput");
        setSize(SIRINA_PROZORA, VISINA_PROZORA);
        postaviProzor();
        traka_.pocni();
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                super.windowClosing(we);
                traka_.zavrsi();
                dispose();
            }
        });
        setVisible(true);
    }

    private void postaviProzor() {
        setLayout(new GridLayout(1, 2));
        add(traka_.platno(), "West");
        Panel levi = new Panel(new GridLayout(2, 1));
        Panel panel = new Panel(new GridLayout(6, 1));

        stani_.setEnabled(false);
        kreni_.addActionListener((ActionEvent ae) -> {
            traka_.nastavi();
            kreni_.setEnabled(false);
            stani_.setEnabled(true);
        });
        stani_.addActionListener((ActionEvent ae) -> {
            traka_.zaustavi();
            stani_.setEnabled(false);
            kreni_.setEnabled(true);
        });
        Label duzina = new Label("Duzina: " + traka_.duzina());
        Label dozvoljena_brzina = new Label("Dozvoljena brzina:");
        polje_.setText(traka_.dozvoljena_brzina_ + "");
        polje_.addActionListener((ActionEvent ae) -> {
            try {
                traka_.promeniDozvoljenuBrzinu(Double.parseDouble(polje_.getText()));
            } catch (NumberFormatException e) {
                // Samo ne promeni brzinu
            }
        });

        Label prebrzi = new Label("Prebrzi:");

        panel.add(kreni_);
        panel.add(stani_);
        panel.add(duzina);
        panel.add(dozvoljena_brzina);
        panel.add(polje_);
        panel.add(prebrzi);

        levi.add(panel);
        levi.add(traka_.prikazivac());

        add(levi, "East");
    }

    public static void main(String[] args) {
        new Autoput();
    }
}
