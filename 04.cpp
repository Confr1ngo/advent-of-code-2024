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
const string filename="04.txt";
namespace PartA{
	const int dx[8]={1,-1,0,0,1,-1,1,-1};
	const int dy[8]={0,0,-1,1,1,-1,-1,1};
	int n,m,cnt;
	string get_4(vector<vector<char>> &mp,int dx,int dy,int x,int y){
		string res="";
		while (res.size()<4){
			res+=mp[x][y];
			x+=dx;y+=dy;
			if (x<0 || y<0 || x>=n || y>=m) break;
		}
		return res;
	}
	void main(){
		auto mp=readchars(filename);
		n=mp.size();m=mp[0].size();
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				for (int k=0;k<8;k++){
					if (get_4(mp,dx[k],dy[k],i,j)=="XMAS") cnt++;
				}
			}
		}
		cout<<cnt<<endl;
	}
}
namespace PartB{
	int n,m,cnt;
	void main(){
		auto mp=readchars(filename);
		n=mp.size();m=mp[0].size();
		for (int i=1;i<n-1;i++){
			for (int j=1;j<m-1;j++){
				if (mp[i][j]!='A') continue;
				bool cond1=((mp[i-1][j-1]=='M' && mp[i+1][j+1]=='S') || (mp[i-1][j-1]=='S' && mp[i+1][j+1]=='M'));
				bool cond2=((mp[i+1][j-1]=='M' && mp[i-1][j+1]=='S') || (mp[i+1][j-1]=='S' && mp[i-1][j+1]=='M'));
				if (cond1 && cond2) cnt++;
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