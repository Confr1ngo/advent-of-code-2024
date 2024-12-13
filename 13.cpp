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
const string filename="13.txt";
namespace PartA{
	int ans;
	void main(){
		auto mp=readstrings(filename);
		for (int i=0;i<(int)mp.size();i+=3){
			string buttona=mp[i],buttonb=mp[i+1],prize=mp[i+2];
			int dx_a=str2int(split(buttona," ")[2].substr(2,2));
			int dy_a=str2int(split(buttona," ")[3].substr(2,2));
			int dx_b=str2int(split(buttonb," ")[2].substr(2,2));
			int dy_b=str2int(split(buttonb," ")[3].substr(2,2));
			int dx_prize=str2int(split(prize," ")[1].substr(2,split(prize," ")[1].size()-3));
			int dy_prize=str2int(split(prize," ")[2].substr(2,split(prize," ")[2].size()-2));
			int minn=INT_MAX;
			for (int i=0;i<=dx_prize/dx_a;i++){
				int remainx=dx_prize-dx_a*i;
				int remainy=dy_prize-dy_a*i;
				if (remainx%dx_b==0 && remainy%dy_b==0){
					if (remainx/dx_b==remainy/dy_b){
						minn=min(minn,i*3+remainx/dx_b);
					}
				}
			}
			if (minn!=INT_MAX) ans+=minn;
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	#define int long long
	int ans;
	void main(){
		auto mp=readstrings(filename);
		for (int i=0;i<(int)mp.size();i+=3){
			string buttona=mp[i],buttonb=mp[i+1],prize=mp[i+2];
			int dx_a=str2int(split(buttona," ")[2].substr(2,2));
			int dy_a=str2int(split(buttona," ")[3].substr(2,2));
			int dx_b=str2int(split(buttonb," ")[2].substr(2,2));
			int dy_b=str2int(split(buttonb," ")[3].substr(2,2));
			int dx_prize=str2int(split(prize," ")[1].substr(2,split(prize," ")[1].size()-3))+10000000000000ll;
			int dy_prize=str2int(split(prize," ")[2].substr(2,split(prize," ")[2].size()-2))+10000000000000ll;
			int b_up=dy_a*dx_prize-dx_a*dy_prize;
			int b_down=dx_b*dy_a-dy_b*dx_a;
			if (b_up%b_down==0){
				int b_presses=b_up/b_down;
				int a_presses=(dx_prize-dx_b*b_presses)/dx_a;
				if (a_presses>=0 && a_presses*dy_a+dy_b*b_presses==dy_prize){
					ans+=a_presses*3+b_presses;
				}
			}
		}
		cout<<ans<<endl;
	}
	#undef int
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}