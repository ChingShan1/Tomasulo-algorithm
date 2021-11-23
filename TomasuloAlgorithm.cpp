// 計算機專題2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include <map>
#include <list>
#include <algorithm>
#define LoadBuffer0 0
#define LoadBuffer1 1
#define StoreBuffer0 2
#define StoreBuffer1 3
#define Adder0 4
#define Adder1 5
#define Adder2 6
#define Multiplier0 7
#define Multiplier1 8

using namespace std;

struct Instruction
{
	int opcode;
	int rs;
	int rt;
	int rd;
	int offset;
	int Issue; 		//紀錄完成該步驟的迴圈
	int Execution;
	int Write;
};
struct ReservationStation
{
	int busy;
	int opcode;
	int FU;	//記錄使用哪個function unit
	string Vj;
	string Vk;
	int Qi;
	int Qj;
	int Qk;
	int A;
	int cycle;
	string addr;
};
struct ReservationStation LoadBuffer[2];
struct ReservationStation StoreBuffer[2];
struct ReservationStation Adder[3];
struct ReservationStation Multiplier[2];

struct RegisterStatus
{
	int Qi;
};
struct RegisterStatus FRegister[16];
struct RegisterStatus IRegister[32];

string temp_comma(string s)
{
	int current = 0; //最初由 0 的位置開始找
	int next;
	string temp = "";
	while (1)
	{
		next = s.find_first_of(",", current);
		if (next != current)
		{
			string tmp = s.substr(current, next - current);
			temp += tmp;
		}
		if (next == string::npos) break;
		current = next + 1; //下次由 next + 1 的位置開始找起。
	}
	return temp;
}
void temp(string s, vector<string>& buf)
{
	int current = 0; //最初由 0 的位置開始找
	int next;
	while (1)
	{
		next = s.find_first_of(" ", current);
		if (next != current )
		{	
			string tmp = s.substr(current, next - current);
			if (tmp.size() != 0) //忽略空字串
				buf.push_back(tmp);
		}
		if (next == string::npos ) break;
		current = next + 1; //下次由 next + 1 的位置開始找起。
	}
}
//LoadBuffer[2];
//StoreBuffer[2];
//Adder[3];
// Multiplier[2];
bool select_case_reservation_stations_check(string sr)
{
	string s = "";
	s = sr;
	//L.D, S.D., ADD.D, SUB.D, MUL.D, and DIV.D
	if (s == "L.D") {
		if (LoadBuffer[2].A > 0)
			return true;
		else
			return false;
	}
	else if (s == "S.D") {
		if (StoreBuffer[2].A > 0)
			return true;
		else
			return false;
	}
	else if (s == "ADD.D") {
		if (Adder[3].A > 0)
			return true;
		else
			return false;
	}
	else if (s == "SUB.D") {
		if (Adder[3].A > 0)
			return true;
		else
			return false;
	}
	else if (s == "MUL.D") {
		if (Multiplier[2].A > 0)
			return true;
		else
			return false;
	}
	else if (s == "DIV.D") {
		if (Multiplier[2].A > 0)
			return true;
		else
			return false;
	}
}

void select_case_reservation_stations_add(string sr)
{
	string s = "";
	s = sr;
	//L.D, S.D., ADD.D, SUB.D, MUL.D, and DIV.D
	if (s == "L.D") {
		LoadBuffer[2].A += 1;
	}
	else if (s == "S.D")
		StoreBuffer[2].A += 1;
	else if (s == "ADD.D")
		Adder[3].A += 1;
	else if (s == "SUB.D")
		Adder[3].A += 1;
	else if (s == "MUL.D")
		Multiplier[2].A += 1;
	else if (s == "DIV.D")
		Multiplier[2].A += 1;
}
void select_case_reservation_stations_sub(string sr)
{
	string s = "";
	s = sr;
	//L.D, S.D., ADD.D, SUB.D, MUL.D, and DIV.D
	if (s == "L.D") 
		LoadBuffer[2].A -= 1;
	else if (s == "S.D")
		StoreBuffer[2].A -= 1;
	else if (s == "ADD.D")
		Adder[3].A -= 1;
	else if (s == "SUB.D")
		Adder[3].A -= 1;
	else if (s == "MUL.D")
		Multiplier[2].A -= 1;
	else if (s == "DIV.D")
		Multiplier[2].A -= 1;
}
int select_case_excute_cycle(string sr)
{
	string s = "";
	s = sr;
	int cycle;
	//L.D, S.D., ADD.D, SUB.D, MUL.D, and DIV.D
	if (s == "L.D") {
		cycle = 2;
	}
	else if (s == "S.D")
		cycle = 1;
	else if (s == "ADD.D")
		cycle = 2;
	else if (s == "SUB.D")
		cycle = 2;
	else if (s == "MUL.D")
		cycle = 10;
	else if (s == "DIV.D")
		cycle = 40;
	else
		return 0;
	return cycle;

}
void Resercation_Stations(vector<string>& buf1 , vector<int>& buf2 , int index )
{
	string s = "";
	s = buf1[0];
	//L.D, S.D., ADD.D, SUB.D, MUL.D, and DIV.D
	if (s == "L.D") {
		for (int i = 0;i < 2;i++) {
			if (LoadBuffer[i].busy == 0) {
				LoadBuffer[i].busy = 1;
				LoadBuffer[i].addr = buf1[2];
				break;
			}
		}
	}
	else if (s == "S.D") {
		for (int i = 0;i <2;i++) {
			if (StoreBuffer[i].busy == 0) {
				StoreBuffer[i].busy = 1;
				StoreBuffer[i].addr = buf1[2];
				break;
			}
		}
	}
	else if (s == "ADD.D") {
		for (int i = 0;i < 3;i++) {
			if (Adder[i].busy == 0) {
				Adder[i].busy = 1;
				Adder[i].opcode = index;
				Adder[i].Vj = buf1[2];
				Adder[i].Vk = buf1[3];
				break;
			}
		}
	}
	else if (s == "SUB.D") {
		for (int i = 0;i < 3;i++) {
			if (Adder[i].busy == 0) {
				Adder[i].busy = 1;
				Adder[i].opcode = index;
				Adder[i].Vj = buf1[2];
				Adder[i].Vk = buf1[3];
				break;
			}
		}
	}
	else if (s == "MUL.D") {
		for (int i = 0;i < 2;i++) {
			if (Multiplier[i].busy == 0) {
				Multiplier[i].busy = 1;
				Multiplier[i].opcode = index;
				Multiplier[i].Vj = buf1[2];
				Multiplier[i].Vk = buf1[3];
				break;
			}
		}
	}
	else if (s == "DIV.D") {
		for (int i = 0;i < 2;i++) {
			if (Multiplier[i].busy == 0) {
				Multiplier[i].busy = 1;
				Multiplier[i].opcode = index;
				Multiplier[i].Vj = buf1[2];
				Multiplier[i].Vk = buf1[3];
				break;
			}
		}
	}
}
void Resercation_Stations_WhoFull(vector<string>& buf1, vector<int>& buf2, int index, map<int, int>& map2 , int &who_index)
{
	string s = "";
	s = buf1[0];
	//L.D, S.D., ADD.D, SUB.D, MUL.D, and DIV.D
	if (s == "L.D") {
		int min = map2[LoadBuffer[0].opcode];
		int index = 0;
		for (int i = 0;i < 2;i++) {
			if (map2[LoadBuffer[i].opcode] <= min) {
				min = map2[LoadBuffer[i].opcode];
				index = i;
				who_index = LoadBuffer[i].opcode;
			}
		}
		LoadBuffer[index].busy = 0;
	}
	else if (s == "S.D") {
		int min = map2[StoreBuffer[0].opcode];
		int index = 0;
		for (int i = 0;i < 2;i++) {
			if (map2[StoreBuffer[i].opcode] <= min) {
				min = map2[StoreBuffer[i].opcode];
				index = i;
				who_index = StoreBuffer[i].opcode;
			}
		}
		StoreBuffer[index].busy = 0;
	}
	else if (s == "ADD.D") {
		int min = map2[Adder[0].opcode];
		int index = 0;
		for (int i = 0;i < 3;i++) {
			if (map2[Adder[i].opcode] <= min) {
				min = map2[Adder[i].opcode];
				index = i;
				who_index = Adder[i].opcode;
			}
		}
		Adder[index].busy = 0;
	}
	else if (s == "SUB.D") {
		int min = map2[Adder[0].opcode];
		int index = 0;
		for (int i = 0;i < 3;i++) {
			if (map2[Adder[i].opcode] <= min) {
				min = map2[Adder[i].opcode];
				index = i;
				who_index = Adder[i].opcode;
			}
		}
		Adder[index].busy = 0;
	}
	else if (s == "MUL.D") {
		int min = map2[Multiplier[0].opcode];
		int index = 0;
		for (int i = 0;i < 2;i++) {
			if (map2 [ Multiplier[i].opcode ] <= min) {
				min = map2[Multiplier[i].opcode];
				index = i;
				who_index = Multiplier[i].opcode;
			}
		}
		Multiplier[index].busy = 0;
	}
	else if (s == "DIV.D") {
		int min = map2[Multiplier[0].opcode];
		int index = 0;
		for (int i = 0;i < 2;i++) {
			if (map2[Multiplier[i].opcode] <= min) {
				min = map2[Multiplier[i].opcode];
				index = i;
				who_index = Multiplier[i].opcode;
			}
		}
		Multiplier[index].busy = 0;
	}
}

void WriteResult(vector<string>& buf1, vector<int> &buf2 ,
	int clock , int index, map<string, int>& map1 , map<int, int>& map2 ,
	bool &flag , map<string, int>& map3 , int find)
{
	if (buf1[0] == "S.D") {
		int exc_cycle = max(find, buf2[0]) + select_case_excute_cycle(buf1[0]);
		buf2.push_back(exc_cycle);
		map1[buf1[1]] = 1;
		map2[index] = exc_cycle;
		map3[buf1[1]] = index;
	}
	else {
		map1[buf1[1]] = 1;
		map2[index] = buf2[1] + 1;
		map3[buf1[1]] = index;
		buf2.push_back(buf2[1] + 1);
	}
}
void Execute(vector<string>& buf1, vector<int>& buf2, 
	int clock, int index, map<string, int>& map1, map<int, int>& map2 , 
	bool &flag, map<string, int>& map3 , int find)
{
	if(buf1[0] == "S.D"){
		buf2.push_back(buf2[0] + 1);
	}
	else {
		if (flag) {
			int exc_cycle = max(find, buf2[0]) + select_case_excute_cycle(buf1[0]);
			buf2.push_back(exc_cycle);
		}
		else {
			int exc_cycle = buf2[0] + select_case_excute_cycle(buf1[0]);
			buf2.push_back(exc_cycle);
		}
	}
	
}
int Issue(vector<string>& buf1, vector<int>& buf2,	int clock ,
	int index , map<string,int>&map1, map<int, int>&map2, 
	bool &flag, map<string, int>& map3 , map<int, int>& save_issue)
{
	if (select_case_reservation_stations_check(buf1[0]) == false) {
		int who_index;
		Resercation_Stations_WhoFull(buf1, buf2, index, map2 , who_index);
		clock = map2[who_index] + 1;
	}
	int num = 0;
	if (buf1[0] == "L.D" || buf1[0] == "S.D"){
		if (map1[buf1[1]] == 1 || map1[buf1[2]] == 1) {
			if (buf1[0] == "S.D") {
				flag = true;
				select_case_reservation_stations_sub(buf1[0]);
				Resercation_Stations(buf1, buf2, index);
				buf2.push_back(save_issue[index - 1] + 1);
				save_issue[index] = clock;
				vector<int> whomax;
				if (map1[buf1[1]] == 1) {
					num = 1;
					whomax.push_back(map2[map3[buf1[num]]]);
				}
				if (map1[buf1[2]] == 1) {
					num = 2;
					whomax.push_back(map2[map3[buf1[num]]]);
				}
				sort(whomax.begin(), whomax.end());
				reverse(whomax.begin(), whomax.end());
				num = whomax[0];
			}
			else {
				flag = true;
				select_case_reservation_stations_sub(buf1[0]);
				Resercation_Stations(buf1, buf2, index);
				buf2.push_back(clock);
				save_issue[index] = clock;
				vector<int> whomax;
				if (map1[buf1[1]] == 1) {
					num = 1;
					whomax.push_back(map2[map3[buf1[num]]]);
				}
				if (map1[buf1[2]] == 1) {
					num = 2;
					whomax.push_back(map2[map3[buf1[num]]]);
				}
				sort(whomax.begin(), whomax.end());
				reverse(whomax.begin(), whomax.end());
				num = whomax[0];

				cout << "yes : " << buf1[0];
			}
		}
		else {
			select_case_reservation_stations_sub(buf1[0]);
			Resercation_Stations(buf1, buf2, index);
			buf2.push_back(clock);
			save_issue[index] = clock;
			flag = false;
		}
		return num;
	}
	else{
		if (map1[buf1[1]] == 1 || map1[buf1[2]] == 1 || map1[buf1[3]] == 1) {
			flag = true;
			select_case_reservation_stations_sub(buf1[0]);
			Resercation_Stations(buf1, buf2, index);
			buf2.push_back(clock);
			save_issue[index] = clock;
			vector<int> whomax;

			if (map1[buf1[2]] == 1 ) {
				num = 2;
				whomax.push_back(map2[map3[buf1[num]]]);
			}
			if (map1[buf1[3]] == 1 ) {
				num = 3;
				whomax.push_back(map2[map3[buf1[num]]]);
			}
			sort(whomax.begin() , whomax.end());
			reverse(whomax.begin(), whomax.end());
			num = whomax[0];
			return num;
		}
		else {
			select_case_reservation_stations_sub(buf1[0]);
			Resercation_Stations(buf1, buf2, index);
			buf2.push_back(clock);
			save_issue[index] = clock;
			flag = false;
			return num;
		}
	}
	return num;
}
int main()
{
	ifstream in;

	in.open("test5.txt");
	if (!in) {

		cout << "fall" << endl;
		return 0;

	}
	vector<string> buffer1, buffer1_split[1000];
	string file = "";
	while (getline(in, file) ){
		buffer1.push_back(file);
	}
	in.close();
	int index = 0;
	for (string i : buffer1) {
		temp(temp_comma(i), buffer1_split[index]);
		index++;
	}
	

	int clock = 1, num_index = 0, stable_num = 0 ;
	bool issue_flag = false;
	vector<int> cycle_table[100];
	map<string, int > F_num_1;
	map<int, int > F_num_2;
	//找對應(有依賴)的index
	map<string, int >F_num3;
	map<int, int>save_issue;
	for (int i = 0; i <= 30; i++) {
		F_num_1["F" + to_string(i)] = 0;
	}
	LoadBuffer[2].A = 2;
	StoreBuffer[2].A = 2;
	Adder[3].A = 3;
	Multiplier[2].A = 2;
	while (1) {
		if (num_index <= index) {
			int find = Issue(buffer1_split[num_index], cycle_table[num_index], clock , num_index , F_num_1, F_num_2 , issue_flag , F_num3 , save_issue);
			Execute(buffer1_split[num_index], cycle_table[num_index], clock , num_index , F_num_1, F_num_2 , issue_flag, F_num3 , find);
			WriteResult(buffer1_split[num_index] , cycle_table[num_index], clock , num_index,F_num_1, F_num_2, issue_flag, F_num3, find);
			num_index++;
		}

		clock++;
		if (clock == index+1) break;
	}





	//string temp = "";
	//in >> temp;
	//std::cout << temp <<endl;
	//for (int i = 0;i < index; i++)
	//{
	//	for (string j : buffer[i])
	//		cout << j<< endl;
	//}
	for (int i = 0;i < index; i++) {
		for (int j : cycle_table[i]) {
			cout << j << "  ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0;i < 2; i++) {
		cout << "LoadBuffer" << i << ": ";
		cout << LoadBuffer[i].busy<<" ";
		cout << LoadBuffer[i].addr << " ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0;i < 2; i++) {
		cout << "StoreBuffer" << i << ": ";
		cout << StoreBuffer[i].busy << " ";
		cout << StoreBuffer[i].addr << " ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0;i < 3; i++) {
		cout << "Adder" << i << ": ";
		cout << Adder[i].busy << " ";
		cout << Adder[i].opcode << " ";
		cout << Adder[i].Vj << " ";
		cout << Adder[i].Vk << " ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0;i < 2; i++) {
		cout << "Multiplier" << i << ": ";
		cout << Multiplier[i].busy << " ";
		cout << Multiplier[i].opcode << " ";
		cout << Multiplier[i].Vj << " ";
		cout << Multiplier[i].Vk << " ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i <= 30; i++) {
		cout<<"F"<<i<<":"<< F_num_1["F" + to_string(i)]<<" ";
	}
	cout << endl;
	//for (auto i = F_num_2.begin() ; i != F_num_2.end(); i++) {
	//	cout << i->first << ":" << i->second << " ";
	//}
}


