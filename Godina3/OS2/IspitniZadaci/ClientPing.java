//==========================================================================================================//
//==========================================================================================================//
//
//  Nikola Bebic - bn140314d@student.etf.rs
//
//  OS2 
//  Socket
//  Klijentski proces
//
//==========================================================================================================//
//==========================================================================================================//
//
//  Zadatak:
//
//  Februar 2015.
//  Korišćenjem koncepta priključnice (socket), na jeziku Java napisati kod klijentskog procesa
//  koji šalje serveru poruku „ping“ i čeka odgovor od servera i ispisuje ga, pa raskida vezu
// 
//==========================================================================================================//
//==========================================================================================================//

import java.io.*;
import java.net.*;
import java.util.logging.*;

public class ClientPing {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("1.1.1.1", 4000);
            OutputStream os = socket.getOutputStream();
            PrintWriter pout = new PrintWriter(os, true);
            pout.println("ping");

            InputStream is = socket.getInputStream();
            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            String message;
            message = br.readLine();
            System.out.println(message);

            socket.close();
        } catch (IOException e) {
            Logger.getLogger(ClientPing.class.getName()).log(Level.SEVERE, null, e);
        }
    }
}
