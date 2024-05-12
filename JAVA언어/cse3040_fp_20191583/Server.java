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
	/*책의 제목, 저자, 빌려간 사람 저장하는 Element(추가로 정렬 및 변환도 가능하다)*/
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
	/*books.txt에서 정보를 읽는다.*/
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
	/*도서관 사용자를 HashMap으로 선언하면서 여러명이 사용 가능하다.*/
	HashMap<String,DataOutputStream> clients;
	Server(){
		clients = new HashMap<>();
		Collections.synchronizedMap(clients);
	}
	/*서버 시작을 정리했다. 서버가 성공적으로 연결되면 안내 문구가 뜬다.*/
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
	/*name이라는 사용자에게 msg를 전달한다.*/
	void send(String name,String msg) {
		try {
			DataOutputStream out = (DataOutputStream)clients.get(name);
			out.writeUTF(msg); 	
		}catch(IOException e) {}
		
		
	}
	/*main함수로 Server의 시작을 담당한다. argument로 port가 입력 안되면 종료된다.*/
	public static void main(String args[]) {
		if(args.length !=1) {
			System.out.print("Please give the port number as an argument.");
			System.exit(0);
		}
		new Server().start(Integer.parseInt(args[0]));
	}
	/*socket을 만들고 가장 중요한 run이 정의되어있다.*/
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
		/*데이터의 모든 처리는 run에서 처리되었다.(books.txt파일의 정보를 읽고 업데이트하며 명령을 수행)*/
		public void run() {
			String name = "";
			String com = "";
			String author = "";
			String title = "";
			String guide = "[available commands]\nadd: add a new book to the list of books.\nborrow: borrow a book from the library.\nreturn: return a book to the library.\ninfo: show list of books I am currently borrowing.\nsearch: search for books.\n";
			int cnt;
			/*books.txt파일을 읽는다.*/
			ElementReader re = new ElementReader();
			ArrayList<Element> list = re.readElements("books.txt");
			Collections.sort(list);
			try {
				/*Client로부터 이름이 입력되고 Server차에는 접속한 사람의 수가 표시된다.*/
				name = in.readUTF();
				clients.put(name, out);
				send(name,"Hello "+name+"\n");
				System.out.println("Current number of users: " + clients.size());			
				while(in!=null) {
					cnt = 0;
					/*Client로부터 명령을 읽어온다.*/
					send(name,name+">> ");
					com = in.readUTF();
					/*add명령을 수행한다.(대부분 명령을 수행하기 전 books.txt파일의 변동사항을 업데이트 받고 시작한다.)*/
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
					}else if(com.equals("borrow")) {  /*borrow 명령을 수행한다.*/
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
					}else if(com.equals("return")) {  /*return 명령을 수행한다.*/
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
					}else if(com.equals("info")) {  /*info 명령을 수행한다.*/
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
					}else if(com.equals("search")) {  /*search 명령을 수행한다.*/
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
						/*명령에 포함되지 않는 명령이 입력될 경우 guide창을 송출한다.*/
						send(name,guide);
					}
					
				}
			}catch(IOException e) {
				
			}finally {
				/*도서관 이용자가 나가면 clients에서 제거하고 Server창에 나간사람의 이름과 남은 사람의 수를 출력한다.*/
				clients.remove(name);
				System.out.println("["+name+"]"+" has disconnected.");
				System.out.println("Current number of users: " + clients.size());
			}
		}
	}
}
