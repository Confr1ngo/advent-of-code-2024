#include<bits/stdc++.h>
using namespace std;
namespace AOCHeader{
	namespace Print{
		template<typename T> void print(vector<vector<T>> v){
			for (auto &row:v){
				for (auto &element:row) cout<<"'"<<element<<"' ";
				cout<<endl;
			}
		}
		template<typename T> void print(vector<T> v){
			for (auto &element:v) cout<<"'"<<element<<"' ";
			cout<<endl;
		}
	}
	using namespace Print;
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
	vector<vector<char>> readchars(string filename){
		ifstream ifs(filename);
		vector<vector<char>> result;
		string s;
		while (getline(ifs,s)){
			s=purge(s);
			if (s.empty()) continue;
			vector<char> row;
			for (char c:s) row.emplace_back(c);
			result.emplace_back(row);
		}
		ifs.close();
		return result;
	}
	vector<string> readstrings(string filename){
		ifstream ifs(filename);
		vector<string> result;
		string s;
		while (getline(ifs,s)){
			if (purge(s)=="") continue;
			result.emplace_back(purge(s));
		}
		ifs.close();
		return result;
	}
	vector<string> get_regex_searches(string s,regex reg){
		vector<string> result;
		smatch m;
		while (regex_search(s,m,reg)){
			result.emplace_back(m.str());
			s=m.suffix().str();
		}
		return result;
	}
	vector<pair<int,vector<string>>> get_regex_search_groups(string s,regex reg,vector<int> required){
		vector<pair<int,vector<string>>> result;
		smatch m;
		int last_matched=-1;
		while (true){
			string next=s.substr(last_matched+1);
			if (regex_search(next,m,reg)){
				vector<string> element;
				for (int i:required) element.emplace_back(m[i]);
				result.emplace_back(m[0].first-next.begin()+last_matched+1,element);
				last_matched=m[0].first-next.begin()+last_matched+1;
			}
			else return result;
		}
	}
	string concat(vector<string> strings){
		string result;
		for (string s:strings) result+=s;
		return result;
	}
}
using namespace AOCHeader;
const string filename="03.txt";
namespace PartA{
	void main(){
		auto strings=readstrings(filename);
		int ans=0;
		for (string s:strings){
			auto groups=get_regex_search_groups(s,regex("mul\\((\\d+),(\\d+)\\)"),{1,2});
			for (auto group:groups){
				ans+=str2int(group.second[0])*str2int(group.second[1]);
			}
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	void main(){
		string s=concat(readstrings(filename));
		bool enabled=true;
		int ans=0,pos=0;
		auto groups=get_regex_search_groups(s,regex("mul\\((\\d+),(\\d+)\\)"),{1,2});
		auto enable=get_regex_search_groups(s,regex("do()"),{});
		auto disable=get_regex_search_groups(s,regex("don't()"),{});
		while (groups.size()){
			if (enable.size() && enable[0].first==pos){
				enable.erase(enable.begin());
				enabled=true;
			}
			if (disable.size() && disable[0].first==pos){
				disable.erase(disable.begin());
				enabled=false;
			}
			if (groups[0].first==pos){
				if (enabled) ans+=str2int(groups[0].second[0])*str2int(groups[0].second[1]);
				groups.erase(groups.begin());
			}
			pos++;
		}
		cout<<ans<<endl;
	}
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}