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
	template<typename T> size_t index(vector<T> v,T element){
		for (size_t i=0;i<v.size();i++){
			if (v[i]==element) return i;
		}
		return -1;
	}
	long long str2int(string s){
		long long result=0;
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
			size_t pos=s.find(pattern);
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
	vector<vector<long long>> readnumbers(string filename){
		ifstream ifs(filename);
		vector<vector<long long>> result;
		string s;
		while (getline(ifs,s)){
			s=purge(s);
			if (s.empty()) continue;
			vector<long long> row;
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
const string filename="11.txt";
namespace PartA{
	map<long long,long long> mp[76];
	long long count(long long num,int stp){
		if (stp==0) return 1;
		if (mp[stp].count(num)) return mp[stp][num];
		long long res;
		string s=to_string(num);
		int len=s.size();
		if (num==0) res=count(1,stp-1);
		else if (len%2==0){
			long long num1=str2int(s.substr(0,len/2));
			long long num2=str2int(s.substr(len/2));
			res=count(num1,stp-1)+count(num2,stp-1);
		}
		else res=count(num*2024,stp-1);
		mp[stp][num]=res;
		return res;
	}
	void main(){
		auto num=readnumbers(filename)[0];
		long long ans=0;
		for (long long i:num){
			ans+=count(i,25);
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	map<long long,long long> mp[76];
	long long count(long long num,int stp){
		if (stp==0) return 1;
		if (mp[stp].count(num)) return mp[stp][num];
		long long res;
		string s=to_string(num);
		int len=s.size();
		if (num==0) res=count(1,stp-1);
		else if (len%2==0){
			long long num1=str2int(s.substr(0,len/2));
			long long num2=str2int(s.substr(len/2));
			res=count(num1,stp-1)+count(num2,stp-1);
		}
		else res=count(num*2024,stp-1);
		mp[stp][num]=res;
		return res;
	}
	void main(){
		auto num=readnumbers(filename)[0];
		long long ans=0;
		for (long long i:num){
			ans+=count(i,75);
		}
		cout<<ans<<endl;
	}
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}