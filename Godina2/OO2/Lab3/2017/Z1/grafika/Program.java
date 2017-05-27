/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package grafika;

import funkcije.*;
import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author Mica
 */
public class Program extends Frame {
    private final static int FRAME_WIDTH=500, FRAME_HEIGHT=300;
    private final ZbirFunkcija zbirFunkcija=new ZbirFunkcija();
    private final Grafik grafik=new Grafik(zbirFunkcija, -10, 10, -10, 10);
        
    {
        grafik.setBrojTacaka(200);
        grafik.setSize(FRAME_WIDTH, FRAME_HEIGHT*2/3);
        grafik.start();
    }
    
    public Program(){
        super("Grafik");
    }
    
    public void initialize(){
        setSize(FRAME_WIDTH, FRAME_HEIGHT);
        dodaj();
        addWindowListener(new WindowAdapter(){
            @Override
            public void windowClosing(WindowEvent we){
                grafik.prekini();
                dispose();
            }
        });
        
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                grafik.setSize(getWidth(), getHeight()*2/3);
            }
        });
        
        setVisible(true);
    }
    
    public void dodaj(){
        Panel panel=new Panel(new BorderLayout());
        
        TextArea textArea=new TextArea("", 5, 20);
        Panel upravljanje=new Panel(new BorderLayout());
        
        Panel donji=new Panel(new FlowLayout());
        Panel gornji=new Panel(new FlowLayout());
        
        Label labelaGornja=new Label("a,b,c:");
        TextField a=new TextField();
        TextField b=new TextField();
        TextField c=new TextField();
        Button dodaj=new Button("Dodaj");
        Button isprazni=new Button("Isprazni");
        
        Label labelaDonja=new Label("v:");
        TextField v=new TextField();
        Button kreni=new Button("Kreni");
        Button stani=new Button("Stani");
        
        gornji.add(labelaGornja);
        gornji.add(a);
        gornji.add(b);
        gornji.add(c);
        gornji.add(dodaj);
        gornji.add(isprazni);
        
        donji.add(labelaDonja);
        donji.add(v);
        donji.add(kreni);
        donji.add(stani);
        
        upravljanje.add(gornji,"North");
        upravljanje.add(donji, "South");
        
        panel.add(upravljanje, "South");
        panel.add(textArea, "West");
        panel.add(grafik, "East");
        
        add(panel);
        //textArea.setText("nhyjdtfbjusfckjindvyfkigvkybsjfdidvkbvjsrfvsbdkivfkjbdsi");
        //textArea.setSize(FRAME_WIDTH/3, FRAME_HEIGHT*2/3);
        
        dodaj.addActionListener((ActionEvent e)->{
            double aa, bb, cc;
            aa=Double.parseDouble(a.getText());
            bb=Double.parseDouble(b.getText());
            cc=Double.parseDouble(c.getText());
            
            Sinusoida funkcija=new Sinusoida(aa, bb, cc);
            zbirFunkcija.dodaj(funkcija);
            
            textArea.setText(zbirFunkcija.toString());
        });
        
        isprazni.addActionListener((ActionEvent e) -> {
            zbirFunkcija.izbaci();
            textArea.setText(zbirFunkcija.toString());
        });
        
        v.addActionListener((ActionEvent e)->{
            grafik.setV(Double.parseDouble(v.getText()));
        });
        
        kreni.addActionListener((ActionEvent e)->{
            grafik.nastavi();
        });
        
        stani.addActionListener((ActionEvent e)->{
            grafik.zaustavi();
        });
    }
    
    public static void main(String []args){
        new Program().initialize();
    }
}
