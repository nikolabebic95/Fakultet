/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package rg2016k1;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.geometry.Bounds;
import javafx.scene.Scene;
import javafx.scene.layout.StackPane;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

/**
 *
 * @author Nikola
 */
public class Main extends Application {
    
    public static double SCREEN_WIDTH = 750;
    public static double SCREEN_HEIGHT = 600;
    
    public static Target target = new Target();
    
    public static Text result = new Text("Result: 0");
    public static Text clicksLeft = new Text("Clicks left: " + Target.NUM_OF_CLICKS);
    
    public static long startTime = -1;
    
    @Override
    public void start(Stage primaryStage) {
        
        StackPane root = new StackPane();
        root.getChildren().add(target);
        root.getChildren().add(result);
        root.getChildren().add(clicksLeft);
        
        target.setTranslateY(25);
        
        result.setFont(new Font("Arial Bold", 20));
        clicksLeft.setFont(new Font("Arial Bold", 20));
                
        result.setTranslateY(-SCREEN_HEIGHT / 2 + 10);
        
        clicksLeft.setTranslateY(-SCREEN_HEIGHT / 2 + 40);
        
        Scene scene = new Scene(root, SCREEN_WIDTH, SCREEN_HEIGHT);
        
        primaryStage.setTitle("Archery");
        primaryStage.setScene(scene);
        primaryStage.show();
        primaryStage.setResizable(false);
        
        Bounds bounds = target.getBoundsInParent();
        double left = bounds.getMinX();
        double right = bounds.getMaxX();                
        double width = right - left;
        double absoluteMove = SCREEN_WIDTH - width;
        
        target.setTranslateX(-absoluteMove / 2);
        
        // calling update once every frame
        new AnimationTimer() {
            @Override
            public void handle(long currentNanoTime) {
                if (startTime == -1) {
                    startTime = currentNanoTime;
                }
                
                long elapsed = currentNanoTime - startTime;
                
                long seconds = elapsed / 1000000000;
                
                double move = ((double)((elapsed % 1000000000)) / 1000000000) * absoluteMove;
                if (seconds % 2 == 0) {
                    target.setTranslateX(-absoluteMove / 2 + move);
                } else {
                    target.setTranslateX(absoluteMove / 2 - move);
                }
            }
        }.start();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
