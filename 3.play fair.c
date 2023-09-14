#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void sanitizeInput(char *input)
 {
    int index = 0;
    for (int i = 0; input[i]; i++) 
	{
        if (isalpha(input[i])) 
		{
            input[index++] = toupper(input[i]);
        }
    }
    input[index] = '\0';
}
void generatePlayfairMatrix(char key[], char matrix[SIZE][SIZE]) 
{
    sanitizeInput(key);
    int used[26] = {0};
    for (int i = 0, r = 0, c = 0; i < SIZE * SIZE; i++) 
	{
        char ch = i < strlen(key) ? key[i] : 'A' + (i - strlen(key));
        if (!used[ch - 'A']) 
		{
            matrix[r][c++] = ch;
            used[ch - 'A'] = 1;
            if (c == SIZE) 
			{
                c = 0;
                r++;
            }
        }
    }
}
void findCharCoordinates(char matrix[SIZE][SIZE], char ch, int *row, int *col) 
{
    for (int i = 0; i < SIZE; i++) 
	{
        for (int j = 0; j < SIZE; j++) 
		{
            if (matrix[i][j] == ch) 
			{
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void cipherOperation(char matrix[SIZE][SIZE], char *input, char *output, int offset) 
{
    int len = strlen(input);
    for (int i = 0; i < len; i += 2) 
	{
        int row1, col1, row2, col2;
        findCharCoordinates(matrix, input[i], &row1, &col1);
        findCharCoordinates(matrix, input[i + 1], &row2, &col2);       
        if (row1 == row2) 
		{
            output[i] = matrix[row1][(col1 + offset) % SIZE];
            output[i + 1] = matrix[row2][(col2 + offset) % SIZE];
        } 
		else if (col1 == col2) 
		{
            output[i] = matrix[(row1 + offset) % SIZE][col1];
            output[i + 1] = matrix[(row2 + offset) % SIZE][col2];
        } 
		else 
		{
            output[i] = matrix[row1][col2];
            output[i + 1] = matrix[row2][col1];
        }
    }
    output[len] = '\0';
}
int main()
 {
    char key[25];
    char matrix[SIZE][SIZE];
    char input[100];
    char encrypted[100];
    char decrypted[100];
    printf("Enter the key: ");
    scanf("%s", key);
    generatePlayfairMatrix(key, matrix);
    printf("Enter the text to encrypt: ");
    scanf("%s", input);
    sanitizeInput(input);
    cipherOperation(matrix, input, encrypted, 1);
    cipherOperation(matrix, encrypted, decrypted, SIZE - 1);
    printf("\nKey Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nOriginal Text: %s\n", input);
    printf("Encrypted Text: %s\n", encrypted);
    printf("Decrypted Text: %s\n", decrypted);
    return 0;
}
