package main;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import cameras.Camera;
import java.util.LinkedList;
import java.util.List;
import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.stage.Stage;
import sprites.Background;
import sprites.Enemy;
import sprites.Floor;
import sprites.Player;

/**
 *
 * @author mile
 */
public class Main extends Application {

    public static final int WINDOW_WIDTH = 1600;
    public static final int WINDOW_HEIGHT = 900;

    public static final int FLOOR_WIDTH = WINDOW_WIDTH;
    public static final int FLOOR_HEIGHT = 50;

    public static final int ENEMY_WIDTH = 100;
    public static final int ENEMY_HEIGHT = 80;

    public static final String TITLE = "Platformer";

    public static final double ENEMY_SPEED = 2.5f;

    private Player player;
    private List<Enemy> enemies;

    private static Main instance;
    
    private double time = 0; // game time in seconds

    private Camera camera; // camera used for applying transformations
    
    // returns the instance of the game (Main class)
    public static Main getInstance(){
        return instance;
    }
    
    public Camera getCamera(){
        return camera;
    }
    
    public double getTime() {
        return time;
    }

    
    // called once per frame to update game state
    private void update() {
        player.update();
        enemies.forEach(e -> e.update());

        // checking collision between player and enemies
        enemies.forEach(e -> {
            if (player.getBoundsInParent().intersects(e.getBoundsInParent())) {
                player.takeHit();
            }
        });
        time += 1. / 60;
    }

    @Override
    public void start(Stage primaryStage) {
        instance = this;
        
        enemies = new LinkedList<>();
        Background bg = new Background(WINDOW_WIDTH, WINDOW_HEIGHT);

        Floor floor = new Floor(FLOOR_WIDTH, FLOOR_HEIGHT);
        floor.setTranslateY(WINDOW_HEIGHT);

        camera = new Camera();
        camera.getChildren().add(floor);

        Group sprites = new Group();
        camera.getChildren().add(sprites);

        // making 100 enemies and adding them to the scene
        for (int i = 0; i < 100; i++) {
            Enemy enemy = new Enemy(ENEMY_SPEED);
            enemy.setTranslateX((1 + i) * 800);
            enemy.setTranslateY(WINDOW_HEIGHT - FLOOR_HEIGHT - ENEMY_HEIGHT / 2);
            sprites.getChildren().add(enemy);
            enemies.add(enemy);
        }

        player = new Player();
        player.setTranslateX(100);
        player.setTranslateY(WINDOW_HEIGHT - FLOOR_HEIGHT - ENEMY_HEIGHT / 2);
        sprites.getChildren().add(player);

        Group root = new Group();
        root.getChildren().add(bg);
        root.getChildren().add(camera);

        Scene scene = new Scene(root, WINDOW_WIDTH, WINDOW_HEIGHT);
        scene.setOnKeyPressed(player);
        scene.setOnKeyReleased(player);
        primaryStage.setTitle(TITLE);
        primaryStage.setScene(scene);
        primaryStage.show();
        primaryStage.setResizable(false);

        // calling update once every frame
        new AnimationTimer() {
            @Override
            public void handle(long currentNanoTime) {
                update();
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
