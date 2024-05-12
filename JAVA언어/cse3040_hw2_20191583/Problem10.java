package homework205;

class Points{
	private double[] arr;
	private int dimention;
	private double sum1=0;
	public Points(double[] p) {
		dimention = p.length;
		arr=p;
	}
	public int getDimention() {return dimention;}
	public double getArr(int n) {return arr[n];}
	
	public boolean equals(Points p) {
		int sum2=0;
		if(p==null) return false;
		
		for(int i=0;i<p.getDimention();i++) {
			sum2+=p.getArr(i);
		}
		
		if(sum1==sum2) return true;
		else return false;
	}
	public String toString() {
		for(int i=0;i<dimention;i++) {
			sum1+=arr[i];
		}
		return("[sum of points: "+sum1+"]");
	}
}


public class Problem10 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Points p1 = new Points(new double[] {1.0, 2.0, 3.0});
		Points p2 = new Points(new double[] {4.0, 5.0, 6.0});
		System.out.println(p1);
		System.out.println(p2);
		System.out.println(p1.equals(p2));
		Points p3 = new Points(new double[] {1.0, 4.0, 7.0});
		Points p4 = new Points(new double[] {3.0, 9.0});
		System.out.println(p3);
		System.out.println(p4);
		System.out.println(p3.equals(p4));
		Points p5 = new Points(new double[] {1.0, 2.0});
		Points p6 = null;
		System.out.println(p5);
		System.out.println(p6);
		System.out.println(p5.equals(p6));
	}

}
