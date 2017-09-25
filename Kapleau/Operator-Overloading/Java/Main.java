public class Main
{
	public static void main(String[] args)
	{
		Complex a = new Complex(2.0, 3.0);
		Complex b = new Complex(4.0, -5.0);

		double i = 5.0;

		System.out.println(a + " + " + b + " = " + a.add(b));
		System.out.println(a + " - " + b + " = " + a.sub(b));
		System.out.println(a + " * " + b + " = " + a.mul(b));
		System.out.println(a + " / " + b + " = " + a.div(b));

		System.out.println(a + " + " + i + " = " + a.add(i));
		System.out.println(a + " - " + i + " = " + a.sub(i));
		System.out.println(a + " * " + i + " = " + a.mul(i));
		System.out.println(a + " / " + i + " = " + a.div(i));
	}
}
