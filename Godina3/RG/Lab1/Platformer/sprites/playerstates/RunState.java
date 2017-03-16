/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sprites.playerstates;

import sprites.Player;

/**
 *
 * @author mile
 */
public class RunState extends State {

    public RunState(Player player) {
        super(player);
    }

    @Override
    public void jumpPressed() {
        super.jumpPressed();
        player.jump();
    }

    @Override
    public void leftReleased() {
        super.leftReleased();
        if (player.isFaceLeft()) {
            player.stop();
        }
    }

    @Override
    public void leftPressed() {
        super.leftPressed();
        player.faceLeft();
        player.run();
    }

    @Override
    public void rightReleased() {
        super.rightReleased();
        if (player.isFaceRight()) {
            player.stop();
        }
    }

    @Override
    public void rightPressed() {
        super.rightPressed();
        player.faceRight();
        player.run();
    }

    @Override
    public void move() {
        player.setTranslateX(player.getTranslateX() + player.getVelocity());
    }

}
