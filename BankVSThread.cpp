#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <random>
#include <vector>
using namespace std;
struct client{
    int balance;
    int id;
    
};
class bank{
    public:
        int bankBalance;
        mutex mtx;
    bank(){
        bankBalance=100;
    }
  
    void withdraw(int amount,client& id)
    {
        lock_guard<mutex> lock(mtx);
        if(amount>bankBalance)
            return;
        if(amount<=0)
            return;    
        bankBalance -=amount;
        id.balance+=amount;
    };    
};
int main(){
    bank MyBank = bank();
    vector<client> clientlist;
    vector<thread> threads;
    for(int i=0;i<15;i++){
        clientlist.push_back({0,i});
    }
    for(int i=0;i<15;i++)
    {
        threads.push_back(thread(&bank::withdraw,&MyBank,15,ref(clientlist.at(i))));
    }
    for(auto& t:threads)
        t.join();
    for (int i = 0; i < 15; i++)
    {
        cout<<"client "<< i << ": has a balance of: "<< clientlist.at(i).balance<<endl;
    }
    cout<<" Final bank Balance: "<< MyBank.bankBalance<<endl;
    return 0;
}