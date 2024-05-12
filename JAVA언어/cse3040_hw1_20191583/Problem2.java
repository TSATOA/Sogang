package homework1;

import java.util.Scanner;

public class Problem2 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int a;
		int i=1;
		int x=1,y=100;
		a=(int)(Math.random()*100+1);
		System.out.print("["+i+"]"+" Guess a number ("+x+"-"+y+"): ");
		Scanner in = new Scanner(System.in);
		int b = in.nextInt();
		while(a!=b) {
			if(b>y||b<x) {
				System.out.println("Not in Range!");
				System.out.print("["+i+"]"+" Guess a number ("+x+"-"+y+"): ");
			}else {
			i++;
			if(a>b) {
				System.out.println("Too small!");
				x=b+1;
			}else {
				System.out.println("Too large!");
				y=b-1;
			}
			System.out.print("["+i+"]"+" Guess a number ("+x+"-"+y+"): ");
			}
			b = in.nextInt();
			
			
		}
		System.out.print("Correct! Number of guesses: "+i);
		in.close();
	}

}
