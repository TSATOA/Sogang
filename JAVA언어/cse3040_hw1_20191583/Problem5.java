package homework1;

import java.util.Scanner;

public class Problem5 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int score[] = new int[5];
		int a,b;
		int i;
		Scanner in = new Scanner(System.in);
		
		for(i=0;i<5;i++) {
			System.out.print("Score of student "+(i+1)+": ");
			score[i] = in.nextInt();
		}
		if(score[0]>score[1]) {
			a=0;
			b=1;
		}else {
			a=1;
			b=0;
		}
		for(i=2;i<5;i++) {
			if(score[i]>score[a]) {
				b=a;
				a=i;
			}else {
				if(score[i]>score[b]) {
					b=i;
				}
			}
		}
		System.out.println("The 1st place is student "+(a+1)+" with "+score[a]+" points.");
		System.out.println("The 2st place is student "+(b+1)+" with "+score[b]+" points.");
		in.close();
	}

}
