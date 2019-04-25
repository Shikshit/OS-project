#include<stdio.h> 
#include<conio.h>

void rr(int no,int remt[10],int curtt,int arT[10], int bsT[10]);

main() 
{
	int procc,j,no,CurT,Rem,indicator=0,time_quan,wait=0,tut=0,arT[10],bsT[10],remt[10],x=1;
	printf("Enter number of processes "); 
	scanf("%d",&no);
	Rem = no;
	
	printf("\nEnter the arrival time and burst time of the processes\n");
	for(procc = 0;procc < no;procc++) 
	{
		printf("\nProcess P%d\n",procc+1);
		printf("Arrival time = "); 
		scanf("%d",&arT[procc]);
		printf("Burst time = "); 
		scanf("%d",&bsT[procc]); 
		remt[procc]=bsT[procc]; 
	} 
	printf("The details of time quantum are as follows:\n");
	printf("The time quantum for first round is 3.\n"); 
	time_quan=3;
	CurT=0;
	for(procc=0;Rem!=0;) 
	{
		if(remt[procc]<=time_quan && remt[procc]>0)
		{ 
			CurT+=remt[procc]; 
			remt[procc]=0; 
			indicator=1; 
		} 
		else if(remt[procc]>0)
		{ 
			remt[procc]-=time_quan; 
			CurT+=time_quan; 
		} 
		if(remt[procc]==0 && indicator==1)			
		{ printf("%d",procc);
			Rem--;				
			printf("P %d",procc+1); 
			printf("\t\t\t%d",CurT-arT[procc]);
			printf("\t\t\t%d\n",CurT-bsT[procc]-arT[procc]);
			wait+=CurT-arT[procc]-bsT[procc]; 
			tut+=CurT-arT[procc]; 
			indicator=0; 
                       
		} 
		if(procc==no-1){
			x++;
			if(x==2){
				procc=0;
				time_quan=6;
				
				printf("The time quantum for second round is 6. \n");
			}
			else{
				break;
			}
		}
		else if(CurT >= arT[procc+1]){
			procc++;
		}
		else{
			procc=0;
		}
	}
	
	rr(no,remt,CurT,arT,bsT);
	
	return 0;
}


void rr(int no,int remt[10],int curtt,int arT[10], int bsT[10]){
	
	float avg_wait,avg_tut;
    int i,j,n=no,temp,btime[20],procc[20],w_time[20],tut_t[20],total=0,loc;
    
    printf("Third round with least burst time.\n");
    
    for(i=0;i<n;i++)
    {
        btime[i]=remt[i];
        w_time[i]=curtt-arT[i]-btime[i];
		procc[i]=i+1;
    }
	
    for(i=0;i<n;i++)
    {
        loc=i;
        for(j=i+1;j<n;j++)
        {
            if(btime[j]<btime[loc]){
            	loc=j;
            }
        }
        temp=btime[i];
        btime[i]=btime[loc];
        btime[loc]=temp;
        temp=procc[i];
        procc[i]=procc[loc];
        procc[loc]=temp;
    }
	
    for(i=1;i<n;i++)
    {
        for(j=0;j<i;j++){
        	w_time[i]+=btime[j];
        }
        total+=w_time[i];
    }
 
    avg_wait=(float)total/n;
    total=0;
    printf("\nProcess\t\tBurst time\t\twaiting time\t\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tut_t[i]=btime[i]+w_time[i];
        total=total + tut_t[i];
        printf("\nP%d\t\t\t%d\t\t\t%d\t\t\t%d",procc[i],btime[i],w_time[i],tut_t[i]);
    }
    avg_tut=(float)total/n;
    printf("\n\nAverage waiting time = %f",avg_wait);
    printf("\n Average turnaround time = %f\n",avg_tut);
	
}



