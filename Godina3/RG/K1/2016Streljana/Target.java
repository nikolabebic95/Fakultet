/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package rg2016k1;

import javafx.geometry.Bounds;
import javafx.scene.Group;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.text.Font;
import javafx.scene.text.Text;

/**
 *
 * @author Nikola
 */
public class Target extends Group {
        
    public static final int NUM_OF_CIRCLES = 7;
    public static final double STEP = 40;
    
    public static final Color MIDDLE = Color.RED;
    public static final Color EVEN = Color.BLACK;
    public static final Color ODD = Color.WHITE;
    
    public static final Font FONT = new Font("Arial Bold", 16);
    
    public static final int[] points = new int[NUM_OF_CIRCLES]; 
    static {
        points[0] = 150;
        points[1] = 120;
        points[2] = 100;
        points[3] = 80;
        points[4] = 60;
        points[5] = 40;
        points[6] = 20;
    }
    
    public static final int NUM_OF_CLICKS = 5;
    
    private int clicksLeft = NUM_OF_CLICKS;
    private int score = 0;
    
    public int getScore() {
        return score;
    }
    
    private void initializeMiddle() {
        Circle circle = new Circle(0, 0, STEP / 2);
        circle.setFill(MIDDLE);
        getChildren().add(circle);
    }
    
    private void initializeCircles() {
        for (int i = NUM_OF_CIRCLES - 1; i > 0; i--) {
            double radius = STEP / 2 + STEP * i;
            Circle circle = new Circle(0, 0, radius);
            if (i % 2 == 0) {
                circle.setFill(EVEN);
            } else {
                circle.setFill(ODD);
            }
            
            getChildren().add(circle);
        }
    }
    
    private void initializePoints() {
        
        Text middleText = new Text(Integer.toString(points[0]));
        middleText.setFill(EVEN);
        middleText.setFont(FONT);
        getChildren().add(middleText);
        
        Bounds middleBounds = middleText.getBoundsInParent();
        
        double middleLeft = middleBounds.getMinX();
        double middleRight = middleBounds.getMaxX();
        double middleUp = middleBounds.getMinY();
        double middleDown = middleBounds.getMaxY();
        
        middleText.setTranslateX(middleText.getTranslateX() - (middleRight - middleLeft) / 2);
        middleText.setTranslateY(middleText.getTranslateY() + (middleDown - middleUp) / 4);
        
        for (int i = 1; i < points.length; i++) {
            Text text = new Text(Integer.toString(points[i]));
            text.setFill(MIDDLE);
            text.setFont(FONT);
            getChildren().add(text);
            
            Bounds bounds = text.getBoundsInParent();
            
            double left = bounds.getMinX();
            double right = bounds.getMaxX();
            double up = bounds.getMinY();
            double down = bounds.getMaxY();
            
            text.setTranslateX(text.getTranslateX() + STEP * i - (right - left) / 2);
            text.setTranslateY(text.getTranslateY() + (down - up) / 4);
        }
    }
    
    void updateScoreInMain() {
        Main.result.setText("Result: " + score);
        Main.clicksLeft.setText("Clicks left: " + clicksLeft);
    }
    
    {
        initializeCircles();
        initializeMiddle();
        initializePoints();
    }
    
    {
        this.setOnMousePressed((MouseEvent event) -> {
            if (clicksLeft == 0) {
                return;
            }
            
            double x = event.getX();
            double y = event.getY();
            
            clicksLeft--;
            
            double radius = Math.sqrt(x * x + y * y);
            
            if (radius < STEP / 2) {
                score += points[0];
            } else {
                for (int i = 1; i < points.length; i++) {
                    if (radius < STEP / 2 + i * STEP) {
                        score += points[i];
                        break;
                    }
                }
            }
            
            updateScoreInMain();
        });
    }
}
