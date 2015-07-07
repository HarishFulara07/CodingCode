#include<stdio.h>

unsigned long long int MOD = 1000000007;

unsigned long long int power(unsigned long long int base, unsigned long long int exp)
{
	unsigned long long int res = 1, i;
	while(exp > 0)
	{
		if(exp % 2 == 1)
		{
			res = (res * base) % MOD ;
		}
		base = (base * base) % MOD;
		exp = exp/2;
	}
	return(res);
}

int main()
{
	unsigned long long int t, n, i;
	scanf("%llu",&t);
	while(t--)
	{	
		unsigned long long int res = 0;
		scanf("%llu",&n);
		if(n%2 == 0)
		{
			res = (res + power(2,(n+2)/2)) % MOD;
			res = (res + power(2,n/2)) % MOD;
		}
		else
		{
			res = (res + power(2,(n+1)/2)) % MOD;
			res = (res + power(2,(n+1)/2)) % MOD;
		}
		printf("%llu\n",res - 2);
	}	
	return(0);
}
