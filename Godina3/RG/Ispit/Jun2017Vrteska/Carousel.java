/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package Jun2017;

import javafx.animation.Interpolator;
import javafx.animation.RotateTransition;
import javafx.animation.Timeline;
import javafx.scene.Group;
import javafx.scene.paint.Color;
import javafx.scene.paint.PhongMaterial;
import javafx.scene.shape.Cylinder;
import javafx.scene.transform.Rotate;
import javafx.scene.transform.Translate;
import javafx.util.Duration;

/**
 *
 * @author Nikola
 */
public class Carousel extends Group {
    private final RotateTransition rotateTransition;
    Group group;
    private final Rotate rotate;
    private double currentTranslate = -100;
    
    public void speedUp() {
        if (currentTranslate > -340) {
            currentTranslate--;
            group.setTranslateY(currentTranslate);
            
            double newRate = (((currentTranslate + 100) * -1) / 250) * 6 + 1;
            rotateTransition.setRate(newRate);
            
            double newRotate = (((currentTranslate + 100) * -1) / 250) * 60;
            rotate.setAngle(newRotate);
        }
    }
    
    public void slowDown() {
        if (currentTranslate < -100) {
            currentTranslate++;
            group.setTranslateY(currentTranslate);
            
            double newRate = (((currentTranslate + 100) * -1) / 250) * 6 + 1;
            rotateTransition.setRate(newRate);
            
            double newRotate = (((currentTranslate + 100) * -1) / 250) * 60;
            rotate.setAngle(newRotate);
        }
    }
    
    {
        Cylinder cylinder = new Cylinder(36, 15);
        PhongMaterial material = new PhongMaterial();
        material.setDiffuseColor(Color.RED);
        
        cylinder.setMaterial(material);
        
        group = new Group();
        group.getChildren().add(cylinder);
        rotate = new Rotate(0, Rotate.X_AXIS);
        
        for (int i = 0; i < 10; i++) {
            Cylinder holder = new Cylinder(5, 100);
            holder.setMaterial(material);
            
            holder.getTransforms().add(new Rotate(90, Rotate.X_AXIS));
            holder.getTransforms().add(new Rotate(i * 36, Rotate.Z_AXIS));
            holder.getTransforms().add(new Translate(0, 50, 0));
            group.getChildren().add(holder);
            
            Swing swing = new Swing();
            swing.getTransforms().add(new Rotate(i * 36, Rotate.Y_AXIS));
            swing.getTransforms().add(new Translate(0, 0, 95));
            swing.getTransforms().add(rotate);
            group.getChildren().add(swing);
        }
        
        group.setTranslateY(currentTranslate);
        
        getChildren().add(group);
        
        rotateTransition = new RotateTransition(Duration.seconds(20), group);
        rotateTransition.setAxis(Rotate.Y_AXIS);
        rotateTransition.setByAngle(-360);
        rotateTransition.setCycleCount(Timeline.INDEFINITE);
        rotateTransition.setInterpolator(Interpolator.LINEAR);
        rotateTransition.play();
    }
}
