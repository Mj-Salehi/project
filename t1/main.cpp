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
#define Nf "Nf.txt"
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
    int na , year ,capacity ,i=1 ,nff=0;
    QVector<string> actors;
    string in , name, director;
    bool st =false;
    //reading file
    fstream file;
    file.open(Nf,ios::in | ios::out);
    if(file.is_open()){
        file >> nff;
    }
    file.close();
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
        cout << "Enter + for add, - for remove, p for print, g for make group, e for edit a film " << endl;
        cin >> in;
        if(in=="+")
        {
            nff++;
            ofstream file;
            file.open(Nf,ios::in | ios::out);
            file << nff;
            file.close();
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
                nff--;
                ofstream file;
                file.open(Nf,ios::in | ios::out);
                file << nff;
                file.close();
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
                nff--;
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
            cout << "Enter the capacity of film : ";
            cin >> capacity;
            Movie a(name,director,actors,year,capacity);
            q.push_back(a);
            st = true;
        }
    }
    return 0;
}
