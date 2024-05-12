package homework1;

import java.util.Scanner;

public class Problem4 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int cnt=0;
		int i;
		Scanner in = new Scanner(System.in);
		System.out.print("Enter a text: ");
		String textst = in.nextLine();
		System.out.print("Enter a letter: ");
		String letterst = in.nextLine();
		int n = letterst.length();
		while(n==0) {
			System.out.println("You must enter a single letter.");
			System.out.print("Enter a letter: ");
			letterst = in.nextLine();
			n=letterst.length();
		}
		in.close();
		
		
		for(i=0;i<textst.length()-letterst.length()+1;i++) {
			String com = textst.substring(i,i+letterst.length());
			if(com.equals(letterst)) cnt++;
		}
		System.out.println("There are "+cnt+" instances of \""+letterst+"\".");
	}

}
