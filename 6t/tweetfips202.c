#define R(a,n)a<<n^a>>64-n
#define H(i,r,p,d)void sha##i(C*h,const C*m,U n){k(r*8,m,n,p,h,d);}
#define L(i,n)for(U i=0;i<n;i++)
typedef long

long unsigned U;typedef unsigned char C;
#define X s[i+5*j]
#define S(x)L(i,r)s[i/8]^=(U)x[i]<<i%8*8
void F(U*s){C R=1,r,x,y;U t,B[5],Y;L(n,

24){L(i,5){B[i]=0;L(j,5)B[i]^=X;}L(i,5){t=B[(i+4)%5]^R(B[(i+1)%5],1);L(j,5)X^=t;}t=s[1];y=r=0;x=1;L(j,24){r+=j+1;Y=2*x+3*y;x=y;y=Y%5;Y=s[x+5

*y];s[x+5*y]=R(t,r%64);t=Y;}L(j,5){L(i,5)B[i]=X;L(i,5)X=B[i]^(~B[(i+1)%5]&B[(i+2)%5]);}L(j,7)if((R=(R<<1)^(113*(R>>7)))&2)*s^=1ULL<<((1<<j)-

1);}}void k(C r,const C*m,U n,C p,C*h,U d){U s[25]={0};C t[200]={0};while(n>=r){S(m);F(s);n-=r;m+=r;}L(i,n)t[i]=m[i];t[n]=p;t[r-1]|=128;S(t)

;F(s);L(i,d)h[i]=s[i/8]>>8*(i%8);}H(3_224,18,6,28)H(3_256,17,6,32)H(3_384,13,6,48)H(3_512,9,6,64)H(ke128,21,31,168)H(ke256,17,31,136)
