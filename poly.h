void print_poly(unsigned int a);
unsigned int add256(unsigned int a, unsigned int b); /* a + b mod p */

unsigned int div_euclide(unsigned int a, unsigned int b, unsigned int *r); /*
floor(a/b). r points towards rest */
unsigned int mul(unsigned int a, unsigned int b); /* a*b dans F2[x] */
unsigned int euclide(unsigned int a, unsigned int b, unsigned int *u, unsigned
	int *v); /* pgcd(a, b). u and v point towards Bezout coeffs a*u + b*v =
	pgcd(a, b) */

unsigned int mul256(); /* a*b mod p */
unsigned int div256(); /* a*b mod p */
unsigned int inv256(); /* a*b mod p */


