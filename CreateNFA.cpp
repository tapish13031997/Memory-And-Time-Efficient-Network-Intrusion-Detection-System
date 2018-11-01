#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;

long long int i,j,k,z,t,n,m,sum,ans,x,y,maxm=0,minm=inf; bool flag;

int main()
{
	freopen("NFA.txt","w",stdout);
	freopen("keywords.txt","r",stdin);
	
	cin>>n;
	
	string s[n];
	
	vector<long long int> sta,en;
	long long int cur=0;
	
	map<char,vector<long long int> > sta0;
	
	vector<pair<plong long int,long long int>> tra;
	
	for(char c='a';c<='z';c++)
	sta0[c].push_back(0);
	
	for(int i=0;i<n;i++)
	{
		cin>>s[i];
		
		sta0[s[i][0]].push_back(++cur);
		
		for(int j=1;j<s[i].size();j++)//up(1,s[i].size(),j)
		tra.pb({{cur,s[i][j]-'a'+1},++cur});
		
		en.push_back(cur);
		
	}
	
	cout<<cur+1<<" "<<26<<endl;//pd(cur+1,26);
	
	cout<<n<<" ";//ps(n);
	
	for(auto c:en)
	cout<<c<<" ";//ps(c);
	
	cout<<endl;
	
	cout<<tra.size()+sta0.size()<<endl;//pp(tra.size()+sta0.size());
	
	
	
	for(auto c:sta0)
	{
		cout<<"0 "<<int(c.F)-int('a')+1<<" ";
		cout<<c.S.size()<<" ";
		for(auto d:c.S) 
		cout<<d<<" ";
		
		cout<<endl;}
	
	
	for(auto c:tra)
	cout<<c.F.F<<" "<<c.F.S<<" "<<"1 "<<c.S<<endl;
	
	
	
	
	
	  		
}
	
