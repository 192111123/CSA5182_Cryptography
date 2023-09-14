#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char plaintext[], char key[]) 
{
    for (int i = 0; plaintext[i] != '\0'; i++) 
	{
        if (isalpha(plaintext[i])) 
		{
            if (islower(plaintext[i]))
                printf("%c", tolower(key[plaintext[i] - 'a']));
            else
                printf("%c", toupper(key[plaintext[i] - 'A']));
        }
		 else 
		 {
            printf("%c", plaintext[i]);
        }
    }
}
void decrypt(char ciphertext[], char key[]) 
{
    for (int i = 0; ciphertext[i] != '\0'; i++) 
	{
        if (isalpha(ciphertext[i])) 
		{
            char c = tolower(ciphertext[i]);
            char *ptr = strchr(key, c);
            if (ptr) 
			{
                int index = ptr - key;
                if (islower(ciphertext[i]))
                    printf("%c", 'a' + index);
                else
                    printf("%c", 'A' + index);
            } 
			else 
			{
                printf("%c", ciphertext[i]);
            }
        } 
		else 
		{
            printf("%c", ciphertext[i]);
        }
    }
}
int main()
 {
    char key[100];
    char plaintext[100];
    printf("Enter the key: ");
    scanf("%s", key);
    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext);
    char ciphertext[100];
    printf("Ciphertext: ");
    encrypt(plaintext, key);
    printf("\n");
    return 0;
}
