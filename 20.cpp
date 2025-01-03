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
const string filename="20.txt";
namespace PartA{
	const int dx[4]={1,-1,0,0};
	const int dy[4]={0,0,-1,1};
	int n,m,startx,starty,endx,endy,ans;
	vector<vector<char>> mp;
	int dist[150][150];
	bool in_range(int x,int y){
		return !(x<0 || x>=n || y<0 || y>=m);
	}
	void main(){
		mp=readchars(filename);
		n=mp.size();m=mp[0].size();
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]=='S'){
					startx=i;starty=j;
					mp[i][j]='.';
				}
				if (mp[i][j]=='E'){
					endx=i;endy=j;
					mp[i][j]='.';
				}
			}
		}
		memset(dist,0x3f,sizeof(dist));
		dist[startx][starty]=0;
		queue<pair<int,int>> q;
		q.emplace(startx,starty);
		while (!q.empty()){
			auto now=q.front();q.pop();
			int x=now.first,y=now.second;
			for (int i=0;i<4;i++){
				int nx=x+dx[i],ny=y+dy[i];
				if (in_range(nx,ny) && mp[nx][ny]!='#'){
					if (dist[nx][ny]>dist[x][y]+1){
						dist[nx][ny]=dist[x][y]+1;
						q.emplace(nx,ny);
					}
				}
			}
		}
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]=='#') continue;
				for (int ddx=-2;ddx<=2;ddx++){
					for (int ddy=-2;ddy<=2;ddy++){
						if (abs(ddx)+abs(ddy)>2) continue;
						int nx=i+ddx,ny=j+ddy;
						if (!in_range(nx,ny)) continue;
						if (mp[nx][ny]=='#') continue;
						int skip_dist=dist[i][j]-dist[nx][ny]-abs(ddx)-abs(ddy);
						if (skip_dist>=100) ans++;
					}
				}
			}
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	const int dx[4]={1,-1,0,0};
	const int dy[4]={0,0,-1,1};
	int n,m,startx,starty,endx,endy,ans;
	vector<vector<char>> mp;
	int dist[150][150];
	bool in_range(int x,int y){
		return !(x<0 || x>=n || y<0 || y>=m);
	}
	void main(){
		mp=readchars(filename);
		n=mp.size();m=mp[0].size();
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]=='S'){
					startx=i;starty=j;
					mp[i][j]='.';
				}
				if (mp[i][j]=='E'){
					endx=i;endy=j;
					mp[i][j]='.';
				}
			}
		}
		memset(dist,0x3f,sizeof(dist));
		dist[startx][starty]=0;
		queue<pair<int,int>> q;
		q.emplace(startx,starty);
		while (!q.empty()){
			auto now=q.front();q.pop();
			int x=now.first,y=now.second;
			for (int i=0;i<4;i++){
				int nx=x+dx[i],ny=y+dy[i];
				if (in_range(nx,ny) && mp[nx][ny]!='#'){
					if (dist[nx][ny]>dist[x][y]+1){
						dist[nx][ny]=dist[x][y]+1;
						q.emplace(nx,ny);
					}
				}
			}
		}
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]=='#') continue;
				for (int ddx=-20;ddx<=20;ddx++){
					for (int ddy=-20;ddy<=20;ddy++){
						if (abs(ddx)+abs(ddy)>20) continue;
						int nx=i+ddx,ny=j+ddy;
						if (!in_range(nx,ny)) continue;
						if (mp[nx][ny]=='#') continue;
						int skip_dist=dist[i][j]-dist[nx][ny]-abs(ddx)-abs(ddy);
						if (skip_dist>=100) ans++;
					}
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