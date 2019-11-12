#include<bits/stdc++.h>
using namespace std;

int fittest;
int secondFit;
string fittestChromo;
string secondFittestChromo;
string chromo[100];
void fitness(int popSize);
void jeanGrey(int popSize);
string crossOver(string father, string mother);
string mutation(string child);
void initPopulation(int popSize, int chromoLenght);

void fitness(int popSize){
	int tampFit=0;
	fittestChromo=secondFittestChromo=chromo[0];
	for(int i=0; i<popSize; i++){
		int currentScore=0;
		for(int j=0; j<chromo[i].size(); j++){
		  if(chromo[i][j]=='1') currentScore++;
		}
		if(i==0){
			fittest=secondFit=currentScore;
		}


		if(currentScore>fittest){
			fittest=currentScore;
			fittestChromo=chromo[i];

		}
		else if(currentScore>secondFit){
			secondFit=currentScore;
			secondFittestChromo=chromo[i];
		}


	}

}

void jeanGrey(int popSize){
	fitness(popSize);
	for(int i=0; i<popSize; i++){
		chromo[i]=mutation(crossOver(fittestChromo, secondFittestChromo));
	}
}

string crossOver(string father, string mother){
	int chromoSize=father.size();
	int defaultPoint=chromoSize/2;
	int midZone=defaultPoint/2;
    int point=rand()%defaultPoint+midZone;
	int tieBreaker=rand()%2;
	string child;
	if(tieBreaker==1){
		child=father.substr(0, point);
		child+=mother.substr(point, chromoSize);
	}
	else {
		child=mother.substr(0, point);
		child+=father.substr(point, chromoSize);

	}
	return child;
}

string mutation(string child){
	int numOfMutaion=rand()%2+1;
	int chromoSize=child.size();
	string cloneChild=child;
	while(numOfMutaion--){
		int point=rand()%chromoSize;
		if(child[point]=='0') cloneChild[point]='1';
		else cloneChild[point]='0';
	}
	return cloneChild;
}


void initPopulation(int popSize, int chromoLenght){
	for(int i=0; i<popSize; i++){
		string newChromo;
		for(int j=0; j<chromoLenght; j++){
			double val=(double)rand()/RAND_MAX;
			if(val<.01) newChromo+='1';
			else newChromo+='0';
		}
		chromo[i]=newChromo;
	}

}

int main(){

	srand(time(0));
	int popSize, chromoLenght;
	cout<<"Enter population size and chromosome lenght : \n";
	cin>>popSize>>chromoLenght;
	initPopulation(popSize, chromoLenght);
	fitness(popSize);
	int generation=1;
	cout<<generation<<": \n"<<fittest<<" "<<secondFit<<"\n"<<fittestChromo<<" "<<secondFittestChromo<<endl;

	//Format : generation, father rank, mother rank, father chromosome, mother chromosome;
	while(secondFit!=chromoLenght){
		generation++;
		jeanGrey(popSize);
		fitness(popSize);
		cout<<generation<<": \n"<<fittest<<" "<<secondFit<<"\n"<<fittestChromo<<" "<<secondFittestChromo<<endl;
	}
	cout<<"\n\nIt took "<<generation<<" to master it!\n\n";

}
