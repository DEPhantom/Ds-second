/* team04
   10727247 廖仁傑 
   10727220 陳正浩*/ 
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <iomanip> 

using namespace std;
#define COLUMNS 6
#define MAX_LEN 10
#define BIG_INT 255
#define MAX 200

struct Student {					// type of a student record
	char sId[MAX_LEN];				// student id
	char sName[MAX_LEN];			// student name
	unsigned char score[COLUMNS];	// a set of scores in [0,100]
	float mean;						// the average of scores
} ;

struct HashType {					// type of a student record
	int list ;
	int hvalue ;
	bool empty ;
	char sId[MAX_LEN];				// student id
	char sName[MAX_LEN];			// student name
	float mean;						// the average of scores
} ;

/*------------------------change binary start-----------------------------*/

class BitCovertion {
	
	public:
		
		BitCovertion( string &fileName );
   		void readFile( string &fileName );
		int isBinary( string &fileNmae );
		void buildBin( string fileName );
		
	private:
		
		void openFile( string fileName );
		void closeFile();
		string readTool( int mode );
   		vector<Student> tempVec;
   		fstream file;
   		fstream outFile;
	
};

BitCovertion::BitCovertion( string &fileName ){
	readFile(fileName);
}

string BitCovertion::readTool( int mode ) {
	
    char controlC = 0;
    char temp;
    string read = "";
    
    if ( mode == 1 ) {
        controlC = '\t';
        if ( ! file.eof() ) {
        	
        	file.get(temp);
        	
            while ( temp != controlC && ! file.eof() ){
            	
           		read.push_back(temp);
            	file.get(temp);
            	
			} // while
			
        } // if
    } // if
	else if ( mode == 2 ) { 
	
	    controlC = '\n';
	    
        if ( ! file.eof() ) {
        	
        	file.get(temp);
        	
            while ( temp != controlC && ! file.eof() ){
            	
           		read.push_back(temp);
            	file.get(temp);
            	
			} // while
			
        } // if
        
	} // else if
	
    return read;
    
} // readTool()

void BitCovertion::readFile( string &fileName ){
	
	openFile(fileName);
	char rBuf[BIG_INT];
	int stNo = 0;
	
    while ( file.getline(rBuf,BIG_INT,'\n') ) {
    	
    	string temp = "";
		Student student ;
		int cNo =0,pre = 0,pos = 0;
		stNo++;
		temp.assign(rBuf);
		pos = temp.find_first_of('\t',pre);
		
		while(pos!=string::npos) {
			
			switch(++cNo){
				
				case 1:strcpy(student.sId, temp.substr(pre,pos-pre).c_str());
				      break;
				case 2:strcpy(student.sName, temp.substr(pre,pos-pre).c_str());
				      break;
				default: student.score[cNo-3] = atoi(temp.substr(pre,pos-pre).c_str());
				      break;    
				      
			} // switch
			
			pre = ++pos;
			pos = temp.find_first_of('\t', pre);
			
		} // while
		
		pos = temp.find_last_of('\t');
		student.mean = atof(temp.substr(pos+1).c_str());
		tempVec.push_back(student);

    } // while
    
    closeFile();
	buildBin(fileName);
	
} // readFile()

void BitCovertion::openFile(string fileName){
	
	fileName = "input"+fileName+".txt";
    file.open( fileName.c_str(), ios::in );
    
    if ( file == NULL ){
    	
		cout << "\r\n\r\n### " << fileName << " does not exist! ###\r\n\r\n";
		cout << "There is no data!\r\n\r\n";
		cout << "\r\nInput a file number:";
		cin >> fileName;
		openFile(fileName);
		
	} // if
	
} // openFile()

void BitCovertion::closeFile(){
	
    file.close();
    
} // closeFile()

void BitCovertion::buildBin( string fileName ){
	
	fileName = "input"+fileName+".bin";
	outFile.open(fileName.c_str(), fstream::out | fstream::binary);
	
	if ( outFile.is_open() ) {
		
		for ( int i = 0 ; i < tempVec.size() ; i++ ){
			outFile.write((char*)&tempVec[i], sizeof(tempVec[i]));
		} // for
		
		outFile.close();
		
	} // if
	
} // buildBin()

/*------------------------change binary end-----------------------------*/

/*------------------------readfile start-----------------------------*/

class QP {
	
	public:
		QP( string fileName );
		bool readFile(string fileName) ;
		vector<Student> store ;
		
	private:
		FILE * file ;
		BitCovertion *binary;

}; 

QP::QP( string fileName ){
	binary = new BitCovertion(fileName);
}

bool QP::readFile(string fileName){
			
 	fstream binFile;
 	Student oneSt;
	int stNo = 0;
			
 	fileName = "input" + fileName + ".bin";
 	binFile.open(fileName.c_str(), fstream::in|fstream::binary);
 			
 	if(binFile.is_open()){
 				
 	    binFile.seekg(0,binFile.end);
 	    stNo = binFile.tellg()/sizeof(oneSt);
  	    binFile.seekg(0,binFile.beg);
  			   
 	    for( int i =0; i<stNo; i++){
 	    	
 	        binFile.read((char*)&oneSt, sizeof(oneSt));
  	        store.push_back(oneSt);
  	        
 	    } // for
 			    
 	    binFile.close();
 	    return true;
 			    
 	} // if
	else {
				
 	    cout << "File Name:" << fileName << "Not Found!" ; 
 	    return false;
 			 
	} // else
    
} // readFile()

/*------------------------readfile end-----------------------------*/

/*------------------------mission1 start-----------------------------*/

class Quadratic {
	
	public:
		Quadratic( string fileName ) ;
		void createHashTable( string fileName ) ;
		void writefile( string fileName  ) ;
		void print() ;
		
	private:
		QP * qp ;
		FILE * file ;
		vector<HashType> hashtable ;
		int  findPrime() ;
		float unsuccessfulEfficiency() ;
		float successfulEfficiency() ;
	
};

Quadratic::Quadratic( string fileName ){
	
	qp = new QP( fileName );
	qp->readFile( fileName ) ;
	
}

void Quadratic::createHashTable( string fileName ){
	
	int tableSize = findPrime() ;
	long long key = 1 ;
	int test = 0 ;
	int loc = 1 ;
	int hvalue = 0 ;
	HashType temp ;
	
	for ( int run = 0 ; run < tableSize ; run++ ){
		temp.empty = true ;
		temp.list = run ;
		hashtable.push_back( temp ) ; 
	} // for
	
	for ( int i = 0 ; i < qp->store.size() ; i++ ){
		
		for ( int j = 0 ; j <= 9 ; j++ ){

			if ( (long long) qp->store.at(i).sId[j] > 47 && (long long) qp->store.at(i).sId[j] < 58 )
				key *= (long long)qp->store.at(i).sId[j] ;
		} // for
		
		key %= tableSize ;
		hvalue = key ;
		
		while (1) {
			
			if ( hashtable.at( (key+test)%tableSize ).empty ) {
				key = (key+test)%tableSize ;
				break ;
			} // if
			    
			test = loc * loc ;
			loc++ ;
			
		} // while
		
		test = 0 ;
		loc = 1 ;
        
		if ( hashtable.at(key).empty ) {
			
			hashtable.at(key).empty = false ;
			hashtable.at(key).hvalue = hvalue ;
			strcpy( hashtable.at(key).sId, qp->store.at(i).sId ) ;
			strcpy( hashtable.at(key).sName, qp->store.at(i).sName ) ;
			hashtable.at(key).mean = qp->store.at(i).mean ;
			
		} // if
		    
		key = 1 ;
		
	} // for
	
} // createHashTable()

int Quadratic::findPrime(){
	
	int check = true ;
	int size = qp->store.size()*1.2 + 1 ;
	
	for( int i = size ; 1 ; i++ ){
		
		for( int j = 1 ; j <= i ; j++ ){
			
			if ( i % j == 0 && j != 1 && j != i ){
				check = false ;
			} // if
			
		} // for
		
		if ( check ){
			return i ;
		} // if
		else {
			check = true ;
		} // else
		
	} // for
	
	return size ;
	
} // findPrime()

float Quadratic::unsuccessfulEfficiency(){
	
	int tableSize = findPrime() ;
	float count = 0 ;

	for ( int i = 0 ; i < tableSize ; i++ ){
		
		for( int j = 0 ; 1 ; j++ ){
				
			if ( hashtable.at((i+j*j)%tableSize).empty )
				break ;
				
			count++ ;
				
		} // for
				   
	} // for
	
	float average = count / tableSize ;
	return average ;
	
} // unsuccessfulEfficiency()

float Quadratic::successfulEfficiency(){
	
	int tableSize = findPrime() ;
	long long key = 1 ;
	float count = 0 ;
    
	for ( int i = 0 ; i < qp->store.size() ; i++ ){
		
		for ( int j = 0 ; j <= 9 ; j++ ){

			if ( (long long) qp->store.at(i).sId[j] > 47 && (long long) qp->store.at(i).sId[j] < 58 )
				key *= (long long)qp->store.at(i).sId[j] ;
		} // for
		
		key %= tableSize ;
		
		for( int z = 0 ; 1 ; z++ ){
			
			count++ ;	
			if ( strcmp( hashtable.at((key+z*z)%tableSize).sId, qp->store.at(i).sId ) == 0 )
				break ;
				
		} // for
		
		key = 1 ;
				   
	} // for
	
	float average = count / qp->store.size() ;
	return average ;
	
} // successfulEfficiency()

void Quadratic::print(){
	
	cout << "Hash table has been successfully created by Quadratic probing" << endl ;
	printf( "unsuccessful search: %.4f comparisons on average\n", unsuccessfulEfficiency() ) ;
	printf( "successful search: %.4f comparisons on average\n", successfulEfficiency() ) ;
	
} // print()

void Quadratic::writefile( string fileName ){
	
	int pos = 0 ;
	fileName = "quadratic" + fileName + ".txt" ;
	file = fopen( fileName.c_str(), "w") ;
	fprintf( file," --- Hash table created by Quadratic probing ---\n" ) ;
			
	while( pos < hashtable.size() ) {
		
		if ( hashtable.at(pos).empty ){
			fprintf( file,"[ %d]\n", hashtable.at(pos).list ) ;
		} // if
		else {
			fprintf( file,"[ %d]\t%d,\t%s,\t%s,\t%.2f\n", hashtable.at(pos).list, hashtable.at(pos).hvalue, 
		        hashtable.at(pos).sId, hashtable.at(pos).sName, hashtable.at(pos).mean ) ;
		} // else
		
		pos++ ;
		
	} // while
			
	fprintf( file," ----------------------------------------------------- " ) ;
	fclose(file) ;
	
} // Writefile()

/*------------------------mission1 end-----------------------------*/

/*------------------------mission2 start-----------------------------*/

class Double {
	
	public:
		Double( string fileName ) ;
		void createHashTable( string fileName ) ;
		void writefile( string fileName  ) ;
		void print() ;
		
	private:
		QP * qp ;
		FILE * file ;
		vector<HashType> hashtable ;
		int  findPrime( int size ) ;
		float successfulEfficiency() ;
};

Double::Double( string fileName ){
	
	qp = new QP( fileName );
	qp->readFile( fileName ) ;
	
}

void Double::createHashTable( string fileName ){

	int tableSize = findPrime( qp->store.size()*1.2+1 ) ;
	long long key = 1 ;
	long long okey ;
	int step = 0 ;
	int maxstep = findPrime( qp->store.size()/3+1 ) ;
	int hvalue = 0 ;
	HashType temp ;
	
	for ( int run = 0 ; run < tableSize ; run++ ){
		temp.empty = true ;
		temp.list = run ;
		hashtable.push_back( temp ) ; 
	} // for
	
	for ( int i = 0 ; i < qp->store.size() ; i++ ){
		
		for ( int j = 0 ; j <= 9 ; j++ ){

			if ( (long long) qp->store.at(i).sId[j] > 47 && (long long) qp->store.at(i).sId[j] < 58 )
				key *= (long long)qp->store.at(i).sId[j] ;
		} // for
		
		okey = key ;
		key %= tableSize ;
		hvalue = key ;
		
		while (1) {
			
			if ( hashtable.at( (key+step)%tableSize ).empty ) {
				key = (key+step)%tableSize ;
				break ;
			} // if
			
			step += maxstep - (okey%maxstep) ;
	        
		} // while
		
		step = 0 ;
        
		if ( hashtable.at(key).empty ) {
			
			hashtable.at(key).empty = false ;
			hashtable.at(key).hvalue = hvalue ;
			strcpy( hashtable.at(key).sId, qp->store.at(i).sId ) ;
			strcpy( hashtable.at(key).sName, qp->store.at(i).sName ) ;
			hashtable.at(key).mean = qp->store.at(i).mean ;
			
		} // if
		    
		key = 1 ;
		
	} // for
	
} // createHashTable()

int Double::findPrime( int size ){
	
	int check = true ;
	
	for( int i = size ; 1 ; i++ ){
		
		for( int j = 1 ; j <= i ; j++ ){
			
			if ( i % j == 0 && j != 1 && j != i ){
				check = false ;
			} // if
			
		} // for
		
		if ( check ){
			return i ;
		} // if
		else {
			check = true ;
		} // else
		
	} // for
	
	return size ;
	
} // findPrime()

float Double::successfulEfficiency(){
	
	int tableSize = findPrime( qp->store.size()*1.2+1 ) ;
	long long key = 1 ;
	long long okey = 0 ;
	int step = 0 ;
	int maxstep = findPrime( qp->store.size()/3+1 ) ;
	float count = 0 ;
    
	for ( int i = 0 ; i < qp->store.size() ; i++ ){
		
		for ( int j = 0 ; j <= 9 ; j++ ){

			if ( (long long) qp->store.at(i).sId[j] > 47 && (long long) qp->store.at(i).sId[j] < 58 )
				key *= (long long)qp->store.at(i).sId[j] ;
		} // for
		
		okey = key ;
		key %= tableSize ;
		
		while (1) {
			
			count++ ;
			if ( strcmp( hashtable.at( (key+step)%tableSize ).sId, qp->store.at(i).sId ) == 0 ) {
				break ;
			} // if
			
			step += maxstep - (okey%maxstep) ;
	        
		} // while
		
		step = 0 ;
		key = 1 ;
				   
	} // for
	
	float average = count / qp->store.size() ;
	return average ;
	
} // successfulEfficiency()

void Double::print(){
	
	cout << "Hash table has been successfully created by Double hashing" << endl ;
	printf( "successful search: %.4f comparisons on average\n", successfulEfficiency() ) ;
	
} // print()

void Double::writefile( string fileName ){
	
	int pos = 0 ;
	fileName = "double" + fileName + ".txt" ;
	file = fopen( fileName.c_str(), "w") ;
	fprintf( file," --- Hash table created by Double hashing    ---\n" ) ;
			
	while( pos < hashtable.size() ) {
		
		if ( hashtable.at(pos).empty ){
			fprintf( file,"[ %d]\n", hashtable.at(pos).list ) ;
		} // if
		else {
			fprintf( file,"[ %d]\t%d,\t%s,\t%s,\t%.2f\n", hashtable.at(pos).list, hashtable.at(pos).hvalue, 
		        hashtable.at(pos).sId, hashtable.at(pos).sName, hashtable.at(pos).mean ) ;
		} // else
		
		pos++ ;
		
	} // while
			
	fprintf( file," ----------------------------------------------------- " ) ;
	fclose(file) ;
	
} // Writefile()

/*------------------------mission2 end-----------------------------*/


string getMenu () {
	string msg = "\r\n";
	msg += "******* Hash Table *****\r\n";
	msg += "* 0. QUIT              *\r\n";
	msg += "* 1. Quadratic probing *\r\n";
	msg += "* 2. Double hashing    *\r\n";
	msg += "************************\r\n"; 
	msg += "Input a choice(0, 1, 2):";
	return msg;
} // getMenu()

int main () {
	
	int command = -1 ;
	string name;
	
	while ( command != 0 ) {
		
		Quadratic *user ;
		Double *user2 ;
		cout << getMenu();
		cin >> command;
		
		if(command == 0);	// 離開 
		
		else if (command == 1){	// 任務一 
			cout << "\r\nInput a file number ([0] Quit):";
			cin >> name;
			
			if ( strcmp(name.c_str(),"0")==0 );
			else {
				
				user = new Quadratic( name ) ;
				user->createHashTable( name ) ;
				user->writefile( name ) ;
				user->print() ;
				
 			} // else
		} // else if
		else if (command == 2){
			cout << "\r\nInput a file number ([0] Quit):";
			cin >> name;
			
			if ( strcmp(name.c_str(),"0")==0 );
			else {
				
				user2 = new Double( name ) ;
				user2->createHashTable( name ) ;
				user2->writefile( name ) ;
				user2->print() ;
				
			} // else
			
		} // else if
		else {
			cout << "Command does not exist!" << endl ;
		} // else
		
	} // while
	
	system("pause");
}
