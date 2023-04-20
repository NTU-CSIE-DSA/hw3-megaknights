#include <bits/stdc++.h>
using namespace std;

signed main(){
    freopen("data", "w+t", stdout);
    cout<<"@subtask samples\n\
manual sample1.in\n\
manual sample2.in\n\
\n\
@subtask small\n";
	cout<<"@include samples\n";
    for(int i=1; i<=12; ++i)cout<<"gen 1 "<<i<<endl;
	cout<<"\n@subtask alive\n";
	cout<<"manual sample1.in\n";
	for(int i=1; i<=12; ++i)cout<<"gen 2 "<<i<<endl;
    cout<<"\n@subtask all\n";
	cout<<"@include small\n";
	cout<<"@include alive\n";
    for(int i=1; i<=12; ++i)cout<<"gen 3 "<<i<<endl;
}
