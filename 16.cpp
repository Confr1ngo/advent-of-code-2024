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
const string filename="16.txt";
namespace PartA{
	vector<vector<char>> mp;
	int minn[210][210][4],n,m;
	const int dx[4]={1,0,-1,0};
	const int dy[4]={0,-1,0,1};
	bool in_range(int x,int y){
		return x>=0 && x<n && y>=0 && y<m;
	}
	int solve(){
		mp=readchars(filename);
		n=mp.size();m=mp[0].size();
		int startx=0,starty=0,endx=0,endy=0;
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]=='S'){
					mp[i][j]='.';
					startx=i;starty=j;
				}
				if (mp[i][j]=='E'){
					mp[i][j]='.';
					endx=i;endy=j;
				}
			}
		}
		memset(minn,0x3f,sizeof(minn));
		queue<tuple<int,int,int,int>> q;
		q.emplace(startx,starty,3,0);
		minn[startx][starty][3]=0;
		while (!q.empty()){
			auto now=q.front();q.pop();
			int x=get<0>(now),y=get<1>(now),dir=get<2>(now),sum=get<3>(now);
			if (in_range(x+dx[dir],y+dy[dir])){
				int nx=x+dx[dir],ny=y+dy[dir];
				if (mp[nx][ny]=='.' && minn[nx][ny][dir]>sum+1){
					minn[nx][ny][dir]=sum+1;
					q.emplace(nx,ny,dir,sum+1);
				}
			}
			if (minn[x][y][(dir+3)%4]>sum+1000){
				minn[x][y][(dir+3)%4]=sum+1000;
				q.emplace(x,y,(dir+3)%4,sum+1000);
			}
			if (minn[x][y][(dir+1)%4]>sum+1000){
				minn[x][y][(dir+1)%4]=sum+1000;
				q.emplace(x,y,(dir+1)%4,sum+1000);
			}
		}
		int ans=0x3f3f3f3f;
		for (int i=0;i<4;i++){
			ans=min(ans,minn[endx][endy][i]);
		}
		return ans;
	}
	void main(){
		cout<<solve()<<endl;
	}
}
namespace PartB{
	vector<vector<char>> mp;
	int minn[210][210][4],n,m;
	bool mark[210][210];
	const int dx[4]={1,0,-1,0};
	const int dy[4]={0,-1,0,1};
	bool in_range(int x,int y){
		return x>=0 && x<n && y>=0 && y<m;
	}
	void main(){
		int ans=PartA::solve();
		mp=readchars(filename);
		n=mp.size();m=mp[0].size();
		int startx=0,starty=0,endx=0,endy=0;
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]=='S'){
					mp[i][j]='.';
					startx=i;starty=j;
				}
				if (mp[i][j]=='E'){
					mp[i][j]='.';
					endx=i;endy=j;
				}
			}
		}
		memset(minn,0x3f,sizeof(minn));
		queue<tuple<int,int,int,int,vector<pair<int,int>>>> q;
		vector<pair<int,int>> temp={{startx,starty}};
		q.emplace(startx,starty,3,0,temp);
		minn[startx][starty][3]=0;
		while (!q.empty()){
			auto now=q.front();q.pop();
			int x=get<0>(now),y=get<1>(now),dir=get<2>(now),sum=get<3>(now);
			auto path=get<4>(now);
			if (x==endx && y==endy && sum==ans){
				for (auto i:path){
					mark[i.first][i.second]=true;
				}
				mark[x][y]=true;
				continue;
			}
			if (in_range(x+dx[dir],y+dy[dir])){
				int nx=x+dx[dir],ny=y+dy[dir];
				if (mp[nx][ny]=='.' && minn[nx][ny][dir]>=sum+1){
					minn[nx][ny][dir]=sum+1;
					path.emplace_back(nx,ny);
					q.emplace(nx,ny,dir,sum+1,path);
					path.pop_back();
				}
			}
			if (minn[x][y][(dir+3)%4]>=sum+1000){
				minn[x][y][(dir+3)%4]=sum+1000;
				q.emplace(x,y,(dir+3)%4,sum+1000,path);
			}
			if (minn[x][y][(dir+1)%4]>=sum+1000){
				minn[x][y][(dir+1)%4]=sum+1000;
				q.emplace(x,y,(dir+1)%4,sum+1000,path);
			}
		}
		int cnt=0;
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
			    if (mark[i][j]) cnt++;
			}
		}
		cout<<cnt<<endl;
	}
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}