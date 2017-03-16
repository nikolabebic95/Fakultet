/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sprites;

import javafx.scene.paint.Color;
import javafx.scene.paint.CycleMethod;
import javafx.scene.paint.LinearGradient;
import javafx.scene.paint.Stop;
import javafx.scene.shape.Rectangle;

/**
 *
 * @author mile
 */
public class Background extends Sprite {

    public Background(int width, int height) {
        Rectangle bg = new Rectangle(0, 0, width, height);
        
        Stop [] stops = new Stop[] {new Stop(0, Color.SKYBLUE), new Stop(1, Color.STEELBLUE)};
        
        bg.setFill(new LinearGradient(0, 0, 0, 1, true, CycleMethod.NO_CYCLE, stops));
        getChildren().add(bg);
    }
}
