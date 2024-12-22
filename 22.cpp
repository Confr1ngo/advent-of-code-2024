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
const string filename="22.txt";
namespace PartA{
	const long long mod=16777216;
	long long operate(long long secret){
		secret=secret^(secret*64)%mod;
		secret=secret^(secret/32)%mod;
		secret=secret^(secret*2048)%mod;
		return secret;
	}
	void main(){
		long long sum=0;
		auto input=readnumbers(filename);
		for (auto &line:input){
			long long num=line[0];
			for (int i=1;i<=2000;i++){
				num=operate(num);
			}
			sum+=num;
		}
		cout<<sum<<endl;
	}
}
namespace PartB{
	const long long mod=16777216;
	long long operate(long long secret){
		secret=secret^(secret*64)%mod;
		secret=secret^(secret/32)%mod;
		secret=secret^(secret*2048)%mod;
		return secret;
	}
	map<tuple<int,int,int,int>,long long> sum;
	void update(long long num,int len){
		map<tuple<int,int,int,int>,long long> cur;
		vector<long long> v={num};
		vector<long long> diff;
		for (int i=1;i<len;i++){
			v.emplace_back(operate(v.back()));
			diff.emplace_back(v[i]%10-v[i-1]%10);
		}
		for (int i=0;i<len-4;i++){
		    auto diffv=make_tuple(diff[i],diff[i+1],diff[i+2],diff[i+3]);
			if (!cur.count(diffv)){
				cur[diffv]=v[i+4]%10;
			}
		}
		for (auto &i:cur){
			sum[i.first]+=i.second;
		}
	}
	void main(){
		long long ans=0;
		auto input=readnumbers(filename);
		for (auto &line:input){
			update(line[0],2000);
		}
		for (auto i:sum){
			ans=max(ans,i.second);
		}
		cout<<ans<<endl;
	}
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}