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
const string filename="17.txt";
namespace PartA{
	int getval(int rega,int regb,int regc,int v){
		if (v<=3) return v;
		if (v==4) return rega;
		if (v==5) return regb;
		if (v==6) return regc;
		assert(!!"Invalid input.");
		return -1;
	}
	void operate(int &ptr,int& rega,int &regb,int &regc,int op,int val,vector<int> &output){
		if (op==0) rega=rega/(1<<getval(rega,regb,regc,val));
		if (op==1) regb=regb^val;
		if (op==2) regb=getval(rega,regb,regc,val)%8;
		if (op==3) if (rega){ptr=val;return;}
		if (op==4) regb=regb^regc;
		if (op==5) output.emplace_back(getval(rega,regb,regc,val)%8);
		if (op==6) regb=rega/(1<<getval(rega,regb,regc,val));
		if (op==7) regc=rega/(1<<getval(rega,regb,regc,val));
		ptr+=2;
	}
	vector<int> run_program(vector<int> program,int rega,int regb,int regc){
		vector<int> output;
		int ptr=0;
		while (ptr+1<(int)program.size()) operate(ptr,rega,regb,regc,program[ptr],program[ptr+1],output);
		return output;
	}
	void main(){
		auto input=readstrings(filename);
		int rega=str2int(split(input[0]," ").back());
		int regb=str2int(split(input[1]," ").back());
		int regc=str2int(split(input[2]," ").back());
		input=split(split(input[3]," ")[1],",");
		vector<int> program;
		for (string i:input) program.emplace_back(str2int(i));
		vector<int> output=run_program(program,rega,regb,regc);
		cout<<output[0];
		for (int i=1;i<(int)output.size();i++){
			cout<<","<<output[i];
		}
		cout<<endl;
	}
}
namespace PartB{
	#define int long long
	int getval(int rega,int regb,int regc,int v){
		if (v<=3) return v;
		if (v==4) return rega;
		if (v==5) return regb;
		if (v==6) return regc;
		assert(!!"Invalid input.");
		return -1;
	}
	void operate(int &ptr,int& rega,int &regb,int &regc,int op,int val,vector<int> &output){
		if (op==0) rega=rega/(1<<getval(rega,regb,regc,val));
		if (op==1) regb=regb^val;
		if (op==2) regb=getval(rega,regb,regc,val)%8;
		if (op==3) if (rega){ptr=val;return;}
		if (op==4) regb=regb^regc;
		if (op==5) output.emplace_back(getval(rega,regb,regc,val)%8);
		if (op==6) regb=rega/(1<<getval(rega,regb,regc,val));
		if (op==7) regc=rega/(1<<getval(rega,regb,regc,val));
		ptr+=2;
	}
	vector<int> run_program(vector<int> program,int rega,int regb,int regc){
		vector<int> output;
		int ptr=0;
		while (ptr+1<(int)program.size()) operate(ptr,rega,regb,regc,program[ptr],program[ptr+1],output);
		return output;
	}
	bool issuffix(vector<int> suff,vector<int> vec){
		if ((int)suff.size()>(int)vec.size()) return false;
		int ptr1=(int)suff.size(),ptr2=(int)vec.size();
		while (ptr1){
			if (suff[--ptr1]!=vec[--ptr2]) return false;
		}
		return true;
	}
	bool solve(int cur,int regb,int regc,vector<int> &program){
		for (int rega=cur;rega<=cur+7;rega++){
			vector<int> output=run_program(program,rega,regb,regc);
			if (output==program){
				cout<<rega<<endl;
				return true;
			}
			if (issuffix(output,program)){
				if (solve(rega*8,regb,regc,program)) return true;
			}
		}
		return false;
	}
	void main(){
		auto input=readstrings(filename);
		int regb=str2int(split(input[1]," ").back());
		int regc=str2int(split(input[2]," ").back());
		input=split(split(input[3]," ")[1],",");
		vector<int> program;
		for (string i:input) program.emplace_back(str2int(i));
		if (solve(1,regb,regc,program)) return;
	}
	#undef int
}
int main(){
	PartA::main();
	PartB::main();
	return 0;
}