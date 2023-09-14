#include <stdio.h>
#include <string.h>
#include <ctype.h>
void railFenceEncrypt(char *plaintext, int rails)
 {
    int length = strlen(plaintext);
    char encrypted[length];
    int pos = 0;
    for (int i = 0; i < rails; i++) 
	{
        int step1 = (rails - i - 1) * 2;
        int step2 = i * 2;
        int j = i;
        int flag = 0;
        while (j < length) 
		{
            encrypted[pos++] = plaintext[j];
            
            if (step1 > 0 && step2 > 0)
			 {
                if (flag == 0)
				 {
                    j += step1;
                    flag = 1;
                } 
				else 
				{
                    j += step2;
                    flag = 0;
                }
            } 
			else if (step1 == 0) 
			{
                j += step2;
            } else 
			{
                j += step1;
            }
        }
    } 
    encrypted[pos] = '\0';
    printf("Encrypted text: %s\n", encrypted);
}
int main() 
{
    char plaintext[1000];
    int rails;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the number of rails: ");
    scanf("%d", &rails);
    strtok(plaintext, "\n");
    railFenceEncrypt(plaintext, rails);
    return 0;
}
