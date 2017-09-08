/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Jun2017;

import javafx.scene.Group;
import javafx.scene.image.Image;
import javafx.scene.paint.Color;
import javafx.scene.paint.PhongMaterial;
import javafx.scene.shape.Box;
import javafx.scene.shape.Cylinder;
import javafx.scene.transform.Rotate;
import javafx.scene.transform.Translate;
/**
 *
 * @author Nikola
 */
public class Swing extends Group {
    {
        PhongMaterial yellow = new PhongMaterial();
        yellow.setDiffuseColor(Color.YELLOW);
        PhongMaterial red = new PhongMaterial();
        red.setDiffuseColor(Color.RED);
        PhongMaterial wood = new PhongMaterial();
        wood.setDiffuseMap(new Image("file:wood.jpg"));
                
        Cylinder up = new Cylinder(1, 30);
        up.setMaterial(yellow);
        up.setTranslateY(15);
        
        Cylinder mid = new Cylinder(2, 10);
        mid.setMaterial(red);
        mid.getTransforms().add(new Translate(0, 30, 0));
        mid.getTransforms().add(new Rotate(90, Rotate.X_AXIS));
        
        Cylinder near = new Cylinder(1, 30);
        near.setMaterial(yellow);
        near.setTranslateY(45);
        near.setTranslateZ(-5);
        
        Cylinder far = new Cylinder(1, 30);
        far.setMaterial(yellow);
        far.setTranslateY(45);
        far.setTranslateZ(5);
        
        Box seat = new Box(10, 1, 10);
        seat.setMaterial(wood);
        seat.setTranslateY(60);
        
        getChildren().addAll(up, mid, near, far, seat);       
    }
}
