#include<bits/stdc++.h>
#include<fstream>
#include<omp.h>
using namespace std;



unsigned int gcd(unsigned int a, unsigned int b)
{
	unsigned int x;
	while (b)
	{
		x = a % b;
		a = b;
		b = x;
    }
    return a;
}


int main(int argc,char* argv[])
{
	
	if (argc != 3)
    	{
        	cout<<"Enter the input file name"<<endl;
        	return -1;
    	}
   	 string filename=argv[1];
	 int thread_count = atoi(argv[2]);
    	 ifstream file(filename);
	string input;
	char c;
	 file >> noskipws;
  	 while ( file >> c )
		 input += c;
   	file.close();
	unsigned int iP, iQ, iD, iE, iN, iTotientN;
	cout<<"Enter the first prime number: "<<endl;
	cin>>iP;
	cout<<"Ente the second prime number: "<<endl;
	cin>>iQ;
	int n=input.length();
	unsigned int message[n];
        long double encryptedMessage[n];

	for(int i=0;i<n;i++){
		message[i]=int(input[i]-65);
	}    
	double startTime = omp_get_wtime();

	cout << "P: " << iP << endl;
	cout << "Q: " << iQ << endl;

	iN = iP * iQ;
	iP -= 1;
	iQ -= 1;
	iTotientN = iP * iQ;

	iE = 2;
	while(iE < iTotientN)
	{
		if(gcd(iE, iTotientN) == 1)
			break;
			
		iE++;
	}
	int i=1;
	while(i < iN)
	{
		iD = (iE * i - 1) % iTotientN;
		if(!iD)
		{
			iD = i;
			break;
		}
		i++;
	}

	cout << "E: " << iE << endl;
	cout << "N: " << iN << endl;
	cout << "\n------ Encrypted message -------" << endl;
	int iChunk = iE / thread_count;
    	int iChunkRemainder = iE % thread_count;
    	int startIndex, endIndex;
    	long double dTemp;
	for(int i = 0; i < n; i++)
	{
		encryptedMessage[i] = 1;
		
		//Getting into the parallel region
		#pragma omp parallel firstprivate(startIndex, endIndex) num_threads(thread_count)
		{
			int myRank = omp_get_thread_num(); //What thread am I?

			dTemp = 1;

			// Computing two varibles to buffer through the array which are derivatives from myRank variable
	        startIndex = myRank * iChunk;
	        if(iChunkRemainder && (startIndex + iChunk) > iE)
	            endIndex = iChunkRemainder;
	        else if (iChunkRemainder && myRank == thread_count - 1 && (startIndex + iChunk) < iE)
	        	endIndex = startIndex + iChunk + iChunkRemainder;
	        else
	            endIndex = startIndex + iChunk;

	        for(int index = startIndex; index < endIndex; index++)
	        	dTemp = dTemp * message[i];

	        /*if(i < 2)
	        	cout << "Start Index: " << startIndex << " | End Index: " << endIndex << " | Process: " << myRank << " | Result: " << dTemp << endl;*/

	        encryptedMessage[i] = encryptedMessage[i] * dTemp;
	    }

	    encryptedMessage[i] = fmod(encryptedMessage[i], iN);

	    cout << encryptedMessage[i] << " ";
	}

	cout << "D: " << iD << endl;
	cout << "N: " << iN << endl;
	
	cout << "\n\n------ Decrypted message -------" << endl;
	iChunk = iD / thread_count;
    iChunkRemainder = iD % thread_count;
    
	for(int i = 0; i < n; i++)
	{
		long double decryptedText = 1;

		//Getting into the parallel region
		#pragma omp parallel firstprivate(startIndex, endIndex) num_threads(thread_count)
		{
			int myRank = omp_get_thread_num(); //What thread am I?

			dTemp = 1;

			// Computing two varibles to buffer through the array which are derivatives from myRank variable
	        startIndex = myRank * iChunk;
	        if(iChunkRemainder && (startIndex + iChunk) > iD)
	            endIndex = iChunkRemainder;
	        else if (iChunkRemainder && myRank == thread_count - 1 && (startIndex + iChunk) < iD)
	        	endIndex = startIndex + iChunk + iChunkRemainder;
	        else
	            endIndex = startIndex + iChunk;

	        for(int index = startIndex; index < endIndex; index++)
	        	dTemp = dTemp * encryptedMessage[i];

	        /*if(i < 2)
	        	cout << "Start Index: " << startIndex << " | End Index: " << endIndex << " | Process: " << myRank << " | Result: " << dTemp << endl;*/

	        decryptedText = decryptedText * dTemp;
	    }

	    decryptedText = fmod(decryptedText, iN);

	    cout <<char(decryptedText+65) << " ";
  	}


	double endTime = omp_get_wtime();

         cout << "\n\nTotal Runtime: " << endTime - startTime << endl;



}
