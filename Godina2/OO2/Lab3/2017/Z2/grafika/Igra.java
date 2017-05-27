/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import figure.Luk;
import figure.Balon;
import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author Mica
 */
public class Igra extends Frame{
    private static final int FRAME_WIDTH=500, FRAME_HEIGHT=300;
    private Scena scena;
    private Luk luk;
    
    public Igra(){
        super("Gadjanje balona");
    }
    
    public void initialize(){
        setSize(FRAME_WIDTH, FRAME_HEIGHT);
        dodaj();
        addWindowListener(new WindowAdapter(){
            @Override
            public void windowClosing(WindowEvent we){
                scena.zaustavi();
                dispose();
            }
        });
        
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                scena.setSize(getWidth(), getHeight()*2/3);
            }
        });
        
        setVisible(true);
        scena.initialize();
    }
    
    public void dodaj(){
        Panel panel=new Panel(new BorderLayout());
        
        scena=new Scena();
        scena.setSize(getWidth(), getHeight()*2/3);
        Panel panelDonji=new Panel(new FlowLayout());
        
        luk=new Luk(Color.BLUE, 10, 10, 5, 20);
        scena.dodaj(luk);
        
        Button gore=new Button("gore");
        Button dole=new Button("dole");
        Button pali=new Button("pali");
        Button baloni=new Button("baloni");
        panelDonji.add(gore);
        panelDonji.add(dole);
        panelDonji.add(pali);
        panelDonji.add(baloni);
        
        panel.add(scena, "Center");
        panel.add(panelDonji, "South");
        add(panel);
        
        gore.addActionListener((ActionEvent e)->{
            if(luk.getY()-luk.getDuzinaIvica()/2-luk.getKorak()>0)
                luk.pomeriGore();
        });
        
        dole.addActionListener((ActionEvent e)->{
            if(luk.getY()+luk.getDuzinaIvica()/2+luk.getKorak()<scena.getHeight()-1)
                luk.pomeriDole();
        });
        
        pali.addActionListener((ActionEvent e)->{
            luk.ispali(16, Color.black, 0.2, scena);
        });
        
        baloni.addActionListener((ActionEvent e)->{
            double x=scena.getWidth()-8;
            double y=scena.getHeight()-8;
            for(int i=0; i<5; i++){
                double brzina=Math.random()*(0.08-0.06)+0.06;
                Balon balon=new Balon(Color.GREEN, Color.RED, 16, brzina, x, y);
                scena.dodaj(balon);
                x-=16+30;
            }
        });
        
    }
    
    public static void main(String []args){
        new Igra().initialize();
    }
    
}
