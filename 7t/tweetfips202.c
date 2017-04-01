#define C const u8
#define F(i,n,...)for(i=0;i<n;++i){__VA_ARGS__;}
#define H(i,r,p,d)int sha##i(u8*h,C*m,u64 n){K(r*8,m,n,6+25*p,h,d);return 0;}
#define T typedef unsigned
#define S static
#define V(a,n)((a<<n)|(a>>(64-n)))
T char u8;T long long u64;S u64 L(C*x){u64 r=0,i;F(i,8,r|=(u64)x[i]<<8*i)return r;}S void f(u64*s){u8 x,y,j,R=1,r,n;u64 t,B[5],Y;F(n,24,F(x,5,B[x]=0;F(y,5,B[x]^=s[x+5*y]))F(x,5,t=B[(x+4)%5]^V(B[(x+1)%5],1);F(y,5,s[x+5*y]^=t))t=s[x=1];y=r=0;F(j,24,r+=j+1;Y=2*x+3*y;x=y;y=Y%5;Y=s[x+5*y];s[x+5*y]=V(t,r%64);t=Y)F(y,5,F(x,5,B[x]=s[x+5*y])F(x,5,s[x+5*y]=B[x]^(~B[(x+1)%5]&B[(x+2)%5])))F(y,7,if((R=(R<<1)^(113*(R>>7)))&2)*s^=1ULL<<((1<<y)-1)))}S void K(u8 r,C*m,u64 n,u8 p,u8*h,u64 d){u64 s[25]={0},i;u8 t[200]={0};while(n>=r){F(i,r/8,s[i]^=L(m+8*i))f(s);n-=r;m+=r;}F(i,n,t[i]=m[i])t[i]=p;t[r-1]|=128;F(i,r/8,s[i]^=L(t+8*i))f(s);F(i,d,h[i]=s[i/8]>>8*(i%8))}H(ke128,21,1,168)H(ke256,17,1,136)H(3_224,18,0,28)H(3_256,17,0,32)H(3_384,13,0,48)H(3_512,9,0,64)
