/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sprites;

import javafx.event.EventHandler;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;
import sprites.playerstates.DeadState;
import sprites.playerstates.IdleState;
import sprites.playerstates.JumpState;
import sprites.playerstates.RunState;
import sprites.playerstates.State;

/**
 *
 * @author mile
 */
public class Player extends Sprite implements EventHandler<KeyEvent> {

    private static final Paint IDLE_COLOR = Color.YELLOW;
    private static final Paint RUN_COLOR = Color.GREEN;
    private static final Paint JUMP_COLOR = Color.RED;
    private static final Paint DEAD_COLOR = Color.PURPLE;

    private static final Paint EYE_COLOR = Color.BLACK;

    private static final double PLAYER_VELOCITY = 7.5f;

    private State state;
    private boolean right = true;
    private double velocity = PLAYER_VELOCITY;

    private Circle body;
    private Circle eye;

    public Player() {
        state = new IdleState(this);
        getChildren().clear();
        body = new Circle(0, 0, 40);
        body.setFill(IDLE_COLOR);
        eye = new Circle(15, 0, 10);
        eye.setFill(EYE_COLOR);
        getChildren().add(body);
        getChildren().add(eye);
    }

    public double getVelocity() {
        if (isFaceRight()) {
            return velocity;
        } else {
            return -velocity;
        }
    }

    public void run() {
        state = new RunState(this);
        body.setFill(RUN_COLOR);
    }

    public void faceRight() {
        if (isFaceLeft()) {
            setScaleX(-getScaleX());
        }
        right = true;
    }

    public void faceLeft() {
        if (isFaceRight()) {
            setScaleX(-getScaleX());
        }
        right = false;
    }

    public void jump() {
        state = new JumpState(this);
        body.setFill(JUMP_COLOR);
    }

    public void stop() {
        state = new IdleState(this);
        body.setFill(IDLE_COLOR);
    }

    public void die() {
        state = new DeadState(this);
        body.setFill(DEAD_COLOR);
    }

    public boolean isFaceRight() {
        return right;
    }

    public boolean isFaceLeft() {
        return !right;
    }

    @Override
    public void update() {
        state.move();
    }

    // executed on keyboard input to perform particular actions
    @Override
    public void handle(KeyEvent event) {
        if (event.getCode() == KeyCode.RIGHT && event.getEventType() == KeyEvent.KEY_PRESSED) {
            state.rightPressed();
        } else if (event.getCode() == KeyCode.RIGHT && event.getEventType() == KeyEvent.KEY_RELEASED) {
            state.rightReleased();
        } else if (event.getCode() == KeyCode.LEFT && event.getEventType() == KeyEvent.KEY_PRESSED) {
            state.leftPressed();
        } else if (event.getCode() == KeyCode.LEFT && event.getEventType() == KeyEvent.KEY_RELEASED) {
            state.leftReleased();
        } else if (event.getCode() == KeyCode.SPACE && event.getEventType() == KeyEvent.KEY_PRESSED) {
            state.jumpPressed();
        } else if (event.getCode() == KeyCode.SPACE && event.getEventType() == KeyEvent.KEY_RELEASED) {
            state.jumpReleased();
        } else if (event.getCode() == KeyCode.DIGIT1 && event.getEventType() == KeyEvent.KEY_PRESSED) {
            
        } else if (event.getCode() == KeyCode.DIGIT2 && event.getEventType() == KeyEvent.KEY_PRESSED) {
            
        } else if (event.getCode() == KeyCode.DIGIT3 && event.getEventType() == KeyEvent.KEY_PRESSED) {
            
        }
    }

    public void takeHit() {
        die();
    }
}
