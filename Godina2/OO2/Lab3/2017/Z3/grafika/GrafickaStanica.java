/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import java.awt.*;
import saobracaj.*;

/**
 *
 * @author Mica
 */
public class GrafickaStanica extends BenzinskaStanica{
    Panel panel=new Panel(new BorderLayout());
    
    TextArea leviRed=new TextArea("", 10, 5);
    Panel pumpeDesno=new Panel(new GridLayout(4,1));
    
    GrafickiPrikazivac[] prikazivaci=new GrafickiPrikazivac[4];
    
    @Override
    public void dodaj(Automobil auto){
        super.dodaj(auto);
        leviRed.setText(prikazReda());
    }
    
    public Panel getPanel() {
        return panel;
    }
    
    {   
        for(int i=0; i<4; i++){
            prikazivaci[i]=new GrafickiPrikazivac();
            prikazivaci[i].setSize(50, 100);
            pumpeDesno.add(prikazivaci[i]);
            pumpe[i].setPrikazivac(prikazivaci[i]);
        }
        
        panel.add(leviRed, "West");
        panel.add(pumpeDesno, "Center");
    }
}
