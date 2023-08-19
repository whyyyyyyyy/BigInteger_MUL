#include <stdio.h>
#include <stdint.h>
typedef unsigned long long int u64i;
int main()
{
	u64i a=0xffff123d907613d3,b=0x32ccfa3276d6dd11;
	u64i ta,tb,tc,td,carry1,carry2;
	//a|b   c|d
	ta=a>>32;
	tc=b>>32;
	tb=a<<32;
	tb=tb>>32;
	td=b<<32;
	td=td>>32;
	printf("a,b %016llx  %016llx \nc,d %016llx  %016llx \n",ta,tb,tc,td);
	u64i tl=tb*td,th=ta*tc;
	ta=ta*td;//ac
	tb=tb*tc;//bd
	printf("tl,th %016llx  %016llx \nta,tb %016llx  %016llx \n",tl,th,ta,tb);
	carry1=(ta+tb)>>64;
	carry1=carry1&1;
	printf("carry1:%016llx\n",carry1);
	ta=ta+tb;
	tb=ta>>32;//high 32
	ta=ta<<32;//low 32
	carry2=(ta+tl)>>64;
	carry2=carry2&1;
	printf("carry2:%016llx\n",carry2);
	tl=ta+tl;
	printf("tl:%016llx\n",tl);	//correct!!!!!!2023Äê8ÔÂ19ÈÕ19:52:40 
	th=tb+th+carry2;
	th=th+(carry1<<32);
	printf("th:%016llx\n",th);	//correct!!!!!!
	printf("Result:%016llx  %016llx\n",th,tl);	//correct!!!!!!
	
	
	
	
	//right:00110010110011001100101100000  10000011101101111100100101111000010
	//wrong:00110010110011001100101100000  01110001010001111010010000111101010
	//sub:9381 29D8
	
	
	return 0;
}
