#include <vector>
#include <algorithm>
using namespace std;

int main(){
    vector<int> cardinal={1,2,3,4,5,6,7,8,9,10};
    vector<int>::const_iterator iter=cardinal.begin();
    vector<int>::const_iterator iter_end=cardinal.end();
    int total_elements=1;
    for_each(cardinal.begin(), cardinal.end(), [&total_elements](int i){
        total_elements*=i;
    });
}
