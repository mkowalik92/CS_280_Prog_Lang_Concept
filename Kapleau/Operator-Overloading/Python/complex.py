class complex:
    def __init__(self, real=0.0, fake=0.0):
        self.real = real
        self.fake = fake

    def __add__(self, other):
        if isinstance(other, float):
            return complex(self.real + other, self.fake)
        elif isinstance(other, complex):
            return complex(self.real + other.real, self.fake + other.fake)
        else:
            raise TypeError

    def __radd__(self, other):
        return self + other

    def __sub__(self, other):
        if isinstance(other, float):
            return complex(self.real - other, self.fake)
        elif isinstance(other, complex):
            return complex(self.real - other.real, self.fake + other.fake)
        else:
            raise TypeError

    def __rsub__(self, other):
        return complex(other) - self

    def __mul__(self, other):
        if isinstance(other, float):
            return complex(self.real * other, self.fake * other)
        elif isinstance(other, complex):
            return complex(((self.real * other.real) + ((self.fake * other.fake) * (-1.0))), ((self.real * other.fake) + (self.fake * other.real)))
        else:
            raise TypeError

    def __rmul__(self, other):
        return self * other

    def __truediv__(self, other):
        if isinstance(other, float):
            return complex(self.real / other, self.fake / other)
        elif isinstance(other, complex):
            return complex((((self.real*other.real)+((self.fake*(other.fake*(-1.0)))*(-1.0)))/((other.real*other.real)+(other.fake*other.fake))), (((self.real*(other.fake*(-1.0)))+(self.fake*other.real))/((other.real*other.real)+(other.fake*other.fake))))
        else:
            raise TypeError

    def __rtruediv__(self, other):
        return complex(other) / self

    def __str__(self):
        if ( self.fake < 0.0 ):
            return str(self.real) + str(self.fake) + 'i'
        else:
            return str(self.real) + '+' + str(self.fake) + 'i'

if __name__ == '__main__':

    a = complex(2.0, 3.0)
    b = complex(4.0, -5.0)

    i = 5.0

    print('%s + %s = %s' % (a, b, a + b))
    print('%s + %f = %s' % (a, i, a + i))
    print('%f + %s = %s\n' % (i, a, i + a))

    print('%s - %s = %s' % (a, b, a - b))
    print('%s - %f = %s' % (a, i, a - i))
    print('%f - %s = %s\n' % (i, a, i - a))

    print('%s * %s = %s' % (a, b, a * b))
    print('%s * %f = %s' % (a, i, a * i))
    print('%f * %s = %s\n' % (i, a, i * a))

    print('%s / %s = %s' % (a, b, a / b))
    print('%s / %f = %s' % (a, i, a / i))
    print('%f / %s = %s' % (i, a, i / a))
