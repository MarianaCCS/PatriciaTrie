#include "PatriciaTrie.h"
#include <vector>
using namespace std;

int main(){
    PatriciaTrie* patricia = new PatriciaTrie;
    vector<string> diccionario = {"romano", "roma", "romario", "rosario", "rata", "amor", "amorfo", "amorcito", "amiga"};

    for(string word : diccionario) patricia->insert(word);

    /*
    patricia->insert("amiga");
    patricia->insert("amor"); 
    patricia->insert("amorcito");
    */
    /*
    patricia->insert("a");
    patricia->insert("zapallito");
    patricia->insert("zapallo");
    patricia->insert("zapal");
    patricia->insert("zapallos");
*/
    patricia->print();
    cout<<patricia->find("rata")<<" ";
    for(string word : diccionario) cout<<patricia->find(word)<<" ";
    cout<<endl<<patricia->find("rata")<<endl;
    /*
    cout<<patricia->find("abba")<<endl;
    cout<<patricia->find("zapal")<<endl;
    cout<<patricia->find("zapallito")<<endl;
    cout<<patricia->find("zapallo")<<endl;
    cout<<patricia->find("zapallos")<<endl;
 */
    return 0;
}