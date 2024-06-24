#include <iostream>
#include <bitset>
#include <unordered_map>
#include <queue>

using namespace std;
class Node {
public:
    string value;
    Node* left;
    Node* right;
    Node(string c)
    {
        this->value = c;
        left = NULL;
        right = NULL;
    }
    Node()
    {
        left = NULL;
        right = NULL;
    }
};

void countFrequency(string &str,unordered_map<char,int>&mp){
    for(char ch:str){
        mp[ch]++;
    }
}

void sortByFrequency(unordered_map<char,int>&mp,priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>>&pq){
    string s1="";
    for(auto it:mp){
        s1=it.first;
        pq.push({it.second,s1});
    }
}

Node* buildTree(priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>>&pq,unordered_map<string,Node*>&mp1){
    string s1="";
    while(pq.size()>=2){
        int f1=pq.top().first;
        string ch1=pq.top().second;
        pq.pop();
        int f2=pq.top().first;
        string ch2=pq.top().second;
        pq.pop();
        s1=ch1+ch2;
        pq.push({f1+f2,s1});
        Node *p=new Node(s1);
        mp1[s1]=p;
        if(mp1.find(ch1)==mp1.end()){
            mp1[ch1]=new Node(ch1);
            p->left=mp1[ch1];
        } 
        else p->left=mp1[ch1];
        if(mp1.find(ch2)==mp1.end()) {
            mp1[ch2]=new Node(ch2);
            p->right=mp1[ch2];
        }
        else p->right=mp1[ch2];
    }
    if(pq.size()==1){
        if(s1==""){
            Node *p=new Node(pq.top().second);
            return p;
        }
        else return mp1[pq.top().second];
    }
    return NULL;
}

void generateCodes(Node *root,unordered_map<string,char>&sc,unordered_map<char,string>&cs){
    if(root==NULL) return;
    queue<pair<Node*,string>>q;
    q.push({root,""});
    while(!q.empty()){
        Node *n=q.front().first;
        string s1=q.front().second;
        if(n->left) q.push({n->left,s1+"1"});
        if(n->right) q.push({n->right,s1+"0"});
        if(!n->left && !n->right){
            sc[s1]=(n->value)[0];
            cs[(n->value)[0]]=s1;
        }
        q.pop();
    }
}

pair<string,string> getBinaryandCompressedStrings(string &str,unordered_map<char,string>&cs){
    string binary="",compressed="";
    for(char ch:str){
        binary+=bitset<8>(ch).to_string();
        compressed+=cs[ch];
    }
    return {binary,compressed};
}

string RetrieveString(string &str1,unordered_map<string,char>&sc){
    string ans="",current="";
    for(char ch:str1){
        current+=ch;
        if(sc.find(current)!=sc.end()){
            ans+=sc[current];
            current="";
        }
    }
    return ans;
}

void efficiencyCalculation(string &str,string &compressed){
    long l=str.size()*8;
    long l1=compressed.size();
    cout<<"Actual Length In Bits:"<<endl;
    cout<<l<<endl;
    cout<<"Compressed Length In Bits:"<<endl;
    cout<<l1<<endl;
    cout<<"Efficiency Of Alogrithm:"<<endl;
    cout<<(l-l1)/(l*1.0)*100.0<<"%";
}

int main()
{
  string str;
  getline(cin,str);
   if(str.size()==0){
    cout<<"String is empty!!";
    return 0;
   }
   unordered_map<char,int>mp;
   countFrequency(str,mp);
   priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>>pq;
   sortByFrequency(mp,pq);
   unordered_map<string,Node*>mp1;
   Node *father=buildTree(pq,mp1);
   unordered_map<string,char>sc;
   unordered_map<char,string>cs;
   if(mp.size()==1){
       char x=str[0];
       cs[x]="0";
       sc["0"]=x;
   }
   else{
        generateCodes(father,sc,cs);
   }
   pair<string,string>representations=getBinaryandCompressedStrings(str,cs);
   cout<<"Binary Repsentaion Of String:"<<endl;
   cout<<representations.first<<endl;
   string str1=representations.second;
   cout<<"Compressed Representation Of string:"<<endl;
   cout<<str1<<endl;
   cout<<"Retrieved String from Compressed String:"<<endl;
   string ans=RetrieveString(str1,sc);
   cout<<ans<<endl;
   if(str==ans){
       cout<<"Retrived string matched!!"<<endl;
   }
   else{
       cout<<"Some Error Occured!"<<endl;
       return 2;
   }
   cout<<endl;
   cout<<"Efficiency Calculation For Algorithm(Huffman Coding Algoritm):"<<endl;
   efficiencyCalculation(str,str1);
   return 0;
}
