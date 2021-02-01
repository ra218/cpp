#include <iostream>
#include <vector>
#include "generate.h"
#include <cstdlib>
using namespace std;

int sizeOfEntity,length,mod;
//Vehicle Entity class
class Vehicle
{

public:
    const int baseValue=0;
    int gravity;
    vector<int> difference;
    vector<int> featureList;
    int calcDifference(Vehicle x, Vehicle y);
    int calcGravity(int length,vector<int> a, int baseVal);
    void display(int length,Vehicle obj);

};
// function to calculate vehicle difference
int Vehicle::calcDifference(Vehicle x, Vehicle y)
{
    int temp=0;
    int num=0;
    for(int i=0; i<length; i++)
    {
        temp=x.featureList[i]-y.featureList[i];
        while(temp<0)
        {
            temp=temp+mod;
        }
        num=num+temp;

    }

    return num;

}

// finction to display vehicle features and gravity
void Vehicle::display(int length,Vehicle obj)
{

    for(int i=0; i<length; i++)
    {

        cout<<obj.featureList[i]<<" ";

    }
    cout<<"\t Gravity: "<<obj.gravity;

}
// function to calculate gravity
int Vehicle:: calcGravity(int length,vector<int> a, int baseVal)
{
    int count=0;
    for(int i=0; i<length; i++)
    {

        if(a[i]!=baseVal)
        {
            count++;
        }

    }
    return count;

}
//Entity Animal Class
class Animal
{
public:
    int gravity;
    //  int difference;
    const char baseValue='A';
    // function to calculate gravity
    int calcGravity(vector<char> a, char baseVal)
    {

        int count=0;
        for(int i=0; i<length; i++)
        {

            if(a[i]!=baseVal)
            {
                count++;
            }

        }
        return count;
    }
    vector<int> difference;
    vector<char> featureList;
    //function to calculate animal difference
    int calcDifference(Animal x, Animal y)
    {
        int temp=0;
        int num=0;
        for(int i=0; i<length; i++)
        {
            temp=x.featureList[i]-y.featureList[i];
            if(temp!=0)
            {
                temp=1;
            }
            num=num+temp;

        }

        return num;

    }
    // function to display animal feature and gravity
    void display(Animal obj)
    {
        for(int i=0; i<length; i++)
        {

            cout<<obj.featureList[i]<<" ";

        }
        cout<<"\t Gravity: "<<obj.gravity;


    }
};

//generic template for both vehicle and animal class
template <typename T>
class Collection
{

public:
    static void calcDifference(T objectArray[])
    {
        for(int i=0; i<sizeOfEntity; i++)
        {

            for(int j=0; j<sizeOfEntity; j++)
            {

                int diff=objectArray[i].calcDifference(objectArray[i],objectArray[j]);

                objectArray[i].difference.push_back(diff);
            }

        }
    }


    static void display(T objectArray[])
    {

        cout<<"\n\nDifference table:\n ";
        for(int i=0; i<sizeOfEntity; i++)
        {

            for(int j=0; j<sizeOfEntity; j++)
            {
                cout<<objectArray[i].difference[j]<<" ";
            }
            cout<<"\n ";
        }

    }


    static int minimumGravity(int size,T array[])
    {

        int temp=array[1].gravity;
        for(int i=2; i<size; i++)
        {


            if(array[i].gravity<temp)
            {
                temp=array[i].gravity;
            }

        }

        return temp;
    }

    static int minimumDifference(T obj[])
    {
        int minimumdiff=obj[0].difference[1];
        for(int i=0; i<sizeOfEntity; i++)
        {

            for(int j=0; j<sizeOfEntity; j++)
            {

                if(i!=j)
                {

                    int temp = obj[i].difference[j];
                    if(temp<minimumdiff)
                    {
                        minimumdiff=temp;
                    }

                }

            }
        }
        return minimumdiff;

    }
};


string checkCommandLineArguments(int a)
{

    if(a<5||a>6)
    {
        return ("inappropriate number of arguments entered");


    }
    else
    {
        return "valid";
    }
}


int main(int argc, char *argv[])
{
    int entityType;
    int seed;
    sizeOfEntity;

    string response=checkCommandLineArguments(argc);
    if(response!="valid")
    {
        cerr<<"\n"<<response<<"\n";
        return 0;
    }

    if(argc==5)
    {
        int num=atoi(argv[1]);

        if(num==0||num==1)
        {
            entityType=atoi(argv[1]);
        }
        else
        {

            cerr<<"\ninvalid entityType\n";
            return 0;
        }


        if(atoi(argv[2])>0)
        {
            seed=atoi(argv[2]);
        }
        else
        {
            cerr<<"\ninvalid seed value\n";
            return 0;
        }

        if(atoi(argv[3])>0)
        {
            length=atoi(argv[3]);
        }
        else
        {
            cerr<<"\ninvalid length value\n";
            return 0;
        }

        if(atoi(argv[4])>0)
        {
            sizeOfEntity=atoi(argv[4]);
        }
        else
        {
            cerr<<"\ninvalid size of entity value\n";
            return 0;
        }

    }

    else if(argc==6)
    {
        int num=atoi(argv[1]);

        if(num==0||num==1)
        {
            entityType=atoi(argv[1]);
        }
        else
        {
            cerr<<"\ninvalid entity type\n";
            return 0;
        }
        if(atoi(argv[2])>0)
        {
            seed=atoi(argv[2]);
        }
        else
        {
            cerr<<"\ninvalid seed value\n";
            return 0;
        }
        if(argv[3]>0)
        {
            length=atoi(argv[3]);
        }
        else
        {
            cerr<<"\ninvalid length value\n";
            return 0;
        }
        if(atoi(argv[4])>0)
        {
            sizeOfEntity=atoi(argv[4]);
        }
        else
        {
            cerr<<"\ninvalid size of entity value\n";
            return 0;
        }
        if(atoi(argv[5])>0)
        {
            mod=atoi(argv[5]);
        }
        else
        {
            cerr<<"\ninvalid modulus value\n";
            return 0;
        }
    }
    //string response=checkCommandLineArguments(argc);
    if(response=="valid")
    {
        if(entityType==0)
        {
            Vehicle objArray[sizeOfEntity];
            objArray[0].featureList.assign (length,objArray[0].baseValue);
            objArray[0].gravity=objArray[0].calcGravity(length,objArray[0].featureList,objArray[0].baseValue);
            objArray[0].display(length,objArray[0]);
            cout<<"\n";
            for(int i=1; i<sizeOfEntity; i++)
            {
                for(int j=0; j<length; j++)
                {
                    int feature= generateVehicleFeature(seed,mod);
                    objArray[i].featureList.push_back(feature);
                }
                objArray[i].gravity=objArray[i].calcGravity(length,objArray[i].featureList,objArray[i].baseValue);
                objArray[i].display(length,objArray[i]);
                cout<<"\n";
            }

            cout<<"\nMinimum Gravity: "<<Collection<Vehicle>::minimumGravity(sizeOfEntity,objArray);
            Collection<Vehicle>::calcDifference(objArray);
            Collection<Vehicle>::display(objArray);
            cout<<"\nMinimum Difference: "<<Collection<Vehicle>::minimumDifference(objArray)<<"\n\n";

        }
        else if(entityType==1)
        {
            Animal objArray[sizeOfEntity];
            objArray[0].featureList.assign (length,objArray[0].baseValue);
            objArray[0].gravity=objArray[0].calcGravity(objArray[0].featureList,objArray[0].baseValue);
            objArray[0].display(objArray[0]);
            cout<<"\n";
            for(int i=1; i<sizeOfEntity; i++)
            {
                for(int j=0; j<length; j++)
                {
                    char feature=generateAnimalFeature(seed);
                    objArray[i].featureList.push_back(feature);
                }
                objArray[i].gravity=objArray[i].calcGravity(objArray[i].featureList,objArray[i].baseValue);
                objArray[i].display(objArray[i]);
                cout<<"\n";

            }
            cout<<"\nMinimum Gravity: "<<Collection<Animal>::minimumGravity(sizeOfEntity,objArray);
            Collection<Animal>::calcDifference(objArray);
            Collection<Animal>::display(objArray);
            cout<<"\nMinimum Difference: "<<Collection<Animal>::minimumDifference(objArray)<<"\n\n";
        }
    }
    else
    {
        cerr<<response;
        return -1;
    }
    return 0;

}
