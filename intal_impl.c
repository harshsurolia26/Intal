#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"intal.h"
struct input
{
    int size;
    int number[0];
};
typedef struct input input;
void* power_divide(void* intal1, void* intal2);
void *remove_leading_zeros(input *intal);
void* power(void* intal,void * intal2,void * intal_by_2);
void* intal_create(const char*str)
{
	int i=0;
	long long unsigned int j=0;
	int n=strlen(str);
	int check=0;
	for(i=0;i<n;i++)
	{
		if(str[i]<'0' || str[i]>'9' || str==NULL)
		{
			check=1;
			break;
		}
	}
	i=0;
	if(check==1)
	{
	    input* i1=(input*)malloc(sizeof(input));
		i1->size=-1;
		return i1;
	}
	while(str[j]==48 && j<n) //ignore leading zeros
        j++;
	if(j==n)
	{
		input* i1=(input*)malloc(sizeof(input)+1*sizeof(int));
		i1->size=1;
		i1->number[0]=0;
		return i1;
	}
    input* i1=(input*)malloc(sizeof(input)+(n-j)*sizeof(int));
	i1->size=n-j;
	for(;j<n;j++)
	{
		i1->number[i++]=str[j]-'0';
	}
	return i1;
}

char* intal2str(void* intal)
{
	int i=0;
	int j=0;
	input *i1=(input *)intal;
	if(i1->size==-1)
	{
		return "NaN";
	}
	char *ch=(char*)malloc((i1->size+1)*sizeof(char));
	if(i<i1->size)
    {
	for(i=0;i<i1->size;i++)
	{
		ch[j++]=i1->number[i]+'0';
	}
    }
    else
        ch[j++]=0+'0';

    ch[j]='\0';
	return ch;
}

void* intal_increment(void* intal)
{
    input *i1=(input*)intal;
	if(i1->size==-1)
	{
		input *i2=(input*)malloc(sizeof(input));
		i2->size=-1;
		return i2;	
	}
    input *i2=(input*)malloc(sizeof(input)+(i1->size+1)*sizeof(int));
    i2->size=i1->size+1;
    int k=i1->size-1;
    int carry=1;
    int sum=0;
    long long unsigned int j=0;;
    int i=0;
    while(k>=0)
    {
        int sum=i1->number[k]+carry;
        i2->number[k+1]=sum%10; //placing the sum in the end
        carry=sum/10;
        k--;
    }
    i2->number[0]=carry;
    while(i2->number[j]==0 && j<i2->size)
        j=j+1;
    input *temp=(input*)malloc(sizeof(input)*(i2->size-j)*sizeof(int));
    temp->size=i2->size-j;
    for(;j<i2->size;j++)
    {
        temp->number[i]=i2->number[j];
        i=i+1;
    }
    free(i2);
    return temp;

}
void* intal_decrement(void* intal)
{
    input *temp;
    int nodec=0;
    input*i1=(input*)intal;
	if(i1->size==-1)
	{
		input *i2=(input*)malloc(sizeof(input));
		i2->size=-1;
		return i2;	
	}
	if(i1->size==1)
	{
		if(i1->number[0]==0)
		{
			input *i2=(input*)malloc(sizeof(input)+1*sizeof(int));				
			i2->size=-1;
			return i2;
		}
	}
    input *i2=(input*)malloc(sizeof(input)+(i1->size)*sizeof(int));
    i2->size=i1->size;
    int carry=1;
    int k=i1->size-1;
    long long unsigned int j=0;
    int i=0;
    while(k>=0)
    {
        if(i1->number[k]==0 && nodec!=1)
        {
            i2->number[k]=10-carry;
            carry=1;
        }
        else
        {
            i2->number[k]=i1->number[k]-carry;
            carry=0;
            nodec=1;
        }
        k--;
    }
    if(nodec==0)
    {
        free(i2);
        return i1;
    }
    while(i2->number[j]==0)
        j++;

    temp=(input*)malloc(sizeof(input)+(i2->size-j)*sizeof(int));
    temp->size=i2->size-j;
    for(;j<i1->size;j++)
        temp->number[i++]=i2->number[j];
    free(i2);
    return temp;
}

int intal_compare(void* intal1, void* intal2)
{
	input *i1=(input*)intal1;
	if(i1->size==-1)
		return 0;
	input *i2=(input*)intal2;
	if(i2->size==-1)
		return 0;
	int i,j;
	if(i1->size==i2->size)
	{
		for(i=0;i<i1->size;i++)
		{
			if(i1->number[i]>i2->number[i])
				return 1;
			else if(i2->number[i]>i1->number[i])
				return -1;
		}
		if(i>=i1->size)
			return 0;
	}
	else if(i1->size>i2->size)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void* intal_add(void* intal1, void* intal2)
{
	long long unsigned int j=0;
	int i=0;
	input *temp;
	input *i1=(input  *)intal1;
	if(i1->size==-1)
		return i1;
	input *i2=(input  *)intal2;
	if(i2->size==-1)
		return i2;
	int size;
	if(i1->size>= i2->size)
        size=i1->size;
    else
        size=i2->size;
	int n=size;
	input* i3=(input*)malloc(sizeof(input)+(size+1)*sizeof(int));
	i3->size=size+1;
	int f=i1->size-1;
	int s=i2->size-1;
	int sum=0;
	int carry=0;
	while(f>=0 && s>=0)
    {
        sum=(i1->number[f]+i2->number[s]+carry)%10;
        i3->number[size]=sum;
        carry=(i1->number[f]+i2->number[s]+carry)/10;
        f--;
        s--;
        size--;
    }
    while(f>=0)
    {
        sum=(i1->number[f]+carry)%10;
        i3->number[size]=sum;
        carry=(i1->number[f]+carry)/10;
        f--;
        size--;
    }
    while(s>=0)
    {
        sum=(i2->number[s]+carry)%10;
        i3->number[size]=sum;
        carry=(i2->number[s]+carry)/10;
        s--;
        size--;
    }
    while(size>=0)
    {
        i3->number[size--]=0+carry;
        carry=0;
    }
    j=0;
    i=0;
    while(i3->number[j]==0 && j<i3->size)
        j++;
    if(j==i3->size)
    {
        temp=(input*)malloc(sizeof(input)+(1)*sizeof(int));
        temp->size=1;
        temp->number[0]=0;
    }
    temp=(input*)malloc(sizeof(input)+(i3->size-j)*sizeof(int));
    temp->size=i3->size-j;
    for(;j<i3->size;j++)
        temp->number[i++]=i3->number[j];
    free(i3);
    return temp;
}

void* intal_diff(void* intal1, void* intal2)
{
    int i=0;
    long long unsigned int j=0;
    input *i1=(input*)intal1,*i2=(input*)intal2,*i3;
    input *temp;
	if(i1->size==-1)
		return i1;
	if(i2->size==-1)
		return i2;
    int cmp=intal_compare(intal1,intal2);
    if(cmp==1)
    {
        i1=(input *)intal1;
        i2=(input *)intal2;
    }
    else if(cmp==-1)
    {
        i1=(input *)intal2;
        i2=(input *)intal1;

    }
    else if(cmp==0)
    {
        i3=(input *)malloc(sizeof(input)+1*sizeof(int));
        i3->size=1;
        i3->number[0]=0;
        return i3;
    }

    int size=i1->size;
    i3=(input *)malloc(sizeof(input)+(size+1)*sizeof(int));
    i3->size=size+1;
	int f=i1->size-1;
	int s=i2->size-1;
	int diff=0;
	int carry=0;
	while(f>=0 && s>=0)
    {
        diff=i1->number[f]-i2->number[s]-carry;
        if(diff<0)
        {
            diff=diff+10;
            carry=1;
        }
        else
        {
            carry=0;
        }
        i3->number[size]=diff;
        f--;
        s--;
        size--;
    }
    while(f>=0)
    {
        diff=i1->number[f]-carry;
        if(diff<0)
        {
            diff=diff+10;
            carry=1;
        }
        else
        {
            carry=0;
        }
        i3->number[size]=diff;
        f--;
        size--;
    }
    while(s>=0)
    {
       diff=i2->number[s]-carry;
        if(diff<0)
        {
            diff=diff+10;
            carry=1;
        }
        else
        {
            carry=0;
        }
        i3->number[size]=diff;
        s--;
        size--;
    }
    while(size>=0)
    {
        i3->number[size--]=0;
    }
    j=0;
    i=0;
    while(i3->number[j]==0 && j<i3->size)
        j++;
    if(j==i3->size)
    {
        temp=(input*)malloc(sizeof(input)+(1)*sizeof(int));
        temp->size=1;
        temp->number[0]=0;
    }
    else{
    temp=(input*)malloc(sizeof(input)+(i3->size-j)*sizeof(int));
    temp->size=i3->size-j;
    for(;j<i3->size;j++)
        temp->number[i++]=i3->number[j];
    }
    free(i3);
    return temp;
}

void* intal_multiply(void* intal1, void* intal2)
{
    int i=0;
    long long unsigned int j=0;
    input *temp;
    input *i1;
    input *i2;
    int cmp =intal_compare(intal1,intal2);
    if(cmp==1)
    {
        i1=(input*)intal1;
        i2=(input*)intal2;
    }
    else if(cmp==-1)
    {
        i1=(input*)intal2;
        i2=(input*)intal1;
    }
    else
    {
        i1=(input*)intal1;
        i2=(input*)intal2;
    }
	i1=(input*)intal1;
	i2=(input*)intal2;
	if(i1->size==-1)
		return i1;
	if(i2->size==-1)
		return i2;
    /*if(i1->size==1)
    {
        if(i1->number[0]==0)
            return i1;
    }
    else if(i2->size==1)
    {
        if(i2->number[0]==0)
            return i2;
    }*/
    int sum=0;
    input *i3=(input*)malloc(sizeof(input)+(i1->size+i2->size)*sizeof(int));
    i3->size=i1->size+i2->size;
    for(i=0;i<i3->size;i++)
        i3->number[i]=0;
    int offset=i1->size+i2->size-1;
    for(i=i2->size-1;i>=0;i--)
    {
        int carry=0;
        int k=0;
        int j=0;
        for(j=i1->size-1;j>=0;j--)
        {
            sum=i2->number[i]*i1->number[j];
            sum=sum+carry+i3->number[offset-k];
            carry=sum/10;
            i3->number[offset-k]=sum%10;
            k=k+1;
        }
        if(carry>0)
            i3->number[offset-k]=carry;
        offset=offset-1;
    }
    j=0;
    i=0;
    while(i3->number[j]==0 && j<i3->size)
        j++;
	if(j==i3->size)
	{
		temp=(input*)malloc(sizeof(input)+1*sizeof(int));
		temp->size=1;
		temp->number[0]=0;
		return temp;
	}
    temp=(input*)malloc(sizeof(input)+(i3->size-j)*sizeof(int));
    temp->size=i3->size-j;
    for(;j<i3->size;j++)
        temp->number[i++]=i3->number[j];
    free(i3);
    return temp;
}
    /*int i,j;
        int tmp=0;
    input *i1,*i2,*i3,*i4;
    i1=(input *)intal1;
    i2=(input *)intal2;
    if(i1->size > i2->size)
    {
        int k=i1->size-i2->size;
        i3=(input*)malloc(sizeof(input)+(i1->size)*sizeof(int));
        i3->size=i1->size;
        for(i=0;i<k;i++)
        {
            i3->number[i]=0;
        }
        for(i=0;i<i2->size;i++)
        {
            i3->number[i+k]=i2->number[i];
        }

    }
    else if(i1->size < i2->size)
    {
        int k=i2->size-i1->size;
        i3=(input*)malloc(sizeof(input)+(i2->size)*sizeof(int));
        i3->size=i2->size;
        for(i=0;i<k;i++)
        {
            i3->number[i]=0;
        }
        for(i=0;i<i1->size;i++)
        {
            i3->number[i+k]=i1->number[i];
        }

    }
    else
    {
        //printf("eq\n");
        i3=(input*)malloc(sizeof(input)+(i2->size)*sizeof(int));
        i3->size=i2->size;
        for(i=0;i<i2->size;i++)
        {
            i3->number[i]=i2->number[i];
        }
    }
    int r=i1->size+i3->size-1;
    i4=(input*)malloc(sizeof(input)+(i1->size+i3->size+1)*sizeof(int));
    i4->size=i1->size+i3->size+1;
    for(i=0;i<i4->size;i++)
    {
        i4->number[i]=0;
    }
    int sum=0;
    int sum1=0;
    int mul=0;
    int h=i1->size+i3->size;
    //printf("here1\n");
    printf("%d\n",i3->number[0]);
    if(i1->size==1 || i3->size==1)
    {
        //printf("here2\n");
        sum=i1->number[0];
        sum1=i3->number[0];
        mul=sum*sum1;
        while(mul!=0)
        {
        i4->number[h]=mul%10;
        mul=mul/10;
        //printf("mul:%d\n",mul);
        h--;
        //printf("here3\n");
        }
        return i4;
    }
    input *high1,low1,high2,low3;
    high1=(input*)malloc(sizeof(input)+(i1->size/2)*sizeof(int));
    high1->size=i1->size/2;
    low1=(input*)malloc(sizeof(input)+(i1->size-i1->size/2)*sizeof(int));
    low1->size=i1->size-i1->size/2;
    high2=(input*)malloc(sizeof(input)+(i1->size/2)*sizeof(int));
    high2->size=i1->size/2;
    low2=(input*)malloc(sizeof(input)+(i1->size-i1->size/2)*sizeof(int));
    low2->size=i1->size-i1->size/2;
    for(i=0;i<i1->size/2;i++)
    {
        high1[i]=i1->number[i];
    }
    for(i=i1->size/2;i<i1->size;i++)
    {
        low1[i]=i1->number[i];
    }
    for(i=0;i<i1->size/2;i++)
    {
        high2[i]=i3->number[i];
    }
    for(i=0;i<i1->size/2;i++)
    {
        low2[i]=i3->number[i];
    }
    void *z,z1,z2,z4;
    z=intal_multiply((void*)low1,(void*)low2);
    z1=intal_multiply(intal_add((void*low1),(void*high1)),intal_add((void*low2),(void*high2)))
    z2=intal_multiply((void*)high1,(void*)high2);
    z4=*/

//}
    //return i4;

/*void* intal_divide(void* intal1, void* intal2)
{	//printf("here\n");
	input *i1,*i2;
	i1=(input *)intal1;
	i2=(input *)intal2;
	if(i1->size==-1)
	{
		return intal1;
	}
	
	if(i2->size==-1)
	{
		return intal2;
	}
	if(i2->number[0]==0 && i2->size==1)
	{
		input *i3=(input *)malloc(sizeof(input));
		i3->size=-1;
		return i3;
	}
	if(i1->size==1 && i1->number[0]==0)
	{
		return i1;
	}
	if(i2->size==1 && i2->number[0]==1)
	{
		return i1;
	}
	if(intal_compare(intal1,intal2)==0)
	{
		input*i3=(input *)malloc(sizeof(input)+1*sizeof(int));
		i3->size=1;
		i3->number[0]=1;
		return i3;
	}
	else if(intal_compare(intal1,intal2)==-1)
	{
		input *i3=(input *)malloc(sizeof(input)+1*sizeof(int));
		i3->size=1;
		i3->number[0]=0;
		return i3;
	}
	else
	{
		input *new_intal=(input *)malloc(sizeof(input)+(i1->size)*sizeof(int));
		input *dividend=(input *)malloc(sizeof(input)+(i2->size)*sizeof(int));
		input *divisor=(input *)malloc(sizeof(input)+(i2->size)*sizeof(int));
		dividend->size=divisor->size=i2->size;
		input *result=(input *)malloc(sizeof(input)+1*sizeof(int));
		result->size=1;
		result->number[0]=0;
		int m=i1->size;
		int n=i2->size;
		int i;
		for(i=0;i<n;i++)
		{
			dividend->number[i]=i1->number[i];
			divisor->number[i]=i2->number[i];
		}
		int t=n;
		int count=0;
	
		while(t<=m)
		{
			int flag=0;
			if(intal_compare(dividend,divisor)>=0)
			{
				while(intal_compare(dividend,divisor)>=0)
				{
					
					dividend=(input *)intal_diff(dividend,divisor);
					dividend=(input *)remove_leading_zeros(dividend);
					result=(input *)intal_increment(result);
				}
				new_intal->number[count++]=result->number[0];
				result->number[0]=0;
				result->size=1;
				flag=1;
			}
			else
			{
				if(t==m)
					break;
				dividend=(input *)realloc(dividend,sizeof(input)+(dividend->size+1)*sizeof(int));
				dividend->size++;
				dividend->number[dividend->size-1]=i1->number[t];
			    
			   t++;
				
			}
			if(!flag && intal_compare(dividend,divisor)==-1)
			{
				new_intal->number[count++]=0;
			}
			
		}
		new_intal->size=count;
		free(dividend);
		free(divisor);
		free(result);
	
		return new_intal;
	}	
}*/
void* intal_divide(void* intal1, void* intal2)
{
    input *a=intal1;
    input *b=intal2;
    
if(a->size==-1)
	{
		return intal1;
	}
	if(b->size==-1)
	{
		return intal2;
	}
    input *result,*temp;
    int i=0;
    int j=0;
    long long unsigned int divisor=0;
    long long unsigned int remainder=0;
    int k=0;
    if(b->size==1 && b->number[0]==0){
    	result=(input *)malloc(sizeof(input));
    	result->size=-1;
    	return result;
    }
    if(b->size==1)
    {
        if(b->number[0]==1)
            {
		return a;
            }
    }
    if(a->size==1)
    {
        if(a->number[0]==0)
           {
		return a;
           }
    }
    int cmp=intal_compare(intal1,intal2);
    if(cmp==-1)
    {
        result=(input *)malloc(sizeof(input)+1*sizeof(int));
        result->size=1;
        result->number[0]=0;
        return result;
    }
    else if(cmp==0)
    {
        result=(input *)malloc(sizeof(input)+1*sizeof(int));
        result->size=1;
        result->number[0]=1;
        return result;
    }
	char *res="0";
	result=intal_create(res);
	void *dividend=intal1;
	while(intal_compare(dividend,b)>=0)
	{
		dividend=intal_diff(dividend,b);
		result=intal_increment(result);
	}
    return result;
    
}
void* intal_pow(void* intal1, void* intal2)
{
    input *i1=(input *)intal1;
    input *i2=(input *)intal2;
    input *i4=(input *)intal1;
	input *new_intal;
	if(i1->size==-1)
		return i1;
	if(i2->size==-1)
		return i2;
    void * intal;
    //printf("%d\n",i1->size);
    if(i1->size==1)
    {
        if(i1->number[0]==0)
            return i1;
    }
    if(i2->size==1)
    {
        if(i2->number[0]==0)
        {
            input *i3=(input *)malloc(sizeof(input)+1*sizeof(int));
            i3->size=1;
            i3->number[0]=1;
            return i3;
        }
    }
    //printf("hello\n");
    int j=0;
    char *str_2="2";
    void *intal_by_2=intal_create(str_2);
    long long unsigned int i;
    intal=power(intal1,intal2,intal_by_2);
    new_intal=(input *)intal;
	return new_intal;
}

void* power(void* intal,void * intal2,void * intal_by_2)
{
    void *new_intal;
    input *intal_2=(input *)intal2;
    if(intal_2->size==1 && intal_2->number[0]==0)
    {
        input *h=(input*)malloc(sizeof(input)+1*sizeof(int));
        h->size=1;
        h->number[0]=1;
        return h;
    }
    void *intal_q=power_divide(intal2, intal_by_2);
    new_intal=power(intal,intal_q,intal_by_2);
    new_intal=intal_multiply(new_intal,new_intal);
    if(intal_2->number[intal_2->size-1]%2!=0)
    	new_intal=intal_multiply(new_intal,intal);
    
    return new_intal;
}

void* power_divide(void* intal1, void* intal2)
{
    input *i1=(input *)intal1;
    input *i2=(input *)intal2;
    input *i3;
    if(i2->size==1)
    {
        if(i2->number[0]==1)
            return i1;
    }
    if(i1->size==1)
    {
        if(i1->number[0]==0)
            return i1;
    }
    int cmp=intal_compare(intal1,intal2);
    if(cmp==-1)
    {
        i3=(input *)malloc(sizeof(input)+1*sizeof(int));
        i3->size=1;
        i3->number[0]=0;
        return i3;
    }
    else if(cmp==0)
    {
        i3=(input *)malloc(sizeof(input)+1*sizeof(int));
        i3->size=1;
        i3->number[0]=1;
        return i3;
    }
    i3=(input *)malloc(sizeof(input)+1000000*sizeof(int));
    int i=0;
    int j=0;
    long unsigned int sum=0;
    int rem=0;
    int k=0;
    while(i1->number[i]==0)i++;
    while(i2->number[i]==0)j++;
    while(j<i2->size)
    {
        sum=sum*10+i2->number[j];
        j++;
    }
    while(i< i1->size)
    {
        rem=rem*10+i1->number[i++];
        if(rem<sum)
        {
            i3->number[k++]=0;
        }
        else
        {
            i3->number[k++]=rem/sum;
            rem=rem%sum;
        }
        //printf("Done\n");
    }
    i3->size=k;
    while(i3->number[0]==0)
    {
        for(i=0;i<k-1;i++)
            i3->number[i]=i3->number[i+1];
        i3->size--;
    }
    return i3;
}

void intal_destroy(void* intal)
{
	input *i1=(input*)intal;
	if(i1->size!=-1)    
		free(intal);
}

void *remove_leading_zeros(input *intal)
{
	long long unsigned int j=0;
	input *temp;
	while( intal->number[j]==0 && j<intal->size)j++;
	if(j==intal->size)
	{
		temp=(input *)malloc(sizeof(input)+1*sizeof(int));
		temp->size=1;
		temp->number[0]=0;
	}
	else
	{
		int i=0;
		temp=(input *)malloc(sizeof(input)+(intal->size-j)*sizeof(int));
		temp->size=intal->size-j;
		while(j<intal->size)
		{
			temp->number[i++]=intal->number[j++];
		}
	}
	return temp;
}
