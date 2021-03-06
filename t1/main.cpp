#include <iostream>
#include <windows.h>
#include <string>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QVector>
#include <QMap>
#include <fstream>
//files
#define Movies "Movies.txt"
#define User "user.txt"
#define Admin "admin.txt"
#define Group "group.txt"
using namespace std;
typedef string str;
class Movie {
public:
    str name, director;
    QVector<string> actors;
    int year , capacity;
    Movie(str n,str d,QVector<str> a,int y, int c)
    {
        name = n;
        actors = a;
        director = d;
        year = y;
        capacity = c;
    }
};
int main(void)
{

    //https://github.com/Mj-Salehi/project

    str si="c";
    QList<Movie> q;//list of moives
    QList<str> qq;//list of members of groups
    QMap<str,QList<str>> sq;//neme of group to members
    QVector<str> actors;
    int na , year ,capacity ,i=1 ;
    str in , name, director;
    bool st =false,gt=false,go=true;

    //add movise from file to qlist
    fstream qst;
    qst.open(Movies,ios::in | ios::out);
    if(qst.is_open() && qst.peek() != std::ifstream::traits_type::eof()){
        str tp="" , tmp;
        while(getline(qst,tp)){
            int iname = tp.find("NAME:");
            for(int  j=iname+5;tp[j]!='/';j++)
                tmp+=tp[j];
            name = tmp;
            tmp="";
            int idirector = tp.find("DIRECTOR:");
            for(int j=idirector+9;tp[j]!='/';j++)
                tmp+=tp[j];
            director = tmp;
            tmp="";
            int iactors = tp.find("ACTORS:");
            for(int j=iactors+7;tp[j]!='/';j++)
                tmp+=tp[j];
            actors.push_back(tmp);
            tmp="";
            int iyear = tp.find("YEAR:");
            for(int j=iyear+5;tp[j]!='/';j++)
                tmp+=tp[j];
            year = stoi(tmp);
            tmp="";
            int icapacity = tp.find("CAPACITY:");
            for(int j=icapacity+9;tp[j]!='/';j++)
                tmp+=tp[j];
            capacity = stoi(tmp);
            Movie a(name,director,actors,year,capacity);

            q.push_back(a);
            tmp="";
        }
        qst.close();
    }

    //add groups from file to qlist
    if(go==true)
    {
        fstream gfile;
        gfile.open(Group,ios::in);

        if(gfile.is_open() && gfile.peek() != std::ifstream::traits_type::eof() )
        {

            str tp="" , tmp, gname,members;
            while(getline(gfile,tp)){
                qq.clear();
                int iname = tp.find("NAME:");
                for(int  j=iname+5;tp[j]!='/';j++)
                    tmp+=tp[j];
                gname = tmp;
                tmp="";
                int imember = tp.find("MEMBER:");
                for(int j=imember+7;tp[j]!='/';j++)
                    tmp+=tp[j];
                members = tmp;
                tmp="";
                qq.push_back(members);
                //map name to members
                sq[gname] = qq;
            }
        }
        go=false;
        gfile.close();
    }
    int enter=0;
    //--------------------------------------------------------------------------------------------------------------
    cout << "Hi"<< endl;
    cout << "if you are admin enter a" << endl << "if you are user enter u " << endl << "if you are new enter n"<< endl;
    str user , pass ,  iii;
    cin >> iii;
    if(iii=="a")
    {
        cout << "enter your username:";
        cin >> user;
        cout << "enter your password:";
        cin >> pass;
        fstream af;
        af.open(Admin,ios::in | ios::out);
        if(af.is_open())
        {
            str tp="" , tmp1,tmp2;
            while(getline(af,tp)){
                int uname = tp.find("username:");
                for(int  j=uname+9;tp[j]!='/';j++)
                    tmp1+=tp[j];
                int ipass = tp.find("password:");
                for(int j=ipass+9;tp[j]!='/';j++)
                    tmp2+=tp[j];
                if(user==tmp1 && pass==tmp2)
                {
                    cout << "Welcome admin" << endl;
                    enter =1;
                    while(1){
                        //update movie's file, (at first st is false)
                        if(st==true)
                        {
                            i=0;
                            fstream qst;
                            qst.open(Movies,ios::in | ios::out |ios::trunc);
                            for(auto itr = q.begin();itr!=q.end();itr ++,i++)
                            {
                                qst <<"NAME:"<<(*itr).name<<"/"
                                   <<"DIRECTOR:"<<(*itr).director<<"/"
                                  <<"ACTORS:"<<(*itr).actors.at(i)<<"/"
                                 <<"YEAR:"<<(*itr).year<<"/"
                                <<"CAPACITY:"<<(*itr).capacity<<"/"
                                <<endl;

                            }
                            st=false;
                        }
                        //update group's file
                        if(gt==true)
                        {
                            i=0;
                            fstream qst;
                            qst.open(Group,ios::in | ios::out |ios::trunc);
                            for(auto itr = sq.begin();itr!=sq.end();itr ++,i++)
                            {
                                qst <<"NAME:"<<(*itr).at(i)<<"/"
                                   <<"MEMBER:"<<(*itr).value(i)<<"/"<<endl;
                                i++;

                            }
                            gt=false;
                        }
                        cout << "Enter" << endl << "+ for add" << endl << "- for remove" << endl << "p for print" << endl << "g for make group" << endl << "sg for show in group" << endl << "e for edit a film" << endl << "f for finish " << endl;
                        cin >> in;
                        //add movie
                        if(in=="+")
                        {
                            ofstream qst;
                            qst.open(Movies , ios::in | ios::app );
                            cout << "Enter the name of film : ";
                            cin >> name ;
                            qst <<"NAME:" << name << "/" ;
                            cout << "Enter the director of film : ";
                            cin >> director;
                            qst << "DIRECTOR:"<<director<<"/";
                            cout << "How many actors dose it have ? ";
                            cin >> na;
                            if(na>0)
                            {
                                cout << "Enter the name of actors" << endl;
                                str actor;
                                qst << "ACTORS:";
                                for(int i=0;i<na;i++)
                                {
                                    cin >> actor;
                                    actors.push_back(actor);
                                    qst << actor << " ";
                                }
                                qst << "/";
                            }
                            cout << "In wich year this file was created ? ";
                            cin >> year ;
                            qst << "YEAR:"<<year<<"/";
                            cout << "Enter the capacity of film : ";
                            cin >> capacity;
                            qst << "CAPACITY:"<<capacity<<"/";
                            qst <<endl;
                            qst.close();

                            //build a class and add to list
                            Movie a(name,director,actors,year,capacity);
                            q.push_back(a);
                        }
                        //print movie
                        else if(in=="p")
                        {
                            if(q.size()>0)
                            {
                                i=1;
                                for(auto itr = q.begin();itr!=q.end();itr ++ ,i++)
                                {
                                    cout <<i;
                                    cout <<": ";
                                    cout <<(*itr).name <<"->" << (*itr).capacity  << endl;
                                }
                                string h;
                                cout << "Do you want to show in details? Y or N ?" <<endl;
                                cin >> h;
                                if(h=="Y")
                                {
                                    cout << "Movise are : " <<endl;
                                    i=1;
                                    for(auto itr = q.begin();itr!=q.end();itr ++ ,i++)
                                    {
                                        cout <<i;
                                        cout <<": " << endl;
                                        cout <<"NAME:"<<(*itr).name <<endl
                                            <<"DIRECTOR:"<<(*itr).director <<endl
                                           <<"ACTORS:"<<(*itr).actors.at(i-1) <<endl
                                          <<"YEAR:"<<(*itr).year <<endl
                                         <<"CAPACITY:"<<(*itr).capacity<< endl;
                                    }
                                    i=1;
                                }
                                i=1;
                            }
                            else
                                cout << "No films are available" << endl;
                        }
                        //delete movie
                        else if(in=="-")
                        {
                            if(q.size()>0)
                            {
                                i=1;
                                cout << "Movies are here : " << endl;
                                for(auto itr = q.begin();itr!=q.end();itr ++,i++)
                                {
                                    cout <<i<<": " <<(*itr).name << endl;
                                }
                                i=1;
                                cout << "Enter the number of movie : ";
                                int rm;
                                cin >> rm;
                                q.removeAt(rm-1);
                                cout << "deleted successfuly!" << endl;
                                i=1;

                                st=true;
                            }
                            else
                                cout << "No films are available" << endl;
                        }
                        //make group
                        else if(in=="g")
                        {
                            i=1;
                            cout << "The films are : " << endl;
                            for(auto itr = q.begin();itr!=q.end();itr ++,i++)
                            {
                                cout <<i<<": " <<(*itr).name << endl;
                            }
                            i=1;
                            cout << "Enter the name of group : ";
                            str ng;
                            cin >> ng;
                            qq.clear();
                            cout << "How many films do you want to be in a group : ";
                            int nug;
                            cin >> nug;
                            int number;
                            str tmp="";
                            for(int j=0;j<nug;j++)
                            {
                                cout << "enter member" << j+1<<" : ";
                                cin >> number;
                                tmp+=q.at(number-1).name;
                                tmp+=" ";
                            }
                            qq.push_back(tmp);
                            fstream gfile;
                            gfile.open(Group,ios::in|ios::out|ios::app);
                            gfile << endl <<  "NAME:" << ng << "/" << "MEMBER:" << tmp << "/" ;
                            gfile.close();
                            sq[ng] = qq;

                            cout << ng << " group made successfuly!" << endl;

                        }
                        //show groups
                        else if(in=="sg")
                        {
                            QMapIterator<str,QList<str>> ii(sq);
                            while (ii.hasNext()) {
                                i=0;
                                ii.next();
                                cout << ii.key() << ":" ;
                                for(auto it = ii.value().begin();it!=ii.value().end();it++)
                                {
                                    cout << ii.value().at(i) <<" ";

                                    i++;
                                }
                                cout << endl;
                            }

                        }
                        //edit movie
                        else if(in=="e")
                        {
                            i=1;
                            cout << "The films are : " << endl;
                            for(auto itr = q.begin();itr!=q.end();itr ++,i++)
                            {
                                cout <<i<<": " <<(*itr).name << endl;
                            }
                            i=1;
                            cout << "enter the number of film : ";
                            int nf;
                            cin >> nf;
                            q.removeAt(nf-1);
                            cout << "Enter the name of film : ";
                            cin >> name ;
                            cout << "Enter the director of film : ";
                            cin >> director;
                            cout << "How many actors dose it have ? ";
                            cin >> na;
                            if(na>0)
                                cout << "Enter the name of actors" << endl;
                            str actor;
                            for(int i=0;i<na;i++)
                            {
                                cin >> actor;
                                actors.push_back(actor);
                            }
                            cout << "In wich year this file was created ? ";
                            cin >> year;
                            cout << "Enter the capacity of film : ";
                            cin >> capacity;
                            Movie a(name,director,actors,year,capacity);
                            q.push_back(a);
                            st = true;
                        }
                        else if(in=="f")
                            break;
                    }
                }
                else if(user!=tmp1 || pass!=tmp2)
                {
                    cout << "username or password is wrong" << endl;
                    Sleep(1000);
                }
                system("CLS");
                main();
            }
        }
    }
    else if(iii=="n")
    {
getnewuser:{
            cout << "enter your username:";
            cin >> user;
            cout << "enter your password:";
            cin >> pass;
            fstream uf;
            uf.open(User,ios::in | ios::out);
            str tp="" , tmp1="";
            while(getline(uf,tp)){
                tmp1="";
                int uname = tp.find("username:");
                for(int  j=uname+9;tp[j]!='/';j++)
                    tmp1+=tp[j];
                if(tmp1==user)
                {
                    cout << "This username isn't available, try another username" << endl;
                    Sleep(1000);
                    system("CLS");
                    goto getnewuser;
                }
            }
            uf.close();
            uf.open(User,ios::in | ios::out|ios::app);
            uf << "username:"<<user<<"/"<<"password:"<<pass<<"/"<<endl;
            enter =1;
            uf.close();
        }
    }
    else if(iii=="u") {
        cout << "enter your username:";
        cin >> user;
        cout << "enter your password:";
        cin >> pass;
        fstream uf;
        uf.open(User,ios::in | ios::out);
        if(uf.is_open())
        {
            str tp="" , tmp1,tmp2;
            while(getline(uf,tp)){
                int uname = tp.find("username:");
                for(int  j=uname+9;tp[j]!='/';j++)
                    tmp1+=tp[j];
                int ipass = tp.find("password:");
                for(int j=ipass+9;tp[j]!='/';j++)
                    tmp2+=tp[j];
                if(user==tmp1 && pass==tmp2)
                {
                    enter =1;
                    break;
                }
                tmp1="";
                tmp2=tmp1;
            }
            if(enter==0)
            {
                cout << "username or password is wrong" << endl;
                Sleep(1000);
                system("CLS");
                main();
            }
        }
    }
    if(enter==1)
    {
        cout << "Welcome " << user << endl ;
welcom:
        while(true)
        {
            cout  <<"for print all of the movies enter p" << endl << "for show in group enter g" << endl << "for search movies enter s" << endl << "for search in groups enter sg" << endl << "for choose enter c " << endl << "for exit enter e" << endl;
            str input;
            cin >> input;

            //search in groups
            if(input=="sg")
            {
                str si;
                while(si!="f")
                {
                    system("CLS");
                    ifstream fileInput;
                    int offset;
                    str line;
                    str search ;
                    cout << "enter your string : " << endl;
                    cin >> search;

                    // open file to search
                    fileInput.open(Group);
                    if(fileInput.is_open()) {
                        while(!fileInput.eof()) {
                            getline(fileInput, line);
                            if ((offset = line.find(search, 0)) != string::npos) {
                                str tmp="";
                                int iname = line.find("NAME:");
                                for(int  j=iname;line[j]!='/';j++)
                                    tmp+=line[j];
                                cout << tmp << endl ;
                                tmp="";
                                int idirector = line.find("MEMBER:");
                                for(int j=idirector;line[j]!='/';j++)
                                    tmp+=line[j];
                                cout << tmp << endl ;
                                tmp="";
                                cout << endl;
                            }
                        }
                        fileInput.close();
                    }
                    else if(!fileInput.is_open())
                    {
                        cout << "Unable to open file.";
                        break;
                    }
                    cout << "for finish searching enter f else enter c" << endl;
                    cin >> si;
                }
                cout << endl;
            }
            //search in movies
            else if(input=="s")
            {
                while(si=="c")
                {
                    system("CLS");
                    ifstream fileInput;
                    int offset;
                    str line;
                    str search ;
                    cout << "enter your string : " << endl;
                    cin >> search;
                    // open file to search
                    fileInput.open(Movies);
                    if(fileInput.is_open()) {
                        while(!fileInput.eof()) {
                            getline(fileInput, line);
                            if ((offset = line.find(search, 0)) != string::npos) {
                                str tmp="";

                                int iname = line.find("NAME:");
                                for(int  j=iname;line[j]!='/';j++)
                                    tmp+=line[j];
                                cout << tmp << endl ;
                                tmp="";
                                int idirector = line.find("DIRECTOR:");
                                for(int j=idirector;line[j]!='/';j++)
                                    tmp+=line[j];
                                cout << tmp << endl ;
                                tmp="";
                                int iactors = line.find("ACTORS:");
                                for(int j=iactors;line[j]!='/';j++)
                                    tmp+=line[j];
                                cout << tmp<< endl ;
                                tmp="";
                                int iyear = line.find("YEAR:");
                                for(int j=iyear;line[j]!='/';j++)
                                    tmp+=line[j];
                                cout << tmp<< endl ;
                                tmp="";
                                int icapacity = line.find("CAPACITY:");
                                for(int j=icapacity;line[j]!='/';j++)
                                    tmp+=line[j];
                                cout << tmp<< endl ;
                                tmp="";

                                cout << endl;
                            }
                        }
                        fileInput.close();
                    }
                    else if(!fileInput.is_open())
                    {
                        cout << "Unable to open file.";
                        break;
                    }

                    cout << "for finish searching enter f else enter c" << endl;
                    cin >> si;
                }
                if(si=="f")
                    goto welcom;
                cout << endl;
            }
            //print movies
            else if(input=="p")
            {
                if(q.size()>0)
                {
                    i=1;
                    for(auto itr = q.begin();itr!=q.end();itr ++ ,i++)
                    {
                        cout <<i;
                        cout <<": ";
                        cout <<(*itr).name <<"->" << (*itr).capacity  << endl;
                    }
                    string h;
                    cout << "Do you want to show in details? Y or N ?" <<endl;
                    cin >> h;
                    if(h=="Y")
                    {
                        cout << "Movise are : " <<endl;
                        i=1;
                        for(auto itr = q.begin();itr!=q.end();itr ++ ,i++)
                        {
                            cout <<i;
                            cout <<": " << endl;
                            cout <<"NAME:"<<(*itr).name <<endl
                                <<"DIRECTOR:"<<(*itr).director <<endl
                               <<"ACTORS:"<<(*itr).actors.at(i-1) <<endl
                              <<"YEAR:"<<(*itr).year <<endl
                             <<"CAPACITY:"<<(*itr).capacity<< endl;
                        }
                        i=1;
                    }
                    i=1;
                }
                else
                {
                    cout << "No films are available" << endl;
                    return 0;
                }
                cout << endl;
            }
            //print groups
            else if(input=="g")
            {

                QMapIterator<str,QList<str>> ii(sq);
                while (ii.hasNext()) {
                    i=0;
                    ii.next();
                    cout << ii.key() << ":" ;
                    for(auto it = ii.value().begin();it!=ii.value().end();it++)
                    {
                        cout << ii.value().at(i) <<" ";
                        i++;
                    }
                    cout << endl;
                }
                cout << endl;
            }
            else if(input=="c")
            {
                if(q.size()>0)
                {
                    cout << "Movise are : " <<endl;
                    i=1;
                    for(auto itr = q.begin();itr!=q.end();itr ++ ,i++)
                    {
                        cout <<i;
                        cout <<": " ;
                        cout <<(*itr).name <<"-->" <<(*itr).capacity<< endl;
                    }
                    i=1;
                }
                cout << "enter number of movie" << endl;
                int ch;
                cin >> ch;
                ch--;
                int h=q.at(ch).capacity;
                if(h<=0)
                {
                    cout << "it's impossible to choose, try again" <<endl;
                    Sleep(2000);
                    system("CLS");
                    goto welcom;
                }
                h--;
                Movie a(q.at(ch).name,q.at(ch).director,q.at(ch).actors,q.at(ch).year,h);
                q.replace(ch,a);
                //update movie's file
                st=true;
                i=0;
                fstream qst;
                qst.open(Movies,ios::in | ios::out |ios::trunc);
                for(auto itr = q.begin();itr!=q.end();itr ++,i++)
                {
                    qst <<"NAME:"<<(*itr).name<<"/"
                       <<"DIRECTOR:"<<(*itr).director<<"/"
                      <<"ACTORS:"<<(*itr).actors.at(i)<<"/"
                     <<"YEAR:"<<(*itr).year<<"/"
                    <<"CAPACITY:"<<(*itr).capacity<<"/"
                    <<endl;

                }
                st=false;
                cout << endl;
            }
            else if(input=="e")
                break;
            else
            {
                cout << "Unkown input!" << endl << "try agin!" << endl;
                Sleep(2000);
                system("CLS");
                goto welcom;
            }
        }
    }
    cout << "Have good time!!" << endl;
    return 0;
}
