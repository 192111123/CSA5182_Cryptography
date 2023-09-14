#include <stdio.h>
#include <string.h>
#include <ctype.h>
void sanitizeInput(char *input)
 {
    for (int i = 0; input[i]; i++) 
	{
        if (isalpha(input[i]))
		 {
            input[i] = toupper(input[i]);
        }
    }
}
void encrypt(char *key, char *input, char *output) 
{
    int keyLength = strlen(key);
    int inputLength = strlen(input);
    for (int i = 0, j = 0; i < inputLength; i++) 
	{
        if (isalpha(input[i]))
		 {
            char shift = key[j % keyLength] - 'A';
            output[i] = ((input[i] - 'A' + shift) % 26) + 'A';
            j++;
        }
		 else
		  {
            output[i] = input[i];
        }
    }
    output[inputLength] = '\0';
}
void decrypt(char *key, char *input, char *output)
 {
    int keyLength = strlen(key);
    int inputLength = strlen(input);
    for (int i = 0, j = 0; i < inputLength; i++) 
	{
        if (isalpha(input[i])) 
		{
            char shift = key[j % keyLength] - 'A';
            output[i] = ((input[i] - 'A' - shift + 26) % 26) + 'A';
            j++;
        } 
		else 
		{
            output[i] = input[i];
        }
    }
    output[inputLength] = '\0';
}
int main() 
{
    char key[100];
    char input[100];
    char encrypted[100];
    char decrypted[100];
    printf("Enter the key: ");
    scanf("%s", key);
    sanitizeInput(key);
    printf("Enter the text to encrypt: ");
    scanf("%s", input);
    sanitizeInput(input);
    encrypt(key, input, encrypted);
    decrypt(key, encrypted, decrypted);
    printf("\nOriginal Text: %s\n", input);
    printf("Encrypted Text: %s\n", encrypted);
    printf("Decrypted Text: %s\n", decrypted);
    return 0;
}
