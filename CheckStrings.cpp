/*
* Check whether the string is accepted by the DFA or not
*/
#include<bits/stdc++.h>
using namespace std;

map <char,long long int> transitions[max_no_of_states];

int main()
{
	
	  fstream in_dfa;
	  in_dfa.open("minDFA.out",ios::in);
	  
	  long long int no_of_states,no_of_transitions,q0,no_of_final_states;
	  
	  in_dfa>>no_of_states>>no_of_transitions>>q0>>no_of_final_states;
	  
	  set<long long int> final_states;
	  long long int i;
	  
	  for(int i=0;i<no_of_transitions;i++)// up(0,no_of_transitions,i)
	  {
		  long long int source,destination,label;
		    
		  in_dfa>>source>>label>>destination;
		    
		  if(!isalpha(label))
		  {
	     	      //cout<<"converting_labels into character assuming a to be 0\n";
		      label+='a';
		  }
		    
		  transitions[source][char(label-1)]=destination;
		  //    cout<<source<<' '<<char(label)<<' '<<destination<<endl;
		  
	  }
	
	  
	  for(int i=0;i<no_of_final_states;i++)//up(0,no_of_final_states,i)
	  {
		  long long int temp;
		    
		  in_dfa>>temp;

		  final_states.insert(temp);
	  }
	  
	  in_dfa.close();
	  
	  fstream fin;
          fin.open("sam.txt",ios::in);
	    
	  double time=clock();
	  
	  while(!fin.eof())
	  {
		    //cout<<"Enter string to be checked\nEnter -1 to exit\n";
		    string input;
		    
		   
		    fin>>input;
		    
		    if(input=="-1")break;
		    
		    i=0;
		    
		    long long int current_state=q0;
		    
		    while(i<input.size())
		    {
			    	if(isalpha(input[i]))
			    	input[i]=tolower(input[i]);
			    	
			    	else
			    	if(input[i]<'a' or input[i]>'z')
			    	{
			    		current_state=0;
			    		i++;
			    		continue;
			    	}
			    
			      if(transitions[current_state].find(input[i])==transitions[current_state].end())
			      {
				break;
			      }
			      current_state=transitions[current_state][input[i]];
			      
			       if(final_states.find(current_state)!=final_states.end())
			       {
			       		//cout<<"Block ";//input<<endl;
			       		break;
			       }
			      
			     // cout<<current_state<<endl;
			      i++;
		    }
		    
		    if(final_states.find(current_state)==final_states.end())
		    {
		      //cout<<"Allow ";//input<<endl;
		    }
		    
	    
	  }
	  
	  time=(clock()-time)/CLOCKS_PER_SEC;
	  
	  cout<<time<<endl;
	  
	  fin.close();
	  
	  return 0;
}
