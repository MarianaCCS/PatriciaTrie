#include "PatriciaTrie.h"
using namespace std;

int main(){
    PatriciaTrie* patricia = new PatriciaTrie;
    patricia->insert("ab");
    patricia->insert("abeja"); 
    patricia->insert("abba");
    patricia->insert("a");
    patricia->insert("zapallito");
    patricia->insert("zapallo");
    patricia->insert("zapal");
    patricia->insert("zapallos");

    //patricia->print();

    cout<<patricia->find("a")<<endl;
    cout<<patricia->find("abbas")<<endl;
    cout<<patricia->find("zapal")<<endl;
    cout<<patricia->find("zapallito")<<endl;
    cout<<patricia->find("zapallo")<<endl;
    cout<<patricia->find("zapallos")<<endl;
 
    return 0;
}