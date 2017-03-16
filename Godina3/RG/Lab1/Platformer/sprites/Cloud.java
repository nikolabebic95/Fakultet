/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package sprites;

import javafx.scene.Node;
import javafx.scene.paint.Color;
import javafx.scene.shape.Ellipse;

/**
 *
 * @author Nikola
 */
public class Cloud extends Sprite {

    {
        Ellipse center = new Ellipse(0.3, 0.5);
        Ellipse left = new Ellipse(-0.2, 0.2, 0.18, 0.3);
        Ellipse right = new Ellipse(0.2, 0.2, 0.18, 0.3);
        
        center.setFill(Color.WHITESMOKE);
        left.setFill(Color.WHITESMOKE);
        right.setFill(Color.WHITESMOKE);
        
        getChildren().addAll(new Node[]{center, left, right});
        setScaleX(200);
        setScaleY(120);
    }
}
