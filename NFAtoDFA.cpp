#include<bits/stdc++.h>
using namespace std;

int n,m,f,t;

struct NFAstate{
	vector<int> transitions[30];
};

vector<NFAstate> NFAstates;

struct DFAstate
{
	bool finalState;
	bitset<100005> constituentNFAstates;
	bitset<100005> transitions[30];
	int symbolicTransitions[30]; 
};

map<int,bool > NFA_finalStates;
vector<int> DFA_finalStates;
vector<DFAstate> DFAstates;
queue<int> incompleteDFAstates;

void epsilonClosure(int state,bitset<100005> &closure)
{
	

	for(auto c:NFAstates[state].transitions[0])
	{
		if(closure[c]==0)
		{
			closure[c]=1;
			epsilonClosure(c,closure);
		}
	}
}
void NFAmove(int X, int A, bitset<100005> &Y)
{
	
	for(auto c:NFAstates[X].transitions[A])
	Y[c]=1;
	
}

int main()
{		

	freopen("NFA.txt","r",stdin);
	freopen("preDFA.txt","w",stdout);
	
	double time=clock();
	
	cin>>n>>m>>f;
	
	
	for(int i=0;i<n;i++)
	{
		NFAstate sta;
		
		NFAstates.push_back(sta);
	}
	
	
	for(int i=0;i<f;i++)
	{
		int x;
	
		cin>>x;
		
		NFA_finalStates[x]=true;
	}
	
	
	
	cin>>t;
	
	while(t--)
	{
		int x,a,y,j;
		
		cin>>x>>a>>y;
		
		while(y--)
		{
			cin>>j;
			
			NFAstates[x].transitions[a].push_back(j);
			
			//cout<<t<<endl;
		}
	}
	
	//cout<<t<<endl;
	
	
	
	int d=1;
	
	
	
	DFAstate now;
	
	now.constituentNFAstates[0]=1;
	
	//cout<<now.constituentNFAstates;
	
	epsilonClosure(0,now.constituentNFAstates);
	
	
	
	DFAstates.push_back(now); 
	
	
	
	for(int j=0;j<n;j++)
	{
		if(DFAstates[0].constituentNFAstates[j]==1 and NFA_finalStates[j]==true)
		{	
			DFAstates[0].finalState=true;
			DFA_finalStates.push_back(0);
			break;
		}	
	}
	
	
	
	incompleteDFAstates.push(0);
	
	while(!incompleteDFAstates.empty())
	{
		
	
		int x=incompleteDFAstates.front(); incompleteDFAstates.pop();
		
		for(int i=1;i<=m;i++)
		{
			for(int j=0;j<n;j++)
			if(DFAstates[x].constituentNFAstates[j]==1)
			NFAmove(j,i,DFAstates[x].transitions[i]);
			
//		
		

			for(int j=0;j<n;j++)
			if(DFAstates[x].transitions[i][j]==1)
			epsilonClosure(j,DFAstates[x].transitions[i]);
			
			
			
			bool flag=true;
			
			for(int j=0;j<d;j++)
			if(DFAstates[x].transitions[i]==DFAstates[j].constituentNFAstates)
			{
				DFAstates[x].symbolicTransitions[i]=j;
				flag=false;
				break;
			}
			
			if(flag==true)
			{
				DFAstates[x].symbolicTransitions[i]=d;
				
				DFAstate now;
				
				now.constituentNFAstates=DFAstates[x].transitions[i];
				
				DFAstates.push_back(now);
				
				for(int j=0;j<n;j++)
				if(DFAstates[d].constituentNFAstates[j]==1 and NFA_finalStates[j]==true)
				{
					DFAstates[d].finalState=true;
					DFA_finalStates.push_back(d);
					break;
				}
				
				incompleteDFAstates.push(d);
				d++;
				
			}
	
		}
		
		
	
	}
	
	cout<<d<<" "<<m<<endl;
	
	cout<<DFA_finalStates.size()<<" ";
	
	for(auto c:DFA_finalStates)
	cout<<c<<" ";
	
	cout<<endl;
	
	for(int i=0;i<d;i++)
	for(int j=1;j<=m;j++)
	cout<<i<<" "<<j<<" "<<DFAstates[i].symbolicTransitions[j]<<endl;
	
	time=(clock()-time)/CLOCKS_PER_SEC;	
 	
 	printf("%0.4f",time);
	
	
	
}

