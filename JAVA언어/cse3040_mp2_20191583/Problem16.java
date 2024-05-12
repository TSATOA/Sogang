package mp6;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

class Element implements Comparable<Element>{
	private String fruit;
	private Double price;
	public Element(String a,double b) {
		this.fruit = a;
		this.price = b;
	}
	public String getFruit() {
		return this.fruit;
	}
	public double getPrice() {
		return this.price;
	}
	public int compareTo(Element e) {
		if(this.price<e.getPrice()) return -1;
		if(this.price>e.getPrice()) return 1;
		return this.fruit.compareTo(e.getFruit());
	}
	public String toString() {
		return (this.fruit +" "+ this.price);
	}
}

class ElementReader{
	static ArrayList<Element> readElements(String a) {
		ArrayList<Element> li = new ArrayList<>();
		BufferedReader br;
		String line;
		int idx;
		String Fru;
		double cost;
		try {
			br = new BufferedReader(new FileReader(a));
		}catch(FileNotFoundException e) {
			return null;
		}
		while(true) {
			try {
				line = br.readLine();
				if(line == null) break;
				idx = line.indexOf(" ");
				Fru = line.substring(0,idx);
				cost = Double.parseDouble(line.substring(idx+1));
				li.add(new Element(Fru,cost));
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

public class Problem16 {

	public static void main(String args[]) {
		ArrayList<Element> list = ElementReader.readElements("input.txt");
		if(list == null) {
			System.out.println("Input file not found.");
			return;
		}
		Collections.sort(list);
		Iterator<Element> it = list.iterator();
		while(it.hasNext()) System.out.println(it.next());
	}

}
