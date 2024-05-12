package cse3040fp;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;


public class Server {
	/*å�� ����, ����, ������ ��� �����ϴ� Element(�߰��� ���� �� ��ȯ�� �����ϴ�)*/
	class Element implements Comparable<Element>{
		private String title;
		private String author;
		private String borrower;
		public Element(String a,String b,String c) {
			this.title = a;
			this.author = b;
			this.borrower = c;
		}
		public String getTitle() {
			return this.title;
		}
		public String getAuthor() {
			return this.author;
		}
		public String getBorrower() {
			return this.borrower;
		}
		public void exchangeBorrower(String a) {
			this.borrower = a;
		}
		public int compareTo(Element e) {
			if(this.title.toLowerCase().compareTo(e.getTitle().toLowerCase())<0) return -1;
			if(this.title.toLowerCase().compareTo(e.getTitle().toLowerCase())>0) return 1;
			return this.title.toLowerCase().compareTo(e.getTitle().toLowerCase());
		}
	}
	/*books.txt���� ������ �д´�.*/
	class ElementReader{
		public ArrayList<Element> readElements(String a){
			ArrayList<Element> li = new ArrayList<>();
			BufferedReader br;
			String line;
			String ti;
			String au;
			String bo;
			int idx;
			try {
				br = new BufferedReader(new FileReader(a));
			}catch(FileNotFoundException e) {
				return null;
			}
			while(true) {
				try {
					line = br.readLine();
					if(line == null) break;
					idx = line.indexOf("\t");
					ti = line.substring(0,idx);
					au = line.substring(idx+1);
					idx = au.indexOf("\t");
					bo = au.substring(idx+1);
					au = au.substring(0,idx);
					li.add(new Element(ti,au,bo));
				}catch(IOException e) {
					e.printStackTrace();
				}
			}
			try {
				br.close();
			}catch(IOException e) {
				e.printStackTrace();
			}
			return li;
		}
	}
	/*������ ����ڸ� HashMap���� �����ϸ鼭 �������� ��� �����ϴ�.*/
	HashMap<String,DataOutputStream> clients;
	Server(){
		clients = new HashMap<>();
		Collections.synchronizedMap(clients);
	}
	/*���� ������ �����ߴ�. ������ ���������� ����Ǹ� �ȳ� ������ ���.*/
	public void start(int a) {
		ServerSocket serverSocket = null;
		Socket socket = null;
		try {
			serverSocket = new ServerSocket(a);
			System.out.println("server has started.");
			while(true) {
				socket = serverSocket.accept();
				ServerReceiver thread = new ServerReceiver(socket);
				thread.start();
			}
		}catch(Exception e) {
			e.printStackTrace();
		}
	}
	/*name�̶�� ����ڿ��� msg�� �����Ѵ�.*/
	void send(String name,String msg) {
		try {
			DataOutputStream out = (DataOutputStream)clients.get(name);
			out.writeUTF(msg); 	
		}catch(IOException e) {}
		
		
	}
	/*main�Լ��� Server�� ������ ����Ѵ�. argument�� port�� �Է� �ȵǸ� ����ȴ�.*/
	public static void main(String args[]) {
		if(args.length !=1) {
			System.out.print("Please give the port number as an argument.");
			System.exit(0);
		}
		new Server().start(Integer.parseInt(args[0]));
	}
	/*socket�� ����� ���� �߿��� run�� ���ǵǾ��ִ�.*/
	class ServerReceiver extends Thread{
		Socket socket;
		DataInputStream in;
		DataOutputStream out;	
		ServerReceiver(Socket socket){
			this.socket = socket;
			try {
				in = new DataInputStream(socket.getInputStream());
				out = new DataOutputStream(socket.getOutputStream());
			}catch(IOException e) {}
		}
		/*�������� ��� ó���� run���� ó���Ǿ���.(books.txt������ ������ �а� ������Ʈ�ϸ� ����� ����)*/
		public void run() {
			String name = "";
			String com = "";
			String author = "";
			String title = "";
			String guide = "[available commands]\nadd: add a new book to the list of books.\nborrow: borrow a book from the library.\nreturn: return a book to the library.\ninfo: show list of books I am currently borrowing.\nsearch: search for books.\n";
			int cnt;
			/*books.txt������ �д´�.*/
			ElementReader re = new ElementReader();
			ArrayList<Element> list = re.readElements("books.txt");
			Collections.sort(list);
			try {
				/*Client�κ��� �̸��� �Էµǰ� Server������ ������ ����� ���� ǥ�õȴ�.*/
				name = in.readUTF();
				clients.put(name, out);
				send(name,"Hello "+name+"\n");
				System.out.println("Current number of users: " + clients.size());			
				while(in!=null) {
					cnt = 0;
					/*Client�κ��� ����� �о�´�.*/
					send(name,name+">> ");
					com = in.readUTF();
					/*add����� �����Ѵ�.(��κ� ����� �����ϱ� �� books.txt������ ���������� ������Ʈ �ް� �����Ѵ�.)*/
					if(com.equals("add")) {
						list = re.readElements("books.txt");
						Collections.sort(list);
						send(name,"add-title> ");
						title = in.readUTF();
						if(title.length()==0) continue;
						send(name,"add-author> ");
						author = in.readUTF();
						if(author.length()==0) continue;
						
						for(int i=0;i<list.size();i++) {
							if(list.get(i).getTitle().toLowerCase().equals(title.toLowerCase())) {
								cnt++;
							}
						}
						if(cnt==0) {
							list.add(new Element(title,author,"-"));
							Collections.sort(list);
							send(name,"A new book added to the list.\n");
							FileWriter fw = new FileWriter("books.txt",false);
							BufferedWriter bw = new BufferedWriter(fw);
							for(int i=0;i<list.size();i++) {
								bw.write(list.get(i).getTitle()+"\t"+list.get(i).getAuthor()+"\t"+list.get(i).getBorrower());
								bw.newLine();
							}							
							bw.close();
						}else {
							send(name,"The book already exists in the list\n");
						}			
					}else if(com.equals("borrow")) {  /*borrow ����� �����Ѵ�.*/
						list = re.readElements("books.txt");
						Collections.sort(list);
						cnt=-1;
						send(name,"borrow-title> ");
						title = in.readUTF();
						if(title.length()==0) continue;				
						for(int i=0;i<list.size();i++) {
							if(list.get(i).getTitle().toLowerCase().equals(title.toLowerCase())) {
								cnt = i;
								break;
							}
						}
						if(cnt!=-1) {
							if(list.get(cnt).getBorrower().equals("-")) {
								send(name,"You borrowed a book. - "+list.get(cnt).getTitle()+"\n"); 
								list.get(cnt).exchangeBorrower(name);
								FileWriter fw = new FileWriter("books.txt",false);
								BufferedWriter bw = new BufferedWriter(fw);
								for(int i=0;i<list.size();i++) {
									bw.write(list.get(i).getTitle()+"\t"+list.get(i).getAuthor()+"\t"+list.get(i).getBorrower());
									bw.newLine();
								}							
								bw.close();
							}else {
								send(name,"The book is not available\n");
							}
						}else {
							send(name,"The book is not available\n");
						}
					}else if(com.equals("return")) {  /*return ����� �����Ѵ�.*/
						list = re.readElements("books.txt");
						Collections.sort(list);
						cnt=-1;
						send(name,"return-title> ");
						title = in.readUTF();
						if(title.length()==0) continue;
						for(int i=0;i<list.size();i++) {
							if(list.get(i).getTitle().toLowerCase().equals(title.toLowerCase())) {
								cnt = i;
								break;
							}
						}
						if(cnt!=-1) {
							if(list.get(cnt).getBorrower().toLowerCase().equals(name.toLowerCase())) {
								send(name,"You returned a book. - "+list.get(cnt).getTitle()+"\n");
								list.get(cnt).exchangeBorrower("-");
								FileWriter fw = new FileWriter("books.txt",false);
								BufferedWriter bw = new BufferedWriter(fw);
								for(int i=0;i<list.size();i++) {
									bw.write(list.get(i).getTitle()+"\t"+list.get(i).getAuthor()+"\t"+list.get(i).getBorrower());
									bw.newLine();
								}							
								bw.close();
							}else {
								send(name,"You did not borrow the book.\n");
							}
						}else {
							send(name,"You did not borrow the book.\n");
						}
					}else if(com.equals("info")) {  /*info ����� �����Ѵ�.*/
						list = re.readElements("books.txt");
						Collections.sort(list);
						for(int i=0;i<list.size();i++) {
							if(list.get(i).getBorrower().toLowerCase().equals(name.toLowerCase())) cnt++;
						}
						send(name,"You are currently borrowing "+ cnt + " books:\n");
						cnt = 1;
						for(int i=0;i<list.size();i++) {
							if(list.get(i).getBorrower().toLowerCase().equals(name.toLowerCase())) {
								send(name,cnt + ". " + list.get(i).getTitle() + ", " + list.get(i).getAuthor() + "\n");
								cnt++;
							}
						}
					}else if(com.equals("search")) {  /*search ����� �����Ѵ�.*/
						list = re.readElements("books.txt");
						Collections.sort(list);
						while(true) {
							send(name,"search-string> ");
							title = in.readUTF();
							if(title.length()==0) break;
							if(title.length()>2) break;
							send(name,"Search string must be longer than 2 characters.\n");
						}
						if(title.length()==0) continue;
						for(int i=0;i<list.size();i++) {
							if(list.get(i).getTitle().toLowerCase().indexOf(title.toLowerCase())!=-1) {
								cnt++;
								continue;
							}
							if(list.get(i).getAuthor().toLowerCase().indexOf(title.toLowerCase())!=-1) {
								cnt++;
								continue;
							}
						}
						send(name,"Your search matched "+ cnt + " results.\n");
						cnt = 1;
						for(int i=0;i<list.size();i++) {
							if(list.get(i).getTitle().toLowerCase().indexOf(title.toLowerCase())!=-1 || list.get(i).getAuthor().toLowerCase().indexOf(title.toLowerCase())!=-1) {
								send(name,cnt + ". "+ list.get(i).getTitle() + ", " + list.get(i).getAuthor() + "\n");
								cnt++;
							}
						}
						
						
					}else {
						/*��ɿ� ���Ե��� �ʴ� ����� �Էµ� ��� guideâ�� �����Ѵ�.*/
						send(name,guide);
					}
					
				}
			}catch(IOException e) {
				
			}finally {
				/*������ �̿��ڰ� ������ clients���� �����ϰ� Serverâ�� ��������� �̸��� ���� ����� ���� ����Ѵ�.*/
				clients.remove(name);
				System.out.println("["+name+"]"+" has disconnected.");
				System.out.println("Current number of users: " + clients.size());
			}
		}
	}
}
