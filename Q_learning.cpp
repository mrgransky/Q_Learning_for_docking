// Author : Farid Alijani 
// Q_learning with reward distribution...
// for further sample codes, please visit my GitHub page...

// ----- How to Compile and run c++ file in Ubuntu ------ //
 
 // In a terminal, go to directory that your c++ file exsist and To compile your c++ code, :
 
 g++ -o output Q_learing.cpp

 

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

const int row = 25;
const int col = 25;

ofstream file;
double gamma = .8;
double alpha = .1;
double R_step = row*col;

double R[row][col] = { 0 };
double Q[row][col] = { 0 };

int iterations;
int it_;
int user_action;
double Q_next_state;

int i, j;
double Q_curr_state = Q[i][j];

double reward;

int R_indx_i = 0/*row - row*/;
int R_indx_j = 14/*.5 * col*/;

int P_indx_i = 8/*row - 2*/;
int P_indx_j = 0/*col - 1*/;

int counter;
int Time_Reward;
double sample;

void print_R();
void print_Q();
void save2file();
void iANDj_Generator();

int main()
{
	R[R_indx_i][R_indx_j] = 50; // reward
	R[P_indx_i][P_indx_j] = -20; // punishment
	
	file.open("Matrix.txt");

	print_R();

	cout << "\n iterations ? \n";
	cin >> it_;

	/* initialize random seed: */
	srand(time(NULL));

	while (iterations < it_)
	{
		// -------------------------------- Actions ------------------------------
		if (user_action == 1 && i != 0) // North
		{
			reward = R[i][j];
			Q_next_state = Q[i - 1][j];

			sample = reward + gamma * Q_next_state;
			Q[i][j] = ((1 - alpha) * Q[i][j]) + (alpha * sample);
			Q_curr_state = Q_next_state;
			//printf(" Q_current_state = %f \n",Q_curr_state);
			i--;
			counter++;
		}
		else if (user_action == 1 && i == 0) // North
		{
			cout << "You can't go further up!\n";
		}
		else if (user_action == 3 && i < (row - 1)) // South, i < row
		{
			reward = R[i][j];
			Q_next_state = Q[i + 1][j];

			sample = reward + gamma * Q_next_state;
			Q[i][j] = ((1 - alpha) * Q[i][j]) + (alpha * sample);
			Q_curr_state = Q_next_state;
			//printf(" Q_current_state = %f \n",Q_curr_state);
			i++;
			counter++;
		}
		else if (user_action == 3 && i >= (row - 1)) // South
		{
			cout << "You can't go further down!\n";
		}
		else if (user_action == 2 && j < (col - 1)) // East
		{
			reward = R[i][j];
			Q_next_state = Q[i][j + 1];

			sample = reward + gamma * Q_next_state;
			Q[i][j] = ((1 - alpha) * Q[i][j]) + (alpha * sample);
			Q_curr_state = Q_next_state;
			//printf(" Q_current_state = %f \n",Q_curr_state);
			j++;
			counter++;
		}
		else if (user_action == 2 && j >= (col - 1)) // East, j > col
		{
			cout << "You can't go further right!\n";
		}
		else if (user_action == 4 && j != 0) // West
		{
			reward = R[i][j];
			Q_next_state = Q[i][j - 1];

			sample = reward + gamma * Q_next_state;
			Q[i][j] = ((1 - alpha) * Q[i][j]) + (alpha * sample);
			Q_curr_state = Q_next_state;
			//printf(" Q_current_state = %f \n",Q_curr_state);
			j--;
			counter++;
		}
		else if (user_action == 4 && j == 0) // West, j = 1
		{
			cout << "You can't go further left!\n";
		}
		else if (user_action == 0) // start
		{
			cout << "\nGenerating random pose in grid for 1st. time!\n";
			iANDj_Generator();
		}


		// ------------------------------- Reward Distribution ---------------------------
		// + Reward
		if (i == R_indx_i && j == R_indx_j)
		{
			Time_Reward = -counter;
			cout << " Time Reward = " << Time_Reward << "\n";

			if (abs(Time_Reward) <= R_step)
			{

				cout << "\n Goal is achieved <= " << R_step << " time steps\n";
				reward = R[i][j];
				Q_next_state = 0;

				sample = reward + gamma * Q_next_state;
				Q[i][j] = ((1 - alpha) * Q[i][j]) + (alpha * sample);
			}
			else
			{
				cout << "\n Goal is achieved > " << R_step << " time steps => time_punishment\n";
				reward = -1; // ???
				Q_next_state = 0;

				sample = reward + gamma * Q_next_state;
				Q[i][j] = ((1 - alpha) * Q[i][j]) + (alpha * sample);
			}

			counter = 0;
			print_Q();
			//save2file();
			iANDj_Generator();
			iterations++;
		}
		else if (i == P_indx_i && j == P_indx_j) // - Reward => Punishment
		{
			cout << "\n Failed to achieve a goal! \n";

			reward = R[i][j];
			Q_next_state = 0;

			sample = reward + gamma * Q_next_state;
			Q[i][j] = ((1 - alpha) * Q[i][j]) + (alpha * sample);

			print_Q();
			//save2file();
			iANDj_Generator();
			iterations++;
		}

		cout << "\n Q_value = " << Q_curr_state << " , actions N(1), E(2), S(3), W(4) : ";


                /* --------------- Actions Distribution 
                1. Totally random
                2. Right & left
                3. NE,NW,SE,SW
                                                        -------------------*/
                
                // 1. Totally random
                user_action = ((double)rand() / (RAND_MAX)) * (5 - 1) + 1;
                
                /*// 2. Right & Left
		if (j > R_indx_j) // current pose : Right (1)
		{
			cout << "\n Right Side of the goal ... \n";
			user_action = ((double)rand() / (RAND_MAX)) * (5 - 1) + 1;
		}
		else if (j <= R_indx_j) // current pose : Left (2)
		{
			cout << "\n Left Side of the goal ... \n";
			user_action = ((double)rand() / (RAND_MAX)) * (4 - 1) + 1;
		}*/

                /*// 3. NE,NW,SE,SW
		if(i <= R_indx_i && j > R_indx_j) // current pose : North-East (1)
		{
		user_action = ((double) rand() / (RAND_MAX)) * (5 - 3) + 3;
		} else if (i <= R_indx_i && j <= R_indx_j) // current pose : North-West (2)
		{
		user_action = ((double) rand() / (RAND_MAX)) * (4 - 2) + 2;
		} else if (i > R_indx_i && j <= R_indx_j) // current pose : South-West (3)
		{
		user_action = ((double) rand() / (RAND_MAX)) * (3 - 1) + 1;
		} else if (i > R_indx_i && j > R_indx_j) // current pose : South-East (4)
		{
		user_action = ((double) rand() / (RAND_MAX)) * (5 - 1) + 1;
		}*/


		//cin >> user_action;
		printf(" user action = %i \n", user_action);

	}
	save2file();
	return 0;
}
void print_R()
{
	cout << " R = \n";
	for (int i = 0; i <= (row - 1); i++)
	{
		for (int j = 0; j <= (col - 1); j++)
		{
			cout << setw(5) << R[i][j];
			if (j < col - 1)
			{
				cout << " , ";
			}
		} // j
		cout << "\n";
	} // i
	cout << "\n";
}
void print_Q()
{
	cout << " Q = \n";
	for (int i = 0; i <= (row - 1); i++)
	{
		for (int j = 0; j <= (col - 1); j++)
		{
			cout << setw(5) << Q[i][j];
			if (j < col - 1)
			{
				cout << " , ";
			}
		} // j
		cout << "\n";
	} // i
	cout << "\n";
}

void iANDj_Generator()
{
	// Generate Random Pose for current state (position)

	i = ((double)rand() / (RAND_MAX)) * (row);
	j = ((double)rand() / (RAND_MAX)) * (col);

	Q_curr_state = Q[i][j];

	cout << "\n i = " << i << " , j = " << j << " => Q[i][j] = " << Q_curr_state << " \n";

}
void save2file()
{
	for (int k = 0; k < row - 1; k++)
	{
		for (int l = 0; l < col - 1; l++)
		{
			file << setw(5) << Q[k][l];
			if (l < col - 1)
			{
				file << " , ";
			}
		}
		file << "\n";
	}
	file << "\n";
}
