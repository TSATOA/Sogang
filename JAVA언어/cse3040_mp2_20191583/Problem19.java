package mp9;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collections;

class BookInfo implements Comparable<BookInfo>{
	private int seq;
	private String bookName;
	private String authorName;
	private String price;
	public BookInfo(int seq,String bookName,String authorName,String price) {
		this.seq=seq;
		this.bookName=bookName;
		this.authorName=authorName;
		this.price = price;
	}
	public int getSeq() {return this.seq;}
	public String getBookName() {return this.bookName;}
	public String getAuthorName() {return this.authorName;}
	public String getPrice() {return this.price;}
	
	public int compareTo(BookInfo e) {
		if(this.seq>e.getSeq()) return -1;
		else return 1;
	}
	
	public String toString() {
		return ("#" + this.seq + " " + this.bookName + ", "+ this.authorName + ", " + this.price);
	}
}

class BookReader{
	static ArrayList<BookInfo> readBooks(String a){
		ArrayList<String> lines = new ArrayList<String>();
		ArrayList<BookInfo> res = new ArrayList<>();
		URL url = null;
		BufferedReader input = null;
		String address = a;
		String line = "";
		try {
			url = new URL(address);
			input = new BufferedReader(new InputStreamReader(url.openStream()));
			while((line=input.readLine()) != null) {
				if(line.trim().length() > 0) lines.add(line);
			}
			input.close();
		} catch(Exception e) {
			e.printStackTrace();
		}
		
		int rank = 1;
		int status = 0;
		String authorName="";
		String bookName="";
		for(int i=0; i<lines.size(); i++) {
			String l = lines.get(i);
			if(status == 0) {
				if(l.contains("div class=\"col-lg-9 product-info-listView\"")) status = 1;
			} else if(status == 1) {
				if(l.contains("div class=\"product-shelf-title pr-m\"")) status = 2;
			} else if(status == 2) {
				if(l.contains("href")) {
					int begin = l.indexOf("\">") + 2;
					int end = l.indexOf("</a>");
					bookName = l.substring(begin, end);	
					status = 3;
				}
			}else if(status == 3) {
				if(l.contains("a href")) {
					int begin = l.indexOf("<a href=");
					String aaa = l.substring(begin);
					begin = aaa.indexOf("\">") + 2;
					int end = aaa.indexOf("</a>");
					authorName = aaa.substring(begin,end);
					status = 4;
				}
			}else if(status == 4) {
				if(l.contains("span class=\"current\"")) status = 5;
			}else if(status == 5) {
				if(l.contains("href")) {
					int begin = l.indexOf("\">")+2;
					int end = l.indexOf("</a>");
					String price = l.substring(begin,end);
					res.add(new BookInfo(rank,bookName,authorName,price));
					status = 0;
					rank++;
				}
			}
		}
		
		
		return res;
	}
}

public class Problem19 {
	public static void main(String[] args) {
		ArrayList<BookInfo> books;
		books = BookReader.readBooks("https://www.barnesandnoble.com/b/books/_/N-1fZ29Z8q8");
		Collections.sort(books);
		for(int i=0; i<books.size(); i++) {
		BookInfo book = books.get(i);
		System.out.println(book);
		}
	}
}
