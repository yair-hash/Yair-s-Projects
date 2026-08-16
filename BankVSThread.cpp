#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <random>
#include <vector>
using namespace std;
const int DEFAULT_BALANCE=100;
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
    int result[15][16];
    bank MyBank = bank();
    //begin 15 experiments
    for(int experiment = 0;experiment<15;experiment++){
        //init balances of clients and the bank
        MyBank.bankBalance=DEFAULT_BALANCE;
        vector<client> clientList;
        vector<thread> threads;
        //insert new clients into the list
        for(int i=0;i<15;i++){
            clientList.push_back({0,i});
        }
        // create a thread for each client for trying to witdraw money out of the bank
        for(int i=0;i<15;i++){
            threads.push_back(thread(&bank::withdraw,&MyBank,15,ref(clientList.at(i))));
        }
        //closing the thread
        for(auto& t:threads)
            t.join();  
        //document the result    
        for (int i = 0; i < 15; i++)
        {
        result[experiment][i]=clientList.at(i).balance;  
        }
        result[experiment][15]=MyBank.bankBalance;
    } 
    //printing the results
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++)
        {
            cout<<result[i][j]<<" ";
        }
        cout<<"bank's balance is: "<<result[i][15]<< endl;
        
    }
    return 0;
}