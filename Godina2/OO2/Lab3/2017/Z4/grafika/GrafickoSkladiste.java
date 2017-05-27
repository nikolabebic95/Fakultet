/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import fabrika.Proizvod;
import fabrika.Skladiste;
import java.awt.TextArea;

/**
 *
 * @author Mica
 */
public class GrafickoSkladiste extends Skladiste{
    private final TextArea textArea;

    public GrafickoSkladiste(TextArea textArea, int kapacitet) {
        super(kapacitet);
        this.textArea = textArea;
    }
    
    @Override
    public synchronized void dodaj(Proizvod proizvod) throws InterruptedException{
        super.dodaj(proizvod);
        textArea.setText(super.toString());
    }
    
    @Override
    public synchronized Proizvod uzmi() throws InterruptedException{
        Proizvod p=super.uzmi();
        textArea.setText(super.toString());
        return p;
    }
}
