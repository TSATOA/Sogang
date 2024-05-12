package homework204;

class Point{
	private int dimention;
	private double arr[];
	public Point(double[] p) {
		this.dimention = p.length;
		arr=p;
	}
	public int getDimention() {return dimention;}
	public double getArr(int n) {return arr[n];}
}

class EuclideanDistance{
	private static double distance=0;
	public static double getDist(Point p1, Point p2) {
		if(p1.getDimention()!=p2.getDimention()) {
			return -1;
		}else {
			for(int i=0;i<p1.getDimention();i++) {
				distance += Math.pow((p1.getArr(i)-p2.getArr(i)),2);
				}
			distance = Math.sqrt(distance);
			
			return distance;
			}
		}
}


class ManhattanDistance{
	private static double distance=0;
	public static double getDist(Point p1, Point p2) {
		if(p1.getDimention()!=p2.getDimention()) {
			return -1;
		}else {
			for(int i=0;i<p1.getDimention();i++) {
				if(p1.getArr(i)>p2.getArr(i)) {
					distance += p1.getArr(i) - p2.getArr(i);
				}else {
					distance += p2.getArr(i) - p1.getArr(i);
				}
			}
			return distance;
		}
		
	}
}

public class Problem09 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Point p1 = new Point(new double[] {1.0, 2.0, 3.0});
		Point p2 = new Point(new double[] {4.0, 5.0, 6.0});
		System.out.println("Euclidean Distance: "+EuclideanDistance.getDist(p1,p2));
		System.out.println("Manhattan Distance: "+ManhattanDistance.getDist(p1,p2));
		Point p3 = new Point(new double[] {1.0, 2.0, 3.0});
		Point p4 = new Point(new double[] {4.0, 5.0});
		System.out.println("Euclidean Distance: "+EuclideanDistance.getDist(p3,p4));
		System.out.println("Manhattan Distance: "+ManhattanDistance.getDist(p3,p4));
	}

}
