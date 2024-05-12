package homework1;

import java.util.Scanner;

public class Problem3 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int cnt=0;
		int i;
		Scanner in = new Scanner(System.in);
		System.out.print("Enter a text: ");
		String textst = in.nextLine();
		char textar[] = textst.toCharArray();
		System.out.print("Enter a letter: ");
		String letterst = in.nextLine();
		int n = letterst.length();
		while(n!=1) {
			System.out.println("You must enter a single letter.");
			System.out.print("Enter a letter: ");
			letterst = in.nextLine();
			n=letterst.length();
		}
		in.close();
		char letter[] = letterst.toCharArray();
		
		for(i=0;i<textst.length();i++) {
			if(textar[i]==letter[0]) cnt++;
		}
		System.out.println("There are "+cnt+" "+letter[0]+"'s in the text.");
		
	}

}
