#include <bits/stdc++.h>
using namespace std;
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define ll long long
queue<string> fifo;
queue<string> qu;
vector<ll> vec;
ll cs_mutex=1;
ll execute=1;
pthread_mutex_t read_ct;
ll readerscount=0;
clock_t start;
ll cre=1;
void sema_waiti(ll &s){
	while(s<=0);
	s--;
}


void sema_signal(ll &s){
	s++;
}

void reading1(){
	sleep(1);
}

void writingh(){
	sleep(1);
}

 void *reading(void *arguments){
 	
 string s=*((string *)(arguments));
 clock_t tr=clock();

 		cout<<"thread started "<<s<<endl;
 	
 	pthread_mutex_lock(&read_ct);
 	readerscount++;
 	if(readerscount==1)
 	sema_waiti(cs_mutex);
 	pthread_mutex_unlock(&read_ct);
 	sema_signal(execute);
 	
 	
 	//reading
 	reading1();
 
 	
 	pthread_mutex_lock(&read_ct);
 	readerscount--;	
    cout<<"thread completed "<<s<<endl;
 	if(readerscount==0)
 	sema_signal(cs_mutex);
 	pthread_mutex_unlock(&read_ct);
 	
 	
 	
 	return NULL;
 }
 
 
 void *writing(void *arguments){

string s=*((string *)(arguments));
clock_t tw=clock();

cout<<"thread started "<<s<<endl;

sema_waiti(cs_mutex);

//witing;
writingh();

sema_signal(cs_mutex);	
cout<<"thread completed "<<s<<endl;
sema_signal(execute);


 
 
 return NULL;
 }
 
 
 
 void *executionofthreads(void * arguments){
 	 pthread_t write;ll vec_ind=0;
      while(1){
      	if(fifo.size()<=0)break;
      	else{  
      		if((fifo.front())[0]=='r'){
      			pthread_t reader[vec[vec_ind]];
                vec_ind++;
      			for(ll j=0;j<vec[vec_ind-1];j++){
      				sema_waiti(execute);
      				string p=fifo.front();
      				 pthread_create(&reader[j],NULL,reading,&(p));
      				 fifo.pop();
      				sleep(0.1);
      				
      			}
      			for(ll j=0;j<vec[vec_ind-1];j++){
      				pthread_join(reader[j],NULL);
      			}
      		}
      		else
      		{sema_waiti(execute);
      		string p=fifo.front();fifo.pop();
      		pthread_create(&write,NULL,writing,&p);
      		 pthread_join(write,NULL);
      	     }
        }
        pthread_t read;  
    }
        
return NULL; }

void *create_readers(void *ar){
	int p=((int )ar);
	string s="r";
	for(ll j=1;j<=p;j++){
		//sema_waiti(cre);
		s="r";
		s+=to_string(j);
		qu.push(s);
		//sema_signal(cre);
	}
	return NULL;
}
 void *create_writers(void *ar){sleep(0.625);
		int q=((int )ar);
		string s="wr";
	for(ll j=1;j<=q;j++){
		//sema_waiti(cre);
		s="wr";
		s+=to_string(j);
		qu.push(s);
		//sema_signal(cre);
	}
	return NULL;
}

int main() {
pthread_mutex_init(&read_ct,NULL);
ll cas;
cout<<"Enter 1 for manual input else 0"<<endl;
cin>>cas;
if(cas==0){
ll no_of_readers;
ll no_of_writers;ll c=0;
cout<<"Input number of readers"<<endl;
cin>> no_of_readers;
cout<<"Input number of writers"<<endl;
cin>> no_of_writers;
	pthread_t re;
	pthread_t wr;
    pthread_create(&wr,NULL,create_writers,&no_of_writers);
	pthread_create(&re,NULL,create_readers,&no_of_readers);
		
		pthread_join(re,NULL);
		pthread_join(wr,NULL);
     
	while(qu.size()!=0){
	string d=qu.front();
	cout<<d<<endl;
	if(d[0]=='r')c++;
	else if(c!=0){
	vec.push_back(c);c=0;
	}
	fifo.push(d);
	qu.pop();
}  if(c!=0)
   vec.push_back(c);

    }
	else{
    ll t;cin>>t;
	string x;ll c=0;
	clock_t start=clock();
	for(ll j=0;j<t;j++)
   {cin>>x;if(x[0]=='r')c++;
   else if(c!=0){
   	vec.push_back(c);c=0;
   }
   	fifo.push(x);
   }
   if(c!=0)
   vec.push_back(c);
    }

   pthread_t yt;
   pthread_create(&yt,NULL,executionofthreads,NULL);
   pthread_join(yt,NULL);
	return 0;
}
