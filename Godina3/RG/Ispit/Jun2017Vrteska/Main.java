/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Jun2017;

import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.PerspectiveCamera;
import javafx.scene.Scene;
import javafx.scene.SceneAntialiasing;
import javafx.scene.transform.Rotate;
import javafx.scene.transform.Translate;
import javafx.stage.Stage;

/**
 *
 * @author Nikola
 */
public class Main extends Application {    
    @Override
    public void start(Stage primaryStage) {
        Group root = new Group();
        
        Carousel carousel = new Carousel();
        
        root.getChildren().addAll(new Stand(), new Bar(), carousel);
        
        PerspectiveCamera camera = new PerspectiveCamera(true);
        camera.setFarClip(5000);
        Group cameraGroup = new Group(camera);
        cameraGroup.getTransforms().addAll(new Translate(0, -500, -1000), new Rotate(-20, Rotate.X_AXIS));
        
        root.getChildren().add(cameraGroup);
        
        Scene scene = new Scene(root, 700, 700, true, SceneAntialiasing.BALANCED);
        
        scene.setOnKeyPressed(event -> {
            switch (event.getCode()) {
                case UP:
                    carousel.speedUp();
                    break;
                case DOWN:
                    carousel.slowDown();
                    break;
            }
        });
        
        scene.setOnScroll(event -> {
            double step = event.getDeltaY();
            camera.setTranslateZ(camera.getTranslateZ() - step);
        });
        
        scene.setCamera(camera);
        primaryStage.setScene(scene);
        primaryStage.setTitle("Carousel");
        primaryStage.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
