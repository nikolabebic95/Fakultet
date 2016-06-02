import napredak.*;

import java.awt.*;
import java.awt.event.*;

/**
 * (10 поена) Програм на графичкој корисничкој површи према слици,
 * приказује један правоугаони и један кружни индикатор
 * напредовања одговарајућих симулираних послова. Одговарајућа
 * дугмад за заустављање/наставак рада мењају натпис
 * "Крени"/"Стани" у зависности од стања одговарајућег посла
 * чијим радом управљају. Користити фиксне вредности свих
 * параметара, не треба ништа читати са конзоле.
 */
public final class Program extends Frame {

    private final static Pravougaoni PRAVOUGAONI = new Pravougaoni(Color.ORANGE);
    private final static Kruzni KRUZNI = new Kruzni(Color.RED);

    private final static String POCETAK = "Kreni";
    private final static String KRAJ = "Stani";

    private final static Button PRAVOUGAONI_DUGME = new Button(POCETAK);
    private final static Button KRUZNI_DUGME = new Button(POCETAK);

    private final static int SIRINA_PROZORA = 1000;
    private final static int VISINA_PROZORA = 500;

    private final static Simulirani PRAVOUGAONI_POSAO = new Simulirani(1000, 5, 2, 5);
    private final static Simulirani KRUZNI_POSAO = new Simulirani(1000, 5, 2, 5);

    private final static Napredak PRAVOUGAONI_NAPREDAK = new Napredak(PRAVOUGAONI, PRAVOUGAONI_POSAO);
    private final static Napredak KRUZNI_NAPREDAK = new Napredak(KRUZNI, KRUZNI_POSAO);

    private Program() {
        super("Napredak");
        setSize(SIRINA_PROZORA, VISINA_PROZORA);
        PRAVOUGAONI_NAPREDAK.prijavi();
        KRUZNI_NAPREDAK.prijavi();
        postaviProzor();
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we) {
                PRAVOUGAONI_POSAO.zavrsi();
                KRUZNI_POSAO.zavrsi();
                dispose();
            }
        });
        setVisible(true);
    }

    private void postaviProzor() {
        Panel panel = new Panel(new GridLayout(1, 2));
        panel.add(PRAVOUGAONI);
        panel.add(KRUZNI);

        Panel dugmici = new Panel(new FlowLayout());
        dugmici.add(PRAVOUGAONI_DUGME);
        dugmici.add(KRUZNI_DUGME);

        PRAVOUGAONI_DUGME.addActionListener((ActionEvent ae) -> {
            if (PRAVOUGAONI_POSAO.stanje()) {
                PRAVOUGAONI_POSAO.zaustavi();
                PRAVOUGAONI_DUGME.setLabel(POCETAK);
            } else {
                PRAVOUGAONI_POSAO.nastavi();
                PRAVOUGAONI_DUGME.setLabel(KRAJ);
            }
        });
        KRUZNI_DUGME.addActionListener((ActionEvent ae) -> {
            if (KRUZNI_POSAO.stanje()) {
                KRUZNI_POSAO.zaustavi();
                KRUZNI_DUGME.setLabel(POCETAK);
            } else {
                KRUZNI_POSAO.nastavi();
                KRUZNI_DUGME.setLabel(KRAJ);
            }
        });

        add(panel, "Center");
        add(dugmici, "South");
    }

    public static void main(String[] args) {
        new Program();
    }
}
