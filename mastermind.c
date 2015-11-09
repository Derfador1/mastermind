#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const unsigned int MAX_SIZE = 6;


char secret_guess(int counter, char * secret_holder);
int type_check(int counter, char * array);
void red_white_checker(int *red, int *white, char * computer_guess, char * guess, int counter);
int if_winner(int *red, int total_guesses);
int restarter(int counter, char * computer_guess, char * guess);

int main(int argc, char *argv[])
{
	char *computer_guess;
	char *guess;
	int red[] = {0};
	int white[] = {0};
	int counter = (MAX_SIZE - 2);
	int total_guesses = 0;
	int character_eater;
	int rflag = 0;


	computer_guess = malloc(MAX_SIZE);
	guess = malloc(MAX_SIZE);

	srand(time(NULL));

	secret_guess(counter, computer_guess);

	if (argc == 1)
	{
		goto start;
	}
	else if (argc == 2)
	{
		if (strncmp(argv[1], "-h", 10) == 0) //means they are equal
		{
			printf("Use -s to print secret guess\n");
			printf("Use -r to remove number of red or white in guess\n");
		}
		else if (strncmp(argv[1], "-s", 10) == 0)
		{
			printf("%.4s\n", computer_guess);
		}
		else if (strncmp(argv[1], "-r", 10) == 0)
		{
			rflag = 1;
		}
		else
		{
			printf("No valid arguments given.\n");
			goto start;
		}
	}
	else
	{
		printf("To many arguments given.\n");
		goto start;
	}

	
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
					free(guess);
					free(computer_guess);
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

			if (rflag == 1)
			{
				//turns off printing feature
			}
			else
			{
				printf("R:%d and W:%d\n", *red, *white);
			}

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


char secret_guess(int counter, char * secret_holder)
{
	int r;
	for (int count = 0; count < counter; count++)
	{
		r = (rand() % 10) + '0';
		secret_holder[count] = r;
	}
	return *secret_holder;
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
	int character_eater2;

	re_try = malloc(MAX_SIZE);

	while(1)
	{
		printf("Would you like to play again? y or n: ");
		fgets(re_try, (MAX_SIZE - 3), stdin);

		if (strlen(re_try) < 3)
		{
			if (re_try[0] == 'y' && re_try[1] == '\n')
			{
				secret_guess(counter, computer_guess);
				free(re_try);
				return 1;	
			}				
			else if (re_try[0] == 'n' && re_try[1] == '\n')
			{
				free(re_try);
				free(guess);
				free(computer_guess);
				exit(1);
			}
			else
			{
				printf("I did not understand. Try again.\n");
				while((character_eater2 = getchar()) != '\n' && character_eater2 != EOF)
				{
					//eats rest of input in stdin buffer
				}
			}
		}

	}
	return 0;
}
