// 10727220 陳正浩 10727247 廖仁傑
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include<iostream>
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


class Adjlist{
	
    private: 
        bindata bintemp;
        data *temp;
        data *tail;
        int node;
	    vector<int> queue;
        int path;
   
    protected:
	    vector<adjdata> adjlist;// 動態陣列
	
	public:
		Adjlist() {					//constructor
          temp = NULL;
          tail = NULL;
          node = 0;
		}

       		
		void print() {	
          cout << "<<< There are " << adjlist.size() <<" IDs in total. >>>\n";
          cout << "<<< There are " << node <<" nodes in total. >>>\n";	
		} // print()


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
              } // if()
              i++;
            } // while 

            if ( nodata == true ) {
	          adjlist.push_back( initial );
              strcpy( adjlist[adjlist.size()-1].id, bintemp.getid );
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

                  if( strcmp( tail->getid, bintemp.getid ) != 0 ) {
                    temp = new data;
                    temp->next = NULL;
                    strcpy( temp->getid, bintemp.getid );
                    temp->weight = bintemp.weight;
                    temp->loc = 0; // 排完序再給 
                    tail->next = temp;
                  } // if()

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
			filein.read( bintemp.putid, sizeof( bintemp.getid ) ); 
            filein.read( bintemp.getid, sizeof( bintemp.getid ) ); 
            filein.read( (char *) &bintemp.weight, sizeof( float ) );
            addadj();
            node++;
			while( !filein.eof( ) ) {	            
	            filein.read( bintemp.putid, sizeof( bintemp.getid ) ); 
                filein.read( bintemp.getid, sizeof( bintemp.getid ) ); 
                filein.read( (char *) &bintemp.weight, sizeof( float ) );
                addadj();
                node++;
			} // while()

            node--;

          

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
	      fileName = "pairs" + fileName + ".adj" ;
	      filein.open( fileName.c_str() ,ios::out ) ;
          int i = 0;
          int j = 0;
          int count = 0;
          filein << "<<< There are " << adjlist.size() <<" IDs in total. >>>\n";
          while( i < adjlist.size() ) {
	        filein << "[ " << i+1 << " ]" << " ";
            filein << adjlist[i].id << ":\n";
            walk = adjlist[i].head;
            while ( walk != NULL ) {
              
              filein << "	("<< j+1 << ") ";
              filein << walk->getid << ",  ";
              filein << walk->weight << "	";
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

        bool havelist() {
	       if( adjlist.empty() ) {
	         return false;
	       } // if()
           else {
	         return true;
	       } // else
	    } // havelist()

        bool havepath() {
          int i = 0;
          bool empty = true;
          while( i < adjlist.size() ) {
	        if( !adjlist[i].path.empty() )
              empty = false;
            i++; 
	      } // while()

          return !empty;

       } // havepath
        		
		void print2() {	
          cout << "<<< There are " << adjlist.size() <<" IDs in total. >>>\n";	
		} // print()


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

        void bfsearch( int loc ) {
          temp = adjlist[queue[0]].head;
          adjlist[loc].havecame = true;
          while( temp != NULL ) {
            if( adjlist[temp->loc].havecame == false ) {
	          adjlist[loc].path.push_back( adjlist[temp->loc].id );
              adjlist[temp->loc].havecame = true;
	          queue.push_back( temp->loc );
              path++;
	        } // if
             
            temp = temp->next;

          } // while()

          queue.erase( queue.begin() ); 
	      
        } // bfsearch()

        void counts( int loc ) {
          path = 0;
          queue.push_back( loc );
          bfsearch( loc ); 
          while( queue.empty() == false ) {
	        bfsearch( loc );
          } // while() 


	    } // counts()

        void allinitail() {
	      int i = 0;
          while( i < adjlist.size() ) {
            adjlist[i].havecame = false;
            i++; 
	      } // while()

	    } // allinitail()

        void setconnect() {
	      int i = 0;
          while( i < adjlist.size() ) {
	        allinitail();
	        counts( i );
            adjlist[i].connector = path;
            i++; 
	      } // while()

	    } // setconnect()

        void sortput2() { 
	      adjdata swap;
	      int i = 0;
          int j = 0;
          int max = 0;
	      while( i < adjlist.size() ) {
	        while( j < adjlist.size() ) {
	          if( adjlist[j].connector > adjlist[max].connector ) {
	            max = j;
	          } // if()
              else if( adjlist[j].connector == adjlist[max].connector 
                       && strcmp( adjlist[j].id, adjlist[max].id ) < 0 ) {
	            max = j;
	          } // else if
              j++;

	        } // while()

            swap = adjlist[i];
            adjlist[i] = adjlist[max];
            adjlist[max] = swap;
            j = i+1;
            i++;
            max = i;
            
	      } // while


        } // sortput2()

        void sortpath() {
	      char tempid[10];
          int i = 0;
          int j = 0;
          int k = 0;
          int max = 0; 
	      while( i < adjlist.size() ) {
	
	        while( j < adjlist[i].path.size() ) {
	
              max = j;
              strcpy( tempid, adjlist[i].path[j].c_str() );
              while( k < adjlist[i].path.size() ) {
	            if( strcmp( adjlist[i].path[k].c_str(), tempid ) < 0 ) {
                  strcpy( tempid, adjlist[i].path[k].c_str() );
                  max = k;
                } // if() 

                k++;

	          } // while()

              adjlist[i].path[max] = adjlist[i].path[j];
              adjlist[i].path[j] = tempid;
              j++;
              k = j;

	        } // while()

            i++;
            j = 0;
            k = 0;
             
	      } // while
	      
	    } // sortpath()

        void write2() {
	      fileName = fileName.substr( 5, 3 );
	      fileName = "pairs" + fileName + ".cnt" ;
	      filein.open( fileName.c_str() ,ios::out ) ;
          int i = 0;
          int j = 0;
          int count = 0;
          filein << "<<< There are " << adjlist.size() <<" IDs in total. >>>\n";
          while( i < adjlist.size() ) {
	        filein << "[ " << i+1 << " ]" << " ";
            filein << adjlist[i].id << "(" << adjlist[i].path.size() <<"):\n";
            while ( j < adjlist[i].path.size() ) {
              
              filein << "	("<< j+1 << ") ";
              filein << adjlist[i].path[j] << "	";
              if( count < 9)
                count++;
              else {
	            filein << "\n";
	            count = 0;
	          } // else
                
              j++;

            } // while()

            filein << "\n";
	        i++;
            j = 0;
            count = 0;

          } // while()

          filein.close();

	    } // write()

        

		
}; // Bfs


class Dfs : public Adjlist {
	
    private:
        data *temp;
        vector<int> queue; 
        int path;
        float effect;  

	public:
		Dfs( float ask ) {					//constructor 
          temp = NULL; 
          effect = ask;    
		}

        
		
		void print() {	
          cout << "<<< There are " << adjlist.size() <<" IDs in total. >>>\n";	
		} // print()

        void printall() {
	      ;	
	    } // printall() 

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

        bool nodone( int &loc ) { // 找到還沒走過的那個 
          int i = 0;
          while( i < adjlist.size() ) {
	        if( adjlist[i].havecame == false ) {
	          loc = i;
              return true;
	        } // if()
	        
            i++;
	      } // while

          return false;

	    } // nodone()

        void bfsearch( int loc ) {
          temp = adjlist[queue[0]].head;
          adjlist[loc].havecame = true;
          while( temp != NULL ) {
            if( adjlist[temp->loc].havecame == false && temp->weight >= effect ) {
	          adjlist[loc].path.push_back( adjlist[temp->loc].id );
              adjlist[temp->loc].havecame = true;
	          queue.push_back( temp->loc );
              path++;
	        } // if
             
            temp = temp->next;

          } // while()

          queue.erase( queue.begin() ); 
	      
        } // bfsearch()

        void counts( int loc ) {
          path = 0;
          queue.push_back( loc );
          bfsearch( loc ); 
          while( queue.empty() == false ) {
	        bfsearch( loc );
          } // while() 


	    } // counts()

        void allinitail() {
	      int i = 0;
          while( i < adjlist.size() ) {
            adjlist[i].havecame = false;
            i++; 
	      } // while()

	    } // allinitail()

        void setconnect() {
	      int i = 0;
          while( i < adjlist.size() ) {
	        allinitail();
	        counts( i );
            adjlist[i].connector = path;
            i++; 
	      } // while()

	    } // setconnect()

        void sortput2() { 
	      adjdata swap;
	      int i = 0;
          int j = 0;
          int max = 0;
	      while( i < adjlist.size() ) {
	        while( j < adjlist.size() ) {
	          if( adjlist[j].connector > adjlist[max].connector ) {
	            max = j;
	          } // if()
              j++;

	        } // while()

            swap = adjlist[i];
            adjlist[i] = adjlist[max];
            adjlist[max] = swap;
            j = i+1;
            i++;
            max = i;
            
	      } // while

        } // sortput2()

        void sortpath() {
	      char tempid[10];
          int i = 0;
          int j = 0;
          int k = 0;
          int max = 0; 
	      while( i < adjlist.size() ) {
	
	        while( j < adjlist[i].path.size() ) {
	
              max = j;
              strcpy( tempid, adjlist[i].path[j].c_str() );
              while( k < adjlist[i].path.size() ) {
	            if( strcmp( adjlist[i].path[k].c_str(), tempid ) < 0 ) {
                  strcpy( tempid, adjlist[i].path[k].c_str() );
                  max = k;
                } // if() 

                k++;

	          } // while()

              adjlist[i].path[max] = adjlist[i].path[j];
              adjlist[i].path[j] = tempid;
              j++;
              k = j;

	        } // while()

            i++;
            j = 0;
            k = 0;
             
	      } // while
	      
	    } // sortpath()

        void write() {
	      fileName = fileName.substr( 5, 3 );
	      fileName = "pairs" + fileName + ".inf" ;
	      filein.open( fileName.c_str() ,ios::out ) ;
          int i = 0;
          int j = 0;
          int count = 0;
          filein << "<<< There are " << adjlist.size() <<" IDs in total. >>>\n";
          while( i < adjlist.size() ) {
	        if( adjlist[i].path.size() > 0 ) {
	          filein << "[ " << i+1 << " ]" << " ";
              filein << adjlist[i].id << "(" << adjlist[i].path.size() <<"):\n";
              while ( j < adjlist[i].path.size() ) {
              
                filein << "	("<< j+1 << ") ";
                filein << adjlist[i].path[j] << "	";
                if( count < 9)
                  count++;
                else {
	              filein << "\n";
	              count = 0;
	            } // else


                j++;

              } // while()

              filein << "\n"; 
            } // if() 

	        i++;
            j = 0;
            count = 0;

          } // while()

          filein.close();

	    } // write()

}; // class




int main() {
	
    Adjlist adj = Adjlist();
    do {
	
        int order;
		string command = "" ; 
        string sid = "";
    	//string title, numstr ;


    	cout << endl << "**** Graph data manipulation ****";
    	cout << endl << "* 0. QUIT                       *"; 
   		cout << endl << "* 1. Build adjacency lists      *"; 
   		cout << endl << "* 2. Compute connection counts  *";
        cout << endl << "* 3. Estimate influence values  *"; 
    	cout << endl << "*********************************";
    	cout << endl << "Input a command(0, 1, 2, 3): "; 
    	cin >> command ; 
    	if ( ( command.compare( "1" ) == 0 ) || ( command.compare( "2" ) == 0 ) || ( command.compare( "3" ) == 0 ) 
             || ( command.compare( "4" ) == 0 ) ) {

          if ( ( command.compare( "1" ) == 0 ) || ( command.compare( "3" ) == 0 ) ) {  
        	cout << endl << "Input a file number ( e.g., 401, 402, ...): ";
            fileName = "";
        	cin >> fileName;
            fileName = "pairs" + fileName + ".bin" ;
            filein.open( fileName.c_str() ,ios::in | ios::binary  ) ;
            if ( !filein ) {
	          fileName = fileName.substr( 5, 3 );
	          fileName = "pairs" + fileName + ".txt" ;
              filein.open( fileName.c_str() ,ios::in ) ;
              while( !filein ) {
		        cout << endl << "Open error, Input a file number ( e.g., 401, 402, ...): ";
		        cin >> fileName;
                fileName = "pairs" + fileName + ".txt" ;
                filein.open( fileName.c_str() ,ios::in ) ;	
			  } // while()

              filein.close();

	        } // if()
		    
          } // if() 

            
			
			
			
			if ( command.compare( "1" ) == 0 ) {
	          if( adj.havelist() ) {
	            adj.delet();
                adj = Adjlist();
	          } // if()  

              adj.readinput();
              filein.close();
              adj.sortget();
              adj.sortput();
              adj.write();
              adj.print();

              
              			
			}
            
            else if ( command.compare( "2" ) == 0 ) {
              if ( adj.havelist() ) {
	            if ( !adj.havepath() ) {
                  adj.mark();
                  adj.setconnect();
                  adj.sortput2(); 
                  adj.sortpath();
                } // if()
                  adj.write2();
                  adj.print2();  
              } // if()            
              else
                cout << "Do Mission One First" << endl;
              
	        } // else if()
            else if ( command.compare( "3" ) == 0 ) {
	          float ask;
              cout << "Input a real number in [0,1]:" ;
              cin >> ask;
	          Dfs d1 = Dfs( ask );              
              d1.readinput();
              filein.close();
              d1.sortget();
              d1.sortput();
              d1.mark();
              d1.setconnect();
              d1.sortput2(); 
              d1.sortpath();
              d1.write();
              d1.print();
              d1.delet();;
              
              
	        } // else if()
            else if ( command.compare( "4" ) == 0 ) {
	          ;
              
              
	        } // else if()
            
			
			
			


    	} // if
     	else if ( command.compare( "0" ) == 0 )
       		break;
     	else
      		 cout << endl << "Command does not exist!" << endl;

	}  while (true);
	

	return 0;

} // main() 



