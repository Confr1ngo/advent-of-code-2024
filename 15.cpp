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
	string concat(vector<string> mp,string pattern=""){
		string result;
		for (int i=0;i<(int)mp.size();i++){
			if (i) result=result+pattern+mp[i];
			else result=mp[i];
		}
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
const string filename="15.txt";
namespace PartA{
	const int dx[4]={1,-1,0,0};
	const int dy[4]={0,0,-1,1};
	const string dir="v^<>";
	vector<string> mp;
	int n,m,x,y;
	bool in_range(int i,int j){
		return i>=0 && i<n && j>=0 && j<m;
	}
	void execute(char c){
		int ddx=dx[dir.find(c)],ddy=dy[dir.find(c)];
		int box_cnt=0;
		int i=x+ddx,j=y+ddy;
		while (in_range(i,j) && mp[i][j]=='O'){
			box_cnt++;
			i+=ddx,j+=ddy;
		}
		if (!in_range(i,j) || mp[i][j]=='#') return;
		mp[i][j]='O';
		mp[x+ddx][y+ddy]='.';
		x+=ddx,y+=ddy;
	}
	void main(){
		auto str=readstrings(filename);
		str.erase(str.begin());
		while (str[0][0]=='#'){
			mp.emplace_back(str[0].substr(1,str[0].size()-2));
			str.erase(str.begin());
		}
		mp.pop_back();
		string op=concat(str);
		n=mp.size();
		m=mp[0].size();
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]=='@'){
					x=i;y=j;
					mp[i][j]='.';
				}
			}
		}
		for (char c:op) execute(c);
		int ans=0;
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]=='O') ans+=100*(i+1)+j+1;
			}
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	const int dx[4]={1,-1,0,0};
	const int dy[4]={0,0,-1,1};
	const string dir="v^<>";
	vector<string> mp;
	int n,m,x,y;
	string enlarge(string s){
		string res="";
		for (char c:s){
			if (c=='#') res+="##";
			if (c=='O') res+="[]";
			if (c=='@') res+="@.";
			if (c=='.') res+="..";
		}
		return res;
	}
	bool in_range(int i,int j){
		return i>=0 && i<n && j>=0 && j<m;
	}
	bool check(int i,int j,int ddx,int ddy){
		if (!in_range(i,j) || mp[i][j]=='#') return false;
		if (mp[i][j]=='.') return true;
		if (ddx==0) return check(i,j+ddy,ddx,ddy);
		if (mp[i][j]=='[') return check(i+ddx,j,ddx,ddy) && check(i+ddx,j+1,ddx,ddy);
		if (mp[i][j]==']') return check(i+ddx,j,ddx,ddy) && check(i+ddx,j-1,ddx,ddy);
		assert("Invalid character");
		return false;
	}
	void push(int i,int j,int ddx,int ddy){
		if (!in_range(i,j)) return;
		if (mp[i][j]=='#') return;
		if (mp[i][j]=='.') return;
		if (ddx==0){
			push(i,j+ddy,ddx,ddy);
			mp[i][j+ddy]=mp[i][j];
			mp[i][j]='.';
			return;
		}
		if (mp[i][j]=='['){
			push(i+ddx,j,ddx,ddy);
			push(i+ddx,j+1,ddx,ddy);
			mp[i+ddx][j]=mp[i][j];
			mp[i+ddx][j+1]=mp[i][j+1];
			mp[i][j]=mp[i][j+1]='.';
		}
		if (mp[i][j]==']'){
			push(i+ddx,j,ddx,ddy);
			push(i+ddx,j-1,ddx,ddy);
			mp[i+ddx][j]=mp[i][j];
			mp[i+ddx][j-1]=mp[i][j-1];
			mp[i][j]=mp[i][j-1]='.';
			mp[i][j]='.';
		}
		assert("Invalid character");
	}
	void execute(char c){
		int ddx=dx[dir.find(c)],ddy=dy[dir.find(c)];
		if (!in_range(x+ddx,y+ddy)) return;
		if (ddx==0){
			if (check(x,y+ddy,ddx,ddy)){
				push(x,y+ddy,ddx,ddy);
				x+=ddx;y+=ddy;
			}
			return;
		}
		if (mp[x+ddx][y]=='['){
			if (check(x+ddx,y,ddx,ddy) && check(x+ddx,y+1,ddx,ddy)){
				push(x+ddx,y,ddx,ddy);
				push(x+ddx,y+1,ddx,ddy);
				x+=ddx;y+=ddy;
			}
		}
		else if (mp[x+ddx][y]==']'){
			if (check(x+ddx,y,ddx,ddy) && check(x+ddx,y-1,ddx,ddy)){
				push(x+ddx,y,ddx,ddy);
				push(x+ddx,y-1,ddx,ddy);
				x+=ddx;y+=ddy;
			}
		}
		else if (mp[x+ddx][y]=='.'){
			x+=ddx;y+=ddy;
		}
	}
	void main(){
		auto str=readstrings(filename);
		str.erase(str.begin());
		while (str[0][0]=='#'){
			mp.emplace_back(enlarge(str[0].substr(1,str[0].size()-2)));
			str.erase(str.begin());
		}
		mp.pop_back();
		string op=concat(str);
		n=mp.size();
		m=mp[0].size();
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]=='@'){
					x=i;y=j;
					mp[i][j]='.';
				}
			}
		}
		for (char c:op) execute(c);
		int ans=0;
		for (int i=0;i<n;i++){
			for (int j=0;j<m;j++){
				if (mp[i][j]=='[') ans+=100*(i+1)+j+2;
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