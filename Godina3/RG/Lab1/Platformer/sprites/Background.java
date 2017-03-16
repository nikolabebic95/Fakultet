/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sprites;

import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

/**
 *
 * @author mile
 */
public class Background extends Sprite {

    public Background(int width, int height) {
        Rectangle bg = new Rectangle(0, 0, width, height);
        bg.setFill(Color.SKYBLUE);
        getChildren().add(bg);
    }
}
