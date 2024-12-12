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
const string filename="12.txt";
namespace PartA{
	const int dx[4]={1,-1,0,0};
	const int dy[4]={0,0,-1,1};
	vector<vector<char>> mp;
	bool vis[150][150];
	int n,m,ans;
	bool in_range(int x,int y){
		return (x>=0 && x<n && y>=0 && y<m);
	}
	int solve(int x,int y){
		int c=0;
		set<pair<int,int>> areas;
		queue<pair<int,int>> q;
		q.emplace(x,y);
		vis[x][y]=true;
		while (!q.empty()){
			auto now=q.front();q.pop();
			areas.emplace(now);
			int x=now.first,y=now.second;
			for (int i=0;i<4;i++){
				int nx=x+dx[i],ny=y+dy[i];
				if (in_range(nx,ny) && !vis[nx][ny] && mp[nx][ny]==mp[x][y]){
					vis[nx][ny]=true;
					q.emplace(nx,ny);
				}
			}
		}
		for (auto i:areas){
			for (int j=0;j<4;j++){
				int nx=i.first+dx[j],ny=i.second+dy[j];
				if (!areas.count(make_pair(nx,ny))) c++;
			}
		}
		return c*areas.size();
	}
	void main(){
		mp=readchars(filename);
		n=mp.size();
		m=mp[0].size();
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (!vis[i][j]) ans+=solve(i,j);
			}
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	const int dx[4]={1,-1,0,0};
	const int dy[4]={0,0,-1,1};
	vector<vector<char>> mp;
	bool vis[150][150];
	int n,m,ans;
	int count(set<int> s){
		if (s.size()==0) return 0;
		vector<int> v;
		for (auto i:s) v.emplace_back(i);
		int pre=-1,cnt=0;
		for (int i=0;i<(int)v.size();i++){
			if (pre!=-1 && v[i]!=pre+1) cnt++;
			pre=v[i];
		}
		return cnt+1;
	}
	bool in_range(int x,int y){
		return (x>=0 && x<n && y>=0 && y<m);
	}
	int solve(int x,int y){
		int c=0;
		set<pair<int,int>> areas;
		queue<pair<int,int>> q;
		q.emplace(x,y);
		vis[x][y]=true;
		while (!q.empty()){
			auto now=q.front();q.pop();
			areas.emplace(now);
			int x=now.first,y=now.second;
			for (int i=0;i<4;i++){
				int nx=x+dx[i],ny=y+dy[i];
				if (in_range(nx,ny) && !vis[nx][ny] && mp[nx][ny]==mp[x][y]){
					vis[nx][ny]=true;
					q.emplace(nx,ny);
				}
			}
		}
		set<int> edges_r[2][150],edges_c[2][150];
		for (auto i:areas){
			for (int j=0;j<4;j++){
				int nx=i.first+dx[j],ny=i.second+dy[j];
				if (!areas.count(make_pair(nx,ny))){
					if (j==0) edges_r[0][nx].emplace(ny);
					if (j==1) edges_r[1][i.first].emplace(ny);
					if (j==2) edges_c[0][i.second].emplace(nx);
					if (j==3) edges_c[1][ny].emplace(nx);
				}
			}
		}
		for (int k=0;k<2;k++){
			for (int i=0;i<=n;i++) c+=count(edges_r[k][i]);
			for (int i=0;i<=m;i++) c+=count(edges_c[k][i]);
		}
		return c*areas.size();
	}
	void main(){
		mp=readchars(filename);
		n=mp.size();
		m=mp[0].size();
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (!vis[i][j]) ans+=solve(i,j);
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