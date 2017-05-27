/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import fabrika.*;
import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author Mica
 */
public class Radionica {
    public static void main(String[] args){
        Frame frame=new Frame("Radionica");
        Panel panel=new Panel(new BorderLayout());
        TextArea textArea=new TextArea("", 11, 9);
        GrafickoSkladiste skladiste=new GrafickoSkladiste(textArea,20);
        Panel levi=new Panel(new GridLayout(5,1));
        Panel[] panelMotori=new Panel[5];
        for(int i=0; i<5; i++)
            panelMotori[i]=new Panel(new GridLayout(1,3));
        Mehanizam[] mehanizmi=new Mehanizam[5];
        for(int i=0; i<3; i++)
            mehanizmi[i]=new Masina(skladiste);
        for(int i=3; i<5; i++)
            mehanizmi[i]=new Traka(skladiste);
        GrafickiMotor[] motori=new GrafickiMotor[5];
        for(int i=0; i<5; i++){
            motori[i]=new GrafickiMotor(panelMotori[i],mehanizmi[i]);
            motori[i].initialize();
        }
        
        frame.addWindowListener(new WindowAdapter(){
            @Override
            public void windowClosing(WindowEvent we){
                for(int i=0; i<5; i++)
                    motori[i].interrupt();
                frame.dispose();
            }
        });
        
        for(int i=0; i<5; i++)
            levi.add(panelMotori[i]);
        panel.add(levi, "Center");
        panel.add(textArea, "East");
        frame.add(panel);
        
        frame.setSize(500,300);
        
        for(int i=0; i<5; i++)
            motori[i].start();
        
        frame.setVisible(true);
    }
}
