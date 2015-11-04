#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 6

void secret_guess(int count, char * secret_holder);

int main(void)
{
	char computer_guess[MAX_SIZE];
	char *guess;
	char *checker;
	int red = 0;
	int white = 0;
	int red_counter;
	int white_counter;
	int count = 0;
	int total_guesses = 0;

	guess = malloc(MAX_SIZE);
	checker = malloc(MAX_SIZE);
	
	srand(time(NULL));

	secret_guess(count, computer_guess);

	printf("\n");
	
	start:
	{
		while(1)
		{
			printf("Guess a number: ");
			fgets(guess, MAX_SIZE, stdin);

			if (guess[4] == '\n')
			{
				printf("Correct\n");	
			}
			else if (guess[4] != '\n')
			{
				printf("enter again\n");
				guess[0] = '\0';
				goto start;
				//break;
			}

			for (red_counter = 0; red_counter < 4; red_counter++)
			{
				checker[red_counter] = guess[red_counter];
				if (computer_guess[red_counter] == checker[red_counter])
				{
					red++;
					checker[red_counter] = 11;
				}
				else
				{
					for (white_counter = 0; white_counter < 4; white_counter++)
					{
						checker[white_counter] = guess[white_counter];
						if (computer_guess[red_counter] == checker[white_counter])
						{
							white++;
							checker[white_counter] = 11;
							break;
						}
					}
				}
			}

			printf("R:%d and W:%d\n", red, white);
			total_guesses++;
			if (red == 4)
			{
				printf("You have won in %d guesses\n", total_guesses);
				break;
			}
			red = 0;
			white = 0;
		}
		free(guess);
		free(checker);
	}
}

void secret_guess(int count, char * secret_holder)
{
	for (count = 0; count < 4; count++)
	{
		int r = (rand() % 10) + '0';
		secret_holder[count] = r;
		//printf("%c", secret_holder[count]);
	}
}
