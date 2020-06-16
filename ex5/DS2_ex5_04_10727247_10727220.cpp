// 10727220 陳正浩 10727247 廖仁傑
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<fstream>  
#include<vector>
#include<time.h>
#pragma GCC optimize(2)




using namespace std ;

static fstream filein;
static fstream fileout;

static string fileName;

static double time1 = 0 ;
static double time2 = 0 ;


struct data { 	// link list
    char getid[10];
    float weight;
    int loc;
    data * next; 
    

};

struct DFSdata{
	vector<string> cc ;
};

struct bindata { 	// get data
    char putid[10];
    char getid[10];
    float weight;    

};


struct adjdata { 	//every adj data
    data * head;
    char id[10];
    int connector;
    vector<string> path;
    bool havecame;
    
};

struct mapdata {
	char id[10];
    float weight;
    int gate;
};

class Adjlist{
	
   
    protected:
	    bindata bintemp;
        data *temp;
        data *tail;
        int node;
	    vector<adjdata> adjlist;// 動態陣列
        float effect; 
	
	public:
	    Adjlist() {					//constructor
		}

		Adjlist( float ask ) {					//constructor
          temp = NULL;
          tail = NULL;
          node = 0;
          effect = ask;
		}

       		
		void print() {	
          cout << "<<< There are " << adjlist.size() <<" IDs in total. >>>\n";
          cout << "<<< There are " << node <<" nodes in total. >>>\n";	
		} // print()

        void printall() {
	      ;

        } // printall()

        void addadj() {
	      adjdata initial;
          initial.head = NULL;
          initial.connector = 0;
          initial.havecame = false;
          strcpy( initial.id, "" );
	      if( adjlist.empty() ) { // 全空 
	        adjlist.push_back( initial );
            strcpy( adjlist[0].id, bintemp.getid );
            adjlist.push_back( initial );
            adjlist[0].head = new data;
            temp = adjlist[0].head;
            temp->next = NULL;
            strcpy( temp->getid, bintemp.putid );
            temp->weight = bintemp.weight;
            temp->loc = 0; // 排完序再給 
            strcpy( adjlist[1].id, bintemp.putid ); 
            adjlist[1].head = new data;
            temp = adjlist[1].head;
            temp->next = NULL;
            strcpy( temp->getid, bintemp.getid );
            temp->weight = bintemp.weight;
            temp->loc = 0; // 排完序再給 
           
          } // if()
          else { // 有東西 
	        bool nodata = true;
            int i = 0;
            while( i < adjlist.size() && nodata ) {
	          if( strcmp( adjlist[i].id, bintemp.getid ) == 0 ) { 
	            nodata = false; 
                temp = adjlist[i].head->next;
                tail = adjlist[i].head;
                while( temp != NULL ) {
	              tail = tail->next;
                  temp = temp->next;
	            } // while()

                temp = new data;
                temp->next = NULL;
                strcpy( temp->getid, bintemp.putid );
                temp->weight = bintemp.weight;
                temp->loc = 0; // 排完序再給 
                tail->next = temp;

              } // if()
              i++;
            } // while 

            if ( nodata == true ) {
	          adjlist.push_back( initial );
              strcpy( adjlist[adjlist.size()-1].id, bintemp.getid );
              adjlist[adjlist.size()-1].head = new data;
              adjlist[adjlist.size()-1].head->next = NULL;
              strcpy( adjlist[adjlist.size()-1].head->getid, bintemp.putid );
              adjlist[adjlist.size()-1].head->weight = bintemp.weight;
              adjlist[adjlist.size()-1].head->loc = 0; // 排完序再給  
	        } // if()             

            i = 0;
            nodata = true; 

            while( i < adjlist.size() && nodata ) {
	          if( strcmp( adjlist[i].id, bintemp.putid ) == 0 ) { // 已經有學號了  
	            nodata = false; 
                if( adjlist[i].head == NULL ) { //尚未有聯絡人 
	              adjlist[i].head = new data;
                  adjlist[i].head->next = NULL;
                  strcpy( adjlist[i].head->getid, bintemp.getid );
                  adjlist[i].head->weight = bintemp.weight;
                  adjlist[i].head->loc = 0; // 排完序再給 
                } // if()
                else { // find the last and put
                  temp = adjlist[i].head->next;
                  tail = adjlist[i].head;
                  while( temp != NULL ) {
	                tail = tail->next;
                    temp = temp->next;
	              } // while()

                  temp = new data;
                  temp->next = NULL;
                  strcpy( temp->getid, bintemp.getid );
                  temp->weight = bintemp.weight;
                  temp->loc = 0; // 排完序再給 
                  tail->next = temp;

	            } // else

              } // if()
              i++;

            } // while 

            if ( nodata == true ) { // 沒學號 
	          adjlist.push_back( initial );
              strcpy( adjlist[adjlist.size()-1].id, bintemp.putid );
              adjlist[adjlist.size()-1].head = new data;
              adjlist[adjlist.size()-1].head->next = NULL;
              strcpy( adjlist[adjlist.size()-1].head->getid, bintemp.getid );
              adjlist[adjlist.size()-1].head->weight = bintemp.weight;
              adjlist[adjlist.size()-1].head->loc = 0; // 排完序再給  

	        } // if()

	      } // else

	    } // addadj()

        void readinput() {		// read the input bin
     
            int i = 0;
            filein.seekg( 0, filein.end );
		    int stNo = filein.tellg()/sizeof( bintemp );
		    filein.seekg( 0, filein.beg) ;
			for( i = 0 ; i < stNo ; i++  ) {	            
	            filein.read( bintemp.putid, sizeof( bintemp.getid ) ); 
                filein.read( bintemp.getid, sizeof( bintemp.getid ) ); 
                filein.read( (char *) &bintemp.weight, sizeof( float ) );
                if( bintemp.weight <= effect ) {
                  addadj();
                  node++;
                  node++;
                } // if()

			} // for()
          

		} // readinput()
        
        void sortput() {
	      adjdata swap;
	      int i = 0;
          int j = 0;
          int max = 0;
	      while( i < adjlist.size() ) {
	        while( j < adjlist.size() ) {
	          if( strcmp( adjlist[j].id, adjlist[max].id ) < 0 ) {
	            max = j;
	          } // if()
              j++;

	        } // while()

            strcpy( swap.id, adjlist[max].id );            
            swap.head = adjlist[max].head;
            strcpy( adjlist[max].id, adjlist[i].id );            
            adjlist[max].head = adjlist[i].head;
            strcpy( adjlist[i].id, swap.id );            
            adjlist[i].head = swap.head;
            j = i+1;
            i++;
            max = i;
            
	      } // while

        } // sortput()

        void sortget() {
	      data *swap = NULL;
          data *stail = NULL;
          data *walk = NULL;
          data tempdata;
          int i = 0;
	      while( i < adjlist.size() ) {
	
	        walk = adjlist[i].head;
            stail = walk;
            swap = walk;
	        while( walk != NULL ) {
	
              while( stail->next != NULL ) {
	            if( strcmp( stail->next->getid, swap->getid ) < 0 ) { 
                  swap = stail->next;
                } // if()

                stail = stail->next;

	          } // while()

              strcpy( tempdata.getid, swap->getid );
              tempdata.loc = swap->loc;
              tempdata.weight = swap->weight;
              strcpy( swap->getid, walk->getid );
              swap->loc = walk->loc;
              swap->weight = walk->weight;
              strcpy( walk->getid, tempdata.getid );
              walk->loc = tempdata.loc;
              walk->weight = tempdata.weight;

              walk = walk->next;
              stail = walk;
              swap = walk;

	        } // while()

            i++;
             
	      } // while
	      
	    } // sortget()

        void write() {
        	
	      data *walk = NULL;
	      fileName = fileName.substr( 5, 3 );
          stringstream ss;
          ss << effect;
          string threshold = ss.str();
	      fileName = "pairs" + fileName + "_" + threshold + ".adj" ;
	      filein.open( fileName.c_str() ,ios::out ) ;
          int i = 0;
          int j = 0;
          int count = 0;
          int pointnum = 0;
          
          filein << "<<< There are " << adjlist.size() <<" IDs in total. >>>\n";
          while( i < adjlist.size() ) {
          	
            if ( i < 9 ){
          		filein << "[  " << i+1 << "]" << " ";
			} // if
			else if ( i >= 9 && i < 99 ){
				filein << "[ " << i+1 << "]" << " ";
			} // else if
			else {
				filein << "[" << i+1 << "]" << " ";
			} // else
	            
            filein << adjlist[i].id << ": \n\t";
            walk = adjlist[i].head;
            while ( walk != NULL ) {
              
              if ( j < 9 ){
              	filein << "( "<< j+1 << ") ";
			  } // if
			  else {
			  	if ( j != 0 && j %10 == 0 ){
			  	  	filein << '\t' ;
				} // if
			  	filein << "("<< j+1 << ") ";
			  } // else
              
              filein << walk->getid << ",  ";
              pointnum = walk->weight * 10 * 10 ;
              if ( pointnum % 10 == 0 && pointnum >= 10 ){
              	filein << " " ;
			  } // if
			  
              filein << walk->weight ;
              if ( walk->next != NULL && (j+1)%10 != 0){
              	filein << "\t";
			  } // if
              
              
              if( count < 9)
                count++;
              else {
	            filein << "\n";
	            count = 0;
	          } // else
                
              j++;
              walk = walk->next;

            } // while()

            filein << "\n";
	        i++;
            j = 0;
            count = 0;

          } // while()

          filein << "<<< There are " << node <<" nodes in total. >>>\n";
          filein.close();

	    } // write()

        void delet() {
	       adjlist.clear();
	    } // delet()

}; // Adjlist

class Dfs : public Adjlist {
	
    private:
	    vector<DFSdata> stack;
        int path; 

	public:
		
		Dfs() {					//constructor 
          tail = NULL;
          node = 0;
          temp = NULL; 
          effect = 1;    
		}

        void readinput() {
	      int i = 0;
          char info = '\0'; 
	      while( !filein.eof( ) ) {	
            if ( info == ']' ){
              filein >> bintemp.putid;
              for( int i = 9; i > -1; i-- ) {
	            if( bintemp.putid[i] == ':' ) 
                  bintemp.putid[i] = '\0';
	          } // for()  

            } // if
            else if ( info == ')' ) {
              filein >> bintemp.getid;
              for( int i = 9; i > -1; i-- ) {
	            if( bintemp.getid[i] == ',' ) 
                  bintemp.getid[i] = '\0';
	          } // for()                
              filein >> bintemp.weight;
              if( bintemp.weight <= effect && !filein.eof( ) ) {
                addadj();
                node++;
                node++;
              } // if()

	        } // else if()
	        
            filein >> info;

          } // while()


	    } // readinput()

        void mark() {
	      int i = 0;
          int j = 0;
	      while( i < adjlist.size() ) {
	        temp = adjlist[i].head;
	        while( temp != NULL ) {
	          while( j < adjlist.size() ) {
	            if( strcmp( temp->getid, adjlist[j].id ) == 0 )
	              temp->loc = j;
                j++;

              } // while()
              j = 0;
              temp = temp->next;

	        } // while()
            i++; 

	      } // while()

	    } // mark()
	    
	    void countConnectComponent(){
	    	
	    	DFSdata head  ;
	    	for ( int i = 0 ; i < adjlist.size() ; i++ ){
	    		
	    		if ( adjlist[i].havecame == false ){
	    			stack.push_back( head ) ;
	    			dfs(i) ;
				} // if
				
			} // for
	    	
 		} // countConnectComponent()
	    
	    void dfs( int pos ){
	    	
	    	data * temp ;
	    	
	    	if ( adjlist[pos].havecame ){
	    		;
			} // if
			else {
				
				temp = adjlist[pos].head ;
				if ( !adjlist[pos].havecame){
					stack[stack.size()-1].cc.push_back( adjlist[pos].id ) ;
 				} // if
 				
				adjlist[pos].havecame = true ;
				while ( temp != NULL ){
					
					dfs( temp->loc ) ;
					temp = temp->next ;
					
				} // while
				
			} // else
	    	
		} // dfs()
		
		void sortconnectComponent(){
			
			for ( int i = 0 ; i < stack.size() ; i++ ){
				
				for ( int j = 0 ; j < stack[i].cc.size() ; j++ ){
					
					for ( int z = j+1 ; z < stack[i].cc.size() ; z++ ){
						
						if ( strcmp( stack[i].cc[j].c_str(), stack[i].cc[z].c_str() ) > 0 )
						    swap( stack[i].cc[j], stack[i].cc[z] ) ;
						
					} // for
					
				} // for
				
			} // for
			
		} // connectComponent()


        void sortConnectNum(){
       	
       	    for ( int i = 0 ; i < stack.size() ; i++ ){
       	    	
       	    	for ( int j = i+1 ; j < stack.size() ; j++ ){
       	    		
       	    		if ( stack[i].cc.size() < stack[j].cc.size() ){
       	    			swap( stack[i], stack[j] ) ;
					} // if       	    		    
       	    		else if ( stack[i].cc.size() == stack[j].cc.size() ){
       	    			
       	    			if ( strcmp( stack[i].cc[0].c_str(), stack[j].cc[0].c_str() ) < 0 )
       	    			    swap( stack[i], stack[j] ) ;
       	    			
					} // else if
					
				} // for
       	    	
			} // for
			
	   } // arrange

        void writeDFS() {
        	
	      int run = 0 ;
          run = fileName.length()-4;
	      fileName = fileName.substr( 0, run );
	      fileName = fileName + ".cc" ;
	      filein.open( fileName.c_str() ,ios::out ) ;
          int i = 0;
          int j = 0;
          int count = 0;
          int pointnum = 0;
          
          filein << "<<< There are " << stack.size() <<" connected components in total. >>>";	
          while( i < stack.size() ) {
          	
          	filein << "\n";
            if ( i < 9 ){
          		filein << "{ " << i+1 << "} Connected Component: size = " <<  stack[i].cc.size() << "\n" ;
			} // if
			else if ( i >= 9 && i < 99 ){
				filein << "{" << i+1 << "} Connected Component: size = " <<  stack[i].cc.size() << "\n" ;
			} // else if
	            
            
            while ( j < stack.at(i).cc.size() ) {
              
              if ( count == 8 ){
			  	filein << "\n" ;
			  } // if
			  
              if ( j < 9 ){
              	filein << " \t(  "<< j+1 << ") ";
			  } // if
			  else if ( j >= 9 && j < 99 ){
			  	filein << " \t( "<< j+1 << ") ";
			  } // else if
			  else {
			  	filein << " \t("<< j+1 << ") ";
			  } // else
			
              filein << stack.at(i).cc.at(j) ;

              if( count < 8)
                count++;
              else {
	            count = 1;
	          } // else
                
              j++;
              
            } // while()

	        i++;
            j = 0;
            count = 0;

          } // while()

          filein.close();

	    } // writeDFS()
	    
	    
		
		void printall() {	
		
          cout << "<<< There are " << stack.size() <<" connected components in total. >>>\n";	
          
          for ( int i = 0 ; i < stack.size() ; i++ ){
          	cout << "{ " << i+1 << "} Connected Component: size = " <<  stack[i].cc.size() << "\n" ;
		  } // for
		  
		} // print()

}; // class

class Dijk : public Adjlist {
	
    private:
        vector<mapdata> distance;
        data *temp;
        int origin;

	public:
		
		Dijk() {					//constructor 
          temp = NULL;    
          effect = 1;
		}

        void readinput() {
	      int i = 0;
          char info = '\0'; 
	      while( !filein.eof( ) ) {	
            if ( info == ']' ){
              filein >> bintemp.putid;
              for( int i = 9; i > -1; i-- ) {
	            if( bintemp.putid[i] == ':' ) 
                  bintemp.putid[i] = '\0';
	          } // for()  

            } // if
            else if ( info == ')' ) {
              filein >> bintemp.getid;
              for( int i = 9; i > -1; i-- ) {
	            if( bintemp.getid[i] == ',' ) 
                  bintemp.getid[i] = '\0';
	          } // for()                
              filein >> bintemp.weight;
              if( bintemp.weight <= effect && !filein.eof( ) ) {
                addadj();
                node++;
                node++;
              } // if()

	        } // else if()
	        
            filein >> info;

          } // while()


	    } // readinput()

        void printlist() {
	      int i = 0;
          cout << endl;
          while( i < adjlist.size() ) {
	        cout << adjlist[i].id << " ";
            if( (i+1)%8 == 0 )
              cout << endl;
            i++;
	      } // while()
      
          cout << endl;

	    } // printlist()

        void mark() {
	      int i = 0;
          int j = 0;
	      while( i < adjlist.size() ) {
	        adjlist[i].connector = -1;
	        temp = adjlist[i].head;
	        while( temp != NULL ) {
	          while( j < adjlist.size() ) {
	            if( strcmp( temp->getid, adjlist[j].id ) == 0 )
	              temp->loc = j;
                j++;

              } // while()
              j = 0;
              temp = temp->next;

	        } // while()
            i++; 

	      } // while()

	    } // mark()

        void runthemap( int loc, float shortest ) {
	      data * temp2 = adjlist[loc].head;
          mapdata tempmap;
          int maploc;
          float nowdis;
          while( temp2 != NULL ) {  
	        if ( adjlist[temp2->loc].connector == -1 ) { // 沒被記錄過
              strcpy( tempmap.id, temp2->getid );
              tempmap.weight = temp2->weight+shortest;
              tempmap.gate = temp2->loc;
              distance.push_back( tempmap );
              adjlist[temp2->loc].connector = distance.size()-1;
            } // if() 
            
            nowdis = shortest + temp2->weight;
            maploc = adjlist[temp2->loc].connector;
            if ( distance[maploc].weight > nowdis ) {
	          distance[maploc].weight = nowdis;
	        } // if()

            temp2 = temp2->next;
	      } // while()
 
	    } // runthemap()

        void findnext( int &loc, float &shortest ) {
	      int i = 0;
          float min = 99999;
          while( i < distance.size() ) {
	        if( min > distance[i].weight && adjlist[distance[i].gate].havecame == false ) {
	          min = distance[i].weight;
              loc = distance[i].gate;
	        } // if()

            i++; 
	      } // while()

          if( min == 99999 ) {
	        loc = origin;
	      } // if()
          else {
	        shortest = min;
	      } // else

	    } // findnext()

        bool dijksearch( string target ) {
	      int loc = 0;
          float shortest = 0;;
          bool find = false;
          mapdata tempmap; 
	      while( loc < adjlist.size() && !find ) {
	        if( strcmp( target.c_str(), adjlist[loc].id ) == 0 ){
	          find = true;
	        } // if()
	        loc++;
	      } // while()

          if ( find ) {
            loc = loc-1; 
            strcpy( tempmap.id, adjlist[loc].id );
            tempmap.weight = 0;
            tempmap.gate = loc;
            distance.push_back( tempmap );
            adjlist[loc].connector = distance.size()-1;           
            origin = loc;
          } // if()
          else 
            cout << "student number doesn't exist" << endl ;

          while( find && adjlist[loc].havecame == false ) {
	        adjlist[loc].havecame = true; 
            runthemap( loc, shortest );
            findnext( loc, shortest ); 
          
          } // while()

          return find;

	    } // dijksearch()

        void sortdis() {
	      mapdata swap;
	      int i = 0;
          int j = 0;
          int max = 0;
	      while( i < distance.size() ) {
	        while( j < distance.size() ) {
	          if( distance[j].weight < distance[max].weight ) {
	            max = j;
	          } // if()

              j++;

	        } // while()

            strcpy( swap.id, distance[max].id );            
            swap.weight = distance[max].weight;
            swap.gate = distance[max].gate;
            distance[max] = distance[i];
            distance[i] = swap;
          
            i++;
            max = i;
            j = i;

          } // while()
            
	    } // sortdis()

        void write2() {
	              	
          int i = 1;
          int count = 0;
          int pointnum = 0;

          if ( distance.size() > 0) {     
            filein << endl;
            filein << "origin: " << adjlist[origin].id << endl;	
          } // if()

          while( i < distance.size() ) {
          	            
              filein << "( "<< i << ") ";
			  filein << '\t' ;              
              filein << distance[i].id << ", ";
              pointnum = distance[i].weight * 10 * 10 ;
			  
              filein << distance[i].weight ;
              if ( i < distance.size() && i%8 != 0){
              	filein << "\t";
			  } // if
              
              
              if( count < 7 )
                count++;
              else {
	            filein << "\n";
	            count = 0;
	          } // else
                
              i++;


          } // while()

          filein << endl;

	    } // write2()

        void initial() {
	      int i = 0;
	      distance.clear();
          while( i < adjlist.size() ) {
	        adjlist[i].connector = -1;
	        adjlist[i].havecame = false; 
            i++;
	      } // while()

	    } // initail()

}; // class


int main() {
	
    fileName = "";

    do {

        int order;
		string command = "" ; 
        string sid = "";
    	//string title, numstr ;


    	cout << endl << "******* Graph data applications ******";
    	cout << endl << "* 0. Create adjacency lists          *"; 
   		cout << endl << "* 1. Build connected components      *"; 
   		cout << endl << "* 2. Find shortest paths by Dijkstra *";
    	cout << endl << "***************************************";
    	cout << endl << "Input a command(0, 1, 2) [Any other key to quit ]: "; 
    	cin >> command ; 
    	if ( ( command.compare( "1" ) == 0 ) || ( command.compare( "2" ) == 0 ) || ( command.compare( "0" ) == 0 ) ) {

          if ( ( command.compare( "0" ) == 0 ) ) {  
        	cout << endl << "Input a file number ( e.g., 501, 502, ...): ";
        	cin >> fileName;
            fileName = "pairs" + fileName + ".bin" ;
            filein.open( fileName.c_str() ,ios::in | ios::binary  ) ;
            if ( !filein ) {
	          fileName = fileName.substr( 5, 3 );
	          fileName = "pairs" + fileName + ".txt" ;
              filein.open( fileName.c_str() ,ios::in ) ;
              while( !filein ) {
		        cout << endl << "Open error, Input a file number ( e.g., 501, 502, ...): ";
		        cin >> fileName;
                fileName = "pairs" + fileName + ".bin" ;
                filein.open( fileName.c_str() ,ios::in | ios::binary  ) ;
			  } // while()


	        } // if()
		    
          } // if() 
          else if ( ( command.compare( "1" ) == 0 ) || ( command.compare( "2" ) == 0 ) ) {
	          int run = 0 ;
              run = fileName.rfind(".");
	          fileName = fileName.substr( 0, run );
	          fileName = fileName + ".adj" ;
	          filein.open( fileName.c_str() ,ios::in | ios::binary  ) ;
              if( !filein ) {
	            cout << "Do mission 0 first\n";
                command = -1;
              } // if
	      } // else

            
			
			
			
			if ( command.compare( "0" ) == 0 ) {
              float ask;
              cout << "Input a real number in (0,1]:" ;

              cin >> ask;
              while( ask <= 0 || ask > 1 ){
              	cout << "### It is NOT in (0,1] ###\n" ;
              	cout << "Input a real number in (0,1]:" ;
              	cin >> ask ;
			  } // while
              Adjlist adj = Adjlist( ask );
              adj.readinput();
              filein.close();
              adj.sortget();
              adj.sortput();
              adj.write();
              adj.print();
              adj.delet();
              
              			
			}
            
            else if ( command.compare( "1" ) == 0 ) {            	
	          Dfs d1 = Dfs();            
              d1.readinput();
              filein.close();
              d1.sortget();
              d1.sortput();
              d1.mark();
              d1.countConnectComponent() ;
              d1.sortconnectComponent() ;
              d1.sortConnectNum() ;
              d1.writeDFS() ;
              d1.printall() ;
              d1.delet();
              
	        } // else if()

            else if ( command.compare( "2" ) == 0 ) {
	          bool firstime = true;
	          Dijk di1 = Dijk();
	          int readid = 0;
              di1.readinput();
              filein.close();
              di1.sortget();
              di1.sortput();
              di1.mark(); 
              di1.initial();
              di1.printlist();
              int run = 0 ;
              run = fileName.length()-4;
	          fileName = fileName.substr( 0, run );
	          fileName = fileName + ".ds" ;	          
              cout << "Input a student ID ( 0 is exit ) :";
              cin >> readid; 
              while( readid != 0 ) {
	            stringstream ss;
                ss << readid;
                if ( di1.dijksearch( ss.str() ) && firstime ) {
                  filein.open( fileName.c_str() ,ios::out ) ;
                  firstime = false;
                } // if()
                di1.sortdis();
                di1.write2();
                di1.initial();
                di1.printlist();
                cout << "Input a student ID ( 0 is exit ) :";
                cin >> readid; 
	          } // while()       

              if( firstime == false )
                filein.close();
              
	        } // else if()
			
			
			


    	} // if
       		
     	else
      		break;

	}  while (true);
	

	return 0;

} // main() 



