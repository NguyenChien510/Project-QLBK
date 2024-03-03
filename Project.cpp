#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Dinh nghia DATE
struct date{
	int ngay;
	int thang;
	int nam;
};
typedef struct date DATE;

//Dinh nghia struct BUU DIEN
struct buukien{
	int mabd;
	string nggui;
	string ngnhan;
	string diachi;
	float trongluong;
	DATE ngaygui;
	string nd;
	int dongia;
};
typedef struct buukien BK;

//Thiet lap node
struct node{
	BK data;
	node *next;
};
typedef struct node* NODE;
struct list{
	NODE head;
	NODE tail;
};
typedef struct list LIST;
void KhoiTaoDanhSach(LIST &l){
	l.head = NULL;
	l.tail = NULL;
}
//Tao Node
NODE makenode(BK x){
	NODE newnode = new node();
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}
//Cac thao tac xu li Node
void ThemDau(LIST &l,NODE p){
	if(l.head==NULL){
		l.head = l.tail = p;
	}
	else{
		p->next = l.head;
		l.head = p;
	}
}
void ThemCuoi(LIST &l,NODE p){
	if(l.head==NULL){
		l.head = l.tail = p;
	}
	else{
		l.tail->next = p;
		l.tail = p;
	}
}
void XoaDau(LIST &l){
	NODE temp = l.head;
	l.head = l.head->next;
	delete(temp);
}
void XoaCuoi(LIST &l){
	NODE prev=NULL;
	NODE temp=l.head;
	while(temp->next!=NULL){
		prev = temp;
		temp=temp->next;
	}
	prev->next=NULL;
	delete(temp);
}
bool Xoa(LIST &l,int x){
	if(l.head==NULL) return false;
	if(l.head->data.mabd==x){
		XoaDau(l);
		return true;
	}
	if(l.tail->data.mabd==x){
		XoaCuoi(l);
		return true;
	}
	NODE temp = l.head;
	NODE prev = NULL;
	while((temp!=NULL) && (temp->data.mabd!=x)){
		prev = temp;
		temp=temp->next;
	}
	if(temp==NULL) return false;
	prev->next = temp->next;
	delete(temp);
	return true;
}
//Doc Ngay Thang Nam
void Doc_Date(ifstream &filein,DATE &x){
	filein >> x.ngay;
	filein.ignore();
	filein >> x.thang;
	filein.ignore();
	filein >> x.nam;
	
}
//Doc ThongTin 1 Buu kien
void Doc_1(ifstream &filein,BK &x){
	filein >> x.mabd;
	filein.ignore();
	getline(filein,x.nggui,',');
	getline(filein,x.ngnhan,',');
	getline(filein,x.diachi,',');
	getline(filein,x.nd,',');
	filein >> x.trongluong;
	filein.ignore();
	filein >> x.dongia;
	filein.ignore();
	Doc_Date(filein,x.ngaygui);
}
//Doc ThongTin Nhieu Buu kien
void Doc_All(ifstream &filein,LIST &l){
	while(!filein.eof()){
		//B1:Doc thong tin buu kien
		BK x;
		Doc_1(filein,x);
		//B2:Tao NODE
		NODE newnode= makenode(x);
		//B3:Them bk vao DSLK don
		if (filein.peek() == EOF)break;// kiem tra neu da ket thuc tep
		ThemCuoi(l,newnode);
	}
}

//Ham Xuat
void Xuat(BK x){
	cout << "\nMa Buu Dien    : " << x.mabd;
	cout << "\nNguoi Gui      : " << x.nggui;
	cout << "\nNguoi Nhan     : " << x.ngnhan;
	cout << "\nDia chi        : " << x.diachi;
	cout << "\nNoi Dung       : " << x.nd;
	cout << "\nTrong Luong    : " << x.trongluong;
	cout << "\nDon gia        : " << x.dongia;
	cout << "\nNgay Gui(d/m/y): " << x.ngaygui.ngay<<"/"<<x.ngaygui.thang<<"/"<<x.ngaygui.nam;
}
//Xuat DanhSach
void XuatDanhSach(LIST l){
	int dem=1;
	for(NODE k=l.head;k!=NULL;k=k->next){
		cout << "\n\t\t\t Buu Kien "<< dem++;
		Xuat(k->data);
	}
}
void out(){
	cout << "\n-----------------------------"<<endl;
	cout << "      QUAN LI BUU KIEN!      " <<endl;
	cout << "1.Them buu kien."<<endl;
	cout << "2.Xoa buu kien."<<endl;
	cout << "3.In danh sach buu kien."<<endl;
	cout << "-----------------------------"<<endl;
	cout << "Nhap lua chon cua ban: ";
}
void NhapThongTin(ofstream &fileout,BK &x){
	cout << "\nNhap ma buu dien : ";cin>>x.mabd;fileout<<x.mabd;cin.ignore();
	cout << "Nhap ten nguoi gui : ";getline(cin,x.nggui);fileout<<x.nggui;
	cout << "Nhap ten nguoi nhan: ";getline(cin,x.ngnhan);fileout<<x.ngnhan;
	cout << "Dia chi            : ";getline(cin,x.diachi);fileout<<x.diachi;
	cout << "Noi Dung           : ";getline(cin,x.nd);fileout<<x.nd;
	cout << "Khoi Luong Buu Kien: ";cin>>x.trongluong;fileout<<x.trongluong;
	cout << "Don gia            : ";cin>>x.dongia;fileout<<x.dongia;cin.ignore();
	cout << "Ngay gui           : "<<endl;
	cout << "Nhap ngay : ";cin>>x.ngaygui.ngay;fileout<<x.ngaygui.ngay;
	cout << "Nhap thang: ";cin>>x.ngaygui.thang;fileout<<x.ngaygui.thang;
	cout << "Nhap nam  : ";cin>>x.ngaygui.nam;fileout<<x.ngaygui.nam;
//	fileout << x.mabd << "," << x.nggui << "," << x.ngnhan << "," << x.diachi << "," << x.nd << "," << x.trongluong << "," << x.dongia << "," << x.ngaygui.ngay << "/" << x.ngaygui.thang << "/" << x.ngaygui.nam;
}

int main(){
	LIST l;KhoiTaoDanhSach(l);
	ifstream filein;
	filein.open("input.txt",ios::in);
	Doc_All(filein,l);
	int option;while(1){
		out();
		cin>>option;
		switch(option){
//			case 1:
//			NhapThongTin(fileout,x);
//			ThemCuoi(l,makenode(x));
//				fileout<<endl;
//				break;
			case 2:
				int target;cout<<"Nhap ma buu dien can xoa: ";cin>>target;
				if(Xoa(l,target))cout<<"Xoa thanh cong!";
				else cout <<"Khong tim thay ma buu dien can xoa!";	
				break;
			case 3:
				XuatDanhSach(l);
				break;
			default:
				cout << "Lua chon khong hop le!";
		}
	}
	
	

	
	filein.close();
}
    
