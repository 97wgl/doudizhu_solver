#include<stdio.h>
#include<conio.h>
int same(int p[],int plen)
{
	int i;
	int s[15];
	for(i=1;i<=14;i++)
	{
		s[i]=0;
	}
	for(i=0;i<plen;i++)
	{
		if(p[i]==15) s[14]++;
		else s[p[i]]++;
	}
	int max1,max2=0;
	for(i=1;i<=14;i++)
	{
		if(s[i]>max2)
		{
			max1=i;
			max2=s[i];
		}
	}
	return max1*10+max2;
}
int same2(int p[],int plen)
{
	int i;
	int s[16];
	for(i=1;i<=15;i++)
	{
		s[i]=0;
	}
	for(i=0;i<plen;i++)
	{
		s[p[i]]++;
	}
	int max1,max2=0;
	for(i=1;i<=15;i++)
	{
		if(s[i]>max2)
		{
			max1=i;
			max2=s[i];
		}
	}
	return max1*10+max2;
}
int paixing(int p[],int plen)
{
	if(plen==0) return -1;
	int n=same(p,plen);
	if(n%10==1)
	{
		if(plen==1) return 1;
		else if(plen>=5&&p[0]<=12)
		{
			for(int i=0;i<plen-1;i++)
			{
				if(p[i]-p[i+1]!=1) return 0;
			}
			return 10+plen-4;
		}
	}
	else if(n%10==2)
	{
		if(plen==2)
		{
			if(p[0]==p[1]) return 2;
			else if(p[1]==14&&p[0]==15) return 21;
		}
		else if(plen%2==0&&plen>=6&&p[0]<=12)
		{
			for(int i=0;i<plen-2;i+=2)
			{
				if(p[i]-p[i+2]!=1) return 0;
				else if(p[i]!=p[i+1]) return 0;
			}
			if(p[plen-1]!=p[plen-2]) return 0;
			return 21+plen/2-2;
		}
		return 0;
	}
	else if(n%10==3)
	{
		if(plen==3) return 3;
		else if(plen==4) return 31;
		else if(plen==5)
		{
			int s[3],slen=0;
			for(int i=0;i<plen;i++)
			{
				if(p[i]!=n/10) s[slen++]=p[i];
			}
			if(s[0]==s[1]&&p[0]<=13) return 32;
			return 0;
		}
		else
		{
			if(p[0]==15&&p[1]==14) return 0;
			int three=0;
			int i;
			int st[15];
			for(i=1;i<=14;i++)
			{
				st[i]=0;
			}
			for(i=0;i<plen;i++)
			{
				if(p[i]==15) st[14]++;
				else st[p[i]]++;
			}
			if(p[0]>13&&p[1]>13) return 0;
			if(p[0]==13&&p[1]==13&&p[2]==13) return 0;
			for(i=n/10;st[i]==3&&i<=12;i++)
			{
				three++;
			}
			for(i=0;i<three;i++)
			{
				st[i+n/10]=0;
			}
			int two=0,one=0;
			for(i=1;i<=15;i++)
			{
				if(st[i]==1) one++;
				else if(st[i]==2&&i<=13) two++;
				else if(st[i]==3) return 0;
			}
			if(one==three&&two==0) return 301+three*10;
			if(two==three&&one==0&&p[0]!=15&&p[1]!=14) return 302+three*10;
			if(two==0 && one==0) return 300+three*10;
			return 0;
		}
		return 0;
	}
	else if(n%10==4)
	{
		if(plen==4) return 4;
		if(plen==6)
		{
			int s[3],slen=0;
			for(int i=0;i<plen;i++)
			{
				if(p[i]!=n/10) s[slen++]=p[i];
			}
			if(s[0]!=s[1]&&(s[0]!=15||s[1]!=14)) return 421;
			return 0;
		}
		if(plen==8)
		{
			if(p[0]>13) return 0;
			int s[4],slen=0;
			for(int i=0;i<plen;i++)
			{
				if(p[i]!=n/10) s[slen++]=p[i];
			}
			if(same(s,slen)%10==2&&same(s,slen)/10<=13)
			{
				int u=same(s,slen);
				int t[4],tlen=0;
				for(int i=0;i<slen;i++)
				{
					if(s[i]!=u/10) t[tlen++]=s[i];
				}
				if(t[0]==t[1]) return 422;
				return 0;
			}
			return 0;
		}
		return 0;
	}
	return 0;
}
int jinshou=0,jinshou2[10];
bool canout(int p[],int plen,int l[],int llen)
{
	int a=paixing(p,plen);
	if(a==0) return 0;
	if(jinshou!=0)
	{
		for(int i=0;i<jinshou;i++)
		{
			if(jinshou2[i]==a) return 0;
		}
	}
	if(llen==0)
	{
		if(plen==0) return 0;
		return 1;
	}
	if(plen==0) return 1;
	int b=paixing(l,llen);
	if(b==21) return 0;
	if(b==4)
	{
		if(a!=21&&a!=4) return 0;
		if(a==4&&p[0]<=l[0]) return 0;
		return 1;
	}
	if(a!=b&&a!=4&&a!=21) return 0;
	int c=same2(p,plen),d=same2(l,llen);
	if(c/10<=d/10&&a!=4&&a!=21) return 0;
	return 1;
}
/*
1:单张
11-18:顺子
2:对子
21:王炸
22-29:连对
3:三张
31:三带一
32:三带二
3x0类，3x1类，3x2类:三顺/飞机
4:炸弹
421:四带二（单张）
422:四带二（对子）
0:不能这样出
-1:不出 
*/
struct cal{
	int winner;
	int move[25][15];
	int move2[25];
	int move3;
};
char name[16][10]={"不出","3","4","5","6","7","8","9","10","J","Q","K","A","2","小王","大王"};
void print(cal a)
{
	printf("出牌顺序：\n");
	for(int i=0;i<a.move3;i++)
	{
		if(a.move2[i]==0)
		{
			if(i==0) printf("%s",name[0]);
			else printf("-%s",name[0]);
			continue;
		}
		for(int j=0;j<a.move2[i];j++)
		{
			if(j==0&&i!=0) printf("-%s",name[a.move[i][j]]);
			else printf("%s",name[a.move[i][j]]);
		}
	}
	if(a.winner>=1) printf("  P1赢\n");
	else if(a.winner<=1) printf("  P2赢\n");
}
long long node=0;
long long pow1(int a,int b)
{
	long long c=1;
	for(int i=1;i<=b;i++)
	{
		c*=a;
	}
	return c;
}
cal CLHAI_1_0(int p1[],int p1len,int p2[],int p2len,int l[],int llen,int deep,bool now)
{
	int i;
	cal first;
	/*
	for(i=0;i<25;i++)
	{
		first.move2[i]=-1;
	}*/
	if(p1len==0)
	{
		first.winner=1;
		first.move3=deep;
		return first;
	}
	if(p2len==0)
	{
		first.winner=-1;
		first.move3=deep;
		return first;
	}
	int new1[15],new1len; 
	if(now)
	{
		if(canout(p2,p2len,l,llen))
		{
			first.winner=-1;
			first.move2[deep]=p2len;
			first.move3=deep+1;
			for(int i=0;i<p2len;i++)
			{
				first.move[deep][i]=p2[i];
			}
			return first;
		}
	}
	else
	{
		if(canout(p1,p1len,l,llen))
		{
			first.winner=1;
			first.move2[deep]=p1len;
			first.move3=deep+1;
			for(int i=0;i<p1len;i++)
			{
				first.move[deep][i]=p1[i];
			}
			return first;
		}
	}
	if(now)
	{
		for(i=0;i<p2len;i++)
		{
			new1[i]=p2[i];
		}
		new1len=p2len;
	}
	else
	{
		for(i=0;i<p1len;i++)
		{
			new1[i]=p1[i];
		}
		new1len=p1len;
	}
	first.winner=0;
	first.move3=deep+1;
	const int n=100;
	int returned[n][15],relen[n],renum=0;
	int returned2[n][15];
	if(now)
	{
		for(long long i=1;i<pow1(2,p2len);i++)
		{
			int u[30],ulen=0;
			long long u1=i;
			for(int u1len=0;u1len<p2len;u1len++)
			{
				if(u1%2==1)
				{
					u[ulen]=p2[u1len];
					ulen++;
				}
				u1/=2;
			}
			if(canout(u,ulen,l,llen))
			{
				bool jj=1;
				for(int k=0;k<renum;k++)
				{
					if(relen[k]!=ulen) continue;
					bool kk=1;
					for(int l=0;l<relen[k];l++)
					{
						if(u[l]!=returned2[k][l])
						{
							kk=0;
							break;
						}
					}
					if(kk)
					{
						jj=0;
						break;
					}
				}
				if(jj)
				{
					relen[renum]=ulen;
					for(int j1=0;j1<ulen;j1++)
					{
						returned2[renum][j1]=returned[renum][j1]=u[j1];
					}
					renum++;
				}
			}
		}
	}
	else
	{
		for(i=1;i<pow1(2,p1len);i++)
		{
			int u[15],ulen=0;
			int u1=i;
			for(int u1len=0;u1len<p1len;u1len++)
			{
				if(u1%2==1)
				{
					u[ulen]=p1[u1len];
					ulen++;
				}
				u1/=2;
			}
			if(canout(u,ulen,l,llen))
			{
				bool jj=1;
				for(int k=0;k<renum;k++)
				{
					if(relen[k]!=ulen) continue;
					bool kk=1;
					for(int l=0;l<relen[k];l++)
					{
						if(u[l]!=returned2[k][l])
						{
							kk=0;
							break;
						}
					}
					if(kk)
					{
						jj=0;
						break;
					}
				}
				if(jj)
				{
					relen[renum]=ulen;
					for(int j1=0;j1<ulen;j1++)
					{
						returned2[renum][j1]=returned[renum][j1]=u[j1];
					}
					renum++;
				}
			}
		}
	}
	if(llen!=0)
	{
		relen[renum]=0;
		renum++;
	}
	first.winner=0;
	for(i=0;i<renum;i++)
	{
		node++;
		if(deep<=5)
		printf("%d %d/%d node %lld\n",deep,i+1,renum,node);
		int new2[15],j;
		for(j=0;j<new1len;j++)
		{
			new2[j]=new1[j];
			for(int k=0;k<relen[i];k++)
			{
				if(returned[i][k]==new2[j])
				{
					returned[i][k]=new2[j]=0;
					break;
				}
			}
		}
		int new3[15],new3len=0;
		for(j=0;j<new1len;j++)
		{
			if(new2[j]!=0)
			{
				new3[new3len]=new2[j];
				new3len++;
			}
		}
		cal cmp;
		if(now)
		{
			cmp=CLHAI_1_0(p1,p1len,new3,new3len,returned2[i],relen[i],deep+1,!now);
			cmp.move2[deep]=relen[i];
			for(int a3=0;a3<relen[i];a3++)
			{
				cmp.move[deep][a3]=returned2[i][a3];
			}
			if(first.winner==0)
			{
				first.winner=cmp.winner;
				first.move3=cmp.move3;
				for(int a1=0;a1<cmp.move3;a1++)
				{
					first.move2[a1]=cmp.move2[a1];
					for(int a2=0;a2<cmp.move2[a1];a2++)
					{
						first.move[a1][a2]=cmp.move[a1][a2];
					}
				}
			}
			else if(cmp.winner==-1)
			{
				first.winner=cmp.winner;
				first.move3=cmp.move3;
				for(int a1=0;a1<cmp.move3;a1++)
				{
					first.move2[a1]=cmp.move2[a1];
					for(int a2=0;a2<cmp.move2[a1];a2++)
					{
						first.move[a1][a2]=cmp.move[a1][a2];
					}
				}
				return first;
			}
		}
		else
		{
			cmp=CLHAI_1_0(new3,new3len,p2,p2len,returned2[i],relen[i],deep+1,!now);
			cmp.move2[deep]=relen[i];
			for(int a3=0;a3<relen[i];a3++)
			{
				cmp.move[deep][a3]=returned2[i][a3];
			}
			if(first.winner==0)
			{
				first.winner=cmp.winner;
				first.move3=cmp.move3;
				for(int a1=0;a1<cmp.move3;a1++)
				{
					first.move2[a1]=cmp.move2[a1];
					for(int a2=0;a2<cmp.move2[a1];a2++)
					{
						first.move[a1][a2]=cmp.move[a1][a2];
					}
				}
			}
			else if(cmp.winner==1)
			{
				first.winner=cmp.winner;
				first.move3=cmp.move3;
				for(int a1=0;a1<cmp.move3;a1++)
				{
					first.move2[a1]=cmp.move2[a1];
					for(int a2=0;a2<cmp.move2[a1];a2++)
					{
						first.move[a1][a2]=cmp.move[a1][a2];
					}
				}
				return first;
			}
		}
	}
	return first;
}
/*
3:1
4:2
5:3
6:4
7:5
8:6
9:7
10:8
J:9
Q:10
K:11
A:12
2:13
JOKER:14/15
*/
int main()
{
	int i,j;
	int p1[16]={11,11,3,3,2,1},p2[16]={13,13,3,3,2,1},l[16]={0},p1len=13,p2len=9,llen=0;
	printf("斗地主残局解题器\n");
	printf("输入P1牌数：");
	scanf("%d",&p1len);
	printf("输入P2牌数：");
	scanf("%d",&p2len);
	printf("输入P1牌：");
	for(int i=0;i<p1len;i++)
	{
		scanf("%d",&p1[i]);
	}
	printf("输入P2牌：");
	for(int i=0;i<p2len;i++)
	{
		scanf("%d",&p2[i]);
	}
	printf("输入禁手数量：");
	scanf("%d",&jinshou);
	printf("输入禁手：");
	for(int i=0;i<jinshou;i++)
	{
		scanf("%d",&jinshou2[i]);
	}
	while(p1len>0&&p2len>0)
	{
		node=0;
		printf("\nP1牌：");
		for(j=0;j<p1len;j++)
		{
			printf("%s ",name[p1[j]]);
		}
		printf("\n");
		if(llen==0) printf("%s",name[0]);
		for(j=0;j<llen;j++)
		{
			printf("%s ",name[l[j]]);
		}
		printf("\nP2牌：");
		for(j=0;j<p2len;j++)
		{
			printf("%s ",name[p2[j]]);
		}
		printf("\n");
		printf("\n正在计算……\n\n");
		cal st=CLHAI_1_0(p1,p1len,p2,p2len,l,llen,0,0);
		print(st);
		llen=st.move2[0];
		for(i=0;i<st.move2[0];i++)
		{
			l[i]=st.move[0][i];
		}
		for(i=0;i<p1len;i++)
		{
			for(int j=0;j<st.move2[0];j++)
			{
				if(p1[i]==st.move[0][j])
				{
					p1[i]=st.move[0][j]=0;
					break;
				}
			}
		}
		int new3[15],new3len=0;
		for(j=0;j<p1len;j++)
		{
			if(p1[j]!=0)
			{
				new3[new3len]=p1[j];
				new3len++;
			}
		}
		p1len=new3len;
		for(j=0;j<new3len;j++)
		{
			p1[j]=new3[j];
		}
		printf("\nP1牌：");
		for(j=0;j<p1len;j++)
		{
			printf("%s ",name[p1[j]]);
		}
		printf("\n");
		if(llen==0) printf("%s",name[0]);
		for(j=0;j<llen;j++)
		{
			printf("%s ",name[l[j]]);
		}
		printf("\nP2牌：");
		for(j=0;j<p2len;j++)
		{
			printf("%s ",name[p2[j]]);
		}
		printf("\n\n");
		if(p1len==0) break;
		int l2[15],l2len=llen;
		for(i=0;i<llen;i++)
		{
			l2[i]=l[i];
		}
		do
		{
			printf("请输入P2出牌数:");
			scanf("%d",&llen);
			if(llen!=0) printf("请输入P2出牌:");
			for(i=0;i<llen;i++)
			{
				scanf("%d",&l[i]);
			}
		}while(!canout(l,llen,l2,l2len));
		l2len=llen;
		for(i=0;i<llen;i++)
		{
			l2[i]=l[i];
		}
		for(i=0;i<p2len;i++)
		{
			for(int j=0;j<l2len;j++)
			{
				if(p2[i]==l2[j])
				{
					p2[i]=l2[j]=0;
					break;
				}
			}
		}
		new3len=0;
		for(j=0;j<p2len;j++)
		{
			if(p2[j]!=0)
			{
				new3[new3len]=p2[j];
				new3len++;
			}
		}
		p2len=new3len;
		for(j=0;j<p2len;j++)
		{
			p2[j]=new3[j];
		}
	}
	getch();
	return 0;
}
