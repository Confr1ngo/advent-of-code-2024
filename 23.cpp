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
const string filename="23.txt";
namespace PartA{
	bool flag[700][700];
	int get_id(string s){
		return (s[0]-'a')*26+(s[1]-'a');
	}
	void main(){
		auto input=readstrings(filename);
		for (string i:input){
			flag[get_id(i.substr(0,2))][get_id(i.substr(3,2))]=true;
			flag[get_id(i.substr(3,2))][get_id(i.substr(0,2))]=true;
		}
		int cnt=0;
		for (int i=0;i<=675;i++){
			for (int j=i+1;j<=675;j++){
				for (int k=j+1;k<=675;k++){
					if (i==j || j==k || i==k) continue;
					if (i/26!=19 && j/26!=19 && k/26!=19) continue;
					if (flag[i][j] && flag[i][k] && flag[j][k]){
						cnt++;
					}
				}
			}
		}
		cout<<cnt<<endl;
	}
}
namespace PartB{
	unordered_map<string,unordered_set<string>> e;
	unordered_set<string> node;
	vector<string> ans;
	int maxn;
	void BronKerbosch(vector<string>& r,vector<string>& p,vector<string>& x){
		if (p.empty() && x.empty()){
			if ((int)r.size()>maxn){
				maxn=r.size();
				ans=r;
			}
			return;
		}
		for (int i=0;i<(int)p.size();i++){
			vector<string> r1=r;
			r1.emplace_back(p[i]);
			vector<string> p1;
			for (string j:p){
				if (e[p[i]].count(j)){
					p1.emplace_back(j);
				}
			}
			vector<string> x1;
			for (string j:x){
				if (e[p[i]].count(j)){
					x1.emplace_back(j);
				}
			}
			BronKerbosch(r1,p1,x1);
			p.erase(p.begin()+i);
			x.emplace_back(p[i]);
		}
	}
	void main(){
		auto input=readstrings(filename);
		for (string i:input){
			e[i.substr(0,2)].emplace(i.substr(3));
			e[i.substr(3)].emplace(i.substr(0,2));
			node.emplace(i.substr(0,2));
			node.emplace(i.substr(3));
		}
		vector<string> r,p,x;
		for (string i:node){
			p.emplace_back(i);
		}
		BronKerbosch(r,p,x);
		sort(ans.begin(),ans.end());
		for (int i=0;i<(int)ans.size();i++){
			if (i) cout<<",";
			cout<<ans[i];
		}
		cout<<endl;
	}
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}