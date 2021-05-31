#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

using namespace std;


/*  basic data structures */ 
/*
int -> minterm such as <1>
set<int> -> a implicant such as <1, 3, 5>.(a Prime Implicant, a Essential Prime Implicant)
set<set<int>> -> group of implicants such as <<1,3,5>, <2,4,7>> (Prime Implicants, Essential Prime Implicants, a Minimal Expression)
set<set<set<int>>> -> group of the expressions such as <<<1,3,5> , <2,4,7>> , <<1,3,5> , <2,9,10>>> (Minmal Expressions)
*/

set<int> testMinTerm;        //Target Minterms
set<set<int>> PrimeImplicant;     //Prime Implicants group
set<set<int>> EssentialPrimeImplicant;    //Essential Prime Implicants group
set<set<set<int>>> Expression;      //Minimal Expression

vector<int> StoredMinTerm[4]={{1,2,3,4,5,6},       //3-variable
                            {0, 1, 2, 5, 6, 7, 8, 9, 10, 14},   //4-variable
                            {5, 6, 8, 9, 13, 14, 15, 18, 21, 22, 23, 24, 25, 28, 30}};      //5-variable

string literal[2][5] = { {"a'", "b'", "c'", "d'", "e'"}, {"a", "b", "c", "d", "e"}};

class Group; //group of terms Class
void findMinimalExpression(set<int> MinTerm, set<set<int>> prime, set<set<int>> accumulator);   //Extract Expressions from Prime Implicants
void minNumTerm();  //reserve only minimal expressions
vector<int> set2vec(set<int> s, int num);   //convert a implicant to vector
string set2str(set<int> s, int num);    //convert a implicatn to literals
int numofOne(int x);    //number of 1's
void Quine_McCluskey(int _numofVar);    //Quine-McCluskey Algorithm

class Group{
    public:
        Group(){}
        
        // Compare two Group class and return combined Group if it can
        Group compare(Group& g, int num){
            Group _next;
            for(int i = 0 ;i < this->size(); i++){
                for(int j = 0 ; j < g.size(); j++){
                    vector<int> vec1 = set2vec(this->group[i], num);
                    vector<int> vec2 = set2vec(g.group[j], num);
                    int diff = 0;
                    for(int k = 0 ; k < num ; k++){
                        if(vec1[k] != vec2[k])
                            diff++;
                    }
                    if(diff==1){
                        set<int> s = this->group[i];
                        s.insert(g.group[j].begin(), g.group[j].end());
                        _next.push(s);
                        check[i] = 1;
                        g.check[j] = 1;
                    }
                }
            }

            return _next;
        }

        //return a unused implicant. It could be a prime implicant
        set<int> primeImp(int i){
            set<int> ret;
            if(check[i]!=1)
                ret = group[i];
            return ret;
        }
        
        int size(){
            return group.size();
        }

        //push a one-literal minterm into the group
        void push(int x){
            set<int> s;
            s.insert(x);
            group.push_back(s);
            check = new int[group.size()];

            for(int i = 0 ;i < (int)group.size(); i++)
                check[i] = 0;
        }

        //push a multi-literal minterm into the group
        void push(set<int> s){
            group.push_back(s);
            check = new int[group.size()];
            for(int i = 0 ;i < (int)group.size(); i++)
                check[i] = 0;
        }
        // debugging purpose
        void printOut(){
            for(auto i : group){
                for(auto j : i)
                    cout<<j<<' ';
                cout<<endl;
            }
            cout<<"------------------"<<endl;
            for(int i = 0 ;i < (int)group.size(); i++)
                cout<<check[i]<<endl;
        }

    private:
        int* check; //check whether implicants are used
        vector<set<int>> group; //group of the implicants
};

//Extract Minimal Expression from Prime Implicants
void findMinimalExpression(set<int> MinTerm, set<set<int>> prime, set<set<int>> accumulator){
    if(MinTerm.empty())
        Expression.insert(accumulator);
    else{
        for(auto i : MinTerm){
            for(auto j : prime){ 
                if(j.find(i) == j.end())
                    continue;
                set<set<int>> tempAcc = accumulator;
                set<int> tempMinTerm = MinTerm;
                set<set<int>> tempPrime = prime;

                tempAcc.insert(j);

                for(auto k : j)
                    if(tempMinTerm.find(k)!=tempMinTerm.end())
                        tempMinTerm.erase(tempMinTerm.find(k));

                tempPrime.erase(tempPrime.find(j));
                findMinimalExpression(tempMinTerm, tempPrime, tempAcc);
            }
        }
    }
}

 //remove large number of expressions, filtering by the number of terms and the number of literals
void minNumTerm(){
    int minNum = 32;
    for(auto i : Expression)
        minNum = min(minNum, (int)i.size());

    //filtering by number of terms
    for(set<set<set<int>>>::iterator it = Expression.begin(); it != Expression.end();)
        if((*it).size() > minNum)
            Expression.erase(it++);
        else
            it++;
    
    int maxLiteral = 0;
    for(auto i : Expression){
        int temp = 0;
        for(auto j : i)
            temp+=(int)j.size();
        maxLiteral=max(maxLiteral, temp);
    }

    //filtering by the number of literals
    for(set<set<set<int>>>::iterator it = Expression.begin(); it != Expression.end();){
        int temp = 0;
        for(auto i : (*it)){
            temp+=(int)i.size();
        }
        if(temp < maxLiteral)
            Expression.erase(it++);
        else
            it++;
    }
}


//convert a implicant to vector
vector<int> set2vec(set<int> s, int num){
    vector<int> ret;
    int minOne = *(s.begin());  //the smallest value in the implicant
    int maxOne = *(s.rbegin()); //the biggest value in the implicant

    //minterm to 0, 1 or '-'
    for(int i = num-1; i >=0; i--){
        if( (minOne & (1<<i)) == (maxOne & (1 << i)) )
            ret.push_back((minOne & (1<<i)) >> i);  //0 or 1
        else
            ret.push_back(-1);  //store -1 if it is '-'
    }
    return ret;
}

//convert a implicatn to literals
string set2str(set<int> s, int num){
    vector<int> temp = set2vec(s, num);
    string ret;
    for(int i = 0 ;i < (int)temp.size(); i++){
        if(temp[i]==1)
            ret+=literal[1][i];
        else if(temp[i] ==0 )
            ret+=literal[0][i];
    }
    return ret;
}

//number of one's in a integer
int numofOne(int x){
    int ret = 0;
    while(x){
        if((x & 1) == 1)
            ret++;
        x = x>>1;
    }
    return ret;
}

void Quine_McCluskey(int _numofVar){

    Group* Groups = new Group[_numofVar+1];

    //Sort groups by number of 1's
    for(auto& it : testMinTerm)
        Groups[numofOne(it)].push(it);

    vector<Group> alive; //current implicants

    //initial group to store in alive
    for(int i = 0 ;i <= _numofVar; i++){
        if(Groups[i].size()!=0)
            alive.push_back(Groups[i]);
    }

    //decide prime implicants by Quine-McCluskey algorithm
    while(1){

        vector<Group> next; //next stage implicants

        int sz = alive.size();


        //generate next stage implicants by comparing
        for(int i = 0 ;i < sz-1; i++){
            Group temp = alive[i].compare(alive[i+1], _numofVar); 
            if(temp.size()!=0)
                next.push_back(temp);
                 
            //store a implicant to PrimeImplicant if it is
            for(int j = 0 ;j < alive[i].size(); j++){
                set<int> s = alive[i].primeImp(j);   
                if(s.size()!=0)
                    PrimeImplicant.insert(s);
            }    
        }
        
        //Last implicants case(does not compare because it is last one)
        for(int j = 0 ;j < alive[sz-1].size(); j++){
                set<int> s = alive[sz-1].primeImp(j);
                if(s.size()!=0)
                    PrimeImplicant.insert(s);
            }    
               
        alive = next;

        //break if there is no alive implicants
        if(alive.size()==0)
            break;  
    }

    set<int> restMinTerm = testMinTerm;  //Minterms except Essential prime implicants
    set<set<int>> restPrimeImplicant = PrimeImplicant; //Prime Implicants except Essential prime implicants


    //find prime implicants by prime implicant chart
    for(auto& i : testMinTerm){
        int cnt=0;
        set<int> temp;
        for(auto& j : PrimeImplicant){
            if(j.find(i)!=j.end()){
                cnt++;
                temp = j;
            }
        }
        if(cnt==1){ 
            EssentialPrimeImplicant.insert(temp);
            if(restPrimeImplicant.find(temp)!= restPrimeImplicant.end())
                restPrimeImplicant.erase(restPrimeImplicant.find(temp));    
            for(auto k : temp)
                if(restMinTerm.find(k) != restMinTerm.end())
                    restMinTerm.erase(restMinTerm.find(k));             
        }
    }
    
    set<set<int>> acc = EssentialPrimeImplicant;

    findMinimalExpression(restMinTerm, restPrimeImplicant, acc);
    
    minNumTerm();
}

int main() {
    while(1){
        int numofVar;
        cout<<"테스트하고자 하는 변수 개수를 입력하세요(3, 4, 5만 허용): ";
        cin >> numofVar;
        if(numofVar >5 && numofVar <3){
            cout<<"잘못된 입력입니다. 다시 입력하세요"<<endl;
            continue;
        }
        
        //set initializations
        testMinTerm.clear();
        PrimeImplicant.clear();
        EssentialPrimeImplicant.clear();
        Expression.clear();

        for(auto i : StoredMinTerm[numofVar-3])
            testMinTerm.insert(i);
    
        Quine_McCluskey(numofVar);

        //minimal expression print out
        cout<<"num of Expression: "<<Expression.size()<<endl;
        for(auto i : Expression){
            for(auto j : i){
                cout<<set2str(j, numofVar);
                if(j != *(i.rbegin()))
                    cout<<" + ";
            }
            cout<<endl<<"------------------------------------------------------------"<<endl;
        }
    }
    return 0; 
}
