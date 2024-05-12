package mp2;

class SubsequenceChecker{
	static void check(String a,String b) {
		char x[] = a.toCharArray();
		char y[] = b.toCharArray();
		int[] z = new int[b.length()];
		int cnt=0;
		for(int i=0;i<a.length();i++) {
			if(y[cnt]==x[i]) {
				z[cnt]=i;
				cnt++;
			}
			if(cnt==b.length()) break;
		}
		if(cnt==b.length()) {
			System.out.println(b + " is a subsequence of " + a);
			for(int i=0;i<cnt;i++)
				System.out.print(z[i]+" ");
			System.out.println();
		}else {
			System.out.println(b + " is not a subsequence of " + a);
		}
	}
}

public class Promplem12 {

	public static void main(String[] args) {
		SubsequenceChecker.check("supercalifragilisticexpialidocious","pads");
		SubsequenceChecker.check("supercalifragilisticexpialidocious","padsx");
	}

}
