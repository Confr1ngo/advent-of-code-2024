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
	template<typename T> int index(vector<T> v,T element){
		for (int i=0;i<(int)v.size();i++){
			if (v[i]==element) return i;
		}
		return -1;
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
}
using namespace AOCHeader;
const string filename="05.txt";
namespace PartA{
	void main(){
		auto mp=readstrings(filename);
		vector<pair<int,int>> condition;
		while (mp[0].find("|")!=string::npos){
			condition.emplace_back(str2int(split(mp[0],"|")[0]),str2int(split(mp[0],"|")[1]));
			mp.erase(mp.begin());
		}
		int ans=0;
		for (string s:mp){
			vector<string> split_raw=split(s,",");
			vector<int> sp;
			for (string s:split_raw) sp.emplace_back(str2int(s));
			bool flag=true;
			for (pair<int,int> p:condition){
				int pos1=index(sp,p.first),pos2=index(sp,p.second);
				if (pos1==-1 || pos2==-1) continue;
				if (pos1>pos2){
					flag=false;
					break;
				}
			}
			if (flag) ans+=sp[(int)sp.size()/2];
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	void main(){
		auto mp=readstrings(filename);
		vector<pair<int,int>> condition;
		while (mp[0].find("|")!=string::npos){
			condition.emplace_back(str2int(split(mp[0],"|")[0]),str2int(split(mp[0],"|")[1]));
			mp.erase(mp.begin());
		}
		int ans=0;
		for (string s:mp){
			vector<string> split_raw=split(s,",");
			vector<int> sp;
			for (string s:split_raw) sp.emplace_back(str2int(s));
			bool flag=true;
			for (pair<int,int> p:condition){
				int pos1=index(sp,p.first),pos2=index(sp,p.second);
				if (pos1==-1 || pos2==-1) continue;
				if (pos1>pos2){
					flag=false;
					break;
				}
			}
			if (!flag){
				while (!flag){
					flag=true;
					for (pair<int,int> p:condition){
						int pos1=index(sp,p.first),pos2=index(sp,p.second);
						if (pos1==-1 || pos2==-1) continue;
						if (pos1>pos2){
							flag=false;
							swap(sp[pos1],sp[pos2]);
						}
					}
				}
				ans+=sp[(int)sp.size()/2];
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