package homework2;

interface IntSequence{
	public abstract boolean hasNext();
	public abstract int next();
}

class FibonacciSequence implements IntSequence{
	private int number=0;
	private int res=0;
	private int res1=0;

	public boolean hasNext() {return true;}
	public int next() {
		if(number==0) {
			number++;
			return 0;
		}else if(number==1) {
			res=1;
			number++;
			return 1;
		}else {
			int k = res;
			res = res+res1;
			res1=k;
			number++;
			return res;
		}
	}
}

public class Problem06 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		IntSequence seq = new FibonacciSequence();
		for(int i=0;i<20;i++) {
			if(seq.hasNext() == false) break;
			System.out.print(seq.next() + " ");
		}
		System.out.println(" ");
	}

}
