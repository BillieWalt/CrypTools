#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include<math.h>

int mod_invese(int d,int n);        //模逆运算
int mod_power(int a,int k,int n);  //模幂运算
void searchprime(int n);             //判断n是否为素数
void rsa();                          //RSA测试
void eigamal();                      //EIGAMAL测试


//模逆运算，用模逆算法，此处编写程序时候u,v为实际计算过程中v的各个值
int mod_invese(int d,int n)//求d模n的逆，n 为正整数
{
    int a,b,q,r,u=0,v=1,t;//a为被除数，b为除数，q为商
    a=n;
    b=(d>=0)?(d%n):-(d%n);//规定正负数mod（n）都取正；
    while(b!=0)
	{
        q=(int)a/b;
        r=a-b*q;
        a=b;
        b=r;
        t=v;
        v=u-q*v;
        u=t;//把每次没有进行运算的v的值给u
	}//辗转相除，直到余数b=0，跳出循环
    if(a!=1) return 0;
    return((u<0)?u+n:u);//返回的值都是mod(n)后的值，使得最后的值是正数；
}

//模幂运算
int mod_power(int a,int k,int n)  //要求n为正整数
{
	int x,y,t;
    y=a;
    t=k;
    if(t<0)
	{
		y=mod_invese(y,n);
        if(y<0) return(0);//没有模逆
        t=-t;
	}
    x=1;
    if(t==0) return(1);
    while(t>1)
	{
		if(t&0x00000001)
		x=(x*y)%n;
        y=(y*y)%n;
        t>>=1;
	}
    x=(x*y)%n;
    return(x);
}

//判断n是否为素数，此处使用最暴力的方法，将n取余小于n的所有值
void searchprime(int n)
{
	   int i;
	   for(i=2;i<=n-1;i++)
	   {
		   if(n%i==0)
			   break;
	   }//将小于n的数依次除n，若可以整除，则不是素数，退出循环
       if(i<n-1)
		  printf("%d不是素数\n",n);
	   else
		  printf("%d是素数\n",n);
}

//RSA算法
void rsa()
{
	int i=0,p,q,fn,n,e,x,d,m,c,w;
	printf("请输入素数p：");
	scanf("%d",&p);
	printf("请输入素数q(与p相异)：");
	scanf("%d",&q);
	n=p*q;//计算两个素数相乘的结果n
	printf("产生的n=p*q=%d\n",n);
	fn=(p-1)*(q-1);//计算fn
    printf("产生的fn=(p-1)*(q-1)=%d\n",fn);
	printf("请输入随机加密指数e（满足fn与e互素）：");
	scanf("%d",&e);
	d=mod_invese(e,fn);//计算e模fn的结果，并将d作为加密指数
	if(d==0) printf("错误!\n");
	else
	{
		printf("产生的解密指数d=%d\n",d);
		printf("公钥k1=(e,n)=(%d,%d)\n",e,n);
		printf("私钥k2=d=%d\n",d);
		printf("请输入明文:");
		scanf("%d",&m);
		c=mod_power(m,e,n);//计算m的e次方模n，结果作为密文
		printf("密文c=%d\n\n",c);
		printf("加密:c=%d^%dmod(%d) = %d\n\n",m,e,n,c);
		printf("解密:m=%d^%dmod(%d) = %d\n\n",c,d,n,mod_power(c,d,n));
	}
}

//EIGAMAL算法
void eigamal()
{
	int d,b,m,c1,c2,k,p,a,r,x,y,i,j,t;
	printf("请输入素数p=");
    scanf("%d",&p);
		for(i=2;i<p;i++)
		{    t=1;
			for(j=1;j<p;j++)
			{
				t=(t*i)%p;
				if(t==1)
					if(j==p-1)goto loop2;
					else break;
			}
		}
	loop2:printf("计算出的原根a=%d\n",i);
	a=i;
	printf("随机秘密输入整数d(0 ~ p-2):");
	scanf("%d",&d);
	b=mod_power(a,d,p);
	printf("b=a^dmod p=%d\n",b);
	printf("公钥:k1=(p,a,b)=(%d,%d,%d)\n",p,a,b);
	printf("私钥:k2=d=%d\n",d);
	printf("请输入明文m:");
	scanf("%d",&m);
	printf("请输入正整数k，其中(1<k<=p-1):");
	scanf("%d",&k);
	c1=mod_power(a,k,p);
	c2=(m*mod_power(b,k,p))%p;
	printf("加密:c=(c1,c2)=(%d,%d)\n",c1,c2);
	m=mod_power(c1,d,p);
	m=mod_invese(m,p);
	m=m*c2%p;
	printf("解密:m=%d\n\n",m);
}

//主程序
int main()
{
	int l,a,k,n,p;
	while(1)
	{
	    printf("密码学实验算法菜单\n\n");
	    printf("1.模逆算法\n");
		printf("2.模幂算法\n");
		printf("3.Miller-Rabin素性检验方法\n");
		printf("4.RSA加密与签名\n");
		printf("5.EIGamal加密与签名\n");
		printf("6.退出\n");
		printf("\n请输入需要的算法种类:");
		scanf("%d",&l);
	    switch(l)
		{
	     case 1:
			 {
				printf("a模n的逆\n");
		        printf("请输入a：");
		        scanf("%d",&a);
	       	    printf("请输入n：");
		        scanf("%d",&n);//a模n的数据输入
	 	        printf("a模n产生的逆为：%d\n\n",mod_invese(a,n));//调用计算模逆的函数
			    break;
			 }
	     case 2:
			 {
				printf("a的k次方模n\n");
		        printf("请输入a：");
		        scanf("%d",&a);
		        printf("请输入k：");
		        scanf("%d",&k);
		        printf("请输入n：");
		        scanf("%d",&n);//a的k次方模n的数据输入
		        printf("a的k次方模n产生的数为：%d\n\n",mod_power(a,k,n));//调用计算模幂的函数
			    break;
			 }
	    case 3:
			{
		        printf("请输入需要检验的素数P：");
		        scanf("%d",&p);
		        searchprime(p);//调用判断是否为素数的函数
			    break;
			}
	    case 4:
			{
		        rsa();//调用RSA测试函数
			    break;
			}

	    case 5:
			{
		        eigamal();//调用EIGAMAL测试函数
			    break;
			}
	    case 6:
			{
		        printf("谢谢使用！\n\n");
		        return 0;
				break;
			}
	    default:
			{
		        printf("输入错误！\n\n");
			    break;
			}
		}
	}
}
