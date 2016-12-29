#include<fstream>
#include<iomanip>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
class student
{
	int rollno;
	char name[50];
	int ppl,se,spt,dms,mp,poc;
	float per;
	char grade;
	void calculate();
public:
	void getdata();
	void showdata();
	void res();
	void show_tabular();
	int retrollno();
};
void student::calculate()
{
	per=(ppl+se+spt+dms+mp+poc)/6.0;
	if(per>=75.0)
		grade='A';
	else if(per<75.0 && per>=60.0)
		grade='B';
	else if(per<60.0 && per>=45.0)
		grade='C';
	else if(per<45.0 && per>=36.0)
		grade='D';
	else
		grade='F';
}
void student::res()
{
	if(per>36.0)
	cout<<"\n Result : PASS";
	else
	cout<<"\n Result : FAIL";
}
void student::getdata()
{
	cout<<"\n Enter Roll Number :";
	cin>>rollno;
	cout<<"\n Enter Name :";
	gets(name);
	cout<<"\t\t\t MARKS out of 100 ";
	cout<<"\n Enter marks of PPL : ";
	cin>>ppl;
	cout<<"\n Enter marks of SE : ";
	cin>>se;
	cout<<"\n Enter marks of SPT : ";
	cin>>spt;
	cout<<"\n Enter marks of DMS : ";
	cin>>dms;
	cout<<"\n Enter marks of MP : ";
	cin>>mp;
	cout<<"\n Enter marks of POC : ";
	cin>>poc;
	calculate();
}
void student::showdata()
{
	cout<<"\n Roll number : "<<rollno;
	cout<<"\t\t\t\t\t Name : "<<name<<"\n\t\t\t\tMARKS";
	cout<<"\n PPL : "<<ppl;
	cout<<"\t\t\t\t\t\t SE : "<<se;
	cout<<"\n SPT : "<<spt;
	cout<<"\t\t\t\t\t\t DMS: "<<dms;
	cout<<"\n MP:"<<mp;
	cout<<"\t\t\t\t\t\t\t POC :"<<poc;
	cout<<"\n Percentage :"<<per;
	cout<<"\t\t\t\t\t Grade :"<<grade;
	res();
}
void student::show_tabular()
{
	const char separator = ' ';
	cout<<rollno<<""<<setw(15)<<setfill(separator)<<name
	<<setw(9)<<setfill(separator)<<ppl<<setw(5)
	<<setfill(separator)<<se<<setw(6)<<setfill(separator)
	<<spt<<setw(6)<<setfill(separator)<<dms<<setw(5)
	<<setfill(separator)<<mp<<setw(6)<<setfill(separator)<<
	poc<<setw(12)<<setfill(separator)<<per
	<<setw(8)<<""<<setfill(separator)<<grade<<endl;
}
int  student::retrollno()
{
	return rollno;
}
void write_student();
void display_all();
void display_sp(int);
void modify_student(int);
void delete_student(int);
void student_password();
void dataentry_password();
void class_result();
void result();
void result1();
void entry_menu();
void main()
{
	int choice;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);
	clrscr();
	do
	{
		cout<<"\n\n 1.STUDENT ";
		cout<<"\n\n 2.DATA ENTRY OPERATOR ";
		cout<<"\n\n 3.EXIT ";
		cout<<"\n\n Enter your choice (1 TO 3) : ";
		cin>>choice;
		switch(choice)
		{
			case 1: student_password();
				break;
			case 2: dataentry_password();
				break;
			case 3: exit(0);
			default:
			{
			       cout<<"\n\n WRONG CHOICE "<<"\n\n PLEASE TRY AGAIN....\n";
			}

		}
	  }while(choice!=3);
getch();
}
void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("marks.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write((char *) &st, sizeof(student));
	outFile.close();
	cout<<"\n\n Student Record Has Been Created Sucessfully !!!";
	cin.ignore();
	getch();
}
void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("marks.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !!! Press any Key...";
		getch();
		return;
	}
	cout<<"\n\n\n\t\t\t   DISPLAY ALL RECORD !!!\n\n";
	while(inFile.read((char *) &st, sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n================================================================================\n";
	}
	inFile.close();
	getch();
}
void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("marks.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		getch();
		return;
	}
	int flag=0;
	while(inFile.read((char *) &st, sizeof(student)))
	{
		if(st.retrollno()==n)
		{
			 st.showdata();
			 flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\n\t Record Does Not Exist";
	getch();
}
void modify_student(int n)
{
	int found=0;
	student st;
	fstream File;
	File.open("marks.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		getch();
		return;
	}
	while(File.read((char *) &st, sizeof(student)) && found==0)
	{
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\n\t Please Enter The New Details of student "<<endl;
			st.getdata();
			int pos=(-1)*sizeof(st);
			File.seekp(pos,ios::cur);
			File.write((char *) &st, sizeof(student));
			cout<<"\n\n\t Record Updated Successfully !!!";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n\t Record Not Found ";
	getch();
}
void delete_student(int n)
{
	student st;
	int found=0;
	char confirm;
	ifstream infile;
	infile.open("marks.dat",ios::in|ios::binary);
	if(!infile)
	cout<<"\n\n\t File could not be open !! Press any Key...";
	ofstream outfile;
	outfile.open("Temp.dat",ios::out|ios::app|ios::binary);
	while(!infile.eof())
	{
		infile.read((char *) &st, sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			found=1;
			cout<<"\n\n\t ARE YOU SURE YOU WANT TO DELETE THIS RECORD (Y/N)... ";
			cin>>confirm;
			if(confirm=='n')
				outfile.write((char *) &st, sizeof(student));
			else
			cout<<"\n\n\t Record Deleted ..";
		}
		else
			outfile.write((char *) &st, sizeof(student));
		infile.read((char *) &st, sizeof(student));
	}
	if(found==0)
		cout<<"\n\n\t RECORD NOT FOUND ";
	outfile.close();
	infile.close();
	remove("marks.dat");
	rename("Temp.dat","marks.dat");
getch();
}
void student_password()
{
	char confirm;
	int i=0;
	char username[50], password[50];
	char username1[50]="vipul", password1[50]="12345678",p;
	clrscr();
	cout << "\n\nEnter Username : ";
	cin>>username;
	if(strlen(username) < 4)
	{
		cout << "\n\nUsername length must be atleast 4 characters long.";
	}
	else
	{
		cout << "\n\nEnter Password : ";
		while((p=getch())!= 13)
		{
			password[i++] = p;
			printf("*");
		}
		password[i]=NULL;
		if(strlen(password) < 6)
		{
			cout << "\n\nPassword length must be atleast 6 characters long.";
		}
		else if(!strcmp(username,username1) && !strcmp(password,password1))
		{
			cout << "\n\nYOU HAVE SUCCESSFULLY LOGGED IN!!!" << endl;
			result1();
			do
			{
				cout<<"\n\n DO YOU WANT TO CONTINUE (Y/N): ";
				cin>>confirm;
				if(confirm=='Y'|confirm=='y')
				{
					clrscr();
					result1();
				}
				else
				exit(0);
			}while(confirm!='N'|confirm!='n');
			exit(0);
		}
		else
		{
			cout << "\n\nSORRY!!!YOU HAVE ENTERED WRONG DETAILS " << endl;
			cout << "\n\nPLEASE!!!TRY AGAIN.... ";
		}
	}
}
void dataentry_password()
{
	int i=0;
	char username2[50],password2[50],ch;
	char username3[50]="dataentry",password3[50]="1234567890",q;
	clrscr();
	cout << "\n\nEnter Username : ";
	cin>>username2;
	if(strlen(username2) < 4)
	{
		cout << "\n\nUsername length must be atleast 4 characters long.";
	}
	else
	{
		cout << "\n\nEnter Password : ";
		while((q=getch())!= 13)
		{
			password2[i++] = q;
			printf("*");
		}
		password2[i]=NULL;
		if(strlen(password2) < 6)
		{
			cout << "\n\nPassword length must be atleast 6 characters long.";
		}
		else if(!strcmp(username2,username3) && !strcmp(password2,password3))
		{
			cout << "\n\nYOU HAVE SUCCESSFULLY LOGGED IN!!!" << endl;
			do
			{
				cout<<"\n\n\n\tMAIN MENU";
				cout<<"\n\n\t1. RESULT MENU";
				cout<<"\n\n\t2. ENTRY/EDIT MENU";
				cout<<"\n\n\t3. EXIT";
				cout<<"\n\n\tPlease Select Your Option (1-3) : ";
				cin>>ch;
				clrscr();
				switch(ch)
				{
					case '1': result();
						  break;
					case '2': entry_menu();
						  break;
					case '3':
						 exit(0);
					default :
					{
						  cout<<"\n\n WRONG CHOICE "<<"\n\n PLEASE TRY AGAIN....\n";
					}
				 }
			}while(ch!=3);
		}
		else
		{
			cout << "\n\nSORRY!!!YOU HAVE ENTERED WRONG DETAILS " << endl;
			cout << "\n\nPLEASE !!!TRY AGAIN.... ";
		}
       }
}
void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("marks.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\n\n File could not be open !!! Press any Key...";
		getch();
		return;
	}
	cout<<"\n\n\t\t\t    ALL STUDENTS RESULT \n\n";
	cout<<"================================================================================\n";
	cout<<"R.No       Name        PPL   SE   SPT   DMS   MP   POC    Percentage   Grade"   <<endl;
	cout<<"================================================================================\n";
	while(inFile.read((char *) &st, sizeof(student)))
	{
		st.show_tabular();
	}
	getch();
	inFile.close();
}
void result()
{
	char ch;
	int rno;
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\t4. EXIT";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? :";
	cin>>ch;
	clrscr();
	switch(ch)
	{
		case '1' : class_result();
			   break;
		case '2' : cout<<"\n\n\tEnter Roll Number of student : ";
			   cin>>rno;
			   display_sp(rno);
			   break;
		case '3' : break;
		case '4' : exit(0);
		default  :cout<<"\a";
	}
}
void result1()
{
	char ch;
	int rno;
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\t1. Student Report Card";
	cout<<"\n\n\t2. EXIT";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? :";
	cin>>ch;
	clrscr();
	switch(ch)
	{
		case '1' : cout<<"\n\n\tEnter Roll Number of student : ";
			   cin>>rno;
			   display_sp(rno);
			   break;
		case '2' : exit(0);
		default  : cout<<"\a";
	}
}
void entry_menu()
{
	char ch;
	int num;
	clrscr();
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	clrscr();
	switch(ch)
	{
		case '1':write_student();
			 break;
		case '2':display_all();
			 break;
		case '3':cout<<"\n\n\tPlease Enter roll number :";
			 cin>>num;
			 display_sp(num);
			 break;
		case '4':cout<<"\n\n\tPlease Enter roll number :";
			 cin>>num;
			 modify_student(num);
			 break;
		case '5':cout<<"\n\n\tPlease Enter roll number :";
			 cin>>num;
			 delete_student(num);
			 break;
		case '6':break;
		default: cout<<"\a";
			 entry_menu();
	}
}


