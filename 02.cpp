#include<bits/stdc++.h>
using namespace std;
namespace AOCHeader{
	template<typename T> struct NotBool:public true_type{};
	template<> struct NotBool<bool>:public false_type{};
	template<typename T> vector<enable_if_t<NotBool<T>::value,T>> get_column(vector<vector<T>> mp,int column){
		vector<T> result;
		for (auto &row:mp) result.emplace_back(row[column]);
		return result;
	}
	int str2int(string s){
		int result=0;
		for (auto &c:s) result=result*10+c-'0';
		return result;
	}
	string purge(string s,bool hard=false){
		while (s.size() && s[0]==' ') s.erase(s.begin());
		while (s.size() && (s.back()==' ' || s.back()=='\r' || s.back()=='\n')) s.pop_back();
		while (hard && s.find(" ")!=string::npos) s.erase(s.find(" "),1);
		return s;
	}
	vector<string> split(string s,string pattern){
		vector<string> result;
		while (s.find(pattern)!=string::npos){
			int pos=s.find(pattern);
			if (pos) result.emplace_back(s.substr(0,s.find(pattern)));
			s=s.substr(s.find(pattern)+1);
		}
		if (s.size()) result.emplace_back(s);
		return result;
	}
	template<typename T> int count(vector<T> mp,T value){
		int result=0;
		for (auto &e:mp) if (e==value) result++;
		return result;
	}
	vector<vector<int>> readnumbers(string filename){
		ifstream ifs(filename);
		vector<vector<int>> result;
		string s;
		while (getline(ifs,s)){
			s=purge(s);
			if (s.empty()) continue;
			vector<int> row;
			vector<string> numbers=split(s," ");
			for (auto &number:numbers) row.emplace_back(str2int(number));
			result.emplace_back(row);
		}
		ifs.close();
		return result;
	}
	vector<vector<char>> readmap(string filename){
		ifstream ifs(filename);
		vector<vector<char>> result;
		string s;
		while (getline(ifs,s)){
			s=purge(s,true);
			if (s.empty()) continue;
			vector<char> row;
			for (char c:s) row.emplace_back(c);
			result.emplace_back(row);
		}
		ifs.close();
		return result;
	}
}
template<typename T> void print(vector<vector<T>> v){
	for (auto &row:v){
		for (auto &element:row) cout<<"'"<<element<<"' ";
		cout<<endl;
	}
}
using namespace AOCHeader;
const string filename="02.txt";
namespace PartA{
	bool check(vector<int> row){
		int side=row[0]<row[1];
		for (int i=0;i<(int)row.size()-1;i++){
			if ((row[i]<row[i+1])!=side) return false;
			if (abs(row[i]-row[i+1])>3 || row[i]==row[i+1]) return false;
		}
		return true;
	}
	void main(){
		int ans=0;
		auto numbers=readnumbers(filename);
		for (auto &row:numbers){
			if (check(row)) ans++;
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	bool check(vector<int> row){
		int side=row[0]<row[1];
		for (int i=0;i<(int)row.size()-1;i++){
			if ((row[i]<row[i+1])!=side) return false;
			if (abs(row[i]-row[i+1])>3 || row[i]==row[i+1]) return false;
		}
		return true;
	}
	void main(){
		int ans=0;
		auto numbers=readnumbers(filename);
		for (auto &row:numbers){
			if (check(row)) ans++;
			else{
				auto cpy=row;
				for (int i=0;i<(int)cpy.size();i++){
					row.erase(row.begin()+i);
					if (check(row)){
						ans++;
						break;
					}
					row=cpy;
				}
			}
		}
		cout<<ans<<endl;
	}
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}