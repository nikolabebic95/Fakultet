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
public class GrafickiMotor extends Motor{
    private final Panel panel;
    Checkbox radi=new Checkbox("radi");
    Label dt=new Label("dt:");
    TextField dtText=new TextField("100", 6);
    Label m=new Label(super.mehanizam.toString());

    public GrafickiMotor(Panel panel, Mehanizam mehanizam) {
        super(mehanizam);
        this.panel = panel;
    }
    
    @Override
    public void podesiLabelu(String string){
        m.setText(string);
    }
    public void initialize(){
        radi.addItemListener((ItemEvent e)->{
            if(radi.getState())
                nastavi();
            else
                zaustavi();
        });
        
        dtText.addActionListener((ActionEvent e)->{
            setVreme(Double.parseDouble(dtText.getText()));
        });
        
        panel.add(radi);
        panel.add(dt);
        panel.add(dtText);
        panel.add(m);
    }
}
