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
const string filename="08.txt";
namespace PartA{
	bool vis[60][60];
	int ans,n,m;
	vector<pair<int,int>> v[128];
	bool in_range(int x,int y){
		return (x>=0 && y>=0 && x<n && y<m);
	}
	void main(){
		auto mp=readchars(filename);
		n=mp.size();
		m=mp[0].size();
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]!='.') v[(int)mp[i][j]].emplace_back(i,j);
			}
		}
		for (int i=0;i<128;i++){
			for (int j=0;j<(int)v[i].size();j++){
				for (int k=j+1;k<(int)v[i].size();k++){
					int nx1=v[i][j].first-(v[i][k].first-v[i][j].first);
					int nx2=v[i][k].first+(v[i][k].first-v[i][j].first);
					int ny1=v[i][j].second-(v[i][k].second-v[i][j].second);
					int ny2=v[i][k].second+(v[i][k].second-v[i][j].second);
					if (in_range(nx1,ny1)) vis[nx1][ny1]=true;
					if (in_range(nx2,ny2)) vis[nx2][ny2]=true;
				}
			}
		}
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (vis[i][j]) ans++;
			}
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	bool vis[60][60];
	int ans,n,m;
	vector<pair<int,int>> v[128];
	bool in_range(int x,int y){
		return (x>=0 && y>=0 && x<n && y<m);
	}
	void main(){
		auto mp=readchars(filename);
		n=mp.size();
		m=mp[0].size();
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]!='.') v[(int)mp[i][j]].emplace_back(i,j);
			}
		}
		for (int i=0;i<128;i++){
			for (int j=0;j<(int)v[i].size();j++){
				for (int k=j+1;k<(int)v[i].size();k++){
					int dx=v[i][k].first-v[i][j].first,dy=v[i][k].second-v[i][j].second;
					int nx=v[i][j].first,ny=v[i][j].second;
					while (in_range(nx,ny)){
						vis[nx][ny]=true;
						nx-=dx;ny-=dy;
					}
					nx=v[i][j].first;ny=v[i][j].second;
					while (in_range(nx,ny)){
						vis[nx][ny]=true;
						nx+=dx;ny+=dy;
					}
				}
			}
		}
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (vis[i][j]) ans++;
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