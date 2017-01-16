//==========================================================================================================//
//==========================================================================================================//
//
//  Nikola Bebic - bn140314d@student.etf.rs
//
//  OS2 
//  Socket
//  Serverski proces
//
//==========================================================================================================//
//==========================================================================================================//
//
//  Zadatak:
//
//  Jul 2015.
//  Korišćenjem koncepta priključnice (socket), na jeziku Java napisati kod serverskog procesa
//  koji na svaki novi klijentski zahtev odgovara naizmenično porukom „Yes“ i „No“, pa raskida vezu.
// 
//==========================================================================================================//
//==========================================================================================================//

import java.io.*;
import java.net.*;
import java.util.logging.*;

public class ServerYesNo {
    public static void main(String[] args) {
        try {
            ServerSocket server = new ServerSocket(4000);
            boolean messageYes = true;
            while (true) {
                Socket client = server.accept();
                PrintWriter pout = new PrintWriter(client.getOutputStream());
                pout.println(messageYes ? "Yes" : "No");
                messageYes = !messageYes;
                client.close();
            }
        } catch (IOException e) {
            Logger.getLogger(ServerYesNo.class.getName()).log(Level.SEVERE, null, e);
        }
    }
}
