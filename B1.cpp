

#include <iostream>
using namespace std;

int main() {
	{ int m,n,k;
	  int pos;
	    cout<<"\n m = "; 
	    cin>>m;
	     cout<<"\n n= "; 
	    cin>>n;
	     cout<<"\n k = "; 
	    cin>>k;
      int  s[m][n]; int p1=-1,p2=-1;
    
      cout<<"\n2D Array Input:\n";
      for(int i=0;i<m;i++)
      {
        for(int j=0;j<n;j++)
        {
            cout<<"\ns["<<i<<"]["<<j<<"]=  ";
            cin>>s[i][j];
        }
      } 
       
      
      for(int i=0;i<m;i++)
      {
          if(s[i][0]<=k && s[i][n]>=k)
      { 
        for(int j=0;j<n;j++)
        {
            if(s[i][j]==k)
            {
                p1=i;
                p2=j;
            }
        }
       
      } 
      }
      if(p1==-1||p2==-1)
      {
          cout<<"False";
      }
      else{
          cout<<"True\n";
          cout<<p1<<" "<<p2<<" ";
      }
      
} }


