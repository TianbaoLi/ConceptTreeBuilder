#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<cstdlib> 
#include<cstring>
#include<vector>
using namespace std;
class Concept
{
public:
	char id[30];
	char name[200];
	char type[30];
	Concept *father;
	Concept()
	{
		memset(id,0,sizeof(id));
		memset(name,0,sizeof(name));
		memset(type,0,sizeof(type));
		father=NULL;
	}
};

vector <Concept*> List;

int main()
{
	FILE *SubClassIn;
	SubClassIn=fopen("rdfsSubClassOf.tsv","r");
	char temp[500],result[500];
	bool validflag,idflag,wordnet;
	int length;
	while(EOF)
	{
		validflag=1;
		length=0;
		wordnet=0;
		if(fgets(temp,500,SubClassIn)==NULL)
			break;
		if(strcmp(temp,"")==0)
			break;
		if(temp[1]=='h'&&temp[2]=='b'&&temp[3]=='f'&&temp[4]=='i'&&temp[5]=='x')
			continue;
		for(int k=2;k<(int)strlen(temp);k++)
			if(temp[k-2]=='<'&&temp[k]=='>')
			{
				validflag=0;
				break;
			}
		if(validflag==0)
			continue;
		Concept *c=NULL,*f=NULL;
		c=new Concept();
		f=new Concept();
		int i=0,j=0;
		if(temp[0]=='\t')
		{
			i++;
			wordnet=1;
		}
		else
		{
			while(temp[i]!='_')
				i++;
			i++;
			while(temp[i]!='>')
			{
				c->id[j]=temp[i];
				length++;
				i++;
				j++;
			}
			i+=2;
		}
		i++;
		j=0;
		while(temp[i]!='_')
		{
			c->type[j]=temp[i];
			length++;
			i++;
			j++;
		}
		i++;
		j=0;
		if(wordnet==0)
			while(temp[i]!='>'||temp[i+1]>'9')
			{
				if(temp[i]=='&')
					break;
				c->name[j]=temp[i];
				length++;
				i++;
				j++;
			}
		else
			while(temp[i]!='_'||temp[i+1]>'9')
			{
				if(temp[i]=='&')
					break;
				c->name[j]=temp[i];
				length++;
				i++;
				j++;
			}
		i++;
		j=0;
		while(temp[i]!='>'&&temp[i]>='0'&&temp[i]<='9')
		{
			c->id[j]=temp[i];
			length++;
			i++;
			j++;
		}
		while(temp[i]!='<')
			i++;
		j=0;
		i++;
		idflag=0;
		for(int k=i;k<(int)strlen(temp);k++)
			if(temp[k]>='0'&&temp[k]<='9')
			{
				idflag=1;
				break;
			}
		if(idflag==0)
			continue;
		while(temp[i]!='_')
		{
			f->type[j]=temp[i];
			length++;
			i++;
			j++;
		}
		i++;
		j=0;
		while(temp[i]!='_'||temp[i+1]>'9')
		{
			if(temp[i]=='&')
				break;
			f->name[j]=temp[i];
			length++;
			i++;
			j++;
		}
		i++;
		j=0;
		while(temp[i]!='>'&&temp[i]>='0'&&temp[i]<='9')
		{
			f->id[j]=temp[i];
			length++;
			i++;
			j++;
		}
		c->father=f;
		List.push_back(c);
		List.push_back(f);
		length+=6;
		printf("%d\n",length);
		sprintf(result,"@%s@%s@%s@%s@%s@%s\n",c->id,c->name,c->type,f->id,f->name,f->type);
		printf("%s",result);
		//delete f;
		delete c;
		//printf("%s\n\n",temp);
		//system("pause");
	}
	system("pause");
	return 0;
}
