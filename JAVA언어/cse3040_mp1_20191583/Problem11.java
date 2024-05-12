package mp1;

class PalindromeChecker{
	
	static void check(String a) {
		int length = a.length();
		char b[]=a.toCharArray();
		int cnt=0;
		for(int i=0;i<length/2;i++) {
			if(b[i]==b[length-i-1]) {
				cnt++;
			}
		}
		if(cnt==length/2) 
			System.out.println(a + " is a palindrome.");
		else
			System.out.println(a + " is not a plaindrome.");
	}
	static void check(int a) {
		int length = (int)(Math.log10(a)+1);
		int x,y;
		int cnt=0;
		for(int i=0;i<length/2;i++) {
			x=a;
			y=a;
			for(int j=0;j<length-i-1;j++) {
				x = x/10;
			}
			x=x%10;
			for(int j=0;j<i;j++) {
				y = y/10;
			}
			y=y%10;
			if(x==y) cnt++;
		}
		if(cnt==length/2) 
			System.out.println(a + " is a palindrome.");
		else
			System.out.println(a + " is not a plaindrome.");
	}
}

public class Problem11 {

	public static void main(String[] args) {
		PalindromeChecker.check("abcde");
		PalindromeChecker.check("abcba");
		PalindromeChecker.check(1234);
		PalindromeChecker.check(12321);
	}

}
