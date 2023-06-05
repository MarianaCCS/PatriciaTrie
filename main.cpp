#include "PatriciaTrie.h"
using namespace std;

int main(){
    PatriciaTrie* patricia = new PatriciaTrie;
    patricia->insert("ab");
    patricia->insert("abeja");
    patricia->insert("abba");
    patricia->insert("zapallo");
    patricia->insert("zapallos");
    cout<<patricia->find("abba")<<endl;
    cout<<patricia->find("zapallo")<<endl;
    cout<<patricia->find("zapallos")<<endl;
    cout<<patricia->find("ab")<<endl;
    cout<<patricia->find("abeja")<<endl;
    cout<<patricia->find("abejas")<<endl;
    return 0;
}