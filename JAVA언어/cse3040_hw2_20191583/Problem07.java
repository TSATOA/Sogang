package homework202;

import java.util.Scanner;

interface IntSequenceStr{
	public abstract boolean hasNext();
	public abstract int next();
}

class BinarySequenceStr implements  IntSequenceStr{
	private int number;
	private int a;
	public BinarySequenceStr(int n) {
		number = n;
		a=(int)(Math.log(number)/Math.log(2));
	}
	public boolean hasNext() {return a!=-1;}
	public int next() {
		int n = (int)(Math.log(number)/Math.log(2));
		if(a>n) {
			a--;
			return 0;
		}else {
			number = number-(int)Math.pow(2,n);
			a--;
			return 1;
		}
	}
}

public class Problem07 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		System.out.print("Enter a positive integer: ");
		String str = in.nextLine();
		int num = Integer.parseInt(str);
		in.close();
		System.out.println("Integer: "+num);
		IntSequenceStr seq = new BinarySequenceStr(num);
		System.out.print("Binary number: ");
		while(seq.hasNext()) System.out.print(seq.next());
		System.out.println(" ");
	}

}
