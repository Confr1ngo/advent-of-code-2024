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
const string filename="24.txt";
namespace PartA{
	map<string,bool> val;
	bool operate(string var1,string var2,string op){
		if (op=="AND") return val[var1] && val[var2];
		if (op=="OR") return val[var1] || val[var2];
		if (op=="XOR") return val[var1]^val[var2];
		return 0;
	}
	void main(){
		long long ans=0;
		auto input=readstrings(filename);
		while (input[0].find("->")==string::npos){
			val[input[0].substr(0,3)]=(input[0][5]=='1');
			input.erase(input.begin());
		}
		while (!input.empty()){
		    for (int i=0;i<(int)input.size();i++){
				auto temp=split(input[i]," ");
				if (val.count(temp[0]) && val.count(temp[2])){
					val[temp[4]]=operate(temp[0],temp[2],temp[1]);
					input.erase(input.begin()+i);
					break;
				}
			}
		}
		for (auto i:val){
			if (i.first[0]=='z' && i.second){
				ans|=(1ll<<str2int(i.first.substr(1)));
			}
		}
		cout<<ans<<endl;
	}
}
namespace PartB{
	map<string,bool> val;
	bool operate(string var1,string var2,string op){
		if (op=="AND") return val[var1] && val[var2];
		if (op=="OR") return val[var1] || val[var2];
		if (op=="XOR") return val[var1]^val[var2];
		return 0;
	}
	string join(vector<string> &v){
		string ans="";
		for (string &i:v){
			ans=ans+i+" ";
		}
		return ans;
	}
	string zfill(string s,int len){
		while ((int)s.size()<len){
			s="0"+s;
		}
		return s;
	}
	void main(){
		auto input=readstrings(filename);
		while (input[0].find("->")==string::npos){
			val[input[0].substr(0,3)]=(input[0][5]=='1');
			input.erase(input.begin());
		}
		// Swap `y?? OP x??` to `x?? OP y??` to simplify
		for (string &i:input){
			vector<string> temp=split(i," ");
			if (temp[0][0]=='y' && temp[2][0]=='x') swap(temp[0],temp[2]);
			i=join(temp);
		}
		// Make sure x00 y00 are the first values
		sort(input.begin(),input.end());
		// Sort by toposort
		vector<tuple<string,string,string,string>> sorted;
		while (!input.empty()){
		    for (int i=0;i<(int)input.size();i++){
				auto temp=split(input[i]," ");
				if (val.count(temp[0]) && val.count(temp[2])){
					val[temp[4]]=operate(temp[0],temp[2],temp[1]);
					sorted.emplace_back(temp[0],temp[1],temp[2],temp[4]);
					input.erase(input.begin()+i);
					break;
				}
			}
		}
		set<string> ans;
		// Find the first carry bit
		string pre=(get<1>(sorted[0])=="AND"? get<3>(sorted[0]):get<3>(sorted[1]));
		for (int i=0;i<45;i++){
			if (i==0){
				sorted.erase(sorted.begin());
				sorted.erase(sorted.begin());
				continue;
			}
			vector<tuple<string,string,string,string>> temp;
			for (int j=0;j<5;j++){
				temp.emplace_back(sorted[0]);
				sorted.erase(sorted.begin());
			}
			// Sort the 5 operations in each set
			sort(temp.begin(),temp.end(),[](auto &a,auto &b){
				if (get<0>(a)[0]=='x' && get<1>(a)=="AND") return true;
				if (get<0>(b)[0]=='x' && get<1>(b)=="AND") return false;
				if (get<0>(a)[0]=='x' && get<1>(a)=="XOR") return true;
				if (get<0>(b)[0]=='x' && get<1>(b)=="XOR") return false;
				if (get<1>(a)=="AND") return true;
				if (get<1>(b)=="AND") return false;
				if (get<1>(a)=="XOR") return true;
				if (get<1>(b)=="XOR") return false;
				if (get<1>(a)=="OR") return true;
				if (get<1>(b)=="OR") return false;
				return false;
			});
			// Check if the 5 pairs of parameters are valid
			string and_res=get<3>(temp[0]);
			string xor_res=get<3>(temp[1]);

			if (!((get<0>(temp[2])==xor_res && get<2>(temp[2])==pre) || (get<0>(temp[2])==pre && get<2>(temp[2])==xor_res))){
				if (!(get<0>(temp[2])==xor_res || get<2>(temp[2])==xor_res)) ans.emplace(xor_res);
				if (!(get<0>(temp[2])==pre     || get<2>(temp[2])==pre    )) ans.emplace(pre);
			}
			string and_res2=get<3>(temp[2]);

			if (!((get<0>(temp[3])==xor_res && get<2>(temp[3])==pre) || (get<0>(temp[3])==pre && get<2>(temp[3])==xor_res))){
				if (!(get<0>(temp[3])==xor_res || get<2>(temp[3])==xor_res)) ans.emplace(xor_res);
				if (!(get<0>(temp[3])==pre     || get<2>(temp[3])==pre    )) ans.emplace(pre);
			}
			if (get<3>(temp[3])!="z"+zfill(to_string(i),2)) ans.emplace(get<3>(temp[3]));

			if (!((get<0>(temp[4])==and_res2 && get<2>(temp[4])==and_res) || (get<0>(temp[4])==and_res && get<2>(temp[4])==and_res2))){
				if (!(get<0>(temp[4])==and_res  || get<2>(temp[4])==and_res )) ans.emplace(and_res);
				if (!(get<0>(temp[4])==and_res2 || get<2>(temp[4])==and_res2)) ans.emplace(and_res2);
			}
			pre=get<3>(temp[4]);
		}
		for (auto it=ans.begin();it!=ans.end();it++){
			if (it!=ans.begin()) cout<<",";
			cout<<*it;
		}
		cout<<endl;
	}
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}