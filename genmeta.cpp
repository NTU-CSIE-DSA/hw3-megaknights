#include <bits/stdc++.h>
using namespace std;

string toS(int n){
    string s;
    s+='0'+n/10;
    s+='0'+n%10;
    return s;
}

signed main(){
    cout<<"{\n\
    \"name\": \"Jumping Mega Knights\",\n\
    \"timeLimit\": 1.0,\n\
    \"memLimit\": 1048576,\n\
    \"testdata\": [\n";
    string score[4]={"0","15","20","65"};
    string s, t, s0="", out="";
    int i=0;
    while(cin>>s>>t){
        if(s0!=s){
            if(s0!="")out+="]\n        },\n", ++i;
            out+="        {\n\
            \"points\": "+score[i]+",\n\
            \"tests\": [";
            s0=s;
        }
        out+='"'+t+"\", ";
    }
    out+="]\n        }\n";
    out+="    ]\n}";
    for(int i=0; i<(int)out.size()-2; ++i)if(out[i]==','&&out[i+1]==' '&&out[i+2]==']'){
        out[i]=' ';
    }
    cout<<out;
}
