void print_poly(unsigned int a);
unsigned int add256(unsigned int a, unsigned int b); /* a + b mod p */

unsigned int div_euclidean(unsigned int a, unsigned int b, unsigned int *r);
/* div_euclidean(a, b) * b = a + r */

unsigned int mul(unsigned int a, unsigned int b); /* a * b in F2[x] */
unsigned int euclid(unsigned int a, unsigned int b, unsigned int *u, unsigned int *v);
/* pgcd(a, b). u and v point towards Bezout coeffs a*u + b*v = pgcd(a, b) */

unsigned int mul256(unsigned int a, unsigned int b); /* a * b mod p */
unsigned int div256(unsigned int a, unsigned int b); /* a / b mod p */
unsigned int inv256(unsigned int a); /* a^-1 mod p */


