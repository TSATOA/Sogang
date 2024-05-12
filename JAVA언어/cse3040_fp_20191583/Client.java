package cse3040fp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ConnectException;
import java.net.Socket;
import java.util.Scanner;

public class Client {
	/*Client���� �Էµ� ������ ������ �����Ѵ�.*/
	static class ClientSender extends Thread{
		Socket socket;
		DataOutputStream out;
		String name;
		Scanner scanner;
		ClientSender(Socket socket, String name, Scanner sc){
			this.socket = socket;
			this.scanner = sc;
			try {
				out = new DataOutputStream(socket.getOutputStream());
				this.name = name;
			}catch(Exception e) {}
		}
		@SuppressWarnings("all")
		/*����� �Է¹ް� server�� �����Ѵ�.*/
		public void run() {
			String com = "";
			String title = "";
			String author = "";
			String string = "";
			try {
				if(out!=null) {
					out.writeUTF(name );
				}
				while(out!=null) {
					//scanner.nextLine();
					com = scanner.nextLine();
					out.writeUTF(com);
					if(com.equals("add")) {
						title = scanner.nextLine();
						out.writeUTF(title);
						if(title.length()==0) continue;
						author = scanner.nextLine();
						out.writeUTF(author);
					}else if(com.equals("borrow")) {
						title = scanner.nextLine();
						out.writeUTF(title);
					}else if(com.equals("return")) {
						title = scanner.nextLine();
						out.writeUTF(title);
					}else if(com.equals("search")) {
						string = scanner.nextLine();
						out.writeUTF(string);
					}
				}
			}catch(IOException e) {}
		}
	}
	/*Server�κ��� ���۵� ������ �ް� ����Ѵ�.*/
	static class ClientReceiver extends Thread{
		Socket socket;
		DataInputStream in;
		
		ClientReceiver(Socket socket){
			this.socket = socket;
			try {
				in = new DataInputStream(socket.getInputStream());
			}catch(IOException e) {}
		}
		public void run() {
			while(in!=null) {
				try {
					
					System.out.print(in.readUTF());
				}catch(IOException e) {}
			}
		}
	}
	public static void main(String args[]) {
		/*IP�ּҿ� port�� arguments�� �Էµ��� ������ �����Ѵ�.*/
		if(args.length !=2) {
			System.out.print("Please give the IP address and port number as arguments.");
			System.exit(0);
		}
		try {
			Socket socket = new Socket(args[0],Integer.parseInt(args[1]));
			Scanner sc = new Scanner(System.in);
			String name = "";
			int a;
			/*������� �̸��� �Է¹޴´�.*/
			while(true) {
				System.out.print("Enter userID>> ");
				a=1;
				name = sc.nextLine();
				if(name.indexOf(" ")!=-1 || name.length()==0) {
					System.out.println("UserID must be a single word with lowercase alphabets and numbers.");
					continue;
				}
				for(int i=0;i<name.length();i++) {
					if((name.charAt(i)<'0')||((name.charAt(i)>'9')&&(name.charAt(i)<'a'))||(name.charAt(i)>'z')) {
						System.out.println("UserID must be a single word with lowercase alphabets and numbers.");
						a=0;
						break;
					}
				}
				if(a!=1) continue;
				else break;
			}
			
			/*Thread�� �����Ų��.*/
			Thread sender = new Thread(new ClientSender(socket,name,sc));
			Thread receiver = new Thread(new ClientReceiver(socket));
			sender.start();
			receiver.start();
		}catch(ConnectException ce) {
			System.out.print("Connection establishment failed.");
			System.exit(0);
		}catch(Exception e) {
			
		}
		
	}
}
