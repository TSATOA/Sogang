package mp4;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

class ItemReader{
	static boolean fileToBox(String a, FruitBox<Fruit> box) {
		BufferedReader br;
		String line;
		int idx;
		String Fru;
		double cost;
		try {
			br = new BufferedReader(new FileReader(a));
		}catch(FileNotFoundException e) {
			System.out.println("Input file not found.");
			return false;
		}
		while(true) {
			try {
				line = br.readLine();
				if(line == null) break;
				idx = line.indexOf(" ");
				Fru = line.substring(0,idx);
				cost = Double.parseDouble(line.substring(idx+1));
				box.add(new Fruit(Fru,cost));
			}catch(IOException e) {
				e.printStackTrace();
			}
		}
		try {
			br.close();
		}catch(IOException e) {
			e.printStackTrace();
		}
		return true;
	}
}
class Fruit{
	private String fruit;
	private double cost;
	public Fruit(String a,double b) {
		this.fruit = a;
		this.cost = b;
	}
	public String getFruit() {
		return this.fruit;
	}
	public double getCost() {
		return this.cost;
	}
}

class FruitBox<T>{
	private ArrayList<Fruit> list = new ArrayList<>();
	void add(Fruit item) {
		list.add(item);
		System.out.println(list.get(getNumItems()-1).getFruit() + " "+ list.get(getNumItems()-1).getCost());
		}
	
	public int getNumItems() {return list.size();}
	public double getMaxPrice() {
		double max=0;
		for(int i=0;i<getNumItems();i++) {
			if(list.get(i).getCost()>max) {
				max = list.get(i).getCost();
			}
		}
		return max;
	}
	public String getMaxItem(){
		double max = 0;
		int m = 0;
		for(int i=0;i<getNumItems();i++) {
			if(list.get(i).getCost()>max) {
				max = list.get(i).getCost();
				m=i;
			}
		}
		return list.get(m).getFruit();
	}
	
	public double getMinPrice() {
		double min = Double.MAX_VALUE;
		for(int i=0;i<getNumItems();i++) {
			if(list.get(i).getCost()<min) {
				min = list.get(i).getCost();
			}
		}
		return min;
	}
	public String getMinItem(){
		double min = Double.MAX_VALUE;
		int m = 0;
		for(int i=0;i<getNumItems();i++) {
			if(list.get(i).getCost()<min) {
				min = list.get(i).getCost();
				m=i;
			}
		}
		return list.get(m).getFruit();
	}
	public double getAvgPrice() {
		double avg = 0;
		for(int i=0;i<getNumItems();i++) {
			avg += list.get(i).getCost();
		}
		return avg/getNumItems();
	}
}


public class Problem14 {

	public static void main(String[] args) {
		FruitBox<Fruit> box = new FruitBox<>();
		boolean rv = ItemReader.fileToBox("input_prob14.txt",box);
		if(rv == false) return;
		box.add(new Fruit("orange",9.99));
		System.out.println("----------------");
		System.out.println("    Summary");
		System.out.println("----------------");
		System.out.println("number of items: " + box.getNumItems());
		System.out.println("most expensive item: "+box.getMaxItem() + " (" + box.getMaxPrice() + ")");
		System.out.println("cheapest item: " + box.getMinItem() + " (" + box.getMinPrice() + ")");
		System.out.printf("average price of items: %.2f",box.getAvgPrice());		
	}
}
