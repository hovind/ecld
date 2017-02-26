#include <stdio.h>
#include <limits.h> /* CHAR_BIT */

void
print256(unsigned int a)
{
	int i;
	int first = 1;

	if (a) {
		for (i = CHAR_BIT - 1; i >= 0; --i) {
			if (a & (1 << i)) {
				if (first) 
					first = 0;
				else
					printf("+");	
				
				if (i)
					printf("x^%d", i);
				else
					printf("%d", 1);
			}
		}
	} else {
		printf("%d", a);
	}
}

void
print_poly(unsigned int a)
{
	int i;
	int first;
	unsigned int mask;

	if (a) {
		first = 1;
		mask = 1 << CHAR_BIT*sizeof(a) - 1;
		for (i = CHAR_BIT*sizeof(a) - 1; a; --i, a = a << 1) {
			if (a & mask) {
				if (first) 
					first = 0;
				else
					printf("+");	
					
				if (i)
					printf("x^%d", i);
				else
					printf("%d", 1);
			}
		}
	} else {
		printf("%d", 0);
	}
}

unsigned int
add256(unsigned int a, unsigned int b)
{
	return a ^ b;
}

unsigned int
div_euclidean(unsigned int a, unsigned int b, unsigned int *r)
{
	int factor;
	unsigned int tmp;

	int i;
	int j;
	unsigned int ret = 0;
	
	j = 0;
	tmp = b;
	while (tmp = tmp >> 1)
		++j;
	
	for (;;) {
		i = 0;
		tmp = a;
		while (tmp = tmp >> 1)
			++i;
		
		if (i < j) {
			*r = a;
			return ret;
		} else {	
			factor = i - j;
			ret |= 1 << factor;
			a = add256(a, b << factor);
		}
	}
}

unsigned int
mul(unsigned int a, unsigned int b)
{
	int i;
	unsigned int ret = 0;
	for (i = 0; a; ++i, a = a >> 1) {
		if (a & 0b1)
			ret = add256(ret, b << i);
	}
	return ret;	
}

unsigned int
euclid(unsigned int a, unsigned int b, unsigned int *u, unsigned int *v)
{
	unsigned int r_prev = a;
	unsigned int r      = b;
	unsigned int s_prev = 0;
	unsigned int s      = 1;
	unsigned int t_prev = 0;
	unsigned int t      = 1;
	unsigned int tmp;
	unsigned int q;

	while (r) {
		tmp = r;
		q = div_euclidean(r_prev, r, &r);
		r_prev = tmp;

		tmp = t;
		t = add256(t_prev, mul(q, t));
		t_prev = tmp;

		tmp = s;
		s = add256(t_prev, mul(q, t));
		s_prev = tmp;
		
	}
	*u = t;
	*v = s;	
	return q;
}

unsigned int mul256(unsigned int a, unsigned int b); /* a*b mod p */
unsigned int div256(unsigned int a, unsigned int b)
{
	return mul256(a, inv256(b));
}
unsigned int inv256();

int
main()
{
	unsigned int oct = 93;
	unsigned int n;
	unsigned int d;
	unsigned int r;

	unsigned int q;
	unsigned int u;
	unsigned int v;

	print_poly(oct);
	printf("\n\n");
	
	n = 0b01010111;
	d = 0b00001011;
	print_poly(n);
	printf(" = ");
	oct = div_euclidean(n, d, &r);
	print_poly(oct);
	printf(" * ");
	print_poly(d);
	printf(" + ");
	print_poly(r);
	printf("\n\n");

	print_poly(oct);
	printf(" * ");
	print_poly(d);
	printf(" = ");
	oct = mul(oct, d);
	print_poly(oct);
	printf("\n\n");
	
	printf("gcd(");
	print_poly(oct);
	printf(", ");
	print_poly(d);
	printf(") = ");
	q = euclid(oct, d, &u, &v);
	print_poly(q);
	printf("\n");
	printf("u = ");
	print_poly(u);
	printf(", v = ");
	print_poly(v);
	printf("\n\n");
	

	return 0;
}	


