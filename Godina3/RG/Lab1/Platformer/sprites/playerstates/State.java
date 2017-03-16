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
public abstract class State {

    protected Player player;
    
    public State(Player player){
        this.player = player;
    }
    
    public void rightPressed() {
    }

    public void rightReleased() {
    }

    public void leftPressed() {
    }

    public void leftReleased() {
    }

    public void jumpPressed() {
    }

    public void jumpReleased() {
    }
    
    public void move(){
    }
}
