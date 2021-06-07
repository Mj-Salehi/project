#include <iostream>
#include <string>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QVector>
#include <QMap>
#include <fstream>
#define Movies "Movies.txt"
#define User "user.txt"
#define Admin "admin.txt"
#define Group "group.txt"
using namespace std;
typedef string st;
class Movie {
public:
    st name, director;
    QVector<string> actors;
    int year , capacity;
    Movie(st n,st d,QVector<string> a,int y, int c)
    {
        name = n;
        actors = a;
        director = d;
        actors = a;
        year = y;
        capacity = c;
    }
};
int main(void)
{
    QList<Movie> q;
    QList<string> qq;
    QMap<string,QList<string>> sq;
    int na , year ,capacity ,i=1 ;
    QVector<string> actors;
    string in , name, director;
    bool st =false,go=true;
    fstream qst;
    //add movise from file to qlist
    qst.open(Movies,ios::in | ios::out);
    if(qst.is_open()){
        string tp="" , tmp;
        while(getline(qst,tp)){
            int iname = tp.find("name:");
            for(int  j=iname+5;tp[j]!='/';j++)
                tmp+=tp[j];
            name = tmp;
            tmp="";
            int idirector = tp.find("director:");
            for(int j=idirector+9;tp[j]!='/';j++)
                tmp+=tp[j];
            director = tmp;
            tmp="";
            int iactors = tp.find("actors:");
            for(int j=iactors+7;tp[j]!='/';j++)
                tmp+=tp[j];
            actors.push_back(tmp);
            tmp="";
            int iyear = tp.find("year:");
            for(int j=iyear+5;tp[j]!='/';j++)
                tmp+=tp[j];
            year = stoi(tmp);
            tmp="";
            int icapacity = tp.find("capacity:");
            for(int j=icapacity+9;tp[j]!='/';j++)
                tmp+=tp[j];
            capacity = stoi(tmp);
            Movie a(name,director,actors,year,capacity);
            q.push_back(a);
            tmp="";
        }
        qst.close();
    }
    //add group to qlist
    if(go==true)
    {
        fstream gfile;
        gfile.open(Group,ios::in|ios::out);
        if(gfile.is_open())
        {
            string tp="" , tmp, gname,members;
            while(getline(gfile,tp)){
                qq.clear();
                int iname = tp.find("name:");
                for(int  j=iname+5;tp[j]!='/';j++)
                    tmp+=tp[j];
                gname = tmp;
                tmp="";
                int imember = tp.find("member:");
                for(int j=imember+7;tp[j]!='/';j++)
                    tmp+=tp[j];
                members = tmp;
                tmp="";
                qq.push_back(members);
                sq[gname] = qq;
            }
        }
        go=false;
        gfile.close();
    }
    int enter=0;
    cout << "Hi"<< endl;
    cout << "If you are admin enter a, if you are user enter u and if you are new user enter n"<< endl;
    string user , pass ,  iii;
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
            string tp="" , tmp1,tmp2;
            while(getline(af,tp)){
                int uname = tp.find("username:");
                for(int  j=uname+9;tp[j]!='/';j++)
                    tmp1+=tp[j];
                int ipass = tp.find("password:");
                for(int j=ipass+9;tp[j]!='/';j++)
                    tmp2+=tp[j];
                if(user==tmp1 && pass==tmp2)
                {
                    cout << "Welcome admin" <<endl;
                    enter =1;
                    while(1){
                        //update movies file
                        if(st==true)
                        {
                            i=0;
                            fstream qst;
                            qst.open(Movies,ios::in | ios::out |ios::trunc);
                            for(auto itr = q.begin();itr!=q.end();itr ++,i++)
                            {
                                qst <<"name:"<<(*itr).name<<"/"
                                   <<"director:"<<(*itr).director<<"/"
                                  <<"actors:"<<(*itr).actors.at(i)<<"/"
                                 <<"year:"<<(*itr).year<<"/"
                                <<"capacity:"<<(*itr).capacity<<"/"
                                <<endl;

                            }
                            st=false;
                        }
                        cout << "Enter + for add, - for remove, p for print, g for make group, e for edit a film, f for finish " << endl;
                        cin >> in;
                        if(in=="+")
                        {
                            ofstream qst;
                            qst.open(Movies , ios::in | ios::app );
                            cout << "Enter the name of film : ";
                            cin >> name ;
                            qst <<"name:" << name << "/" ;
                            cout << "Enter the director of film : ";
                            cin >> director;
                            qst << "director:"<<director<<"/";
                            cout << "How many actors dose it have ? ";
                            cin >> na;
                            if(na>0)
                            {
                                cout << "Enter the name of actors" << endl;
                                string actor;
                                qst << "actors:";
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
                            qst << "year:"<<year<<"/";
                            cout << "Enter the capacity of film : ";
                            cin >> capacity;
                            qst << "capacity:"<<capacity<<"/";
                            Movie a(name,director,actors,year,capacity);
                            q.push_back(a);
                            qst <<endl;
                            qst.close();
                        }
                        else if(in=="p")
                        {

                            if(q.size()>0)
                            {
                                i=1;
                                for(auto itr = q.begin();itr!=q.end();itr ++ ,i++)
                                {
                                    cout <<i;
                                    cout <<": ";
                                    cout <<(*itr).name << endl;
                                }
                                i=1;
                            }
                            else
                                cout << "No films are available" << endl;
                        }
                        else if(in=="-")
                        {
                            if(q.size()>0)
                            {
                                i=1;
                                cout << "The films are here : " << endl;
                                for(auto itr = q.begin();itr!=q.end();itr ++,i++)
                                {
                                    cout <<i<<": " <<(*itr).name << endl;
                                }
                                i=1;
                                cout << "Enter the number of movie : ";
                                int rm;
                                cin >> rm;
                                q.removeAt(rm-1);
                                i=1;
                                for(auto itr = q.begin();itr!=q.end();itr ++,i++)
                                {
                                    cout <<i<<": " <<(*itr).name << endl;

                                }
                                st=true;
                            }
                            else
                                cout << "No films are available" << endl;
                        }
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
                            string ng;
                            cin >> ng;
                            fstream gfile;
                            gfile.open(Group,ios::in|ios::out|ios::app);
                            gfile << "name:" << ng << "/member:";
                            cout << "How many films do you want to be in a group : ";
                            int nug;
                            cin >> nug;
                            int number;
                            qq.clear();
                            for(int j=0;j<nug;j++)
                            {
                                cout << "enter the " << j+1<<" member : ";
                                cin >> number;
                                qq.push_back(q.at(number-1).name);
                            }
                            sq[ng] = qq;
                            QMapIterator<string,QList<string>> ii(sq);
                            while (ii.hasNext()) {
                                i=0;
                                ii.next();

                                cout << ii.key() << ":" ;
                                for(auto it = ii.value().begin();it!=ii.value().end();it++)
                                {
                                    cout << ii.value().at(i) <<" ";
                                    gfile << ii.value().at(i) <<" ";
                                    i++;
                                }
                                cout << endl;
                                gfile << "/" <<endl;
                            }
                            gfile.close();
                        }
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
                            string actor;
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
                tmp1="";
                tmp2=tmp1;
                cout << "username or password is wrong" << endl;
                main();
            }
        }
    }
    else if(iii=="n")
    {
        cout << "enter your username:";
        cin >> user;
        cout << "enter your password:";
        cin >> pass;
        fstream uf;
        uf.open(User,ios::in | ios::out|ios::app);
        uf << "username:"<<user<<"/"<<"password:"<<pass<<"/"<<endl;
        enter =1;
        uf.close();
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
            string tp="" , tmp1,tmp2;
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
                main();
            }
        }
    }
    if(enter==1)
    {
        cout << "Hi " << user << endl ;
        //print movies
        if(q.size()>0)
        {
            cout << "Movise are : " <<endl;
            i=1;
            for(auto itr = q.begin();itr!=q.end();itr ++ ,i++)
            {
                cout <<i;
                cout <<": ";
                cout <<(*itr).name <<"->" << (*itr).capacity  << endl;
            }
            i=1;
        }
        else
        {
            cout << "No films are available" << endl;
            return 0;
        }
        cout << "Do you want to show in group? Y or N ?" <<endl;
        string g;
        cin >> g;
        if(g=="Y")
        {
            QMapIterator<string,QList<string>> ii(sq);
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

            cout << "choose a film" << endl;
            int ch;
            cin >> ch;
            ch--;
            int h=q.at(ch).capacity;
            if(h<=0)
            {
                cout << "it's impossible to choose, try again" <<endl;
                main();
            }
            h--;
            Movie a(q.at(ch).name,q.at(ch).director,q.at(ch).actors,q.at(ch).year,h);
            q.replace(ch,a);
            st=true;

        if(st==true)
        {

                i=0;
                fstream qst;
                qst.open(Movies,ios::in | ios::out |ios::trunc);
                for(auto itr = q.begin();itr!=q.end();itr ++,i++)
                {
                    qst <<"name:"<<(*itr).name<<"/"
                       <<"director:"<<(*itr).director<<"/"
                      <<"actors:"<<(*itr).actors.at(i)<<"/"
                     <<"year:"<<(*itr).year<<"/"
                    <<"capacity:"<<(*itr).capacity<<"/"
                    <<endl;

                }
                st=false;
        }
    }

    return 0;
}
