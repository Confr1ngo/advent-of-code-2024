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
const string filename="09.txt";
namespace PartA{
	int p[200010],pos,cnt,l=1;
	void main(){
		memset(p,0xff,sizeof(p));
		string s=readstrings(filename)[0];
		for (int i=0;i<(int)s.size();i++){
			if (i&1){
				for (int j=1;j<=s[i]-'0';j++){
					p[++pos]=-1;
				}
			}
			else{
				for (int j=1;j<=s[i]-'0';j++){
					p[++pos]=cnt;
				}
				cnt++;
			}
		}
		while (pos>l){
			while (~p[l] && pos>l) l++;
			if (pos==l) break;
			swap(p[l],p[pos]);
			pos--;
		}
		long long ans=0;
		for (int i=1;i<=200000;i++){
			if (p[i]>=0) ans+=(i-1)*p[i];
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	vector<pair<int,int>> v;
	int id,idx[10010];
	void main(){
		string s=readstrings(filename)[0];
		for (int i=0;i<(int)s.size();i++){
			if (i%2==1 && s[i]!='0') v.emplace_back(s[i]-'0',-1);
			if (i%2==0) v.emplace_back(s[i]-'0',id++);
		}
		while (id--){
			int pos;
			for (pos=0;pos<(int)v.size();pos++){
				if (v[pos].second==id) break;
			}
			for (int i=0;i<(int)v.size();i++){
				if (i==pos) break;
				if (v[i].second==-1 && v[i].first>=v[pos].first){
					int temp_len=v[pos].first,temp_id=v[pos].second;
					v[pos].second=-1;
					if (pos!=(int)v.size()-1 && v[pos+1].second==-1){
						v[pos].first+=v[pos+1].first;
						v.erase(v.begin()+pos+1);
					}
					if (pos!=0 && v[pos-1].second==-1){
						v[pos-1].first+=v[pos].first;
						v.erase(v.begin()+pos);
					}
					v.insert(v.begin()+i,make_pair(temp_len,temp_id));
					v[i+1].first-=temp_len;
					if (v[i+1].first==0) v.erase(v.begin()+i+1);
					break;
				}
			}
		}
		long long ans=0;
		int p=0;
		for (int i=0;i<(int)v.size();i++){
			if (v[i].second==-1) p+=v[i].first;
			else{
				for (int j=1;j<=v[i].first;j++){
					ans+=v[i].second*(p++);
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