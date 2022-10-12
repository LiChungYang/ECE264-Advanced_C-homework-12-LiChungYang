#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"
#define MAX 100

Stack * init()
{
	Stack * st = malloc(sizeof(Stack));
	st -> top = NULL;
	return st;
}

Node * insert(float value, Node * list)
{
	Node * new = malloc(sizeof(Node));
	new -> val = value;
	new -> next = list;
	return new;
}

Node * delete(Node * list)
{
	if(list == NULL)
	{
		return NULL;
	}

	Node * re = list -> next;
	free(list);
	return re;
}

void push(Stack * st, float key)
{
	st -> top = insert(key, st -> top);
}

bool isEmpty(Stack * st)
{
	return st -> top == NULL;
}

float check(Stack * st)
{
	if(isEmpty(st))
	{
		printf("Malformed Input\n");
		exit(1);
	}
	return st -> top -> val;
}

float pop(Stack * st)
{
	if(isEmpty(st))
	{
		printf("Malformed Input\n");
		exit(1);
	}
	float retval = check(st); 
	st -> top = delete(st -> top);
	
	return retval;
}

void freeStack(Stack * st)
{
	while(!isEmpty(st))
	{
		pop(st);
	}
	free(st);
}

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments.\n");
		fprintf(stderr, "Usage: ./pa11 <input file>\n");		
		return EXIT_FAILURE;
	}

	float result; //store the result of your calculation here.
	
	/* Insert code here to perform the RPN calculation.
	Don't forget to free any memory you allocate once you're done with it! */
	Stack * st = init();
	float opt1;
	float opt2;
	float newvalue;
	int tempv;
	int ctr = 1;
	float pushvalue;
	char * number = malloc(sizeof(char));

	FILE *f = fopen(argv[1], "r");
	if(!f)
	{
		return EXIT_FAILURE;
	}
	
	char line[1000];
	fscanf(f,"%[^\n]",line);
	int len = strlen(line);
	
	for(int i = 0; i < len; i++)
	{
		if(isdigit(line[i]) || line[i] == '.' || (line[i] == '-' && isdigit(line[i+1])))
		{
			
			int numlen = 1;
			tempv = i + 1;
			while((isdigit(line[tempv]) || line[tempv] == '.') && line[tempv] != ' ')
			{
				numlen++; 
				tempv++;
			}
			number = realloc(number,sizeof(char) * numlen);
			
			number[0] = line[i];
			tempv = i + 1;
			while((isdigit(line[tempv]) || line[tempv] == '.') && line[tempv] != ' ' && ctr < numlen) 
			{
				number[ctr] = line[tempv];
				ctr++;
				tempv++;
			}
			i = tempv;
			ctr = 1;
			
			pushvalue = strtof(number,NULL);
			push(st,pushvalue);
			
			free(number);
			number = NULL;
		}
		else if(line[i] != ' ')
		{
			opt1 = pop(st);
			opt2 = pop(st);
			if(line[i] == '*')
			{
				newvalue = opt2 * opt1;
			}
			else if(line[i] == '/')
			{
				newvalue = opt2 / opt1;
			}
			else if(line[i] == '+')
			{
				newvalue = opt2 + opt1;
			}
			else if(line[i] == '-')
			{
				newvalue = opt2 - opt1;
			}
			push(st,newvalue);
		}
	}

	result = newvalue;
	pop(st);

	if(!isEmpty(st))
	{
		printf("Malformed Input\n");
		fclose(f);
		freeStack(st);
		exit(1);
	}

	printf("%f\n", result);
	fclose(f);
	freeStack(st);
	
	return EXIT_SUCCESS;
}

