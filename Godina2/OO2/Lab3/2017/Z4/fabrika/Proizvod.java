/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fabrika;

/**
 *
 * @author Mica
 */
public class Proizvod {
    private static int ID=0;
    private final int id=ID++;
    
    @Override
    public String toString(){
        return ""+id;
    }
}
