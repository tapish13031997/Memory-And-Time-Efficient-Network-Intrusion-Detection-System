#include<bits/stdc++.h>
using namespace std;

long long int i,j,ans,n,x,y,m,mymax=LLONG_MIN,mymin=LLONG_MAX,b,c,z,sum;

map <vector<long long int>,long long int> t_table,tf_table;//transitions table

bool is_finale[MAX_STATES];

vector <long long int> row_t_table[MAX_STATES];

vector <pair<long long int,long long int> > occurrence[MAX_STATES];

long long int q0;

long long int mycount[MAX_STATES+10];

//void mergef(long long int original_state,long long int current_state);
void merge(long long int original_state,long long int current_state)//merging for non final_states
{
	 long long int k;
	 if(current_state==q0)
	 {
	  	q0=original_state;
	 }
	 for(int k=0;k<occurrence[current_state].size();k++)//up(0,occurrence[current_state].size(),k)
	 {
	  	  if(is_finale[occurrence[current_state][k].F]==false)
		  {
			  t_table.erase(row_t_table[occurrence[current_state][k].F]);
			  row_t_table[occurrence[current_state][k].F][occurrence[current_state][k].S-1]=original_state;
		          if(t_table.find(row_t_table[occurrence[current_state][k].F])==t_table.end())
		    	      t_table[row_t_table[occurrence[current_state][k].F]]=occurrence[current_state][k].F;
			  else
			      merge(t_table[row_t_table[occurrence[current_state][k].F]],occurrence[current_state][k].F);
		  }
		  
		 else
		  {
			  tf_table.erase(row_t_table[occurrence[current_state][k].F]);
			  row_t_table[occurrence[current_state][k].F][occurrence[current_state][k].S-1]=original_state;
			  if(tf_table.find(row_t_table[occurrence[current_state][k].F])==tf_table.end())
			      tf_table[row_t_table[occurrence[current_state][k].F]]=occurrence[current_state][k].F;
			  else
			      merge(tf_table[row_t_table[occurrence[current_state][k].F]],occurrence[current_state][k].F);
		  }
	 
	 }
	 
}


int main()
{
       long long int k;
       
       freopen("preDFA.txt","r",stdin);
       freopen("minDFA.out","w",stdout);
       
       long long int no_of_states,no_of_symbols,no_of_final_states;
       
       cin>>no_of_states>>no_of_symbols;//symbol from 1 to no_of_symbols
       
        //states from 0 to no_of_states-1
       vector <long long int> final_states;
       
       cin>>no_of_final_states;
       
       long long int transitions[no_of_states+10][no_of_symbols+10];
       
       for(int i=0;i<no_of_final_states;i++)//up(0,no_of_final_states,i)
       {
	       cin>>x;
	       is_finale[x]=true;
       }
       
       long long int source,symbol,destination;
       
       while(cin>>source>>symbol>>destination)
       {
          transitions[source][symbol]=destination;
          occurrence[destination].pb({source,symbol});
          mycount[destination]++;
       }
       
       for(int i=0;i<no_of_states;i++)//up(0,no_of_states,i)
       {
		vector<long long int> temp;
		
		if(mycount[i]==0)//removes states that are unreachable
		  continue;
		  
		for(int j=1;j<no_of_symbols;j++)//up(1,no_of_symbols+1,j)
		{
		  temp.push_back(transitions[i][j]);
		}  
		
		if(is_finale[i]==true)
		{
			  if(tf_table.find(temp)!=tf_table.end())
			  {
			      long long int original_state=tf_table[temp];
			      merge(original_state,i);
			  }
			  else
			  {
			      tf_table[temp]=i;
			      row_t_table[i]=temp;
			  }
		}
		else
		{
			  if(t_table.find(temp)!=t_table.end())
			  {
			      long long int original_state=t_table[temp];
			      merge(original_state,i);
			  }
			  else
			  {
			      t_table[temp]=i;
			      row_t_table[i]=temp;
			  }
		}
       }
       //output format
       //total_states
       //total_transition
       //initial state
       //no of final_states
       //transitions
       //final states
       no_of_states=0;
       no_of_final_states=0;
       
       vector<pair<long long int,long long int> > final_transitions[MAX_STATES+10];
       
       long long int no_of_transitions=0;
       
       for(auto states:t_table)
       {
		j=1;
		long long int current_state=states.S;
		no_of_states++;
		for(auto kk:states.F)
		{
		  final_transitions[current_state].pb({j,kk});
		  no_of_transitions++;
		  j++;
		}
       } 
       
       for(auto states:tf_table)
       {
		j=1;
		long long int current_state=states.S;
		no_of_states++;
		no_of_final_states++;
		final_states.pb(current_state);
		for(auto kk:states.F)
		{
		  final_transitions[current_state].pb({j,kk});
		  no_of_transitions++;
		  j++;
		}
       }
       
       cout<<no_of_states<<' '<<no_of_transitions<<' '<<q0<<' '<<no_of_final_states<<endl;
       
       for(int i=0;i<MAX_STATES+10;i++)//up(0,MAX_STATES+10,i)
       {
		for(auto kk:final_transitions[i])
		{
		  cout<<i<<' '<<kk.F<<' '<<kk.S<<endl;
		}
       }
       
       for(auto kk:final_states)
       {
        	cout<<kk<<' ';
       }
       
       cout<<endl;
       return 0;
}
