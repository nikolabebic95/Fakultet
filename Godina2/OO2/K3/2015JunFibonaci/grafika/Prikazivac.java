package grafika;

import proizvodnja.*;

import java.awt.*;
import java.awt.event.*;

/**
 * (25 поена) Графички приказивач, на обухваћеном активном
 * платну, црта фигуру са слике на основу генерисаног низа
 * целобројних вредности, према приложеној слици. За сваки број
 * низа се црта кружни лук полупречника једнаког генерисаном
 * броју, ширине угла (разлике почетног и крајњег угла)
 * Math.PI/2. Центар лука који представља први број низа
 * налази се на средини површине за цртање, а његов почетни угао
 * је 0. Центре и углове лукова који представљају остале бројеве у
 * низу прилагодити, тако да фигура изгледа као на приложеној
 * слици. Цртање може да се покрене и прекине.
 */
public final class Prikazivac extends Frame {

    private Thread nit_ = null;
    private final CheckboxGroup grupa_ = new CheckboxGroup();
    private final Checkbox fibonacijev_ = new Checkbox("Fibonacijev", true, grupa_);
    private final Checkbox trougaoni_ = new Checkbox("Trougaoni", false, grupa_);

    private final static double SIRINA_UGLA = Math.PI / 2;
    private final static double POCETNI_UGAO = 0;
    private final static double SIRINA_KRUGA = 2 * Math.PI;

    private final static int SIRINA_PROZORA = 600;
    private final static int VISINA_PROZORA = 600;
    private final static String IME_PROZORA = "Nizovi";

    private class Platno extends Canvas implements Runnable {
        private void kreni() {
            if (nit_ != null) nit_.interrupt();
            nit_ = new Thread(this);
            nit_.start();
        }

        private void stani() {
            if (nit_ != null) nit_.interrupt();
        }

        @Override
        public void run() {
            Generator generator;
            Graphics g = getGraphics();
            g.setColor(Color.LIGHT_GRAY);
            g.fillRect(0, 0, getWidth(), getHeight());
            if (fibonacijev_.getState()) generator = new Fibonacijev();
            else generator = new Trougaoni();
            double pocetni_ugao = POCETNI_UGAO;
            double krajnji_ugao = pocetni_ugao + SIRINA_UGLA;
            int centar_x = getWidth() / 2;
            int centar_y = getHeight() / 2;
            int kvadrant = 0;
            double poluprecnik = 0;
            try {
                while (!Thread.interrupted()) {
                    Tacka centar = new Tacka(centar_x, centar_y);
                    double prethodni = poluprecnik;
                    poluprecnik = generator.proizvedi();
                    Luk luk = new Luk(centar, poluprecnik, pocetni_ugao, krajnji_ugao, getGraphics());
                    luk.crtaj();
                    pocetni_ugao = krajnji_ugao;
                    if (pocetni_ugao >= SIRINA_KRUGA) pocetni_ugao -= SIRINA_KRUGA;
                    krajnji_ugao += SIRINA_UGLA;
                    if (krajnji_ugao > SIRINA_KRUGA) krajnji_ugao -= SIRINA_KRUGA;
                    kvadrant = (kvadrant + 1) % 4;
                    switch (kvadrant) {
                        case 1:
                            centar_x += 0;
                            centar_y += (int) (poluprecnik - prethodni);
                            break;
                        case 2:
                            centar_x += (int) (poluprecnik - prethodni);
                            centar_y += 0;
                            break;
                        case 3:
                            centar_x += 0;
                            centar_y += (int) -(poluprecnik - prethodni);
                            break;
                        case 0:
                            centar_x += (int) -(poluprecnik - prethodni);
                            centar_y += 0;
                            break;
                    }
                }
            } catch (InterruptedException e) {
            }
        }
    }

    private Prikazivac() {
        super(IME_PROZORA);
        setBounds(0, 0, SIRINA_PROZORA, VISINA_PROZORA);
        setLayout(new BorderLayout());
        popuniProzor();
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                if (nit_ != null) nit_.interrupt();
                dispose();
            }
        });
        setVisible(true);
    }

    private void popuniProzor() {
        Panel gornji = new Panel(new FlowLayout());
        gornji.add(fibonacijev_);
        gornji.add(trougaoni_);
        Platno platno = new Platno();
        platno.setBackground(Color.LIGHT_GRAY);
        Panel donji = new Panel(new FlowLayout());
        Button kreni = new Button("Kreni");
        kreni.addActionListener((ActionEvent ae) -> platno.kreni());
        Button stani = new Button("Stani");
        stani.addActionListener((ActionEvent ae) -> platno.stani());
        donji.add(kreni);
        donji.add(stani);
        add(gornji, "North");
        add(platno, "Center");
        add(donji, "South");
    }

    public static void main(String args[]) {
        new Prikazivac();
    }
}
