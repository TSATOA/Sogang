package homework1;

import java.util.Scanner;

public class Problem1 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
			Scanner in = new Scanner(System.in);
			System.out.print("ASCII code teller. Enter a letter: ");
			String asc = in.nextLine();
			int n = asc.length();

			if(n==1) {
				char c[] = asc.toCharArray();
				if((c[0]>='a'&&c[0]<='z')||(c[0]>='A'&&c[0]<='Z')) {
					String message = String.format("The ASCII code of C is %d",(int)c[0]);
					System.out.println(message);
				}else {
					System.out.println("You must input a single uppercase or lowercase alphabet.");
				}
			}else {
				System.out.println("You must input a single uppercase or lowercase alphabet.");
			}
		
			in.close();
		
	}

}
