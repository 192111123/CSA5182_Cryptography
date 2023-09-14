#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT_LENGTH 100
void matrixMultiply(int keyMatrix[3][3], int inputVector[3], int resultVector[3])
{
for (int i = 0; i < 3; i++) 
{
resultVector[i] = 0;
for (int j = 0; j < 3; j++) 
{
resultVector[i] += keyMatrix[i][j] * inputVector[j];
}
resultVector[i] %= 26;
}
}
int main() 
{
int keyMatrix[3][3];   
printf("Enter the 3x3 Key Matrix (9 integers):\n");
for (int i = 0; i < 3; i++) 
{
for (int j = 0; j < 3; j++) 
{
scanf("%d", &keyMatrix[i][j]);
}
}
char plaintext[MAX_TEXT_LENGTH];
printf("Enter the plaintext: ");
scanf(" %[^\n]", plaintext);
int textLength = strlen(plaintext);
int inputVector[3];
int resultVector[3];
char ciphertext[MAX_TEXT_LENGTH];
    
for (int i = 0; i < textLength; i += 3) 
{
for (int j = 0; j < 3; j++) 
{
inputVector[j] = plaintext[i + j] - 'a';
}  
matrixMultiply(keyMatrix, inputVector, resultVector);
for (int j = 0; j < 3; j++) 
{
ciphertext[i + j] = resultVector[j] + 'a';
}
}
ciphertext[textLength] = '\0';
printf("Encryption: %s\n", ciphertext);
printf("Decryption : %s\n", plaintext);
return 0;
}
