#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const unsigned int MAX_SIZE = 6;



void secret_guess(int counter, char * secret_holder);
int type_check(int counter, char * array);
void red_white_checker(int *red, int *white, char * computer_guess, char * guess, int counter);
int if_winner(int *red, int total_guesses);
int restarter(int counter, char * computer_guess, char * guess);

int main(void)
{
	char *computer_guess;
	char *guess;
	int red[] = {0};
	int white[] = {0};
	int counter = (MAX_SIZE - 2);
	int total_guesses = 0;
	int character_eater;

	computer_guess = malloc(MAX_SIZE);
	guess = malloc(MAX_SIZE);

	srand(time(NULL));

	secret_guess(counter, computer_guess);
	
	start:
	{
		while(1)
		{
			printf("Guess a number (q to quit): ");
			fgets(guess, MAX_SIZE, stdin);

			if (strlen(guess) < (MAX_SIZE - 1))
			{
				if (guess[0] == 'q')
				{
					printf("You have chosen to quit.\n");
					break;
				}
				else
				{
					printf("Invalid input. Try again.\n");
					goto start;
				}
			}
			else if (guess[4] != '\n')
			{
				printf("Invalid input. Try again.\n");
				while((character_eater = getchar()) != '\n' && character_eater != EOF)
				{
					//eats rest of input in stdin buffer
				}
				goto start;
			}
			else
			{
				if (!(type_check(counter, guess)))
				{
					printf("Type was incorrect. Try again.\n");
					goto start;
				}
			}

			red_white_checker(red, white, computer_guess, guess, counter);

			printf("R:%d and W:%d\n", *red, *white);
			total_guesses++;

			if(0 == if_winner(red, total_guesses))
			{

				if(1 == restarter(counter, computer_guess, guess))
				{
					*red = 0;
					*white = 0;
					total_guesses = 0;
					goto start;
				}
				else
				{
					break;
				}
			}

			*red = 0;  //resetting value of red for next guess
			*white = 0;  //resetting the value of white for next guess

		}
	}
}

void secret_guess(int counter, char * secret_holder)
{
	for (int count = 0; count < counter; count++)
	{
		int r = (rand() % 10) + '0';
		secret_holder[count] = r;
		printf("%c\n", secret_holder[count]);
	}
}

int type_check(int counter, char * array)
{
	for (int count = 0; count < counter; count++)
	{
		if (!isdigit(array[count]))
		{
			if (array[0] == 'q' && array[3] == 't')
			{
				printf("quitting\n");
				exit(1);
			}
			else
			{
				return 0;
			}
		}
	}
	return 1;
}

void red_white_checker(int *red, int *white, char * computer_guess, char * guess, int counter)
{

	for (int red_counter = 0; red_counter < counter; red_counter++)
	{
		if (computer_guess[red_counter] == guess[red_counter])
		{
			(*red)++;
			guess[red_counter] = 11; //changes guess so that multiple values arent added for red
		}
		else
		{
			for (int white_counter = 0; white_counter < counter; white_counter++)
			{
				if (computer_guess[red_counter] == guess[white_counter])
				{
					(*white)++;
					guess[white_counter] = 11; //changes guess so that multiple values 											     arent added for white
					break;
				}
			}
		}
	}
}

int if_winner(int *red, int total_guesses)
{
	if (*red == 4)
	{
		printf("You have won in %d guesses\n", total_guesses);
		return 0;
	}
	else
	{
		return 1;
	}
}

int restarter(int counter, char * computer_guess, char * guess)
{
	char *re_try;

	re_try = malloc(MAX_SIZE);

	while(1)
	{
		printf("Would you like to play again? y or n: ");
		fgets(re_try, MAX_SIZE, stdin);


		if (re_try[0] == 'y')
		{
			secret_guess(counter, computer_guess);
			free(re_try);
			return 1;	
		}				
		else if (re_try[0] == 'n')
		{
			free(re_try);
			free(guess);
			free(computer_guess);
			exit(1);
		}
		else
			printf("I did not understand. Try again.\n");
	}
	return 0;
}
