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
const string filename="18.txt";
namespace PartA{
	const int dx[4]={1,-1,0,0};
	const int dy[4]={0,0,-1,1};
	const int n=71,m=71;
	vector<pair<int,int>> pos;
	int dist[71][71];
	char mp[71][71];
	int solve(){
		memset(dist,0x3f,sizeof(dist));
		queue<tuple<int,int,int>> q;
		q.emplace(0,0,0);
		dist[0][0]=0;
		while (!q.empty()){
		    auto now=q.front();q.pop();
		    int x=get<0>(now),y=get<1>(now),d=get<2>(now);
		    for (int i=0;i<4;i++){
		    	int nx=x+dx[i],ny=y+dy[i];
		    	if (nx<0 || nx>=n || ny<0 || ny>=m || mp[nx][ny]=='#') continue;
				if (d+1>=dist[nx][ny]) continue;
				dist[nx][ny]=d+1;
				q.emplace(nx,ny,d+1);
		    }
		}
		return dist[n-1][m-1];
	}
	void main(){
		auto input=readstrings(filename);
		for (string i:input){
			pos.emplace_back(
				str2int(split(i,",")[1]),
				str2int(split(i,",")[0])
			);
		}
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				mp[i][j]='.';
			}
		}
		for (int i=0;i<1024;i++){
			mp[pos[i].first][pos[i].second]='#';
		}
		cout<<solve()<<endl;
	}
}
namespace PartB{
	const int dx[4]={1,-1,0,0};
	const int dy[4]={0,0,-1,1};
	const int n=71,m=71;
	vector<pair<int,int>> pos;
	int dist[71][71];
	char mp[71][71];
	int solve(){
		memset(dist,0x3f,sizeof(dist));
		queue<tuple<int,int,int>> q;
		q.emplace(0,0,0);
		dist[0][0]=0;
		while (!q.empty()){
		    auto now=q.front();q.pop();
		    int x=get<0>(now),y=get<1>(now),d=get<2>(now);
		    for (int i=0;i<4;i++){
		    	int nx=x+dx[i],ny=y+dy[i];
		    	if (nx<0 || nx>=n || ny<0 || ny>=m || mp[nx][ny]=='#') continue;
				if (d+1>=dist[nx][ny]) continue;
				dist[nx][ny]=d+1;
				q.emplace(nx,ny,d+1);
		    }
		}
		return dist[n-1][m-1];
	}
	void main(){
		auto input=readstrings(filename);
		for (string i:input){
			pos.emplace_back(
				str2int(split(i,",")[0]),
				str2int(split(i,",")[1])
			);
		}
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				mp[i][j]='.';
			}
		}
		for (int i=0;i<(int)pos.size();i++){
			mp[pos[i].first][pos[i].second]='#';
			if (solve()==0x3f3f3f3f){
				cout<<pos[i].first<<","<<pos[i].second<<endl;
				return;
			}
		}
	}
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}