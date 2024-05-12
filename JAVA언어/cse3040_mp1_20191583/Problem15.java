package mp5;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

class Item{
	private String word;
	private int num=0;
	public Item (String a) {
		this.word = a;
		this.num++;
	}
	public void addNum(){
		this.num++;
	}
	public String getWord() {
		return this.word;
	}
	public int getNum() {
		return this.num;
	}
	public String toString() {
		return(this.word + " " + this.num);
	}
}

class MyFileReader{
	static boolean readDataFromFile(String a, ArrayList<Item> list) {
		BufferedReader br;
		String line;
		int idx;
		String in;
		boolean pa;
		try {
			br = new BufferedReader(new FileReader(a));
		}catch(FileNotFoundException e) {
			return false;
		}
		while(true) {
			try {
				line = br.readLine();
				if(line == null) break;
				while(true) {
					idx = line.indexOf(" ");
					if(idx != -1) {
						in = line.substring(0,idx);
						in = in.toLowerCase();
						line = line.substring(idx+1);
					}else {
						in = line;
					}
					pa = false;
					for(int i=0;i<list.size();i++) {
						if(in.equals(list.get(i).getWord())) {
							list.get(i).addNum();
							pa = true;
							break;
						}
					}
					if(pa==false) {
						list.add(new Item(in));
					}
					if(idx==-1) break;
				}
			}catch(IOException e){
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

public class Problem15 {

	public static void main(String[] args) {
		ArrayList<Item> list = new ArrayList<>();
		boolean rv = MyFileReader.readDataFromFile("input_prob15.txt", list);
		if(rv == false) {
			System.out.println("Input file not found.");
			return;
		}
		for(Item it: list) System.out.println(it);
	}

}
