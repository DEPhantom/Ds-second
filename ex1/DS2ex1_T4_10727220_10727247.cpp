/* 10727220 ³¯¥¿¯E 10727247 ¹ù¤¯³Ç */ 
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <time.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std ;


struct inform{
	int listnumber ;
	int graduation ;
}; 

bool test ; // check the testnumber like 103¡A104 exist  

class MinHeap {
	
	FILE * file = NULL ;
	
	public : 
	    
	    vector<inform> store ; // store unprocessed inform
        vector<inform> minheap ; // store minheap tree
        
//---------------------------------------------------ReadInform start--------------------------------------------------//

	    
		void ReadInform( string inputname ){
			
			test = true ;
			int listnum = 1 ;
			int max = 200 ;
			int loc = 0 ;
			int i = 0 ;
			int tab = 0 ;
			int tempnum = 0 ;
			char * gar = new char[max] ;
			char * temp = new char[max] ;
			inform tempinform ;
			cout << endl ;
			
			inputname = "input" + inputname + ".txt" ;
			file = fopen(inputname.c_str(),"r") ;
		
			if ( file == NULL ) {
				cout << inputname << " dose not exist!" << endl ;
				test = false ;
			} // if
		 
			else {
			    
			    for ( int j = 0 ; j < 3 ; j++ ){ // read first 3 line ( unused )
			    	fscanf( file, "%[^\n]%*c", temp ) ;
			    	temp = new char[max] ;
				} // for
				
				
				while( fscanf( file,"%c",&gar[0] ) != EOF ){ 
				
					for ( i = 0 ; i < max ; i++ ){
						
						if ( fscanf( file,"%c",&temp[0] ) == EOF ) 
						    break ;
						    
						if ( temp[0] == '\t' )
					  	    tab++ ;
						
						if ( tab == 0 ){
							i = -1 ;
						} // if
						else if ( tab == 8 ){ // find graduation number
						    fscanf( file, "%d", &tempnum ) ;
						} // else if
						else if ( tab == 9 ){
							break ;
						} // else if
					  	    
					  	
					} // for
					
					fscanf( file, "%[^\n]%*c", gar ) ;

					
					tempinform.listnumber = listnum ;
					listnum++ ;
					tempinform.graduation = tempnum ;
					store.push_back( tempinform ) ;
					
					tab = 0 ;
					temp[0] = '\0' ;
					gar[0] = '\0' ;
					
				} // while
				
			} // else
			
			fclose(file) ;
			
		} // ReadInform()
		
//---------------------------------------------------ReadInform end--------------------------------------------------//
        void CreateMinHeap(){
		    
		    int parent = 0 ;
		    int child = 0 ;
		    int changelistnumber = 0 ;
		    int changegraduation = 0 ;
		    
		    for ( int i = 0 ; i < store.size() ; i++ ){
		    	
		    	minheap.push_back( store.at(i) ) ;
		    	
		    	if ( i == 0 ){
		    		;
				} // if
				else {
					
					child = i ;
					parent = ( i - 1 ) / 2 ;
					
					while ( parent >= 0 && minheap.at( child ).graduation < minheap.at( parent ).graduation ){
						
						swap( minheap.at(child), minheap.at(parent) ) ;
						child = parent ;
						parent = ( parent - 1 ) / 2 ;
						
					} // while
			
				} // else
				
			} // for
		
		
		} // CreateMinHeap()
		
		void PrintResult(){
			
			int leftmostbottom = FindLeftMostBottom() ;
			
	        cout << "<min heap>" << endl ;
			cout << "root : [" << minheap.at(0).listnumber << "] " << minheap.at(0).graduation << endl ;
			cout << "bottom : [" << minheap.at(minheap.size()-1).listnumber << "] " << minheap.at(minheap.size()-1).graduation << endl ;
			cout << "leftmost bottom : [" << minheap.at(leftmostbottom).listnumber << "] " << minheap.at(leftmostbottom).graduation << endl ;
			cout << endl ;
			
		} // PrintResult() 
		
		int FindLeftMostBottom(){
			
			int countlevel = 0 ;
			int parent = minheap.size() - 1 ;
			int leftbottom = 0 ;
			
			while ( parent > 0 ){
				parent = ( parent - 1 ) / 2 ;
				countlevel++ ;
			} // while
			
			while ( countlevel > 0 ){
				leftbottom = ( leftbottom * 2 ) + 1 ;
				countlevel-- ;
			} // while
			
			return leftbottom ;
		} // FindLeftMostBottom()
		
		void Clear(){
			store.clear() ;
			minheap.clear() ;
		} // Clear()

};

class MinMaxHeap {
	
	FILE * file = NULL ;
	
	public : 
	    
	    vector<inform> store ;
        vector<inform> minMaxheap ;
//---------------------------------------------------ReadInform start--------------------------------------------------//

	    
		void ReadInform( string inputname ){
			
			test = true ;
			int listnum = 1 ;
			int max = 200 ;
			int loc = 0 ;
			int i = 0 ;
			int tab = 0 ;
			int tempnum = 0 ;
			char * gar = new char[max] ;
			char * temp = new char[max] ;
			inform tempinform ;
			cout << endl ;
			
			inputname = "input" + inputname + ".txt" ;
			file = fopen(inputname.c_str(),"r") ;
		
			if ( file == NULL ) {
				cout << inputname << " dose not exist!" << endl ;
				test = false ;
			} // if
		 
			else {
			    
			    for ( int j = 0 ; j < 3 ; j++ ){
			    	fscanf( file, "%[^\n]%*c", temp ) ;
			    	temp = new char[max] ;
				} // for
				
				
				while( fscanf( file,"%c",&gar[0] ) != EOF ){ 
				
					for ( i = 0 ; i < max ; i++ ){
						
						if ( fscanf( file,"%c",&temp[0] ) == EOF ) 
						    break ;
						    
						if ( temp[0] == '\t' )
					  	    tab++ ;
						
						if ( tab == 0 ){
							i = -1 ;
						} // if
						else if ( tab == 8 ){
						    fscanf( file, "%d", &tempnum ) ;
						} // else if
						else if ( tab == 9 ){
	
							break ;
						} // else if
					  	    
					  	
					} // for
					
					fscanf( file, "%[^\n]%*c", gar ) ;

					
					tempinform.listnumber = listnum ;
					listnum++ ;
					tempinform.graduation = tempnum ;
					store.push_back( tempinform ) ;
					
					tab = 0 ;
					temp[0] = '\0' ;
					gar[0] = '\0' ;
					
				} // while
				
			} // else
			
			fclose(file) ;
			
		} // ReadInform()
		
		
//---------------------------------------------------ReadInform end--------------------------------------------------//
        void CreateMinMaxHeap(){
		    
		    inform temp ;
		    int parent = 0 ;
		    int child = 0 ;
		    int level = 0 ;
		    
		    for ( int i = 0 ; i < store.size() ; i++ ){
		    	
		    	minMaxheap.push_back( store.at(i) ) ;
		    	
		    	if ( i == 0 ){
		    		;
				} // if
				else {
					
					child = i ;
					parent = ( i - 1 ) / 2 ;
					level = FindLevel( i ) ; // find the child is locate at odd or even
					 
					if ( level == 1 ){ // if locate at odd, level is 1
						
						if ( minMaxheap.at( child ).graduation > minMaxheap.at( parent ).graduation ){
							
							while ( parent >= 1 && minMaxheap.at( child ).graduation > minMaxheap.at( parent ).graduation ){
								
								swap( minMaxheap.at(child), minMaxheap.at(parent) ) ;
								child = parent ;
								parent = ( parent - 1 ) / 2 ; 
								parent = ( parent - 1 ) / 2 ; // count grandfather
								
							} // while
							
						} // if
						
						else {
							
							parent = ( parent - 1 ) / 2 ; // max back to min
							
							while ( parent >= 0 && minMaxheap.at( child ).graduation < minMaxheap.at( parent ).graduation ){
								
								swap( minMaxheap.at(child), minMaxheap.at(parent) ) ;
								child = parent ;
								
								parent = ( parent - 1 ) / 2 ; 
								if ( (parent - 1) < 0 ) // out of the root
					    			break ;
								parent = ( parent - 1 ) / 2 ; // count grandfather
							} // while
							
						} // else
					
					} // if
					
					else if ( level == 2 ){ // if locate at even, level is 2
						
						if ( minMaxheap.at( child ).graduation < minMaxheap.at( parent ).graduation ){
							
							while ( parent >= 0 && minMaxheap.at( child ).graduation < minMaxheap.at( parent ).graduation ){
								
								swap( minMaxheap.at(child), minMaxheap.at(parent) ) ;
								child = parent ;
								
								parent = ( parent - 1 ) / 2 ; // count grandfather
								if ( (parent - 1) < 0 ) // out of the root
					    			break ;
								parent = ( parent - 1 ) / 2 ;
							} // while
							
						} // if
						
						else {
							
							parent = ( parent - 1 ) / 2 ; // min back to max
							
							while ( parent >= 1 && minMaxheap.at( child ).graduation > minMaxheap.at( parent ).graduation ){
								
								swap( minMaxheap.at(child), minMaxheap.at(parent) ) ;
								child = parent ;
								parent = ( parent - 1 ) / 2 ; // count grandfather
								parent = ( parent - 1 ) / 2 ;
								
							} // while
							
						} // else
						
					} // else if
			
				} // else
				
			} // for
		
		
		} // CreateMinMaxHeap()
		
		int FindLevel( int position ){
			 
			int child = position ;
			int parent = ( child - 1 ) / 2 ;
			int countlevel = 1 ;
			
			if ( child == 0 ){
				return 1 ;
			} // if
			else {
				
				while ( parent >= 0 ){
					
					countlevel++ ;
					if ( (parent - 1) < 0 )
					    break ;
					parent = ( parent - 1 ) / 2 ;
					
				} // while
				
				if ( countlevel % 2 == 0 ){
					return 2 ;
				} // if
				else {
					return 1 ;
				} // else
				
			} // else
			
			return 1 ;
			
		} // FindLevel()
		
		void PrintResult(){
			
			int leftmostbottom = FindLeftMostBottom() ;
			
	        cout << "<min-max heap>" << endl ;
			cout << "root : [" << minMaxheap.at(0).listnumber << "] " << minMaxheap.at(0).graduation << endl ;
			cout << "bottom : [" << minMaxheap.at(minMaxheap.size()-1).listnumber << "] " << minMaxheap.at(minMaxheap.size()-1).graduation << endl ;
			cout << "leftmost bottom : [" << minMaxheap.at(leftmostbottom).listnumber << "] " << minMaxheap.at(leftmostbottom).graduation << endl ;
			cout << endl ;
			
		} // PrintResult() 
		
		int FindLeftMostBottom(){
			
			int countlevel = 0 ;
			int parent = minMaxheap.size() - 1 ;
			int leftbottom = 0 ;
			
			while ( parent > 0 ){
				parent = ( parent - 1 ) / 2 ;
				countlevel++ ;
			} // while
			
			while ( countlevel > 0 ){
				leftbottom = ( leftbottom * 2 ) + 1 ;
				countlevel-- ;
			} // while
			
			return leftbottom ;
		} // FindLeftMostBottom()
		
		void Clear(){
			store.clear() ;
			minMaxheap.clear() ;
		} // Clear()

};


int main(int argc, char** argv) {
	
	int command = 0 ;
	string input ;
    MinHeap user ;
    MinMaxHeap user2 ;
    
	cout << "**** Heap Construction *****" << endl ;
	cout << "* 0. QUIT                  *" << endl ;
	cout << "* 1. Build a min heap      *" << endl ;
	cout << "* 2. Build a min-max heap  *" << endl ;
	cout << "****************************" << endl ;
	cout << "Input a command(0, 1, 2): "    ;
	cin >> command ;
	
	while ( command != 0 ){
		
		if ( command == 1 ){
			
			cout << '\n' << "Input a file number ([0] Quit): " ;
			cin >> input ;
			user.ReadInform( input ) ;
			
			while ( test == false ){
				cout << '\n' << "Input a file number ([0] Quit): " ;
				cin >> input ;
				user.ReadInform( input ) ;
			} // while
			
			user.CreateMinHeap() ;
			user.PrintResult() ;
			
		} // if
		
		else if ( command == 2 ){
			
			cout << '\n' << "Input a file number ([0] Quit): " ;
			cin >> input ;
			user2.ReadInform( input ) ;
			
			while ( test == false ){
				cout << '\n' << "Input a file number ([0] Quit): " ;
				cin >> input ;
				user2.ReadInform( input ) ;
			} // while
			
			user2.CreateMinMaxHeap() ;
			user2.PrintResult() ;
			
		} // else if
		
		else {
			cout << '\n' << "Command does not exist!" << endl << endl ;
		} // else
		
		cout << "**** Heap Construction *****" << endl ;
		cout << "* 0. QUIT                  *" << endl ;
		cout << "* 1. Build a min heap      *" << endl ;
		cout << "* 2. Build a min-max heap  *" << endl ;
		cout << "****************************" << endl ;
		cout << "Input a command(0, 1, 2): "    ;
		cin >> command ;
		user.Clear() ;
		user2.Clear() ;
		
	} // while
	
	return 0 ;
}























