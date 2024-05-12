package homework203;

class Shape{
	private double sum=0;
	public double Area() {return sum;}
}

class Circle extends Shape{
	private double radius;
	public Circle(double a) { this.radius = a;}
	public double Area() { return radius*radius*Math.PI; }
}

class Square extends Shape{
	private double length;
	public Square(double a) { this.length = a;}
	public double Area() { return length*length; }
}

class Rectangle extends Shape{
	private double width,height;
	public Rectangle(double a,double b) { this.width=a; this.height = b;}
	public double Area() { return width*height; }
}



public class Problem08 {

	public static double sumArea(Shape[] arr) {
		int n = arr.length;
		double res=0;
		for(int i=0;i<n;i++) {
			res += arr[i].Area();
			
		}
		return res;
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Shape[] arr = {new Circle(5.0), new Square(4.0), new Rectangle(3.0,4.0), new Square(5.0)};
		
		System.out.println("Total area of the shapes is: "+sumArea(arr));	
	}

}
