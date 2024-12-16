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
		int flag=1;
		if (s[0]=='-'){
			flag=-1;
			s=s.substr(1);
		}
		int result=0;
		for (auto &c:s) result=result*10+c-'0';
		return result*flag;
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
const string filename="14.txt";
namespace PartA{
	int n=103,m=101;
	int lu,ld,ru,rd;
	void main(){
		vector<string> mp=readstrings(filename);
		for (string s:mp){
			string rawp=split(s," ")[0].substr(2);
			string rawv=split(s," ")[1].substr(2);
			int starty=str2int(rawp.substr(0,rawp.find(",")));
			int startx=str2int(rawp.substr(rawp.find(",")+1));
			int dy=str2int(rawv.substr(0,rawv.find(",")));
			int dx=str2int(rawv.substr(rawv.find(",")+1));
			int t=100;
			// cout<<startx<<" "<<starty<<" "<<dx<<" "<<dy<<" "<<t<<endl;
			int x=startx+dx*t,y=starty+dy*t;
			// cout<<x<<" "<<y<<" ";
			x=(x%n+n)%n;y=(y%m+m)%m;	
			// cout<<x<<" "<<y<<endl;
			if (x>n/2 && y>m/2) rd++;
			if (x>n/2 && y<m/2) ld++;
			if (x<n/2 && y>m/2) ru++;
			if (x<n/2 && y<m/2) lu++;
		}
		// cout<<lu<<" "<<ld<<" "<<ru<<" "<<rd<<endl;
		cout<<lu*ld*ru*rd<<endl;
	}
}
namespace PartB{
	vector<pair<int,int>> bot;
	vector<pair<int,int>> v;
	const int n=103,m=101;
	bool f[n][m];
	const int dx[8]={0,0,-1,-1,-1,1,1,1};
	const int dy[8]={-1,1,0,1,-1,0,1,-1};
	void sleep(int ms){
		this_thread::sleep_for(chrono::milliseconds(ms));
	}
	bool in_range(int x,int y){
		return x>=0 && x<n && y>=0 && y<m;
	}
	void main(){
		vector<string> mp=readstrings(filename);
		for (string s:mp){
			string rawp=split(s," ")[0].substr(2);
			string rawv=split(s," ")[1].substr(2);
			int starty=str2int(rawp.substr(0,rawp.find(",")));
			int startx=str2int(rawp.substr(rawp.find(",")+1));
			bot.emplace_back(startx,starty);
			int dy=str2int(rawv.substr(0,rawv.find(",")));
			int dx=str2int(rawv.substr(rawv.find(",")+1));
			v.emplace_back(dx,dy);
		}
		while (true){
			static int t=0;
			int failed=0;
			memset(f,0,sizeof(f));
			for (int i=0;i<(int)bot.size();i++){
				f[bot[i].first][bot[i].second]=true;
				bot[i].first=(bot[i].first+v[i].first+n)%n;
				bot[i].second=(bot[i].second+v[i].second+m)%m;
			}
			for (int i=0;i<n;i++){
				for (int j=0;j<m;j++){
					if (f[i][j]){
						bool flag=false;
						for (int k=0;k<8;k++){
							int nx=i+dx[k],ny=j+dy[k];
							if (in_range(nx,ny) && f[nx][ny]) flag=true;
						}
						if (!flag) failed++;
					}
				}
			}
			if (failed<150){
				cout<<t<<endl;
				break;
			}
			t++;
		}
	}
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}