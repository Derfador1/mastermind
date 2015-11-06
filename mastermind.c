#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 6

void secret_guess(int count, char * secret_holder);
int type_check(int count, char * array);
void red_white_checker(int *red, int *white, int red_counter, int white_counter, char * computer_guess, char * guess);

int main(void)
{
	char computer_guess[MAX_SIZE];
	char *guess;
	char *re_try;
	int red[] = {0};
	int white[] = {0};
	int red_counter = 0;
	int white_counter = 0;
	int count = 0;
	int total_guesses = 0;
	int c;
	int begin_again;

	guess = malloc(MAX_SIZE);
	
	re_try = malloc(MAX_SIZE);

	srand(time(NULL));

	secret_guess(count, computer_guess);
	
	start:
	{
		while(1)
		{
			printf("Guess a number (q to quit): ");
			fgets(guess, MAX_SIZE, stdin);

			if (strlen(guess) < 5)
			{
				if (guess[0] == 'q')
				{
					printf("You have chosen to quit.\n");
					break;
				}
				else
				{
					printf("Not enough digits. Try again.\n");
					goto start;
				}
			}
			else if (guess[4] != '\n')
			{
				printf("To many digits. Try again.\n");
				while((c = getchar()) != '\n' && c != EOF)
				{
					//eats rest of input in stdin buffer
				}
				goto start;
			}
			else
			{
				if (!(type_check(count, guess)))
				{
					printf("Type was incorrect. Try again.\n");
					goto start;
				}
			}
			red_white_checker(red, white, red_counter, white_counter, computer_guess, guess);
			printf("R:%d and W:%d\n", *red, *white);
			total_guesses++;
			if (*red == 4)
			{

				printf("You have won in %d guesses\n", total_guesses);
				printf("Would you like to play again? y or n: ");
				fgets(re_try, sizeof(re_try), stdin);


				if (re_try[0] == 'y')
				{
					begin_again = 1;
					secret_guess(count, computer_guess);
					*red = 0;
					*white = 0;
					goto start;	
				}				
				else if (re_try[0] == 'n')
				{
					begin_again = 0;
					break;
				}
				else
				{
					do {
						printf("I did not understand that.\n");
					} while (begin_again != 1 && begin_again != 0);
				}
	
			}

			*red = 0;  //resetting value of red for next guess
			*white = 0;  //resetting the value of white for next guess

		}
		free(guess);
		free(re_try);
	}
}

void secret_guess(int count, char * secret_holder)
{
	for (count = 0; count < 4; count++)
	{
		int r = (rand() % 10) + '0';
		secret_holder[count] = r;
		printf("%c\n", secret_holder[count]);
	}
}

int type_check(int count, char * array)
{
	for (count = 0; count < 4; count++)
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

void red_white_checker(int *red, int *white, int red_counter, int white_counter, char * computer_guess, char * guess)
{

	for (red_counter = 0; red_counter < 4; red_counter++)
	{
		if (computer_guess[red_counter] == guess[red_counter])
		{
			(*red)++;
			guess[red_counter] = 11; //changes guess so that multiple values arent added for red
		}
		else
		{
			for (white_counter = 0; white_counter < 4; white_counter++)
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
