package mp3;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class Text{
	private char arr[];
	
	public boolean readTextFromFile(String a) {
		BufferedReader br;
		String line;
		try{
			br = new BufferedReader(new FileReader(a));
		}catch(FileNotFoundException e) {
			System.out.println("Input file not found.");
			return false;
		}
		while(true) {
			try {
				line = br.readLine();
				if(line == null) break;
				this.arr = line.toCharArray();
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
	
	public int countChar(char c) {
		int cnt = 0;
		for(int i=0;i<(this.arr).length;i++) {
			if(this.arr[i]==c || this.arr[i]==c-32) {
				cnt++;
			}
		}
		return cnt;
	}
}

public class Problem13 {

	public static void main(String[] args) {
		Text t = new Text();
		if(t.readTextFromFile("input_prob13.txt")) {
			for(char c = 'a'; c <= 'z'; c++) {
				System.out.println(c + ":" + t.countChar(c));
			}
		}
	}
}
