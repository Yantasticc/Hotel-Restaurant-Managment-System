#include <bits/stdc++.h>
using namespace std;

class client
{
public:
    static int c_id_count;
    int cost_cnt;
    char c_type;
    

    virtual void check()
    {
        fstream fin;
        fin.open("client.csv", ios::in);
        int target_phn,phn,count = 0;
        cout << "\t\t\tEnter the phone number of the client to display details : ";
        cin >> target_phn;
        cout<<endl;
        cout<<"\t\t\tClient Details \n"<<endl;

        vector<string> row;
        string line, word;
        while (fin >> line) 
		{
            row.clear();
            stringstream s(line);

            while (getline(s,word,',')) 
			{
            row.push_back(word);
            }

            phn = atoi(row[2].c_str());
            if (target_phn == phn) 
			{
                count = 1;
                cout << "\t\t\tClient ID : " << row[0] << "\n";
                cout << "\t\t\tName : " << row[1] << "\n";
                cout << "\t\t\tPhone No : " << row[2] << "\n";
                cout << "\t\t\tAddress : " << row[3] << "\n";
                cout << "\t\t\tNID : " << row[4] << "\n";
                break;
            }
        }

        if (count == 0)
            cout <<"\t\t\tRecord not found\n";

    }
    
    virtual int update()
    {
        fstream fout;
        fout.open("client.csv", ios::out | ios::app);
        int c_id;

        string c_name;
        string c_phone_no;
        string c_address;
        string c_nid;

        cout<<"\t\t\t----------Enter Client Details-----------\n\n";
        cout<<"\t\t\tEnter Client ID : ";
        cin>>c_id;
        cout<<endl<<"\t\t\tEnter Client Name : ";
        cin>>c_name;
        cout<<endl<<"\t\t\tEnter Client Phone No : ";
        cin>>c_phone_no;
        cout<<endl<<"\t\t\tEnter Client Address : ";
        cin>>c_address;
        cout<<endl<<"\t\t\tEnter Client NID : ";
        cin>>c_nid;

        fout << c_id << ","
                 << c_name << ","
                 << c_phone_no << ","
                 << c_address << ","
                 << c_nid << "\n";
        fout.close();
    }
};


class client_hotelroom:virtual public client
{
public:
    void check()
    {
        ifstream inf("hotelroom.txt");

        if(!inf) cout<<endl<<"\t\tUnable to open hotelroom file"<<endl;
        
        int room_id; string room_type; string room_book;
        cout<<endl<<"\t\tHotelrooms to book:"<<endl;

        while(!inf.eof())
        {
            inf>>room_id>>room_type>>room_book;
            if(room_book=="NULL")
            cout<<room_id<<" "<<room_type<<endl;
        }
        inf.close();
    }


   int update()
    {
        int target_room_id,c_id;
        cout<<"\t\t\tPlease enter the required room id : ";
        cin>>target_room_id;
        cout<<"\t\t\tPlease enter the client id : ";
        cin>>c_id;

        string client_id;
        stringstream ss;
        ss << c_id;
        client_id = ss.str();

        ifstream inf("hotelroom.txt");
        ofstream outf("hotelroom1.txt");
        if(!inf) cout<<endl<<"Unable to open hotelroom file"<<endl;
        int room_id; string room_type; string room_book;
        
        while(!inf.eof())
        {
            inf>>room_id>>room_type>>room_book;
            if(room_id==target_room_id)
            {
                cost_cnt+=1000;
                cout<<room_id<<" "<<room_type<<endl;
                outf<<room_id<<" "<<room_type<<" "<<client_id<<endl;
            }
            else
            {
                outf<<room_id<<" "<<room_type<<" "<<room_book<<endl;
            }
        }
        
        outf.close();
        inf.close();
        remove("hotelroom.txt");
        rename("hotelroom1.txt","hotelroom.txt");
        return cost_cnt;
    }


    void checkout()
    {
        int c_id;
        cout<<"\t\t\tPlease enter the client id : ";
        cin>>c_id;
        
        string client_id;
        stringstream ss;
        ss << c_id;
        client_id = ss.str();

        ifstream inf("hotelroom.txt");
        ofstream outf("hotelroom1.txt");
        if(!inf) cout<<endl<<"Unable to open hotelroom file"<<endl;
        int room_id; string room_type; string room_book;

        while(true)
        {
            inf>>room_id>>room_type>>room_book;
            if(inf.eof()) break;
            if(room_book==client_id)
            {
                cout<<room_id<<" "<<room_type<<endl;
                outf<<room_id<<" "<<room_type<<" "<<"NULL"<<endl;
            }
            else
            {
                outf<<room_id<<"\t\t\t "<<room_type<<"\t\t\t "<<room_book<<endl;
            }
        }

        outf.close();
        inf.close();
        remove("hotelroom.txt");
        rename("hotelroom1.txt","hotelroom.txt");
    }
    virtual void display_cost(){};
};


class client_conventionhall:virtual public client
{
    public:
    void check()
    {
        ifstream inf("conventionhall.txt");
        if(!inf) cout<<endl<<"\t\t\tUnable to open conventionhall file"<<endl;
        
        string day,time,hall_book,target_day,target_time,res="\t\t\tNot Booked!!!";
        
        cout<<endl<<"\t\t\tPlease enter the date(Ex: 23/05/2019) : ";
		cin>>target_day;
        cout<<endl<<"\t\t\tPlease enter the time(07:00 / 11:00) : ";
		cin>>target_time;

        while(!inf.eof())
        {
            inf>>day>>time>>hall_book;
            cout<<"\t\t\tDay : "<<day<<endl<<"\t\t\tTime : "<<time<<endl<<"\t\t\tClient ID : "<<hall_book<<endl;
            if(day==target_day && time==target_time) res="\t\t\tBooked!!!";
        }
        cout<<endl<<res<<endl;
        inf.close();
    }


    int update()
    {
        string target_day,target_time;int c_id;
        cout<<"\t\t\tPlease enter the required date : ";
        cin>>target_day;
        cout<<endl<<"\t\t\tPlease enter the required time : ";
        cin>>target_time;
        cout<<endl<<"\t\t\tPlease enter the client id : ";
        cin>>c_id;
        cost_cnt+=20000;

        ofstream outf("conventionhall.txt",ios::app);
        outf<<endl<<"\t\t\t"<<target_day<<"\t\t\t"<<target_time<<" "<<c_id;
        outf.close();
        return cost_cnt;
    }
    virtual void display_cost(){};
};


class client_restaurant:virtual public client
{
public:
    void check()
    {
        ifstream inf("restaurant.txt");
        if(!inf) cout<<endl<<"\t\t\tUnable to open restaurant file"<<endl;
        string day,time,res_book,target_day,target_time,res="\t\t\tNot Booked!!!";
        cout<<endl<<"\t\t\tPlease enter the date(Ex: 23/05/2019) : ";
		cin>>target_day;
        cout<<endl<<"\t\t\tPlease enter the time(Ex: 07:00) : ";
		cin>>target_time;

        while(!inf.eof())
        {
            inf>>day>>time>>res_book;
           //cout<<"\t\t\t"<<"Day : "<<day<<endl<<"\t\t\tTime : "<<time<<endl<<"\t\t\tClient ID : "<<res_book<<endl;
            if(day==target_day && time==target_time)
			{
				res="\t\t\tBooked!!!";
			 } 
        }
        cout<<endl<<res<<endl;
        inf.close();
    }


    int update()
    {
        string target_day,target_time;int c_id;
        cout<<"\t\t\tPlease enter the required date : ";
        cin>>target_day;
        cout<<"\t\t\tPlease enter the required time : ";
        cin>>target_time;
        cout<<"\t\t\tPlease enter the client id : ";
        cin>>c_id;

        cost_cnt+=200;

        ofstream outf("restaurant.txt",ios::app);
        outf<<endl<<target_day<<" "<<target_time<<" "<<c_id;
        outf.close();
        
        return cost_cnt;
    }
    
    virtual void display_cost(){};
    
};


class cost : public client_conventionhall, public client_hotelroom, public client_restaurant
{
public:
    void check(){}
    
    int update() {}


    void display_cost(int cost)
    {
        cout<<endl<<"\t\t\tTotal cost : "<<cost<<endl;
        int paid; cout<<endl<<"\t\t\tPaid money : "; 
		cin>>paid;
        cout<<endl<<"\t\t\tRecievable change : "<<paid-cost<<endl;
        
    }

    cost operator - (cost c)
    {
        cost c3;
        c3.cost_cnt = c.cost_cnt - this->cost_cnt;
        return c3;
    }
    
};


int main()
{
    client *bptr; int t;
    client c1;
    client_conventionhall ch1;
    client_hotelroom h1;
    client_restaurant r1;
    cost c2;
    

	char name[30];
	beginning:
	system("CLS");
	cout<<"\t\t\t--------------------------Welcome---------------------------------\n\n";
	cout<<"\t\t\tPlease Enter Your Name : ";
	cin.getline(name, 20);
	cout<<endl<<"\t\t\tHello "<<name<<" .... "<<"\n\n\t\t\tCLIENT DETAILS \n\n";

	cout<<endl<<"\t\t\t------------------Search Client/ Create Client------------------\n\n";

    while(true)
    {

        A:cout<<endl<<"\t\t\tType 1 to search for a client id"<<endl<<"\t\t\tType 2 to create a client id"<<endl<<"\t\t\tType 0 end "<<endl;
        cout<<"\n\t\t\tEnter Choice : ";
        cin>>t;
        cout<<endl;
        bptr=&c1;

        try
        {
            if(t==1) bptr->check();
            else if(t==2) bptr->update();
            else if (t==0) {}
            else throw(t);
        }
        
        catch(...)
        {
            cout<<endl<<"\t\t\tTyped unavailable option"<<endl; 
            goto A;
        }
        cout<<endl<<"\t\t\t--------------------Select your option-------------------\n\n";
        B:cout<<endl<<"\t\t\tType 1 to book a hotelroom"<<endl<<"\t\t\tType 2 to book convention hall"<<endl<<"\t\t\tType 3 to reserve restaurant meal"<<endl<<"\t\t\tType 4 to check out hotel room"<<endl<<"\t\t\tType 0 to end "<<endl;
        cout<<"\n\t\t\tEnter Choice : ";
        cin>>t;

        try
        {

           if(t==1)
			{
				cout<<endl<<"\t\t\t-----------------Type 1 is Selected for booking a hotelroom----------------\n\n";
				bptr = &h1;
				bptr->cost_cnt=0;
				bptr->check();
				cout<<endl<<"\t\t\tType 1 to checkin , Type 0 to not - ";
				cin>>t; cout<<"\n";
				if(t)
				{
					int i,d;
					cout<<endl<<"\t\t\tHow many rooms do you need ? ";
                    cout<<endl<<"\t\t\tRoom : ";
					cin>>i; 
				    
					while(i--)
						d=bptr->update();
						c2.display_cost(d);
						cout<<endl<<"\t\t\tHotelroom Booked!!\n";
				}			
			}

			else if(t==2)
			{
				cout<<endl<<"\t\t\t-----------------Type 2 is Selected for booking Convention hall----------------\n\n";
				bptr = &ch1;
				bptr->cost_cnt=0;
				bptr->check();
				cout<<endl<<"\t\t\tType 1 to book , Type 0 to not - ";
				cin>>t; cout<<"\n";
				
				
				if(t)
				{
					c2.display_cost(bptr->update());
					cout<<endl<<"\t\t\tConvention hall Booked!!!\n";
				} 
			}	

			else if(t==3)
			{
				cout<<endl<<"\t\t\t---------------Type 3 is Selected to reserve restaurant meal----------------\n\n";
				bptr = &r1;
				bptr->cost_cnt=0;
				bptr->check();
				cout<<endl<<"\t\t\tType 1 to book , Type 0 to not - ";
				cin>>t; cout<<"\n";
				
				if(t)
				{
					c2.display_cost(bptr->update());
					cout<<"\t\t\tRestaurant meal Booked!!!\n";
				}
			}

			else if(t==4)
			{
				cout<<endl<<"\t\t\t-----------------Type 4 is Selected to check out hotel room----------------\n\n";
				h1.checkout();
				cout<<"\t\t\tChecked Out!!!"<<endl;
			}

			else if(t==0)
			{
				break;	
			}

			else throw(t); 
        
		}
        
        
        catch(...)
        {
            cout<<endl<<"\t\t\tTyped unavailable option.";
            goto B;
        }
    }
}
