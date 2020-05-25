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
#include <time.h>

using namespace std;

struct Sender{
	char sender[10] ;
	char recipient[10] ;
	float weight ;
};

struct Relation{
	char sender[10] ;
	char recipient[10] ;
	float weight ;
	int connectnum ;
	Relation * next ;
};

/*------------------------readfile start-----------------------------*/

class File {
	
	public:
		bool readFile(string fileName) ;
		vector<Sender> store ;
		
	private:
		fstream file ;
		
}; 

bool File::readFile( string fileName ){
	
	fileName = "pairs" + fileName + ".bin" ;
	int stNo = 0;
	file.open( fileName.c_str(), fstream::in|fstream::binary );
	
	if( file.is_open() ){
		
		Sender temp ;
		file.seekg( 0, file.end );
		int stNo = file.tellg()/sizeof( temp );
		file.seekg( 0, file.beg) ;
		
		for( int i = 0; i < stNo ; i++ ){
			file.read( (char*)&temp, sizeof(temp) );
			store.push_back( temp );
		} // for
		
		file.close();
		return true;
		
	} // if
	else {
		cout << "fileName:" <<  fileName + " can't found.'\r\n" ; 
		return false;
	} // else

} // readFile()

/*------------------------readfile end-----------------------------*/

/*------------------------mission1 start-----------------------------*/

class AdjacencyList {
	
	public:
		AdjacencyList( string fileName ) ;
		void search( string fileName ) ;
		vector<Relation*> list ; // put mission1 major list
		vector<Relation*> connection ; // put mission2 major list
		vector<Relation> queue ;
		
	private:
		File * reader ;
		FILE * file ;
        void createList( string fileName ) ;
        void arrange( vector<Relation*>& templist ) ;
        void writefileADJ( string fileName ) ;
        void writefileCNT( string fileName ) ;
        void enqueue( int pos ) ;
        Relation* dequeue() ;
        bool isVisit( char name[10] ) ;
        bool firstcheck ;
        void countConnectNum() ;
        int findPos( char name[10] ) ;
        void quickSort( vector<Relation*>& templist, int low, int high ) ;
        int partitionSender( vector<Relation*>& templist, int low, int high ) ;
        
};

AdjacencyList::AdjacencyList( string fileName ){
	
	reader = new File();
	if ( reader->readFile(fileName) == true ) {
		createList(fileName) ;
	} // if
	
}

void AdjacencyList::createList( string fileName ){
	
	Relation * temp ;
	Relation * run ;
	bool test = false ;
	int size = reader->store.size() ;
	
	for ( int i = 0 ; i < size ; i++ ){
		
		temp = new Relation() ; // make a object first
		strcpy( temp->sender, reader->store.at(i).sender ) ;
		strcpy( temp->recipient, reader->store.at(i).recipient ) ;
		temp->weight = reader->store.at(i).weight ;
		temp->next = NULL ;
		
		if ( list.size() == 0 || 
		    (list.size() != 0 && strcmp( reader->store.at(i-1).sender, reader->store.at(i).sender ) != 0) ){ // push back object in the beggining
			
			list.push_back(temp) ;
			run = list.at(list.size()-1) ;
			
		} // if
		else if ( list.size() != 0 && strcmp( reader->store.at(i-1).sender, reader->store.at(i).sender ) == 0 ){ // connect all recipient
			
			run->next = temp ;
			run = run->next ;
			 
		}// else if
		
		for ( int j = 0 ; j < size ; j++ ){ // check recipient did not send any messege
			if ( strcmp( reader->store.at(j).sender, reader->store.at(i).recipient ) == 0 ){
				test = true ;
			} // if
		} // for
		for ( int z = 0 ; z < list.size() ; z++ ){
			if ( strcmp( list.at(z)->sender, reader->store.at(i).recipient ) == 0 ){
				test = true ;
			} // if
		} // for
			
		if ( !test ){ // if recipient did not send any messege, set it
			temp = new Relation() ;
			strcpy( temp->sender, run->recipient ) ;
			strcpy( temp->recipient, " " ) ;
			temp->next = NULL ;
			list.push_back(temp) ;
		} // if
		
		test = false ;
	} // for
	
	arrange(list) ;
	writefileADJ(fileName) ;
	
} // createList()

void AdjacencyList::arrange( vector<Relation*>& templist ){ // arrange all sender and recipient
	
	vector <Relation*> recipientList ;
	Relation * walk ;
	Relation * temp ;
	int run = 0 ;

	for ( int i = 0 ; i < templist.size() ; i++ ){
		
		for ( walk = templist.at(i) ; walk != NULL ; walk = walk->next ){ // copy all the recipient to vector
			
			temp = new Relation() ;
			strcpy( temp->recipient, walk->recipient ) ;
		    temp->weight = walk->weight ;
		    recipientList.push_back( temp ) ;
		    
		} // for
		
		for ( int j = 0 ; j < recipientList.size()-1 ; j++ ){ // arrange all the recipient
			
		    for ( int z = j+1 ; z < recipientList.size() ; z++ ){
		    	
		    	if ( strcmp( recipientList.at(j)->recipient, recipientList.at(z)->recipient ) > 0 ){
		   		    swap( recipientList.at(j), recipientList.at(z) ) ;
			    } // if
		    	
			} // for
		    
		} // for
		
		for ( walk = templist.at(i), run = 0 ; walk != NULL, run < recipientList.size() ; walk = walk->next, run++ ){ // copy arranged vector to recipient list
			
			strcpy( walk->recipient, recipientList.at(run)->recipient ) ;
		    walk->weight = recipientList.at(run)->weight ;

		} // for
		
		recipientList.clear() ;
	} // for

    quickSort( templist, 0, templist.size()-1 ) ;

} // arrange()

void AdjacencyList::quickSort( vector<Relation*>& templist, int low, int high ){
	
	if ( low < high ){
		
		int pi = partitionSender( templist, low, high ) ;
		quickSort( templist, low, pi-1 ) ;
		quickSort( templist, pi+1, high ) ;
		
	} // if
	
} // quickSort()

int AdjacencyList::partitionSender( vector<Relation*>& templist, int low, int high ){
	
	char pivot[10] ;  
	strcpy( pivot, templist.at(high)->sender ) ;
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++){  
         
        if ( strcmp( templist.at(j)->sender, pivot ) < 0 ){  
            i++; // increment index of smaller element  
            swap( templist.at(i), templist.at(j) );  
        }  // if
        
    } // for
    
    swap( templist.at(i+1), templist.at(high) ); 
    return (i + 1);  
	
} // partitionSender()

void AdjacencyList::writefileADJ( string fileName ){ // write ADJ file

    Relation * walk ;
    int run = 1 ;
    fileName = "pairss" + fileName + ".adj" ;
	file = fopen( fileName.c_str(), "w") ;
	fprintf( file,"<<< There are %d IDs in total. >>>", list.size() ) ;
    printf( "\n<<< There are %d IDs in total. >>>\n", list.size() ) ;

    for ( int i = 0 ; i < list.size() ; i++ ){
    	
    	if ( i < 9 ){
    		fprintf( file,"\n[  %d] %s: \n\t", i+1, list.at(i)->sender ) ;
		} // if
		else{
			fprintf( file,"\n[ %d] %s: \n\t", i+1, list.at(i)->sender ) ;
		} // else
    	
		for ( walk = list.at(i), run= 1 ; walk != NULL ; walk = walk->next, run++ ){
			
			if ( strcmp( walk->recipient, " " ) == 0 ){
				;
			} // if
			else if ( run < 10 ){
				fprintf( file,"( %d) %s,\t%.2f\t", run, walk->recipient, walk->weight ) ;
			} // else if
			else if ( walk->next == NULL ){
				fprintf( file,"(%d) %s,\t%.2f", run, walk->recipient, walk->weight ) ;
			} // else
			else {
				fprintf( file,"(%d) %s,\t%.2f\t", run, walk->recipient, walk->weight ) ;
			} // else
			
			if ( run != 0 && (run)%10 == 0 ){
				fprintf( file, "\n\t" ) ;
			} // if
			
		} // for
		
	} // for

    fprintf( file,"\n<<< There are %d nodes in total. >>>\n", reader->store.size() ) ;
    printf( "\n<<< There are %d nodes in total. >>>\n", reader->store.size() ) ;
	fclose(file) ;

} // writefile()

void AdjacencyList::search( string fileName ){ // BFS search 
	
	int size = list.size() ;
	Relation * temp ;
	Relation * walk ;
	bool beg = true ;
	int pos ;

	for ( int i = 0 ; i < size ; i++ ){
		
		beg = true ;
		firstcheck = true ;
		pos = i ;
		
		while ( beg || !queue.empty() ){

			temp = new Relation() ;
			enqueue(pos) ;
			temp = dequeue() ;
			
			if ( !beg ){
				walk->next = temp ;
				walk = walk->next ;
			} // if
			
			if ( beg ){
				connection.push_back( temp ) ;
				walk = connection.at(i) ;
				beg = false ;
			} // if
			
			if ( strcmp( walk->recipient, " " ) == 0 ){
				break ;
			} // if
  
            pos = findPos( walk->recipient ) ;
            
            if ( queue.empty() ){
            	
            	temp = new Relation() ;
			    enqueue(pos) ;
			    
			} // if

		} // for
		
	} // for
	
	arrange( connection ) ;
	writefileCNT( fileName ) ;
	
} // search()

int AdjacencyList::findPos( char name[10] ){ // find name's sender position
	
	int size = list.size() ;
	int pos = 0 ;
	int in = 0 ;
	int end = size-1  ;
	int mid = ( in + end ) / 2 ;
	
	while ( 1 ){
		
		if ( strcmp( list.at(mid)->sender, name ) == 0 ){				
			pos = mid ;
			break ;
		} // if
		else if ( strcmp( list.at(mid)->sender, name ) > 0 ){
			
			end = mid - 1 ;
			mid =  ( in + end ) / 2 ;
		} // else if
		else if ( strcmp( list.at(mid)->sender, name ) < 0 ){
			in = mid + 1 ;
			mid =  ( in + end ) / 2 ;
		} // else if
		
	} // while
	
	return pos ;
			
}  // findPos()

void AdjacencyList::enqueue( int pos ){ // add all recipient to queue
	
	Relation * walk ;
	Relation temp ;
	for ( walk = list.at(pos) ; walk != NULL ; walk = walk->next ){
		
		if ( firstcheck || !isVisit( walk->recipient ) ){
			strcpy( temp.recipient, walk->recipient ) ;
			strcpy( temp.sender, walk->sender ) ;
		    queue.push_back( temp ) ;
		    
		} // if
		
	} // for
	
	firstcheck = false ;
} // enqueue()

Relation* AdjacencyList::dequeue(){ // get first recipient from queue and remove first item
	
	Relation * retemp = new Relation() ;
	strcpy( retemp->recipient, queue.at(0).recipient ) ;
	strcpy( retemp->sender, queue.at(0).sender ) ;
	retemp->next = NULL ;
	queue.erase(queue.begin()) ;
	return retemp ;
	
} // dequeue()

bool AdjacencyList::isVisit( char name[10] ){ // check name whether exist before
	
	int size = queue.size() ;
	Relation * walk ;
	
 	if ( strcmp( name, connection.at(connection.size()-1)->sender ) == 0 ){ // the same as sender
		return true ;
	} // if
	
	if ( strcmp( name, " " ) == 0 ){
		return true ;
	} // if 
	
	for ( walk = connection.at(connection.size()-1) ; walk != NULL ; walk = walk->next ){
		
		if ( strcmp( name, walk->recipient ) == 0 ){
			return true ;
		} // if
		
	} // for

    for ( int i = 0 ; i < queue.size() ; i++ ){
    	
    	if ( strcmp( name, queue.at(i).recipient ) == 0 )
    	    return true ;
    	
	} // for
	return false ;
	
} // isVisit()

void AdjacencyList::countConnectNum(){ // count connection Num and arrange it
	
	int size = connection.size() ;
	Relation* walk ;
	int count = 0 ; 
	
	for ( int i = 0 ; i < size ; i++ ){ // count connection Num
		
		for ( walk = connection.at(i) ; walk != NULL ; walk = walk->next ){
			if ( strcmp( walk->recipient, " " ) != 0 )
			    count++ ;
		} // for
		
		connection.at(i)->connectnum = count ;
		count = 0 ;
	} // for
	
	quickSort( connection, 0, connection.size()-1 ) ;
	
	for ( int i = 0 ; i < size-1 ; i++ ){ // arrange by connection Num
		
		for ( int j = i ; j < size ; j++ ){
		    if ( connection.at(i)->connectnum < connection.at(j)->connectnum ){
		   		swap( connection.at(i), connection.at(j) ) ;
			} // if	
		} // for
		
	} // for

	
} // countConnectNum()

void AdjacencyList::writefileCNT( string fileName ){ // write CNT file

    Relation * walk ;
    int run = 1 ;
    countConnectNum() ;
    fileName = "pairss" + fileName + ".cnt" ;
	file = fopen( fileName.c_str(), "w") ;
	fprintf( file,"<<< There are %d IDs in total. >>>", connection.size() ) ;
    printf( "\n<<< There are %d IDs in total. >>>\n", connection.size() ) ;
    
    for ( int i = 0 ; i < connection.size() ; i++ ){
    	
    	if ( i < 9 ){
    		fprintf( file,"\n[  %d] %s(%d): \n", i+1, connection.at(i)->sender, connection.at(i)->connectnum ) ;
		} // if
		else if ( i < 99 && i >= 9 ){
			fprintf( file,"\n[ %d] %s(%d): \n", i+1, connection.at(i)->sender, connection.at(i)->connectnum ) ;
		} // else
		else if ( i >= 99){
			fprintf( file,"\n[%d] %s(%d): \n", i+1, connection.at(i)->sender, connection.at(i)->connectnum ) ;
		} // else if
    	
		for ( walk = connection.at(i), run = 1 ; walk != NULL ; walk = walk->next, run++ ){
			
			if ( strcmp( walk->recipient, " ") == 0 ){
				;
			} // if
			else if ( run < 10 ){
				fprintf( file,"\t( %d) %s", run, walk->recipient ) ;
			} // else if
			else if ( run > 99 ){
				fprintf( file,"\t(%d) %s", run, walk->recipient ) ;
			} // else if
			else if ( run != 1 && (run-1)%10 == 0  ){
				fprintf( file,"\t(%d) %s", run, walk->recipient ) ;
			} // else if 
			else if ( run%10 == 0 ){
				fprintf( file,"\t(%d) %s", run, walk->recipient ) ;
			} // else if 
			else if ( walk->next == NULL ){
				fprintf( file,"\t(%d) %s", run, walk->recipient ) ;
			} // else
			else {
				fprintf( file,"\t(%d) %s", run, walk->recipient ) ;
			} // else
			
			if ( run != 0 && (run)%10 == 0 ){
				fprintf( file, "\n" ) ;
			} // if
			
		} // for
		
	} // for

    fprintf( file, "\n" ) ;
	fclose(file) ;

} // writefile()

string getMenu () {
	string msg = "\r\n";
	msg += "**** Graph data manipulation ****\r\n";
	msg += "* 0. QUIT                       *\r\n";
	msg += "* 1. Build adjacency lists      *\r\n";
	msg += "* 2. Compute connection counts  *\r\n";
	msg += "*********************************\r\n"; 
	msg += "Input a choice(0, 1, 2):";
	return msg;
} // getMenu()

int main () {
	
	int command = -1 ;
	string name;
	bool test = false ;
	
	while ( command != 0 ) {
		
        AdjacencyList * user ;

		cout << getMenu();
		cin >> command;
		
		if(command == 0);	// 離開 
		
		else if (command == 1){	// 任務一 
		    test = true ;
			cout << "\r\nInput a file number ([0] Quit):";
			cin >> name;
			
			if ( strcmp(name.c_str(),"0")==0 );
			else {
				
				user = new AdjacencyList( name ) ;

 			} // else
		} // else if
		else if (command == 2){
			
			if ( test ){
				user->search( name ) ;
				test = false ;
			} // if
			else {
				cout << "### There is no graph and choose 1 first. ###\n" ;
			} // else
			
		} // else if
		else {
			cout << "Command does not exist!" << endl ;
		} // else
		
	} // while
	
	system("pause");
}
