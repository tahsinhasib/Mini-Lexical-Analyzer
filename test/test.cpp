#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
using namespace std;
int isKeyword(char buffer[]){
	char keywords[40][40] = {"switch","typedef","union",
							"unsigned","void","long","register","short","signed",
							"sizeof","static","volatile","while""auto","break","case","char","const","continue","default",
							"do","double","enum","extern","return","struct","float","for","goto",
							"if","int","else"};
	int i, T4Tutorials_Flag = 0;
	
	for(i = 0; i < 32; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			T4Tutorials_Flag = 1;
			break;
		}
	}	
	return T4Tutorials_Flag;
}
 
int main(){
	char ch, buffer[15], operators[] = "+-*/%=";
	ifstream fin("textfile.txt");
	int i,j=0;
	
	if(!fin.is_open()){
		cout<<"Sorrys: issue in opening the file"<<endl;
		exit(0);
	}
	
	while(!fin.eof()){
   		ch = fin.get();
   		
		for(i = 0; i < 6; ++i){
   			if(ch == operators[i])
   				cout<<ch<<" : operator"<<endl;
   		}
   		
   		if(isalnum(ch)){
   			buffer[j++] = ch;
   		}
   		else if((ch == ' ' || ch == '\n') && (j != 0)){
   				buffer[j] = '\0';
   				j = 0;
   				   				
   				if(isKeyword(buffer) == 1)
   					cout<<buffer<<" is keyword"<<endl;
   				else
   					cout<<buffer<<" : indentifier"<<endl;
   		}
   		
	}
	
	fin.close();
	
	return 0;
}