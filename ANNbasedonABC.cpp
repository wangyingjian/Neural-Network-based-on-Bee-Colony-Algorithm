#include <iostream>
#include "time.h"
#include <math.h>
#define exp 2.71828

using namespace::std;



double sigmod(double a)
{
	double temp=1/(1+pow(exp,-a));
	return temp;
}


double model(double a1,double a2,double b1,double b2)
{	
	double y=(0.8-0.5*pow(exp,(-a2*a2)))*a2-(0.3+0.9*pow(exp,(-a2*a2)))*a1+b2+0.2*b1+0.1*b1*b2;
	return y;
}
double fitness(double a)
{

		return 1/(1+a);

}
double iffit(double *a[],double *b[],int c,int d,int e,int f,int g)//a-sample b-weight c-samplenum d-hidden num e-numx f-w1 g-employee
{
	double *hidden= new double [d];
	double *y= new double [c];
	double fit=0;
	for(int j=0;j<c;j++)
	{
		y[j]=0;
		for(int i=0;i<d;i++)
		{
			hidden[i]=0;
			for(int m=0;m<4;m++)
			{
				hidden[i]=hidden[i]+b[g][m+4*i]*a[j][m];
			}
			double temp=hidden[i]+b[g][e-2-i];
			hidden[i]=sigmod(temp);
			y[j]=y[j]+hidden[i]*b[g][i+f];
		}
		y[j]=y[j]+b[g][e-1];
		y[j]=(a[j][4]-y[j]);
		fit=fit+pow(y[j],2);
	
	}		
	fit=fitness(fit/c);

	return fit;
}
double iffit1(double *a[],double *b[],int c,int d,int e,int f,int g)//a-sample b-weight c-samplenum d-hidden num e-numx f-w1 g-employee
{
	double *hidden= new double [d];
	double *y= new double [c];
	double fit=0;
	for(int j=0;j<c;j++)
	{
		y[j]=0;
		for(int i=0;i<d;i++)
		{
			hidden[i]=0;
			for(int m=0;m<4;m++)
			{
				hidden[i]=hidden[i]+b[g][m+4*i]*a[j][m];
			}
			double temp=hidden[i]+b[g][e-2-i];
			hidden[i]=sigmod(temp);
			y[j]=y[j]+hidden[i]*b[g][i+f];
		}
		y[j]=y[j]+b[g][e-1];
		y[j]=(a[j][4]-y[j]);
		cout<<j<<":"<<y[j]<<endl;
		fit=fit+pow(y[j],2);
		cout<<fit<<endl;
	
	}		
	fit=fit/c;

	return fit;
}
double error(double *a[],double *b[],int c,int d,int e,int f,int g)//a-sample b-weight c-samplenum d-hidden num e-numx f-w1 g-employee
{
	double *hidden= new double [d];
	double *y= new double [c];
	double fit=0;
	for(int j=0;j<c;j++)
	{
		y[j]=0;
		for(int i=0;i<d;i++)
		{
			hidden[i]=0;
			for(int m=0;m<4;m++)
			{
				hidden[i]=hidden[i]+b[g][m+4*i]*a[j][m];
			}
			double temp=hidden[i]+b[g][e-2-i];
			hidden[i]=sigmod(temp);
			y[j]=y[j]+hidden[i]*b[g][i+f];
		}
		y[j]=y[j]+b[g][e-1];
		y[j]=(a[j][4]-y[j]);
		
		fit=fit+pow(y[j],2);
	
	}		

	return fit/c;
}


void main()
{
	srand((unsigned)time(NULL));
	int num;//#nodes of hidden layer
	int samplenum;//size of sample
	int colony;
	//int numx,numy;//weights from input to hidden layer, weights from hidden layer to output
	cout<<"input the number of the nodes of hidden layer:";
	cin>>num;
	cout<<"input size of sample:";
	cin>>samplenum;
	cout<<"input number of colonies:";
	cin>>colony;
	colony=colony/2*2;
	//cout<<colony;
	int overall=0;
	int employee=colony/2;
	int numx=5*num+1+num;
	int w1=4*num;
	int w2=num;
	double *p=new double [employee];
	double addp;
	double temp_p;
	double **food=new double *[employee];
	double **food2=new double *[employee];	
	double *count=new double[employee];
	double judge=0;
	for(int i=0;i<employee;i++)
	{
		count[i]=0;
	}
	for(int i=0;i<employee;i++)
	{
		food[i]=new double[numx];
		food2[i]=new double[numx];
		for(int j=0;j<numx;j++)
		{
			food[i][j]=((double)rand()/RAND_MAX*4-2);
			food2[i][j]=food[i][j];
		}
	}


///////////////////////////////////////////////////////////////////////////
	double **a=new double *[samplenum];
	for(int i=0;i<samplenum;i++)
	{
		a[i]=new double[5];
	}
	for(int i=0;i<4;i++){
			
		a[0][i]=((double)rand()/RAND_MAX*2-1);//a[samplenum][i]
		cout<<a[0][i]<<endl;
	}
	a[0][4]=model(a[0][0],a[0][1],a[0][2],a[0][3]);//the first sample finished
	for(int i=1;i<samplenum;i++)
	{
		a[i][0]=a[i-1][1];
		a[i][1]=a[i-1][4];
		a[i][2]=a[i-1][3];
		a[i][3]=((double)rand()/RAND_MAX*2-1);
		a[i][4]=model(a[i][0],a[i][1],a[i][2],a[i][3]);
	}//all sample finished
	/////////////////////////////////////////////////////////////////////
	//employee
	////////////////////////////////////////////////////////////////////
L1:	
	addp=0;
	for(int i=0;i<employee;i++)
	{
		int k=rand()%(employee-1);
		
		
		if(i==k)
		{
			k=employee-1;
		}
		//cout<<k<<endl;
		int k2=rand()%(numx);
		
		double temp=((double)rand()/RAND_MAX*2-1);
			
		food2[i][k2]=food2[i][k2]+temp*(food2[i][k2]-food[k][k2]);
		
		if(food2[i][k2]>2)
		{
			food2[i][k2]=2;
		}
		else if(food2[i][k2]<-2)
		{
			food2[i][k2]=-2;
		}
		double temp1=(iffit(a,food,samplenum,num,numx,w1,i));
		double temp2=(iffit(a,food2,samplenum,num,numx,w1,i));
		if(temp1<temp2)
		{
			p[i]=temp2;
			food[i][k2]=food2[i][k2];
		}
		else
		{
			p[i]=temp1;
			food2[i][k2]=food[i][k2];
			count[i]++;
		}
		addp=addp+p[i];
	}
	///////////////////////////////////////////////////////////////////////
	//observer
	///////////////////////////////////////////////////////////////////////
	
	for(int i=0;i<employee;i++)
	{
		count[i]=count[i]+1;
	}
	for(int j=0;j<employee;j++)
	{
		temp_p=0;
		double temp=((double)rand()/RAND_MAX*addp);
		int n=0;
		for(int i=0;i<employee;i++)
		{
			temp_p=temp_p+p[i];
			if(temp>temp_p)
			{
				n=n+1;
			}
			else
			{
				//cout<<n<<endl;
				int k=(rand()%(employee-1));
				if(n==k)
				{
					k=employee-1;
				}
				int k2=(rand()%(numx));
				//cout<<k<<endl;
				//for(int h=0;h<numx;h++)
				//{
				double tempnum=((double)rand()/RAND_MAX*2-1);
				//food2[n][h]=food[n][h];
				food2[n][k2]=food2[n][k2]+tempnum*(food2[n][k2]-food[k][k2]);//(1/(1+pow(k,0.2)))*
			//	}
				if(food2[n][k2]>2)
				{
					food2[n][k2]=2;
				}
				else if(food2[n][k2]<-2)
				{
					food2[n][k2]=-2;
				}
				double temp1=(iffit(a,food,samplenum,num,numx,w1,n));
				double temp2=(iffit(a,food2,samplenum,num,numx,w1,n));
				if(temp1<temp2)
				{
					p[n]=temp2;
					
					food[n][k2]=food2[n][k2];
					
				}else
				{
					food2[n][k2]=food[n][k2];
					count[n]++;
				}

				
				break;
			}
		}
	}
	cout<<endl;
	/////////////////////////////////////////////////////////////////////////////////////////////
	//find new food
	/////////////////////////////////////////////////////////////////////////////////////////////
	
	
	double best=-10;
	int bestnum;
	for(int i=0;i<employee;i++)
	{
		if(best<p[i])
		{
			best=p[i];
			bestnum=i;
		}
	}
	double worest=INT_MAX;
	int worestnum;
	for(int i=0;i<employee;i++)
	{
		if(worest>p[i])
		{
			worest=p[i];
			worestnum=i;
		}
	}
	if(count[worestnum]>employee)
	{
			for(int j=0;j<numx;j++)
		{
			food[worestnum][j]=((double)rand()/RAND_MAX*4-2);
			food2[worestnum][j]=food[worestnum][j];
		}
		p[worestnum]=(iffit(a,food,samplenum,num,numx,w1,worestnum));
		count[worestnum]=0;
	}
	overall++;
	judge=(error(a,food,samplenum,num,numx,w1,bestnum));
	cout<<judge<<endl;
	cout<<overall<<endl;
	if(judge>0.01)
	{
		goto L1;
	}
	system("pause");
}