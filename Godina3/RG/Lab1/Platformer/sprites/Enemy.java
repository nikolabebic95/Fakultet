/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sprites;

import javafx.scene.paint.Color;
import javafx.scene.shape.Arc;
import javafx.scene.shape.ArcType;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import javafx.scene.transform.Scale;

/**
 *
 * @author mile
 */
public class Enemy extends Sprite {

    private double velocity;

    public Enemy(double velocity) {
        this.velocity = velocity;
        Arc head = new Arc();
        head.setCenterX(0);
        head.setCenterY(0.3);
        head.setRadiusX(0.5f);
        head.setRadiusY(0.8f);
        head.setStartAngle(0);
        head.setLength(180.0f);
        head.setType(ArcType.CHORD);
        head.setFill(Color.SADDLEBROWN);

        Rectangle leftLeg = new Rectangle(-0.4, 0.3, 0.2, 0.2);
        leftLeg.setFill(Color.BLACK);

        Rectangle rightLeg = new Rectangle(0.2, 0.3, 0.2, 0.2);
        rightLeg.setFill(Color.BLACK);

        Circle leftEye = new Circle(-0.2f, -0.15, 0.15);
        leftEye.setFill(Color.WHITE);

        Circle rightEye = new Circle(0.2f, -0.15, 0.15);
        rightEye.setFill(Color.WHITE);

        getChildren().add(head);
        getChildren().add(leftLeg);
        getChildren().add(rightLeg);
        getChildren().add(leftEye);
        getChildren().add(rightEye);

        Scale scale = new Scale(100, 80);
        getTransforms().add(scale);
    }

    @Override
    public void update() {
        setTranslateX(getTranslateX() - velocity);
    }

}
