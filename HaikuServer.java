import java.net.*;
import java.io.*;

public class HaikuServer
{
	public static void main(String[] args){
		try{
			ServerSocket sock = new ServerSocket(55755);
			
			while(true){
				Socket client = sock.accept();

				PrintWriter pout = new PrintWriter(client.getOutputStream(),true);
				pout.println("In the twilight rain\n these brilliant-hued hibiscus\n A lovely sunset.\n");
				pout.close();
				client.close();
			}
		}catch(IOException ioe){
			System.err.println(ioe);
		}
	}
}
