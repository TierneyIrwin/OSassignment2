import java.net.*;
import java.io.*;

public class HaikuServer
{
	public static void main(String[] args){
		try{
			ServerSocket sock = new ServerSocket(5575);

			while(true){
				Socket client = sock.accept();

				PrintWriter pout = new PrintWriter(client.getOutputStream(),true);
			//	pout.println("haiku here");
				client.close();
			}
		}catch(IOException ioe){
			System.err.println(ioe);
		}
	}
}
