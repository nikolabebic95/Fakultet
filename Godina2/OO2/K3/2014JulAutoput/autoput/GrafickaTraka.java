package autoput;

import java.awt.*;

/**
 * Графичка трака додаје текстуалне описе аута са недозвољеним брзинама на почетак текста
 * у приказивачу (TextArea) у тренутку уласка у траку. На крају сваког циклуса ажурирања
 * постојећих аута у траци на графичком платну (Canvas) исцртава текстуалне описе постојећих
 * аута на положајима који су пропорционални пређеним путевима појединих аута. Почетак траке
 * је на дну, а крај на врху платна. Користи се црна боја за аута која се крећу дозвољеним
 * брзинама и црвена боја за она која се крећу пребрзо. Платно и приказивач могу да се дохвате.
 */
public class GrafickaTraka extends Traka {

    private Color DOZVOLJENA_BRZINA = Color.BLACK;
    private Color ZABRANJENA_BRZINA = Color.RED;

    private final static int BROJ_REDOVA_PRIKAZIVACA = 10;
    private final static int BROJ_KOLONA_PRIKAZIVACA = 10;

    private final static int VISINA_PLATNA = 200;
    private final static int SIRINA_PLATNA = 50;

    private TextArea prikazivac_ = new TextArea("", BROJ_REDOVA_PRIKAZIVACA, BROJ_KOLONA_PRIKAZIVACA, TextArea.SCROLLBARS_VERTICAL_ONLY);
    private Canvas platno_ = new Canvas();
    {
        platno_.setSize(SIRINA_PLATNA, VISINA_PLATNA);
    }

    public GrafickaTraka(double duzina, double dozvoljena_brzina, long kvant_vremena_milisekundi) {
        super(duzina, dozvoljena_brzina, kvant_vremena_milisekundi);
    }

    public GrafickaTraka(double duzina, double dozvoljena_brzina) {
        super(duzina, dozvoljena_brzina);
    }

    @Override
    public GrafickaTraka ubaci(Auto auto) {
        super.ubaci(auto);
        if (auto.brzina() > dozvoljena_brzina_) prikazivac_.insert(auto.toString() + '\n', 0);
        return this;
    }

    private void ispisiNaPlatnu() {
        Graphics graphics = platno_.getGraphics();
        graphics.setColor(Color.WHITE);
        graphics.fillRect(0, 0, platno_.getWidth(), platno().getHeight());
        ElementListe tek = prvi_;
        while (tek != null) {
            double procenat_puta = tek.auto_.predjeniPut() / duzina_;
            int pozicija = (int)(platno_.getHeight() - 1 - procenat_puta * platno_.getHeight());
            if (tek.auto_.brzina() > dozvoljena_brzina_) graphics.setColor(ZABRANJENA_BRZINA);
            else graphics.setColor(DOZVOLJENA_BRZINA);
            graphics.drawString(tek.auto_.toString(), 0, pozicija);
            tek = tek.sled_;
        }
    }

    @Override
    protected void izbaciAutomobile() {
        super.izbaciAutomobile();
        ispisiNaPlatnu();
    }

    public TextArea prikazivac() {
        return prikazivac_;
    }

    public Canvas platno() {
        return platno_;
    }
}
