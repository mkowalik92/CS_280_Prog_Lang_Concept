public class Complex
{
	public Complex()
	{
		this.real = 0.0;
		this.fake = 0.0;
	}

	public Complex(double real, double fake)
	{
		this.real = real;
		this.fake = fake;
	}

	public Complex add(Complex o)
	{
		return new Complex(real + o.real, fake + o.fake);
	}
	public Complex add(double n)
	{
		return new Complex(real + n, fake);
	}

	public Complex sub(Complex o)
	{
		return new Complex(real - o.real, fake - o.fake);
	}
	public Complex sub(double n)
	{
		return new Complex(real - n, fake);
	}

	public Complex mul(Complex o)
	{
		return new Complex( ((real * o.real) + ((fake * o.fake) * (-1.0))), ((real * o.fake) + (fake * o.real)) );
	}
	public Complex mul(double n)
	{
		return new Complex(real * n, fake * n);
	}

	public Complex div(Complex o)
	{
		return new Complex( ((real*o.real)+((fake*(o.fake*(-1.0)))*(-1))) / ((o.real*o.real)+(o.fake*o.fake)), ((real*(o.fake*(-1.0)))+(fake*o.real)) / ((o.real*o.real)+(o.fake*o.fake)) );
	}
	public Complex div(double n)
	{
		return new Complex(real / n, fake / n);
	}

	public String toString()
	{
		if ( fake < 0.0 )
		{
			return real + fake + "i";
		}
		else
		{
			return real + "+" + fake + "i";
		}
	}

	private double real;
	private double fake;
}
