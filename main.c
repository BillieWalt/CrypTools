#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include<math.h>

int mod_invese(int d,int n);        //ģ������
int mod_power(int a,int k,int n);  //ģ������
void searchprime(int n);             //�ж�n�Ƿ�Ϊ����
void rsa();                          //RSA����
void eigamal();                      //EIGAMAL����


//ģ�����㣬��ģ���㷨���˴���д����ʱ��u,vΪʵ�ʼ��������v�ĸ���ֵ
int mod_invese(int d,int n)//��dģn���棬n Ϊ������
{
    int a,b,q,r,u=0,v=1,t;//aΪ��������bΪ������qΪ��
    a=n;
    b=(d>=0)?(d%n):-(d%n);//�涨������mod��n����ȡ����
    while(b!=0)
	{
        q=(int)a/b;
        r=a-b*q;
        a=b;
        b=r;
        t=v;
        v=u-q*v;
        u=t;//��ÿ��û�н��������v��ֵ��u
	}//շת�����ֱ������b=0������ѭ��
    if(a!=1) return 0;
    return((u<0)?u+n:u);//���ص�ֵ����mod(n)���ֵ��ʹ������ֵ��������
}

//ģ������
int mod_power(int a,int k,int n)  //Ҫ��nΪ������
{
	int x,y,t;
    y=a;
    t=k;
    if(t<0)
	{
		y=mod_invese(y,n);
        if(y<0) return(0);//û��ģ��
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

//�ж�n�Ƿ�Ϊ�������˴�ʹ������ķ�������nȡ��С��n������ֵ
void searchprime(int n)
{
	   int i;
	   for(i=2;i<=n-1;i++)
	   {
		   if(n%i==0)
			   break;
	   }//��С��n�������γ�n�������������������������˳�ѭ��
       if(i<n-1)
		  printf("%d��������\n",n);
	   else
		  printf("%d������\n",n);
}

//RSA�㷨
void rsa()
{
	int i=0,p,q,fn,n,e,x,d,m,c,w;
	printf("����������p��");
	scanf("%d",&p);
	printf("����������q(��p����)��");
	scanf("%d",&q);
	n=p*q;//��������������˵Ľ��n
	printf("������n=p*q=%d\n",n);
	fn=(p-1)*(q-1);//����fn
    printf("������fn=(p-1)*(q-1)=%d\n",fn);
	printf("�������������ָ��e������fn��e���أ���");
	scanf("%d",&e);
	d=mod_invese(e,fn);//����eģfn�Ľ��������d��Ϊ����ָ��
	if(d==0) printf("����!\n");
	else
	{
		printf("�����Ľ���ָ��d=%d\n",d);
		printf("��Կk1=(e,n)=(%d,%d)\n",e,n);
		printf("˽Կk2=d=%d\n",d);
		printf("����������:");
		scanf("%d",&m);
		c=mod_power(m,e,n);//����m��e�η�ģn�������Ϊ����
		printf("����c=%d\n\n",c);
		printf("����:c=%d^%dmod(%d) = %d\n\n",m,e,n,c);
		printf("����:m=%d^%dmod(%d) = %d\n\n",c,d,n,mod_power(c,d,n));
	}
}

//EIGAMAL�㷨
void eigamal()
{
	int d,b,m,c1,c2,k,p,a,r,x,y,i,j,t;
	printf("����������p=");
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
	loop2:printf("�������ԭ��a=%d\n",i);
	a=i;
	printf("���������������d(0 ~ p-2):");
	scanf("%d",&d);
	b=mod_power(a,d,p);
	printf("b=a^dmod p=%d\n",b);
	printf("��Կ:k1=(p,a,b)=(%d,%d,%d)\n",p,a,b);
	printf("˽Կ:k2=d=%d\n",d);
	printf("����������m:");
	scanf("%d",&m);
	printf("������������k������(1<k<=p-1):");
	scanf("%d",&k);
	c1=mod_power(a,k,p);
	c2=(m*mod_power(b,k,p))%p;
	printf("����:c=(c1,c2)=(%d,%d)\n",c1,c2);
	m=mod_power(c1,d,p);
	m=mod_invese(m,p);
	m=m*c2%p;
	printf("����:m=%d\n\n",m);
}

//������
int main()
{
	int l,a,k,n,p;
	while(1)
	{
	    printf("����ѧʵ���㷨�˵�\n\n");
	    printf("1.ģ���㷨\n");
		printf("2.ģ���㷨\n");
		printf("3.Miller-Rabin���Լ��鷽��\n");
		printf("4.RSA������ǩ��\n");
		printf("5.EIGamal������ǩ��\n");
		printf("6.�˳�\n");
		printf("\n��������Ҫ���㷨����:");
		scanf("%d",&l);
	    switch(l)
		{
	     case 1:
			 {
				printf("aģn����\n");
		        printf("������a��");
		        scanf("%d",&a);
	       	    printf("������n��");
		        scanf("%d",&n);//aģn����������
	 	        printf("aģn��������Ϊ��%d\n\n",mod_invese(a,n));//���ü���ģ��ĺ���
			    break;
			 }
	     case 2:
			 {
				printf("a��k�η�ģn\n");
		        printf("������a��");
		        scanf("%d",&a);
		        printf("������k��");
		        scanf("%d",&k);
		        printf("������n��");
		        scanf("%d",&n);//a��k�η�ģn����������
		        printf("a��k�η�ģn��������Ϊ��%d\n\n",mod_power(a,k,n));//���ü���ģ�ݵĺ���
			    break;
			 }
	    case 3:
			{
		        printf("��������Ҫ���������P��");
		        scanf("%d",&p);
		        searchprime(p);//�����ж��Ƿ�Ϊ�����ĺ���
			    break;
			}
	    case 4:
			{
		        rsa();//����RSA���Ժ���
			    break;
			}

	    case 5:
			{
		        eigamal();//����EIGAMAL���Ժ���
			    break;
			}
	    case 6:
			{
		        printf("ллʹ�ã�\n\n");
		        return 0;
				break;
			}
	    default:
			{
		        printf("�������\n\n");
			    break;
			}
		}
	}
}
