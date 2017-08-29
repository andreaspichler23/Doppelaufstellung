#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

double input(istream& in=cin)
{
	double x;
	in >> x;
	return x;
}


double probabilityOurWinMatch(double our, double guest)
{
 double diff;
 double weight;
 weight = 2.0;
 diff = guest-our;
 return(tanh(diff*weight)/2.+0.5);
}

// winDouble stores an array, with the probability to win 0,1,2,3 doubles
double probabilityTeam(double *our, double* guest,double *p, double* winDouble,double *winAtLeastDouble)
{

double averageour;
double averageguest;

for(int j=0; j<3; j++) //This loops on the columns
 {
  averageour=(our[j*2]+our[j*2+1])/2.0;
  averageguest=(guest[j*2]+guest[j*2+1])/2.0;
  p[j]=probabilityOurWinMatch(averageour, averageguest);
 }
// Drei Doppel gewinnen
 winDouble[3]=p[0]*p[1]*p[2];


// zwei Doppel gewinnen
 winDouble[2]=	p[0]     *p[1]	   *(1-p[2])+
		p[0]     *(1-p[1]) *p[2]+
		(1-p[0]) *p[1] 	   *p[2];

// Ein Doppel gewinnen
 winDouble[1]=	p[0]     *(1-p[1]) *(1-p[2])+
		(1-p[0]) *p[1]     *(1-p[2])+
		(1-p[0]) *(1-p[1]) *p[2];

// kein Doppel gewinnen
 winDouble[0]=(1-p[0])*(1-p[1])*(1-p[2]);

 winAtLeastDouble[0]=winDouble[3]+winDouble[2]+winDouble[1]+winDouble[0];
 winAtLeastDouble[1]=winDouble[3]+winDouble[2]+winDouble[1];
 winAtLeastDouble[2]=winDouble[3]+winDouble[2];
 winAtLeastDouble[3]=winDouble[3];
}




int main()
{
	int board[17][6]; //creates a 9*9 matrix or a 2d array.
	double itn_guest[6];
	double itn_guest_versionx[6];
	double itn_our[6];
	double itn_our_versionx[6];
	double bestNomination[4];
	int bestNominationIndex[4],bestNominationGuestIndex[4];
	double winDouble[4],winAtLeastDouble[4],winAtLeastDoubleMin[17][4],p[3];
	int winAtLeastDoubleMinIndex[17][4];



	board[0][0]=1;
	board[0][1]=2;
	board[0][2]=3;
	board[0][3]=4;
	board[0][4]=5;
	board[0][5]=6;

	board[1][0]=1;
	board[1][1]=2;
	board[1][2]=3;
	board[1][3]=6;
	board[1][4]=4;
	board[1][5]=5;

	board[2][0]=1;
	board[2][1]=2;
	board[2][2]=4;
	board[2][3]=5;
	board[2][4]=3;
	board[2][5]=6;

	board[3][0]=1;
	board[3][1]=3;
	board[3][2]=2;
	board[3][3]=4;
	board[3][4]=5;
	board[3][5]=6;

	board[4][0]=1;
	board[4][1]=3;
	board[4][2]=2;
	board[4][3]=5;
	board[4][4]=4;
	board[4][5]=6;

	board[5][0]=1;
	board[5][1]=3;
	board[5][2]=2;
	board[5][3]=6;
	board[5][4]=4;
	board[5][5]=5;

	board[6][0]=1;
	board[6][1]=4;
	board[6][2]=2;
	board[6][3]=3;
	board[6][4]=5;
	board[6][5]=6;

	board[7][0]=1;
	board[7][1]=4;
	board[7][2]=2;
	board[7][3]=5;
	board[7][4]=3;
	board[7][5]=6;

	board[8][0]=1;
	board[8][1]=4;
	board[8][2]=2;
	board[8][3]=6;
	board[8][4]=3;
	board[8][5]=5;

	board[9][0]=1;
	board[9][1]=5;
	board[9][2]=2;
	board[9][3]=4;
	board[9][4]=3;
	board[9][5]=6;

	board[10][0]=2;
	board[10][1]=3;
	board[10][2]=1;
	board[10][3]=4;
	board[10][4]=5;
	board[10][5]=6;

	board[11][0]=2;
	board[11][1]=3;
	board[11][2]=1;
	board[11][3]=5;
	board[11][4]=4;
	board[11][5]=6;

	board[12][0]=2;
	board[12][1]=3;
	board[12][2]=1;
	board[12][3]=6;
	board[12][4]=4;
	board[12][5]=5;

	board[13][0]=2;
	board[13][1]=4;
	board[13][2]=1;
	board[13][3]=5;
	board[13][4]=3;
	board[13][5]=6;

	board[14][0]=2;
	board[14][1]=4;
	board[14][2]=1;
	board[14][3]=6;
	board[14][4]=3;
	board[14][5]=5;

	board[15][0]=2;
	board[15][1]=5;
	board[15][2]=1;
	board[15][3]=6;
	board[15][4]=3;
	board[15][5]=4;

	board[16][0]=3;
	board[16][1]=4;
	board[16][2]=1;
	board[16][3]=6;
	board[16][4]=2;
	board[16][5]=5;

	for(int j=0;j<17;j++) 
	 for(int l=0;l<4;l++) winAtLeastDoubleMin[j][l]=2.0;

	for(int j=0; j<6; j++) //This loops on the columns
	{
		cout << "Input the itn of our team\n";
		itn_our[j] = input(); //you can also connect to the file
		cout << itn_our[j];
	}

	for(int j=0; j<6; j++) //This loops on the columns
	{
		cout << "Input the itn of guest team\n";
		itn_guest[j] = input(); //you can also connect to the file
	}


	for(int j=0; j<17; j++)    //All variants of ours
	{
		for(int i=0; i<17; i++) //All variants of guest
		{
			for(int k=0; k<6; k++) 
			{
				itn_guest_versionx[k]	=itn_guest[board[i][k]-1];
				itn_our_versionx[k]	=itn_our[board[j][k]-1];
			}
			probabilityTeam(itn_our_versionx, itn_guest_versionx,p, winDouble,winAtLeastDouble);
			
			for(int l=1;l<4;l++)
			 if (winAtLeastDoubleMin[j][l]>winAtLeastDouble[l])
			 {
				 winAtLeastDoubleMin[j][l]= winAtLeastDouble[l];
				 winAtLeastDoubleMinIndex[j][l]= i;
			 }
			cout << "****** Nomination GUEST: " << i << " OUR:" << j << "******\n";

			for(int k=0; k<6; k++) //This loops on the columns
			{
				cout << "Nomination Our: " << board[j][k] << " itn:" << itn_our[board[j][k]-1] <<  " Guest: " << board[i][k] << " itn:" << itn_guest[board[i][k]-1] ;
			if (k%2==0) cout << " average itn: Our: " << (itn_our_versionx[k]+itn_our_versionx[k+1])/2. << " Guest " << (itn_guest_versionx[k]+itn_guest_versionx[k+1])/2. << "    Prob_win =" << p[k/2];
			cout << "\n";
			}


			for(int k=0; k<4; k++) //This loops on the columns
			{
				cout << "Probability to win exactely " << k << " doubles " << winDouble[k] << "Prob. to win at least " << k << " : " << winAtLeastDouble[k] << "\n";
			}


		}
		// evaluate worst case of our particular nomination for all guest possible nomination
 		for (int l=1;l<4;l++)
		cout << "Worst case to win at least " << l << 
		" double is if guest use nomination: " << winAtLeastDoubleMinIndex[j][l] << "  Prob to win is then " << winAtLeastDoubleMin[j][l] << "\n";


		cout << endl;
	}
    // evaluate best of all our nominations


    for (int l=1;l<4;l++)
     bestNomination[l]=0;

    for(int j=0; j<17; j++)    //All variants of ours
    
     for (int l=1;l<4;l++)
     {
      if (bestNomination[l]<winAtLeastDoubleMin[j][l])
	{
         bestNomination[l]=winAtLeastDoubleMin[j][l];
	 bestNominationGuestIndex[l]=winAtLeastDoubleMinIndex[j][l];
	 bestNominationIndex[l]=j;
	}
     }

     for (int l=1;l<4;l++)
     {
      cout << "Our best nomination to win at least " << l << " doubles is with index " << bestNominationIndex[l] << " and we win with probability " <<  bestNomination[l] << " for us worst guest nomination is index " << bestNominationGuestIndex[l] << "\n";
     }
	
}
