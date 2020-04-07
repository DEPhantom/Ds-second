/* team04
   10727247 廖仁傑 
   10727220 陳正浩*/ 
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
	string schoolname ;
	string lineinform ;
	int listnumber ;
	int graduation ;
}; // 學校代碼	學校名稱	科系代碼	科系名稱	日間∕進修別	等級別	學生數	教師數	上學年度畢業生數	縣市名稱	體系別


struct schoolnameNode{
	inform Key[3] ; // put 2 inform on key, and if there are 3 inform on key, it will be split. 
	int keysize ; // count how many element in key.
	schoolnameNode * left ;
	schoolnameNode * right ;
	schoolnameNode * mid ;
	schoolnameNode * temp ;
	schoolnameNode * parent ;
};

struct graduationNode{
	int graduation ;
    graduationNode * left ;
    graduationNode * right ;
};

bool test ; // // check the testnumber like 203，204 exist  

class Mission23Tree {
	
	FILE * file = NULL ;
	
	public : 
	    
	    vector<inform> store ; // store unprocessed inform
	    schoolnameNode* root1 ; // store 2-3 tree
	    bool end ; // check is spilt end

//---------------------------------------------------ReadInform start--------------------------------------------------//

	    
		void ReadInform( string inputname ){
			
			test = true ;
			int listnum = 1 ;
			int max = 200 ;
			int loc = 0 ;
			int loc2 = 0 ;
			int loc3 = 0 ;
			int i = 0 ;
			int j = 0 ;
			int tab = 0 ;
			char num[max] ;
			char * gar = new char[max] ;
			char * temp = new char[max] ;
			char * name = new char[max] ;
			inform tempinform ;
			cout << endl ;
			inputname = "input" + inputname + ".txt" ;
			file = fopen(inputname.c_str(),"r") ;
		
			if ( file == NULL ) {
				cout << inputname << " dose not exist!" << endl ;
				test = false ;
			} // if
		 
			else {
			    
			    for ( int c = 0 ; c < 3 ; c++ ){
			    	fscanf( file, "%[^\n]%*c", temp ) ;
			    	temp = new char[max] ;
				} // for
				
				
				while( fscanf( file,"%c",&gar[0] ) != EOF ){ 
				
					for ( i = 0 ; i < max ; i++ ){
						
						if ( fscanf( file,"%c",&temp[i] ) == EOF ) 
						    break ;
						    
						if ( temp[i] == '\t' )
					  	    tab++ ;
						
						if ( tab == 0 ){
							i = -1 ;
						} // if
						else if ( tab == 1 ) { // schoolname
						    if ( temp[i] != '\t' ){
						    	name[loc2] = temp[i] ;
								name[loc2+1] = '\0' ;
								loc2++ ;
							} // if
						} // else if
						else if ( tab == 2 || tab == 6 || tab == 7 ){ //not used info
							
							while(1){
								fscanf( file,"%c",&gar[0] ) ;
								if ( gar[0] == '\t' ) {
									tab++ ;
									break ;
								} // if
						
							} // while
							
							while(tab == 7){
								fscanf( file,"%c",&gar[0] ) ;
								if ( gar[0] == '\t' ) {
									tab++ ;
									break ;
								} // if
						
							} // while
							
						} // else if
						else if ( tab == 8 ){ // graduation number
						    if ( temp[i] != '\t' ){
						    	num[loc] = temp[i] ;
						    	loc++ ;
							} // if
						} // else if
						else if ( tab == 9 ){
							temp[i] = '\n' ;
							temp[i+1] = '\0' ;
							break ;
						} // else if
					  	    
					  	
					} // for
					
					fscanf( file, "%[^\n]%*c", gar ) ;

					tempinform.lineinform = temp ;
					tempinform.schoolname = name ;
					tempinform.listnumber = listnum ;
					listnum++ ;
					tempinform.graduation = atoi(num) ;
					store.push_back( tempinform ) ;
					
					tab = 0 ;
					loc = 0 ;
					loc2 = 0 ;
					loc3 = 0 ;
					for( int j = 0 ; j < max ; j++ ){
						temp[j] = '\0' ;
						num[j] = '\0' ;
						name[j] = '\0' ;
						gar[j] = '\0' ;
					} // for
					
				} // while
				
			} // else
			
			fclose(file) ;
			
		} // ReadInform()
		
//---------------------------------------------------ReadInform end--------------------------------------------------//

//---------------------------------------------------Create mission1 binary tree start--------------------------------------------------//
		
		void initial(){
			
			root1 = new schoolnameNode ;
			root1->Key[0]= store.at(0) ;
			root1->keysize = 1 ;
			root1->left = NULL ;
			root1->mid = NULL ;
			root1->temp = NULL ;
			root1->right = NULL ;
			root1->parent = NULL ;
			
			for ( int runnum = 1 ; runnum < store.size() ; runnum++ ){ // insert each info
				
				end = false ;
				Create23Tree( root1, root1, store.at(runnum) ) ;
			
			} // for
			
		} // initial() 
		
		
		void Create23Tree( schoolnameNode* walk, schoolnameNode* parent, inform temp ){
			
			bool nextIsNull = false ;
			
			if ( walk == NULL ){
			   ;
			} // if
			else {

				parent = walk ;
				
				if ( walk->keysize == 1 && temp.schoolname.compare( walk->Key[0].schoolname ) == 0 ){ // have the same name in the tree
					;
				} // if
				else if ( walk->keysize == 2 &&  ( temp.schoolname.compare( walk->Key[0].schoolname ) == 0 || temp.schoolname.compare( walk->Key[1].schoolname ) == 0 ) ){ // have the same name in the tree
					;
				} // else if
				else if ( temp.schoolname.compare( walk->Key[0].schoolname ) < 0 ){
					
					Create23Tree( walk->left, parent, temp ) ;
					if ( walk->left == NULL )
					    nextIsNull = true ;
					
				} // else if
				else if ( walk->keysize == 1 && temp.schoolname.compare( walk->Key[0].schoolname ) > 0 ){
					
					Create23Tree( walk->right, parent, temp ) ;
					if ( walk->right == NULL )
					    nextIsNull = true ;
					
				} // else if
				else if ( walk->keysize == 2 && temp.schoolname.compare( walk->Key[0].schoolname ) > 0 &&  temp.schoolname.compare( walk->Key[1].schoolname ) < 0  ){
					
					Create23Tree( walk->mid, parent, temp ) ;
					if ( walk->mid == NULL )
					    nextIsNull = true ;
					
				} // else if
				else if ( walk->keysize == 2 && temp.schoolname.compare( walk->Key[1].schoolname ) > 0 ){
					
					Create23Tree( walk->right, parent, temp ) ;
					if ( walk->right == NULL )
					    nextIsNull = true ;
					
				} // else if
				
				
			} // else
			
			if ( nextIsNull && !end ){
			    
			    ArrangeKey( walk, temp ) ;
			    
			    if ( walk->keysize == 3 ){
			    	
			    	Split( walk, walk->parent ) ;
                    
				} // if
				
				end = true ;
			
			} // if
			
			
		} // CreateSchoolnameTree()
		
		void ArrangeKey( schoolnameNode* &cur, inform temp ){ // arrange the schoolname the smallest is in the Key[0], and set keysize
		
			if ( cur->keysize == 1 ){
				
				if ( temp.schoolname.compare( cur->Key[0].schoolname ) == 0 ){
					;
				} // if
				else if ( temp.schoolname.compare( cur->Key[0].schoolname ) < 0 ){ 
				    
				    cur->Key[1] = cur->Key[0] ;
					cur->Key[0] = temp ;
					cur->keysize = 2 ;
					
				} // else if
				else if ( temp.schoolname.compare( cur->Key[0].schoolname ) > 0 ){ 
				
				    cur->Key[1] = temp ;
				    cur->keysize = 2 ;
				    
				} // else if
				
			} // if
			else if ( cur->keysize == 2 ){
				
				if ( temp.schoolname.compare( cur->Key[0].schoolname ) == 0 || temp.schoolname.compare( cur->Key[1].schoolname ) == 0 ){
					;
				} // if
				else if ( temp.schoolname.compare( cur->Key[0].schoolname ) < 0 ){ 
				    
				    cur->Key[2] = cur->Key[1] ;
					cur->Key[1] = cur->Key[0] ;
					cur->Key[0] = temp ;
					cur->keysize = 3 ;
					
				} // else if
				else if ( temp.schoolname.compare( cur->Key[0].schoolname ) > 0 && temp.schoolname.compare( cur->Key[1].schoolname ) < 0 ){ 
				
				    cur->Key[2] = cur->Key[1] ;
					cur->Key[1] = temp ;
					cur->keysize = 3 ;
				    
				} // else if
				else if ( temp.schoolname.compare( cur->Key[1].schoolname ) > 0 ){ 
				
				    cur->Key[2] = temp ;
					cur->keysize = 3 ;
					
				} // else if
				
			} // else if
			
		} // ArrangeKey()
		
		void Split( schoolnameNode* kid, schoolnameNode* father ){

			schoolnameNode * child1 = new schoolnameNode ; // make first child
			child1->Key[0]= kid->Key[0] ;
			child1->keysize = 1 ;
			child1->left = kid->left ;
			child1->right = kid->mid ;
			child1->mid = NULL ;
			child1->temp = NULL ;
			
			if ( kid->left != NULL && kid->mid != NULL ){
				child1->left->parent = child1 ;
				child1->right->parent = child1 ;
			} // if
			
			kid->Key[0]= kid->Key[2] ; // set second child
			kid->keysize = 1 ;
			kid->left = kid->right ;
			kid->right = kid->temp ;
			kid->mid = NULL ;
			kid->temp = NULL ;

			if ( father == NULL ){
				
				schoolnameNode * dad = new schoolnameNode ;
				dad->Key[0]= kid->Key[1] ;
				dad->keysize = 1 ;
				dad->left = child1 ;
				dad->right = kid ;
				dad->mid = NULL ;
				dad->temp = NULL ;
				dad->parent = NULL ;
				
				child1->parent = dad ;
				kid->parent = dad ;
				father = dad ;
				root1 = dad ;
           		
			} // if
			else {
				
				if ( father->keysize == 1 ){
					
				    child1->parent = father ;
				    ArrangeKey( father, kid->Key[1] ) ;
				    
					if ( father->left == kid ){
						
						father->mid = kid ;
						father->left = child1 ;
				        
					} // if
					else if ( father->right == kid ){
						
						father->mid = child1 ;
				        father->right = kid ;
						
					} // else if
					
				} // if
				else if ( father->keysize == 2 ){
					
					child1->parent = father ;
				    ArrangeKey( father, kid->Key[1] ) ;
					
					if ( father->left == kid ){
						
						father->temp = father->right ;
						father->right = father->mid ;
				        father->left = child1 ;
				        father->mid = kid ;
				        
					} // if
					else if ( father->mid == kid ){
						
						father->temp = father->right ;
						father->right = kid ;
				        father->mid = child1 ;
				        
					} // else if
					else if ( father->right == kid ){
						
				        father->right = child1 ;
				        father->temp = kid ;
				        
					} // else if
			
					Split( father, father->parent ) ;
					
				} // else if 
			
			} // else
			
			
			
			while ( father->parent != NULL ) {
				
				father = father->parent ;
				
			} // if
			
			root1 = father ;
			
		} // Split()
		
		
		int FindNameTreeHeight( schoolnameNode* walk ){
			
			if ( walk == NULL )
			    return 0 ;
			
			return FindMax( FindNameTreeHeight( walk->left ), FindNameTreeHeight( walk->mid ), FindNameTreeHeight( walk->right ) ) + 1 ;
			
		} // FindNameTreeHeight()
		
		int FindMax( int anum, int bnum, int cnum ){
			
			int max = anum ;
			
			if ( max < bnum )
			    max = bnum ;
			if ( max < cnum )
			    max = cnum ;
			    
			return max ;
			
		} // FindMax()
		
		int CountNodes( schoolnameNode* walk ){
			
			if ( walk == NULL ){
				return 0 ;
			} // if
			else {
				return CountNodes( walk->left) + CountNodes( walk->mid ) + CountNodes( walk->right ) + 1 ;
			} // else
			
			return 0 ;
			
		} // CountNodes()
		
		void print(){
			
			int num = 1 ;
			
			cout << "\n" << "Tree height = " << FindNameTreeHeight(root1) << endl ;
			cout << "Number of nodes = " << CountNodes(root1) << endl ;
			
			if ( root1->keysize == 1 ){
				
				for( int i = 0 ; i < store.size() ; i++ ){
					
					if ( root1->Key[0].schoolname.compare( store.at(i).schoolname ) == 0 ){
						cout << num << ": [" << store.at(i).listnumber << "]" << store.at(i).lineinform ;
						num++ ;
					} // if
					
				} // for
				
			} // if
			else if ( root1->keysize == 2 ){
				
				int first = 0, sec = 1 ;
				
				if ( root1->Key[0].listnumber > root1->Key[1].listnumber ){
					first = 1 ;
					sec = 0 ;
				} // if
				    

				for( int j = 0 ; j < store.size() ; j++ ){
					
					if ( root1->Key[first].schoolname.compare( store.at(j).schoolname ) == 0 ){
						cout << num << ": [" << store.at(j).listnumber << "]" << store.at(j).lineinform ;
						num++ ;
					} // if
					
				} // for
				
				for( int z = 0 ; z < store.size() ; z++ ){
					
					if ( root1->Key[sec].schoolname.compare( store.at(z).schoolname ) == 0 ){
						cout << num << ": [" << store.at(z).listnumber << "]" << store.at(z).lineinform ;
						num++ ;
					} // if
					
				} // for
				
				
			} // else if
			
		} // print()
		
		void clear(){
			
			store.clear() ;
			end = false ;
			test = true ;
			file = NULL ;
			root1 = NULL ;
			delete root1 ;
			
		} // clear()
};

class AVLTree {
	
	FILE * file = NULL ;
	
	public : 
	    
	    vector<inform> store ;
	    graduationNode* root ;

//---------------------------------------------------ReadInform start--------------------------------------------------//

	    
		void ReadInform( string inputname ){
			
			test = true ;
			int listnum = 1 ;
			int max = 200 ;
			int loc = 0 ;
			int loc2 = 0 ;
			int loc3 = 0 ;
			int i = 0 ;
			int j = 0 ;
			int tab = 0 ;
			char num[max] ;
			char * gar = new char[max] ;
			char * temp = new char[max] ;
			char * name = new char[max] ;
			inform tempinform ;
			cout << endl ;
			inputname = "input" + inputname + ".txt" ;
			file = fopen(inputname.c_str(),"r") ;
		
			if ( file == NULL ) {
				cout << inputname << " dose not exist!" << endl ;
				test = false ;
			} // if
		 
			else {
			    
			    for ( int c = 0 ; c < 3 ; c++ ){
			    	fscanf( file, "%[^\n]%*c", temp ) ;
			    	temp = new char[max] ;
				} // for
				
				
				while( fscanf( file,"%c",&gar[0] ) != EOF ){ 
				
					for ( i = 0 ; i < max ; i++ ){
						
						if ( fscanf( file,"%c",&temp[i] ) == EOF ) 
						    break ;
						    
						if ( temp[i] == '\t' )
					  	    tab++ ;
						
						if ( tab == 0 ){
							i = -1 ;
						} // if
						else if ( tab == 1 ) {
						    if ( temp[i] != '\t' ){
						    	name[loc2] = temp[i] ;
								name[loc2+1] = '\0' ;
								loc2++ ;
							} // if
						} // else if
						else if ( tab == 2 || tab == 6 || tab == 7 ){
							
							while(1){
								fscanf( file,"%c",&gar[0] ) ;
								if ( gar[0] == '\t' ) {
									tab++ ;
									break ;
								} // if
						
							} // while
							
							while(tab == 7){
								fscanf( file,"%c",&gar[0] ) ;
								if ( gar[0] == '\t' ) {
									tab++ ;
									break ;
								} // if
						
							} // while
							
						} // else if
						else if ( tab == 8 ){
						    if ( temp[i] != '\t' ){
						    	num[loc] = temp[i] ;
						    	loc++ ;
							} // if
						} // else if
						else if ( tab == 9 ){
							temp[i] = '\n' ;
							temp[i+1] = '\0' ;
							break ;
						} // else if
					  	    
					  	
					} // for
					
					fscanf( file, "%[^\n]%*c", gar ) ;

					tempinform.lineinform = temp ;
					tempinform.schoolname = name ;
					tempinform.listnumber = listnum ;
					listnum++ ;
					tempinform.graduation = atoi(num) ;
					store.push_back( tempinform ) ;
					
					tab = 0 ;
					loc = 0 ;
					loc2 = 0 ;
					loc3 = 0 ;
					for( int j = 0 ; j < max ; j++ ){
						temp[j] = '\0' ;
						num[j] = '\0' ;
						name[j] = '\0' ;
						gar[j] = '\0' ;
					} // for
					
				} // while
				
			} // else
			
			fclose(file) ;
			
		} // ReadInform()
		
//---------------------------------------------------ReadInform end--------------------------------------------------//

//---------------------------------------------------Create mission1 binary tree start--------------------------------------------------//
		
		void initial(){
			
			root = NULL ;
			for ( int runnum = 0 ; runnum < store.size() ; runnum++ ){
				
				CreateAVLTree( root, store.at(runnum).graduation ) ;
				root = CheckBalanced( root ) ;
				
			} // for
			
		} // initial() 
		
		void CreateAVLTree( graduationNode * &walk, int gnum ){
			
			if ( walk == NULL ){
				
				walk = new graduationNode ;
				walk->graduation = gnum ;
				walk->left = NULL ;
				walk->right = NULL ;
				
			} // if
			else if ( walk != NULL ){
				
				if ( gnum < walk->graduation ){
					CreateAVLTree( walk->left, gnum ) ;
				} // if
				else if ( gnum > walk->graduation ){
					CreateAVLTree( walk->right, gnum ) ;
				} // else if
				
			} // else if
			
		} // CreateAVLTree()
		
		graduationNode * CheckBalanced( graduationNode * walk ){
			
			if ( walk->left != NULL )
				walk->left = CheckBalanced( walk->left ) ;
			if ( walk->right != NULL )
				walk->right = CheckBalanced( walk->right ) ;
			
			int Lheight = FindAVLTreeHeight( walk->left ) ;
			int Rheight = FindAVLTreeHeight( walk->right ) ;
			int LLheight = 0 ; 
			int LRheight = 0 ;
			int RLheight = 0 ;
			int RRheight = 0 ;
			
			if ( walk->left != NULL ){
				LLheight = FindAVLTreeHeight( walk->left->left ) ;
				LRheight = FindAVLTreeHeight( walk->left->right ) ;
			} // if
			
			if ( walk->right != NULL ){
				RLheight = FindAVLTreeHeight( walk->right->left ) ;
				RRheight = FindAVLTreeHeight( walk->right->right ) ;
			} // if
			
			
			if ( Lheight - Rheight == 2 ){
				
				if ( LLheight - LRheight >= 0 )
				    walk = LLRotation( walk ) ;
				else {
					
					walk->left = RRRotation( walk->left ) ;
					Lheight = FindAVLTreeHeight( walk->left ) ;
					Rheight = FindAVLTreeHeight( walk->right ) ;
					
					if ( Lheight - Rheight == 2 )
						walk = LLRotation( walk ) ;
						
				} // else
				    
			} // if
			else if ( Lheight - Rheight == -2 ){
				
				if ( RLheight - RRheight <= 0  )
				    walk = RRRotation( walk ) ;
				else {
					
					walk->right = LLRotation( walk->right ) ;
					Lheight = FindAVLTreeHeight( walk->left ) ;
					Rheight = FindAVLTreeHeight( walk->right ) ;
					
					if ( Lheight - Rheight == -2 ){
						
						walk = RRRotation( walk ) ;
					} // if
						
					
					
				} // else
				    
			} // else if 
			
			
			return walk ;
			
		} // CheckBalanced()
		
		int FindAVLTreeHeight( graduationNode* walk ){
			
			if ( walk == NULL )
			    return 0 ;
			
			return FindMax( FindAVLTreeHeight( walk->left ), FindAVLTreeHeight( walk->right ) ) + 1 ;
			
		} // FindAVLTreeHeight()
		
		int FindMax( int anum, int bnum ){
			
			if ( anum < bnum )
			    return bnum ;
			else
			    return anum ;
			    
			return 0 ;
			
		} // FindMax()
		
		graduationNode* LLRotation( graduationNode* walk ){
			
			graduationNode* temp = walk->left ;
			walk->left = temp->right ;
			temp->right = walk ;
			
			return  temp ;
		 	
		} // LLRotation()
		
		graduationNode* RRRotation( graduationNode* walk ){
			
			graduationNode* temp = walk->right ;
			walk->right = temp->left ;
			temp->left = walk ;
			
			return temp ;
		 	
		} // RRRotation()
		
		int CountNodes( graduationNode* walk ){
			
			if ( walk == NULL ){
				return 0 ;
			} // if
			else {
				return CountNodes( walk->left) + CountNodes( walk->right ) + 1 ;
			} // else
			
			return 0 ;
			
		} // CountNodes()
		
		void print(){
			
			int num = 1 ;
			
			cout << "\n" << "Tree height = " << FindAVLTreeHeight(root) << endl ;
			cout << "Number of nodes = " << CountNodes(root) << endl ;
			
			for( int i = 0 ; i < store.size() ; i++ ){
					
			    if ( root->graduation == store.at(i).graduation ){
			    	cout << num << ": [" << store.at(i).listnumber << "]" << store.at(i).lineinform ;
					num++ ;
				} // if
				
		    } // for
			
		} // print()

		void clear(){
			
			store.clear() ;
			test = true ;
			file = NULL ;
			root = NULL ;
			delete root ;
			
		} // clear()
};


int main(int argc, char** argv) {
	
    int command = 0 ;
    string input ;
	cout << "*** Search Tree Utilities **" << endl ;
    cout << "* 0. QUIT                  *" << endl ;
    cout << "* 1. Build 2-3 tree        *" << endl ;
    cout << "* 2. Build AVL tree        *" << endl ;
   	cout << "****************************" << endl ;
   	cout << "Input a command(0, 1, 2): " ;
    cin >> command ;
    cout << endl ;
    
    while ( command != 0 ){
    	
    	if ( command == 1 ){
    		
    		Mission23Tree user ;
    		cout << "Input a file number ([0] Quit): " ;
    		cin >> input ;
    		user.ReadInform( input ) ;
    		if ( test ){
    			
    			user.initial() ;
    			user.print() ;
    			user.clear() ;
    			
			} // if
    		
		} // if
		else if ( command == 2 ){
			
    		AVLTree user2 ;
    		cout << "Input a file number ([0] Quit): " ;
    		cin >> input ;
    		user2.ReadInform( input ) ;
    		if ( test ){
    			
    			user2.initial() ;
    			user2.print() ;
    			user2.clear() ;
    			
			} // if
    		
		} // else if
		else {
			cout << endl << "Command does not exist!" ;
		} // else
		
		
		cout << endl << endl ;
		cout << "*** Search Tree Utilities **" << endl ;
    	cout << "* 0. QUIT                  *" << endl ;
    	cout << "* 1. Build 2-3 tree        *" << endl ;
    	cout << "* 2. Build AVL tree        *" << endl ;
   		cout << "****************************" << endl ;
   		cout << "Input a command(0, 1, 2): " ;
    	cin >> command ;
    	cout << endl ;
    } // while
	
	return 0 ;
}
















