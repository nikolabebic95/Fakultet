/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sprites;

import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.Rectangle;

/**
 *
 * @author mile
 */
public class FloorBlock extends Sprite {

    private final Rectangle block;
    private final Rectangle grass;
    
    public FloorBlock() {
        block = new Rectangle(-0.5, -0.5, 1, 1);        
        block.setFill(Color.SIENNA);
        
        grass = new Rectangle(-0.5, -0.5, 1, 0.3);
        grass.setFill(Color.GREENYELLOW);
        
        getChildren().add(block);
        getChildren().add(grass);
    }

}
