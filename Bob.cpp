#include <cstdlib>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <random>


using namespace std;


//function prototypes below
void printError(string err);
void checkBandContent(string line);
void checkMusicianContent(string line);
void segregateJudges(string line);
void printAwards(int tj);
void printCompleteData();
void startPerformance();
int calculateBandPotential(string bandName, string member);
int calculateBandVariability(string bN, string bM);
double generateRandomNumber(int a,int b);


ofstream outData;
ifstream inBandsData,inMusiciansData,inJudgesData;


string bandName[10],bandMember[10],musicianName[10],judgeName[20];
int j=0,a=0,b=0,musicianMax[10],musicImpact[10],musicianVariability[10],mc0=0,mc1=0,mc2=0,mc3=0,mc4=0,totalJudges=0;
int judgeToughness[20],judgeMood[20];
char musicianCode[10];

int main(int argc,char* argv[])
{
	//reterieving command line arguments and opening respective files below
    string bands=argv[1];
    string musicians=argv[2];
    string judges=argv[3];
    ifstream inData;
    string readString,token;
	string output=argv[4];
    
    outData.open(output);


    inBandsData.open( bands ); // open input file
    inMusiciansData.open( musicians );
    inJudgesData.open( judges );


// check if opened successfully
    if (!inBandsData) 
    {
        printError("Error opening "+ bands);
    }
    if(!inMusiciansData)
    {
        printError("Error opening "+ musicians);
    }
    if(!inJudgesData)
    {
        printError("Error opening "+ judges);
    }



    // validating musician data
    readString="";
    while(getline(inMusiciansData, readString))
    {
        checkMusicianContent(readString);
    }
    readString="";


    // validating band content:

    while(getline(inBandsData, readString))
    {
        checkBandContent(readString);
    }

    readString="";
    mc0=0;
    mc1=0;
    mc2=0;
    while(getline(inJudgesData, readString))
    {
        segregateJudges(readString);
    }

    printCompleteData();

    printAwards(totalJudges);
    inBandsData.close();
    inMusiciansData.close();
    inJudgesData.close();
    startPerformance();
    outData.close();
    return 0;


}

//function to print errors when something bad happens, eg: failed validation or file not found
void printError(string err)
{
    cerr<<err;
    exit(0);
}

//function to validate content in Bands file
void checkBandContent(string line)
{
    string token;
    stringstream ss(line);
//reterieving tokens or substrings with respect to ':' as a delimiter
    while (getline(ss, token, ':'))
    {

        if(j%2==0)
        {
            bandName[a]=token;
            a++;
        }
        else if (j%2==1)
        {
            bandMember[b]=token;
            b++;
        }
        j++;

    }


// validation starts with respect to specifications in the assignment
    for(int i=0; i<a; i++)
    {
        if(bandName[i].empty()||bandMember[i].empty())
        {
            printError("empty name or code in bands file");
        }
        char bCode[bandMember[i].size()+1];
        strcpy(bCode, bandMember[i].c_str());
        int k=0,memberCount=0,totalMembers=0;
        for(int j=0; bCode[j]!='.'; j++)
        {
            int n = sizeof(bCode) / sizeof(bCode[0]);
            int cc;
            if(j%2==0)
            {
                bool isCodePresent = find(begin(musicianCode), end(musicianCode), bCode[j]) != end(musicianCode);
                if(!isCodePresent)
                {
                    printError("The code in bands file is not present in musician file");
                }


                cc=count(bCode, bCode + n, bCode[j]);
                if(cc>1)
                {
                    printError("There must not exist anny repetition of letter in member code");
                }
                if(!(bCode[j]>=65&&bCode[j]<=90))
                {
                    printError("The band member code is not in format LDLD:- Letter digit Letter Digit or the letter is small case");
                }
            }
            else if (j%2==1)
            {
                if(!(bCode[j]>=49&&bCode[j]<=57))
                {
                    printError("The band member code is not in format LDLD:- Letter digit Letter Digit, or the digit is 0");
                }
                else
                {
                    totalMembers=totalMembers+(bCode[j]-48);
                }
            }
        }

        if(totalMembers>10)
        {
            printError("The total band members exceed 10");
        }
    }



}

//function to validate content in musician file
void checkMusicianContent(string line)
{
    int arraySelector=0;
    string token="";
    stringstream ss(line);
	//reterieving tokens or sub string with respect to delimiter ':'
    while (getline(ss, token, ':'))
    {


        if(arraySelector==0)
        {
            char temp[5];
            strcpy(temp, token.c_str());


            musicianCode[mc0]=temp[0];
            mc0++;
        }
        else if (arraySelector==1)
        {
            musicianName[mc1]=token;
            mc1++;
        }
        else if (arraySelector==2)
        {
            musicianMax[mc2]=stoi(token);
            mc2++;
        }
        else if (arraySelector==3)
        {
            musicImpact[mc3]=stoi(token);
            mc3++;
        }
        else if (arraySelector==4)
        {
            musicianVariability[mc4]=stoi(token);
            mc4++;
        }
        arraySelector++;

    }

    for(int m=0; m<mc4; m++)
    {

        if(!(musicianCode[m]>=65&&musicianCode[m]<=90))
        {
            printError("code in musician file is not single character upper case");
        }

        if(musicianMax[m]>5||musicianMax[m]<1)
        {
            printError("musician count not in given range");
        }
        if(musicianVariability[m]>10||musicianVariability[m]<1)
        {
            printError("musician variation not in given range");
        }
        if(musicImpact[m]>10||musicImpact[m]<1)
        {
            printError("musician impact not in given range");
        }
        if(musicianName[m].empty())
        {
            printError("empty name in musician file");
        }


    }


}

// function to extract values from judges file with respect to delimiter ':'
void segregateJudges(string line)
{
    int arraySelector=0;

    string token="";
    stringstream ss(line);
    while (getline(ss, token, ':'))
    {


        if(arraySelector==0)
        {
            judgeName[mc0]=token;
            mc0++;
        }
        else if (arraySelector==1)
        {
            judgeToughness[mc1]=stoi(token);
            mc1++;
        }
        else if (arraySelector==2)
        {
            judgeMood[mc2]=stoi(token);
            mc2++;
        }
        arraySelector++;

    }
}
// function to print awards information
void printAwards(int tj)
{
    int passRequired;
    cout<<"****************************************************\n\nThe information on award levels is shown below:\n\n";
    passRequired=ceil(0*tj);
    cout<< "In order to achieve No Award the minimum number of passes required are: "<<passRequired<<endl;
    cout<<"\n";
    passRequired=ceil(tj*0.2);
    cout<< "In order to achieve Bronze Award the minimum number of passes required are: "<<passRequired<<endl;
    cout<<"\n";
    passRequired=ceil(tj*0.5);
    cout<< "In order to achieve Silver Award the minimum number of passes required are: "<<passRequired<<endl;
    cout<<"\n";
    passRequired=ceil(tj*0.8);
    cout<< "In order to achieve Gold Award the minimum number of passes required are: "<<passRequired<<endl;
    cout<<"\n";
    passRequired=ceil(tj*1);
    cout<< "In order to achieve Platinum Award the minimum number of passes required are: "<<passRequired<<endl;
    cout<<"\n****************************************************";
}
// function to print the extracted data from 3 files given as inputs via command line argument
void printCompleteData()
{

    cout<<"*******************************************"<<endl;
    cout<<"Data for Bands file is shown below\n"<<endl;


    //cout<<" size of band name = "<<sizeof(bandName);
    for(int i=0; !(bandName[i].empty()&&bandMember[i].empty()); i++)
    {
        if(!(bandName[i].empty()&&bandMember[i].empty()))
        {
            //cout<<i;
            cout<<"Band "<<i+1<<" name = "<<bandName[i]<<endl;
            cout<<"Band "<<i+1<<" member codes = "<<bandMember[i]<<endl;
            cout<<"\n\n";
        }
    }
    cout<<"*******************************************"<<endl;
    cout<<"Data for Musicians file is shown below \n"<<endl;


    for(int i=0; !(musicianName[i].empty()); i++)
    {
        cout<<i+1<<". Musician code = "<<musicianCode[i]<<endl;
        cout<<i+1<<". Musician name = "<<musicianName[i]<<endl;
        cout<<i+1<<". Musician maximum = "<<musicianMax[i]<<endl;
        cout<<i+1<<". Musician impact = "<<musicImpact[i]<<endl;
        cout<<i+1<<". Musician variation = "<<musicianVariability[i]<<endl;
        cout<<"\n\n";

    }

    cout<<"*******************************************"<<endl;
    cout<<"Data for Judges file is shown below\n"<<endl;

    for(int i=0; !(judgeName[i].empty()); i++)
    {
        totalJudges++;
        cout<<i+1<<". Judge Name = "<<judgeName[i]<<endl;
        cout<<i+1<<". Judge Toughness = "<<judgeToughness[i]<<endl;
        cout<<i+1<<". Judge mood = "<<judgeMood[i]<<endl;
        cout<<"\n\n";
    }
    cout<<"*******************************************\n"<<endl;
}

// function to start the band performance one by one
void startPerformance()
{

    int pass=0,fail=0;
    for(int i=0; !(bandName[i].empty()&&bandMember[i].empty()); i++)
    {
        pass=0;
        fail=0;
        cout<<"*******************************************";
        cout<<"\nThe performance of band named "<<bandName[i]<<" starts now"<<endl;
        cout<<"\n";

        outData<<"The performance of band named "<<bandName[i]<<" starts now\n\n";


        int bandPotential = calculateBandPotential(bandName[i],bandMember[i]);
        int bandVariability=  calculateBandVariability(bandName[i],bandMember[i]);

        outData<<"Band Potential: "<<bandPotential;
        outData<<"\n\nBand Variability: "<<bandVariability<<"\n\n\n\n";

        //generate random number
        int performanceScore=generateRandomNumber(bandPotential,bandVariability);

        for(int t=0; !(judgeName[t].empty()); t++)
        {

            int tough= judgeToughness[t];
            int mood= judgeMood[t];

            int judgeThreshold=generateRandomNumber(tough,mood);

            outData<<"The judge named "<<judgeName[t]<<" has threshold "<<judgeThreshold;
            outData<<"\n"<<judgeName[t]<<" gave a ";


            if(performanceScore>=judgeThreshold)
            {
                pass++;
                outData<<" pass\n";
            }
            else
            {
                fail++;
                outData<<" fail\n";
            }

        }

        cout<<"The total pass achieved by the band is "<<pass<<endl;
        cout<<"The total fail achieved by the band is "<<fail<<endl;

        if(pass>=ceil(1*totalJudges))
        {
            cout<<"\nThe band has achieved platinum award\n\n";
            outData<<"\nThe band has achieved platinum award\n\n";
            outData<<"---------------------------------------------------------\n";
        }
        else if(pass>=ceil(0.8*totalJudges))
        {
            cout<<"\nThe band has achieved Gold award\n\n";
            outData<<"\nThe band has achieved Gold award\n\n";
            outData<<"---------------------------------------------------------\n";

        }
        else if(pass>=ceil(0.5*totalJudges))
        {
            cout<<"\nThe band has achieved Silver award\n\n";
            outData<<"\nThe band has achieved Silver award\n\n";
            outData<<"---------------------------------------------------------\n";

        }
        else if(pass>=ceil(0.2*totalJudges))
        {
            cout<<"\nThe band has achieved Bronze award\n\n";
            outData<<"\nThe band has achieved Bronze award\n\n";
            outData<<"---------------------------------------------------------\n";

        }
        else if(pass<ceil(0.2*totalJudges))
        {
            cout<<"\nThe band has achieved No award\n\n";
            outData<<"\nThe band has achieved No award\n\n";
            outData<<"---------------------------------------------------------\n";

        }

    }
}
// function to calculate the band potential
int calculateBandPotential(string bN, string bm)
{
    char bCode[bm.size()+1];
    strcpy(bCode, bm.c_str());
    int k=0,memberCount=0,totalMembers=0,impactOfMember=0,totalImpact=0,im=0;
    for(int j=0; bCode[j]!='.'; j++)
    {
        int n = sizeof(bCode) / sizeof(bCode[0]);
        int cc;
        if(j%2==0)
        {
            int indexOfMember = distance(musicianCode, find(musicianCode, musicianCode + 10, bCode[j]));
            impactOfMember=musicImpact[indexOfMember];
        }
        else if (j%2==1)
        {
            im=impactOfMember*(bCode[j]-48);
            totalImpact=totalImpact+im;
        }
    }
    totalImpact=totalImpact+30;
    if(totalImpact>100)
    {
        totalImpact=100;
    }

    return totalImpact;

}

//function to calculate band variation
int calculateBandVariability(string bN, string bm)
{
    char bCode[bm.size()+1];
    strcpy(bCode, bm.c_str());
    int k=0,memberCount=0,totalMembers=0,variationOfMember=0,totalVariation=0,im;
    for(int j=0; bCode[j]!='.'; j++)
    {
        int n = sizeof(bCode) / sizeof(bCode[0]);
        int cc;
        if(j%2==0)
        {
            int indexOfMember = distance(musicianCode, find(musicianCode, musicianCode + 10, bCode[j]));
            variationOfMember=musicianVariability[indexOfMember];
        }
        else if (j%2==1)
        {
            im=variationOfMember*(bCode[j]-48);
            totalVariation=totalVariation+im;

        }
    }



    totalVariation=totalVariation+5;


    return totalVariation;

}

//function to generate randome number
double generateRandomNumber(int mean,int sd)
{

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution (mean,sd);
    return distribution(generator);
}
