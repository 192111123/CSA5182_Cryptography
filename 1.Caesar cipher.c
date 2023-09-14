#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{
	int k,n;
	char input[100];
	printf("Enter input string:");
	scanf("%s",&input);
	printf("Enter key value: ");
	scanf("%d",&k);
	printf("choose the text in which it is to be converted\n");
	printf("1)cypher text\n2)plain text\n");
	scanf("%d",&n);
	if(n==1)
	{
		for(int i=0;i<strlen(input);i++)
		{
		if(islower(input[i]))
		{
			input[i]=((input[i]-'a'+k)%26)+'a';	
		}
		else
		{
			input[i]=((input[i]-'A'+k)%26)+'A';	
		}
		printf("%c",input[i]);
	}
}
else
{
	for(int i=0;i<strlen(input);i++)
	{
		if(islower(input[i]))
		{
			input[i]=((input[i]-'a'-k)%26)+'a';	
		}
		else
		{
			input[i]=((input[i]-'A'-k)%26)+'A';	
		}
		printf("%c",input[i]);
	}
}
}
