/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Jun2017;

import javafx.scene.Group;
import javafx.scene.paint.Color;
import javafx.scene.paint.PhongMaterial;
import javafx.scene.shape.Cylinder;

/**
 *
 * @author Nikola
 */
public class Bar extends Group {
    {
        Cylinder bar = new Cylinder(12, 350);
        Cylinder top = new Cylinder(24, 10);
        
        PhongMaterial barMaterial = new PhongMaterial();
        barMaterial.setDiffuseColor(Color.BLUE);
        
        bar.setMaterial(barMaterial);
        
        PhongMaterial topMaterial = new PhongMaterial();
        topMaterial.setDiffuseColor(Color.RED);
        
        bar.setMaterial(barMaterial);
        top.setMaterial(topMaterial);
        
        bar.setTranslateY(-175);
        top.setTranslateY(-355);
        
        getChildren().addAll(bar, top);
    }
}
