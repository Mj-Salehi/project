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
    cout << "Hi" << endl ;
    QList<Movie> q;
    QList<Movie> qq;
    QMap<string,QList<Movie>> sq;
    int na , year ,capasity ,i=1 ,nf=0;
    QVector<string> actors;
    string in , name, director;
    while(1){
        //reading file
        if(nf==0)
        {
            fstream qst;
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
                    to_string(year) = tmp;
                    tmp="";
                    int icapacity = tp.find("capacity:");
                    for(int j=icapacity+9;tp[j]!='/';j++)
                        tmp+=tp[j];
                    to_string(capasity) = tmp;
                    Movie a(name,director,actors,year,capasity);
                    q.push_back(a);
                    tp="";
                    qst.close();
                }
            }
        }
        cout << "Enter + for add, - for remove, p for print, g for make group, e for edit a film " << endl;
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
            cout << "Enter the capasity of film : ";
            cin >> capasity;
            qst << "capacity:"<<capasity<<"/";
            Movie a(name,director,actors,year,capasity);
            q.push_back(a);
            nf++;
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
                nf--;
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
            cout << "How many films do you want to be in a group : ";
            int nug;
            cin >> nug;
            int number;
            qq.clear();
            for(int j=0;j<nug;j++)
            {
                cout << "enter the " << j+1<<" member : ";
                cin >> number;
                qq.push_back(q.operator [](number-1));
            }
            sq[ng] = qq;
            QMapIterator<string,QList<Movie>> ii(sq);
            while (ii.hasNext()) {
                i=0;
                ii.next();
                cout << ii.key() << ":" ;
                for(auto it = ii.value().begin();it!=ii.value().end();it++)
                {
                    cout << ii.value().at(i).name <<" ";
                    i++;
                }
                cout << endl;
            }
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
            cout << "Enter the capasity of film";
            cin >> capasity;
            Movie a(name,director,actors,year,capasity);
            q.push_back(a);
        }
    }
    return 0;
}

