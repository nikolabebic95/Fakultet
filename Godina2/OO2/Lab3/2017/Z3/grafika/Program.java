/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import java.awt.*;
import java.awt.event.*;
import saobracaj.*;

/**
 *
 * @author Mica
 */
public class Program {
    public static void main(String [] args){
        Frame frame=new Frame("Benzinska stanica");
        Panel panel=new Panel(new BorderLayout());
        
        GrafickaStanica stanica=new GrafickaStanica();
        Panel upravljanje=new Panel(new FlowLayout());
        
        Button otvori=new Button("Otvori");
        Button zatvori=new Button("Zatvori");
        
        otvori.setEnabled(true);
        zatvori.setEnabled(false);
        
        otvori.addActionListener((ActionEvent e)->{
            otvori.setEnabled(false);
            zatvori.setEnabled(true);
            
            stanica.otvori();
        });
        
        zatvori.addActionListener((ActionEvent e)->{
            zatvori.setEnabled(false);
            otvori.setEnabled(true);
            
            stanica.zatvori();
        });
        
        upravljanje.add(otvori);
        upravljanje.add(zatvori);
        upravljanje.setBackground(Color.GRAY);
        panel.add(stanica.getPanel(), "Center");
        panel.add(upravljanje, "South");
        frame.add(panel);
        stanica.pokreni();
        frame.setSize(500,300);
        frame.setVisible(true);
        
        Autoput autoput=new Autoput(stanica);
        autoput.pokreni();
        
        frame.addWindowListener(new WindowAdapter(){
            @Override
            public void windowClosing(WindowEvent we){
                autoput.prekiniRad();
                frame.dispose();
            }
        });
        
    }
}
