#include <bits/stdc++.h>
using namespace std;
#define ll long long
#include<pthread.h>
#include <unistd.h>
#include <time.h>
ll t;

ll tobac=0;
ll pape=0;
ll match=0;
ll agent=1;

void sema_wait(ll &s){
	while(s<=0);
	s--;
}

void sema_signal(ll &s){
	s++;
}

void smoke(){
	sleep(1);
}

void *s1(void * arguments){
	sema_wait(match);
	//smoker one smoking;
	cout<<"smoker 1 started smoking by picking paper and tobacco from the table"<<endl;
	smoke();
	cout<<"smoker 1 completed smoking"<<endl;
	sema_signal(agent);
	return NULL;
}
void *s2(void * arguments){
	sema_wait(pape);
	//smoker one smoking;
	cout<<"smoker 2 started smoking by picking matches and tobacco from the table"<<endl;
	smoke();
	cout<<"smoker 2 completed smoking"<<endl;
	sema_signal(agent);
	return NULL;
}
void *s3(void * arguments){
	sema_wait(tobac);
	//smoker one smoking;
	cout<<"smoker 3 started smoking by picking paper and matches from the table"<<endl;
	smoke();
	cout<<"smoker 3 completed smoking"<<endl;
	sema_signal(agent);
	return NULL;
}


int main() {
    
    
     pthread_t matches;
     pthread_t paper;
     pthread_t toba;
     cin>>t;
     for(ll j=0;j<t;j++){sema_wait(agent);
     	if(j%3==0){  
     		sema_signal(match);
     		pthread_create(&matches,NULL,s1,NULL);
     		pthread_join(matches,NULL);
     		
     	}
     	else if(j%3==1){  
     		sema_signal(pape);
     		pthread_create(&paper,NULL,s2,NULL);
     		pthread_join(paper,NULL);
     		
     	}
     	else{ 
     		sema_signal(tobac);
     		pthread_create(&toba,NULL,s3,NULL);
     		pthread_join(toba,NULL);
     		
     	}
     	
     }


	return 0;
}
