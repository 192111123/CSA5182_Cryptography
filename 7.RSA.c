#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
uint64_t gcd(uint64_t a, uint64_t b) 
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
uint64_t mod_inverse(uint64_t e, uint64_t phi)
 {
    int64_t d = 0, x1 = 0, x2 = 1, y1 = 1, temp_phi = phi;  
    while (e > 0) 
	{
        int64_t quotient = phi / e;
        int64_t remainder = phi - quotient * e;
        phi = e;
        e = remainder;
        int64_t temp_x = x2 - quotient * x1;
        int64_t temp_y = d - quotient * y1;     
        x2 = x1;
        x1 = temp_x;
        d = y1;
        y1 = temp_y;
    }   
    if (phi == 1)
        return (d + temp_phi) % temp_phi;
    return 0; 
}
int main()
 {
    uint64_t p, q, e;   
    printf("Enter the value of p: ");
    scanf("%llu", &p);   
    printf("Enter the value of q: ");
    scanf("%llu", &q);      
    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);
    uint64_t d = mod_inverse(e, phi);
    printf("n: %llu\n", n);
    printf("e: %llu\n", e);
    printf("d: %llu\n", d);
	printf("phi: %llu\n", phi);
    return 0;
}
