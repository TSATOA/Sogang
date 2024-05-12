package mp10;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;



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
	static ArrayList<BookInfo> readBooksJsoup(String a){
		ArrayList<BookInfo> res = new ArrayList<>();
		String url =  a;
		Document doc = null;
		try {
			doc = Jsoup.connect(url).get();
		} catch(IOException e) {
			System.out.println(e.getMessage());
		}
		Elements bestsellers = doc.select("div.col-lg-9.product-info-listView");
		Elements titles = bestsellers.select("div.product-shelf-title.pr-m");
		Elements bookti = titles.select("h3.product-info-title");
		Elements booktitles = bookti.select("a[title]");
		
		Elements authors = bestsellers.select("div.product-shelf-author.contributors");
		
		
		Elements bookauthors = new Elements();
		
		
		for(int i=0;i<booktitles.size();i++) {
			bookauthors.add(authors.eq(i).select("a[href]").first());
		}
		
		
		
		Elements totalprices = bestsellers.select("div.product-shelf-pricing.mt-s.mb-s");
		Elements totalprice = totalprices.select("span.current");
		Elements bookprice = totalprice.select("a[title]");
		
		
		
		for(int i=0;i<booktitles.size();i++) {
			res.add(new BookInfo(i+1,booktitles.eq(i).text(),bookauthors.eq(i).text(),bookprice.eq(i).text()));
		}
		
		return res;
	}
}



public class Problem20 {

	public static void main(String[] args) {
		ArrayList<BookInfo> books;
		books = BookReader.readBooksJsoup("https://www.barnesandnoble.com/b/books/_/N-1fZ29Z8q8");
		Collections.sort(books);
		for(int i=0; i<books.size(); i++) {
		BookInfo book = books.get(i);System.out.println(book);
		}
		
	}

}
