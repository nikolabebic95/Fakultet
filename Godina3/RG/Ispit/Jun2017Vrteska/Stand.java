/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Jun2017;

import javafx.scene.Group;
import javafx.scene.image.Image;
import javafx.scene.paint.PhongMaterial;
import javafx.scene.shape.Cylinder;

/**
 *
 * @author Nikola
 */
public class Stand extends Group {
    {
        Cylinder lower = new Cylinder(200, 10);
        Cylinder middle = new Cylinder(150, 10);
        Cylinder upper = new Cylinder(100, 10);
        
        PhongMaterial material = new PhongMaterial();
        material.setDiffuseMap(new Image("file:metal.jpg"));
        
        lower.setTranslateY(25);
        middle.setTranslateY(15);
        upper.setTranslateY(5);
        
        lower.setMaterial(material);
        middle.setMaterial(material);
        upper.setMaterial(material);
        
        getChildren().add(lower);
        getChildren().add(middle);
        getChildren().add(upper);
    }
}
