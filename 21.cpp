#include<bits/stdc++.h>
using namespace std;
namespace AOCHeader{
	namespace Print{
		template<typename T> void print(vector<vector<T>> v){
			for (auto &row:v){
				for (auto &element:row) cerr<<"'"<<element<<"' ";
				cerr<<endl;
			}
		}
		template<typename T> void print(vector<T> v){
			for (auto &element:v) cerr<<"'"<<element<<"' ";
			cerr<<endl;
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
const string filename="21.txt";
namespace PartA{
	string str_mult(string s,int k){
		string result="";
		while (k--) result+=s;
		return result;
	}
	namespace First{
		pair<int,int> pos[11]={{4,2},{3,1},{3,2},{3,3},{2,1},{2,2},{2,3},{1,1},{1,2},{1,3},{4,3}};
		vector<string> route[11][11];
		pair<string,string> diff(char d1,char d2){
			auto p1=pos[(d1=='A'? 10:d1-'0')];
			auto p2=pos[(d2=='A'? 10:d2-'0')];
			auto val=make_pair(p2.first-p1.first,p2.second-p1.second);
			string res1,res2;
			if (val.first>0) res1=str_mult("v",val.first);
			else res1=str_mult("^",-val.first);
			if (val.second>0) res2=str_mult(">",val.second);
			else res2=str_mult("<",-val.second);
			return make_pair(res1,res2);
		}
		vector<string> generate_first(string s){
			vector<string> result={""},temp;
			s="A"+s;
			for (int i=0;i<4;i++){
				for (string j:result){
					auto val=diff(s[i],s[i+1]);
					if (!((s[i]=='7' && val.first=="vvv") || (s[i]=='4' && val.first=="vv") || (s[i]=='1' && val.first=="v"))){
						temp.emplace_back(j+val.first+val.second+"A");
					}
					if (!((s[i]=='0' && val.second=="<") || (s[i]=='A' && val.second=="<<"))){
						temp.emplace_back(j+val.second+val.first+"A");
					}
				}
				result=temp;
				temp.clear();
			}
			sort(result.begin(),result.end());
			result.resize(unique(result.begin(),result.end())-result.begin());
			return result;
		}
	}
	namespace Others{
		map<char,pair<int,int>> arrows={{'^',{1,2}},{'v',{2,2}},{'<',{2,1}},{'>',{2,3}},{'A',{1,3}}};
		int vis[3][4][3][4][110];
		int dfs(int,int,int,int,int);
		int solve(string,int);
		pair<string,string> diff(int diff1,int diff2){
			string res1,res2;
			if (diff1>0) res1=str_mult("v",diff1);
			else res1=str_mult("^",-diff1);
			if (diff2>0) res2=str_mult(">",diff2);
			else res2=str_mult("<",-diff2);
			return make_pair(res1,res2);
		}
		int dfs(int x1,int y1,int x2,int y2,int k){
			if (vis[x1][y1][x2][y2][k]) return vis[x1][y1][x2][y2][k];
			if (k==0) return vis[x1][y1][x2][y2][k]=1;
			if (!(y1==1 || y2==1)){
				return vis[x1][y1][x2][y2][k]=min(
					solve(diff(x2-x1,y2-y1).first+diff(x2-x1,y2-y1).second+"A",k-1),
					solve(diff(x2-x1,y2-y1).second+diff(x2-x1,y2-y1).first+"A",k-1)
				);
			}
			if (y1==1){
				if (x2==1 && y2==2) return vis[x1][y1][x2][y2][k]=solve(">^A",k-1);
				if (x2==1 && y2==3) return vis[x1][y1][x2][y2][k]=solve(">>^A",k-1);
				if (x2==2 && y2==1) return vis[x1][y1][x2][y2][k]=solve("A",k-1);
				if (x2==2 && y2==2) return vis[x1][y1][x2][y2][k]=solve(">A",k-1);
				return vis[x1][y1][x2][y2][k]=solve(">>A",k-1);
			}
			else{
				if (x1==1 && y1==2) return vis[x1][y1][x2][y2][k]=solve("v<A",k-1);
				if (x1==1 && y1==3) return vis[x1][y1][x2][y2][k]=solve("v<<A",k-1);
				if (x1==2 && y1==1) return vis[x1][y1][x2][y2][k]=solve("A",k-1);
				if (x1==2 && y1==2) return vis[x1][y1][x2][y2][k]=solve("<A",k-1);
				return vis[x1][y1][x2][y2][k]=solve("<<A",k-1);
			}
		}
		int solve(string s,int k){
			int sum=0;
			for (int i=0;i<(int)s.size();i++){
				int x1=arrows[(i==0? 'A':s[i-1])].first,y1=arrows[(i==0? 'A':s[i-1])].second;
				int x2=arrows[s[i]].first,y2=arrows[s[i]].second;
				sum+=dfs(x1,y1,x2,y2,k);
			}
			return sum;
		}
	}
	void main(){
		vector<string> input=readstrings(filename);
		int sum=0;
		for (string i:input){
			vector<string> first=First::generate_first(i);
			int ans=INT_MAX;
			for (string j:first){
				memset(Others::vis,0,sizeof(Others::vis));
				ans=min(ans,Others::solve(j,2));
			}
			sum+=ans*str2int(i.substr(0,3));
		}
		cout<<sum<<endl;
	}
}
namespace PartB{
	string str_mult(string s,int k){
		string result="";
		while (k--) result+=s;
		return result;
	}
	namespace First{
		pair<int,int> pos[11]={{4,2},{3,1},{3,2},{3,3},{2,1},{2,2},{2,3},{1,1},{1,2},{1,3},{4,3}};
		vector<string> route[11][11];
		pair<string,string> diff(char d1,char d2){
			auto p1=pos[(d1=='A'? 10:d1-'0')];
			auto p2=pos[(d2=='A'? 10:d2-'0')];
			auto val=make_pair(p2.first-p1.first,p2.second-p1.second);
			string res1,res2;
			if (val.first>0) res1=str_mult("v",val.first);
			else res1=str_mult("^",-val.first);
			if (val.second>0) res2=str_mult(">",val.second);
			else res2=str_mult("<",-val.second);
			return make_pair(res1,res2);
		}
		vector<string> generate_first(string s){
			vector<string> result={""},temp;
			s="A"+s;
			for (int i=0;i<4;i++){
				for (string j:result){
					auto val=diff(s[i],s[i+1]);
					if (!((s[i]=='7' && val.first=="vvv") || (s[i]=='4' && val.first=="vv") || (s[i]=='1' && val.first=="v"))){
						temp.emplace_back(j+val.first+val.second+"A");
					}
					if (!((s[i]=='0' && val.second=="<") || (s[i]=='A' && val.second=="<<"))){
						temp.emplace_back(j+val.second+val.first+"A");
					}
				}
				result=temp;
				temp.clear();
			}
			sort(result.begin(),result.end());
			result.resize(unique(result.begin(),result.end())-result.begin());
			return result;
		}
	}
	namespace Others{
		map<char,pair<int,int>> arrows={{'^',{1,2}},{'v',{2,2}},{'<',{2,1}},{'>',{2,3}},{'A',{1,3}}};
		long long vis[3][4][3][4][110];
		long long dfs(int,int,int,int,int);
		long long solve(string,int);
		pair<string,string> diff(int diff1,int diff2){
			string res1,res2;
			if (diff1>0) res1=str_mult("v",diff1);
			else res1=str_mult("^",-diff1);
			if (diff2>0) res2=str_mult(">",diff2);
			else res2=str_mult("<",-diff2);
			return make_pair(res1,res2);
		}
		long long dfs(int x1,int y1,int x2,int y2,int k){
			if (vis[x1][y1][x2][y2][k]) return vis[x1][y1][x2][y2][k];
			if (k==0) return vis[x1][y1][x2][y2][k]=1;
			if (!(y1==1 || y2==1)){
				return vis[x1][y1][x2][y2][k]=min(
					solve(diff(x2-x1,y2-y1).first+diff(x2-x1,y2-y1).second+"A",k-1),
					solve(diff(x2-x1,y2-y1).second+diff(x2-x1,y2-y1).first+"A",k-1)
				);
			}
			if (y1==1){
				if (x2==1 && y2==2) return vis[x1][y1][x2][y2][k]=solve(">^A",k-1);
				if (x2==1 && y2==3) return vis[x1][y1][x2][y2][k]=solve(">>^A",k-1);
				if (x2==2 && y2==1) return vis[x1][y1][x2][y2][k]=solve("A",k-1);
				if (x2==2 && y2==2) return vis[x1][y1][x2][y2][k]=solve(">A",k-1);
				return vis[x1][y1][x2][y2][k]=solve(">>A",k-1);
			}
			else{
				if (x1==1 && y1==2) return vis[x1][y1][x2][y2][k]=solve("v<A",k-1);
				if (x1==1 && y1==3) return vis[x1][y1][x2][y2][k]=solve("v<<A",k-1);
				if (x1==2 && y1==1) return vis[x1][y1][x2][y2][k]=solve("A",k-1);
				if (x1==2 && y1==2) return vis[x1][y1][x2][y2][k]=solve("<A",k-1);
				return vis[x1][y1][x2][y2][k]=solve("<<A",k-1);
			}
		}
		long long solve(string s,int k){
			long long sum=0;
			for (int i=0;i<(int)s.size();i++){
				int x1=arrows[(i==0? 'A':s[i-1])].first,y1=arrows[(i==0? 'A':s[i-1])].second;
				int x2=arrows[s[i]].first,y2=arrows[s[i]].second;
				sum+=dfs(x1,y1,x2,y2,k);
			}
			return sum;
		}
	}
	void main(){
		vector<string> input=readstrings(filename);
		long long sum=0;
		for (string i:input){
			vector<string> first=First::generate_first(i);
			long long ans=LLONG_MAX;
			for (string j:first){
				memset(Others::vis,0,sizeof(Others::vis));
				ans=min(ans,Others::solve(j,25));
			}
			sum+=ans*str2int(i.substr(0,3));
		}
		cout<<sum<<endl;
	}
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}