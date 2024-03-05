#include<iostream>
#include<fstream>

using namespace std;



class Helper
{
public:

	static int StringLength(const char* str)
	{
		int size = 0;
		for (int i = 0; str[i] != 0; i++)
		{
			size++;
		}
		return size;
	}
	static void GetStringFromBuffer(const char* temp, char*& str)
	{
		int len = StringLength(temp);
		str = new char[len + 1];
		for (int i = 0; i <= len; i++)
		{
			str[i] = temp[i];
		}
	}

	static bool compareString(const char* str, const char* str2)
	{
		bool flag = true;
		for (int i = 0; i < StringLength(str); i++)
		{
			if (str[i] != str2[i])
			{
				flag = false;
			}
		}
		return flag;
	}

	static char* ConcateIntAndString(const char* str, int num)
	{
		int str_len = StringLength(str);

		int num_copy = num;
		int num_len = 0;
		while (num_copy > 0) {
			num_copy /= 10;
			num_len++;
		}

		char* result = new char[str_len + num_len + 1];

		int i = 0;
		while (str[i] != '\0') {
			result[i] = str[i];
			i++;
		}

		int j = i + num_len - 1;
		while (num > 0) {
			result[j] = '0' + (num % 10);
			num /= 10;
			j--;
		}

		result[str_len + num_len] = '\0';
		return result;
	}


};

class FaceBook;
class Users;
class Pages;
class Date;
class Post;
class Activity;
class Memory;
class Object;
class Comment;
class Activity
{
	int type;
	char* value;
public:
	Activity()
	{
		type = 0;
		value = 0;
	}
	~Activity()
	{
		delete[]value;
	}
	void Print()
	{
		if (type == 1)
		{
			cout << "feeling " << value;

		}

		else if (type == 2)
		{
			cout << "thinking about " << value;
		}
		else if (type == 3)
		{
			cout << "Making " << value;
		}
		else if (type == 4)
		{
			cout << "celebrating " << value;
		}
	}

	void ReadDataFromFile(ifstream& inp)
	{
		char temp[100];
		inp >> type;
		inp.getline(temp, '100');
		Helper::GetStringFromBuffer(temp, value);
	}

	void SetValue(char* text)
	{
		Helper::GetStringFromBuffer(text, value);
	}
};
class Date
{
	int day;
	int month;
	int year;

public:

	static Date CurrentDate;

	Date(int x = 0, int y = 0, int z = 0)
	{
		day = x;
		month = y;
		year = z;
	}

	void ReadDataFromFile(ifstream& inp)
	{
		inp >> day;
		inp >> month;
		inp >> year;
	}

	bool compare(const Date& rhs, bool isMemory)
	{
		if (isMemory == false)
		{
			if(year != rhs.year)
			{
				return false;
			}

			else if (month == rhs.month)
			{
				if (day == rhs.day)
				{
					return true;
				}
				else if (day + 1 == rhs.day || day - 1 == rhs.day)
				{
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
		{
			if (year == rhs.year)
			{
				return false;
			}
			else
			{
				if (month == rhs.month)
				{
					if (day == rhs.day)
					{
						return true;
					}
					else if (day + 1 == rhs.day || day - 1 == rhs.day)
					{
						return true;
					}
					else
						return false;
				}
				else
					return false;
			}
		}
	}

	static int YearDiff(Date lhs , Date rhs)
	{
		int ans;
		ans = lhs.year-rhs.year;
		if(ans<0)
		{
			ans = -ans;
		}
		return ans;
	}

	void Print()
	{
		cout << day << "/" << month << "/" << year;
	}

	void SetData(int d , int m , int y)
	{
		day = d;
		month = m;
		year = y;
	}
};

Date Date::CurrentDate = 0;

class Post
{
	char* Id;
	char* text;
	Date sharedDate;
	Object* sharedBy;
	Object** LikedBy;
	Comment** comments;
	Activity* activity;

	int totalLikedBy;
	int totalComment;

	static int TotalPosts;
public:

	~Post()
	{
		delete[] Id;
        delete[] text;
		if(LikedBy!= 0)
        delete[] LikedBy;
        if(comments != 0)
        delete[] comments;
		if(activity!= 0)
        delete activity;
	}

	Post(const char* txt, Object* SharedBy, Date currentDate)
	{

		activity = 0;
		char* IdForNewPost = Helper::ConcateIntAndString("post" , TotalPosts+1);

		Helper::GetStringFromBuffer(IdForNewPost , Id);
		Helper::GetStringFromBuffer(txt, text);
		sharedBy = SharedBy;
		sharedDate = currentDate;
		totalComment = 0;
		totalLikedBy = 0 ;
	}
	Post()
	{
		Id = 0;
		text = 0;
		sharedBy = 0;
		LikedBy = 0;
		comments = 0;
		activity = 0;
		totalComment = 0;
		totalLikedBy =0 ;
	}
	

	void ReadDataFromFile(ifstream& inp);
	void SetSharedBy(Object* ptr)
	{
		sharedBy = ptr;
	}
	void SetLikedBy(Object* ptr)
	{
		if (totalLikedBy == 0)
		{
			LikedBy = new Object * [10];
			for (int i = 0; i < 10; i++)
			{
				LikedBy[i] = 0;
			}
			LikedBy[totalLikedBy] = ptr;
			totalLikedBy++;
		}
		else
		{
			LikedBy[totalLikedBy] = ptr;
			totalLikedBy++;
		}
	}

	void AddComment(Comment* ptr)
	{
		if (totalComment == 0)
		{
			comments = new Comment*[10];
			for (int i = 0; i < 10; i++)
			{
				comments[i] = 0;
			}
			comments[totalComment] = ptr;
			totalComment++;
		}
		else
		{
			comments[totalComment] = ptr;
			totalComment++;
		}
	}

	bool CompareDate(Date currentDate, bool isMemory)
	{
		if (currentDate.compare(sharedDate, isMemory))
		{
			return true;
		}
		else
			return false;
	}

	void ViewLikedList();

	virtual void Print(bool& flag);
	void Print();

	Date GetSharedDate()
	{
		return sharedDate;
	}

	char* GetId()
	{
		return Id;
	}

};
int Post::TotalPosts = 0;

class Memory : public Post
{
	Post* Original;
public:
	Memory()
	{
		Original = 0;
	}
	~Memory()
	{
		delete Original;
	}
	
	Memory(Post*& oldPost, const char* text, Object* userptr , Date currentDate ) :Post(text, userptr , currentDate)
	{
		Original = oldPost;
	}
	void Print(bool& flag)
	{
		cout << "Shared a memory (" << Date::YearDiff(Original->GetSharedDate() , GetSharedDate()) << " years) ago" << endl;;
		Original->Print(flag);
		flag = true;
	}

	Post* GetOriginalPost()
	{
		return Original;
	}
};
class Object
{
	char* Id;

public:
	Object()
	{
		Id = 0;
	}
	virtual ~Object()
	{
		delete[]Id;
	}
	char* GetID();
	void SetID(char* ptr);
	void SetId(char* id);
	virtual void Print()
	{
		cout << Id;
	}
	virtual void PrintForHome()
	{
		cout << "Error	Not Found!!!!!!!!" << endl;
	}
	virtual void AddPostToTimeline(Post* ptr)
	{
		cout << "Error	Not Found!!!!!!!!" << endl;

	}

};
class Comment
{
	Object* CommentBy;
	char* Text;
	char* Id;

	static int TotalComments;
public:
	Comment(Object* CurrentUser , char* txt)
	{
		char* IdForNewComment = Helper::ConcateIntAndString("c" , TotalComments+1);
		Text = txt;
		CommentBy = CurrentUser;
		Id = IdForNewComment;
	}

	Comment()
	{
		CommentBy = 0;
		Text = 0;
		Id = 0;
	}
	~Comment()
	{
		delete CommentBy;
		delete[]Text;
		delete[]Id;
	}

	void SetValues(char* idStr, char* textStr, Object* commentByPtr)
	{
		CommentBy = commentByPtr;
		Helper::GetStringFromBuffer(textStr, Text);
		Helper::GetStringFromBuffer(idStr, Id);
		TotalComments++;
	}

	void Print()
	{
		CommentBy->PrintForHome();
		cout << " wrote:" << Text << endl;
	}

};
int Comment::TotalComments = 0;

class Pages : public Object

{
	char* Title;
	Post** timeline;

	int totalTimeline;
public:
	Pages()
	{
		Title = 0;
		timeline = 0;
		totalTimeline = 0;
	}
	~Pages()
	{
		delete[] Title;
        if(timeline!= 0)
        delete[] timeline;
	}

	void ReadDataFromFile(ifstream& inp)
	{
		char temp[50];
		inp >> temp;
		char* ptr;
		Helper::GetStringFromBuffer(temp, ptr);
		SetID(ptr);
		inp.ignore();
		inp.getline(temp, 50, '\n');
		Helper::GetStringFromBuffer(temp, Title);
		//delete[]ptr;
		//ptr= 0;
	}

	void PrintForHome()
	{
		cout << Title;
	}

	void AddPostToTimeline(Post* ptr)
	{
		if (totalTimeline == 0)
		{
			timeline = new Post * [10];
			for (int i = 0; i < 10; i++)
			{
				timeline[i] = 0;
			}
			timeline[totalTimeline] = ptr;
			totalTimeline++;
		}
		else
		{
			timeline[totalTimeline] = ptr;
			totalTimeline++;
		}
	}

	void CheckDate(Date CurrentDate, bool isMemory)
	{
		bool temp = false;
		for (int i = 0; i < totalTimeline; i++)
		{
			if (timeline[i]->CompareDate(CurrentDate, isMemory))
			{
				timeline[i]->Print(temp);
			}
		}
	}

	void Print()
	{

		cout << this->GetID() << "\t" << Title << endl;
	}

	void ViewTimeline()
	{
		bool temp = false;
		if(timeline != 0)
		{
			for(int i=0 ; i<totalTimeline ; i++)
			{
				timeline[i]->Print(temp);
			}
		}
	}


	char* GetId()
	{
		return this->GetID();
	}
	

};
class Users :public Object
{
	char* Fname;
	char* Lname;
	Pages** LikedPages;
	Users** FriendList;
	Post** timeline;

	int totalTimeline;
	int numPages;
	int numFriends;

public:
	Users()
	{
		Fname = 0;
		Lname = 0;
		LikedPages = nullptr;
		FriendList = nullptr;
		timeline = nullptr;
		totalTimeline = 0;
		numPages = 0;
		numFriends = 0;
	}
	~Users()
	{
		delete[] Fname;
        delete[] Lname;
		if(LikedPages!= 0)
        delete[] LikedPages;
		if(FriendList!= 0)
        delete[] FriendList;
        if(timeline!= 0)
        delete[] timeline;
	}


	void ReadDataFromFile(ifstream& inp)
	{
		char temp[50];
		inp >> temp;
		char* ptr;
		Helper::GetStringFromBuffer(temp, ptr);
		SetID(ptr);
		inp >> temp;
		Helper::GetStringFromBuffer(temp, Fname);
		inp >> temp;
		Helper::GetStringFromBuffer(temp, Lname);
	}

	void SetPage(Pages* ptr)
	{
		if (numPages == 0)
		{
			LikedPages = new Pages * [10];
			for (int i = 0; i < 10; i++)
			{
				LikedPages[i] = 0;
			}
		}
		LikedPages[numPages] = ptr;
		numPages++;
	}

	void CheckDate(Date CurrentDate, bool isMemory)
	{
		bool temp = false;
		for (int i = 0; i < totalTimeline; i++)
		{
			if (timeline[i]->CompareDate(CurrentDate, isMemory))
			{
				timeline[i]->Print(temp);
			}
		}
	}

	void LikePost(Post* post)
	{
		post->SetLikedBy(this);
	}

	void HomePage(Date currentDate)
	{

		cout << "------------------------------------------------------------------------------" << endl;
		if (FriendList != 0)
		{
			for (int i = 0; i < numFriends; i++)
			{
				FriendList[i]->CheckDate(currentDate, false);
			}
		}

		if (LikedPages != 0)
		{
			for (int i = 0; i < numPages; i++)
			{
				LikedPages[i]->CheckDate(currentDate, false);
			}
		}
		cout << endl;
	}

	void ViewTimeline()
	{
		if(timeline!= 0)
		{
			cout << "---------------------------------------------------------------------------------" << endl;
			for(int i=0 ; i<totalTimeline ; i++)
			{
				if(timeline[i] != 0)
				{
					bool IsNewPost = false;
					timeline[i]->Print(IsNewPost);
					if(IsNewPost)
					{
						timeline[i]->Print();
					}
				}
			}
		}
	}

	void SeeMemory(Date currentDate)
	{
		bool temp = false;
		for (int i = 0; i < totalTimeline; i++)
		{
			if(timeline[i] !=0)
			{
				if (timeline[i]->CompareDate(currentDate, true))
				{
					timeline[i]->Print(temp);
				}
			}
		}
	}
	
	void PrintForHome()
	{
		cout << Fname << " " << Lname;
	}

	void SetFriend(Users* ptr)
	{
		if (numFriends == 0)
		{
			FriendList = new Users * [10];
			for (int i = 0; i < 10; i++)
			{
				FriendList[i] = 0;
			}
		}
		FriendList[numFriends] = ptr;
		numFriends++;
	}

	void AddPostToTimeline(Post* ptr)
	{
		if (totalTimeline == 0)
		{
			timeline = new Post * [10];
			for (int i = 0; i < 10; i++)
			{
				timeline[i] = 0;
			}
			timeline[totalTimeline] = ptr;
			totalTimeline++;
		}
		else
		{
			timeline[totalTimeline] = ptr;
			totalTimeline++;
		}
	}

	void ViewFriendList()
	{
		if(FriendList!=0)
		{
			cout << "---------------------------------- Friend List ----------------------------------" << endl;
			for(int i=0 ; i<numFriends ; i++)
			{
				FriendList[i]->Print();
			}
		}
	}

	void ViewLikedPages()
	{
		if(LikedPages != 0)
		{
			cout << "---------------------------------- Liked Pages ----------------------------------" << endl;
			for(int i=0 ; i<numPages ; i++)
			{
				LikedPages[i]->Print();
			}
		}
	}

	void Print()
	{
		cout << this->GetId() << "\t" << Fname << " " << Lname << endl;
	}

	//getters
	char* GetId()
	{
		return this->GetID();
	}
};
class FaceBook
{
	Pages** pages;
	Users** users;
	Post** posts;
	Comment** comments;

	static int totalUsers;
	static int totalPages;
	static int totalPosts;
	static int totalComments;
public:

	FaceBook()
	{
		pages = 0;
		users = 0;
		posts = 0;
		comments = 0;
	}
	~FaceBook()
	{
		for (int i = 0; i < totalPages; i++)
		{
			if (pages[i] != 0)
				delete pages[i];
		}
		delete[]pages;

		for (int i = 0; i < totalUsers; i++)
		{
			if (users[i] != 0)
				delete users[i];
		}
		delete[]users;

		
		for(int i=0 ; i<totalPosts ; i++)
		{
			if(posts[i] != 0)
				delete posts[i];
		}
		delete[]posts;
	}

	void LoadPages(char* filename)
	{
		ifstream inp;
		inp.open(filename);
		if (inp)
		{
			inp >> totalPages;


			pages = new Pages * [totalPages];
			for (int i = 0; i < totalPages; i++)
			{
				pages[i] = new Pages;
				pages[i]->ReadDataFromFile(inp);
			}

			inp.close();
		}
	}

	void LoadUsers(char* filename)
	{
		ifstream inp;
		inp.open(filename);
		if (inp)
		{
			inp >> totalUsers;

			users = new Users *[totalUsers];
			char*** friendList = new char**[totalUsers];
			char temp[50];

			for (int i = 0; i < totalUsers; i++)
			{
				users[i] = new Users;
				users[i]->ReadDataFromFile(inp);
				friendList[i] = new char* [10];
				for (int h = 0; h < 10; h++)
				{
					friendList[i][h] = 0;
				}
				for (int j = 0; j < 10; j++)
				{
					inp >> temp;
					if (Helper::compareString(temp, "-1"))
					{
						break;
					}
					else
						Helper::GetStringFromBuffer(temp, friendList[i][j]);
				}
				inp.ignore();

				Pages* pointer;
				for (int j = 0; j < 10; j++)
				{
					inp >> temp;
					if (Helper::compareString(temp, "-1"))
					{
						break;
					}
					else
					{
						pointer = GetPageFromId(temp);
						users[i]->SetPage(pointer);
					}
				}

			}

			//associate friends
			Users* ptr;
			for (int j = 0; j < totalUsers; j++)
			{
				for (int k = 0; k < 10; k++)
				{
					if (friendList[j][k] == 0)
					{
						break;
					}

					ptr = GetUserFromId(friendList[j][k]);
					users[j]->SetFriend(ptr);
				}
			}

			//deallocate the 3d pointer
			for (int h = 0; h < totalUsers; h++)
			{
				if(friendList[h])
				{
				for (int g = 0; g < 10; g++)
				{
					if(friendList[h][g])
					delete[]friendList[h][g];
				}
				delete[] friendList[h];
				}

			}

			inp.close();
			
			if(friendList)
			{
				delete[]friendList;
			}
			
		}

		
	}

	void PrintUser(char* str)
	{
		cout << "Set Current User " << str << endl;
		Users* ptr = GetUserFromId(str);
		ptr->Print();
	}

	Users* GetUserFromId(const char* str)
	{
		for (int i = 0; i < totalUsers; i++)
		{
			if (Helper::compareString(str, users[i]->GetId()))
			{
				return users[i];
			}
		}
		return 0;
	}

	Pages* GetPageFromId(char* str)
	{
		for (int i = 0; i < totalPages; i++)
		{
			if (Helper::compareString(str, pages[i]->GetId()))
			{
				return pages[i];
			}
		}
		return 0;
	}

	Object* GetObjectById(char* str)
	{
		if (str[0] == 'u')
		{
			return GetUserFromId(str);
		}
		else if (str[0] == 'p')
		{
			return GetPageFromId(str);
		}
		else
			return 0;
	}

	Post* GetPostById(char* str)
	{
		for (int i = 0; i < totalPosts; i++)
		{
			if (Helper::compareString(str, posts[i]->GetId()))
			{
				return posts[i];
			}
		}

		return 0;
	}

	void LoadPosts(char* filename)
	{
		ifstream inp;
		inp.open(filename);
		char temp[100];
		if (inp)
		{
			inp >> totalPosts;
			posts = new Post * [totalPosts];
			for (int i = 0; i < totalPosts; i++)
			{
				posts[i] = new Post;
				posts[i]->ReadDataFromFile(inp);
				inp >> temp;
				Object* sharedBy = GetObjectById(temp);
				posts[i]->SetSharedBy(sharedBy);
				sharedBy->AddPostToTimeline(posts[i]);
				inp >> temp;
				
				for (int j = 0; temp[0] != '-'; j++)
				{
					posts[i]->SetLikedBy(GetObjectById(temp));
					inp.ignore();
					inp >> temp;
				}
			}
		}
		inp.close();
	}

	void LoadComments(char* filename)
	{
		ifstream inp;
		inp.open(filename);

		if (inp)
		{
			inp >> totalComments;

			char tempId[100], strText[100], temp[50], tempPost[50];
			Object* commentBy;

			comments = new Comment * [totalComments];

			for (int i = 0; i < totalComments; i++)
			{
				comments[i] = new Comment;
				inp >> tempId;
				inp.ignore();

				inp >> tempPost;


				inp >> temp;
				commentBy = GetObjectById(temp);
				inp.ignore();

				inp.getline(strText, 100);

				comments[i]->SetValues(tempId, strText, commentBy);

				Post* ptr = GetPostById(tempPost);
				ptr->AddComment(comments[i]);
			}
			inp.close();
		}
	}
	// 1
	void ViewFriendList(Users* currentUser)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	ViewFriendList" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		currentUser->ViewFriendList();
	}
	// 2
	void ViewLikedPages(Users* currentUser)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	ViewLikedPages" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		currentUser->ViewLikedPages();
	}

	void ViewHome(Users* currentUser , Date currentDate)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	ViewHome" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		currentUser->HomePage(currentDate);
	}

	void ViewTimeline(Users* currentUser)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	ViewTimeline" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		currentUser->ViewTimeline();
	}

	void ViewLikedList(char* str)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	ViewLikedList(" << str << ")" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		Post* post = GetPostById(str);
		post->ViewLikedList();
	}

	void LikePost(Users* currentUser , char* post)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	LikePost(" << post << ")" << endl;

		Post* postToLike = GetPostById(post);
		currentUser->LikePost(postToLike);
	}

	void AddComment(Users* CurrentUser , char* post , char* txt)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	PostComment(" << post << " , " << txt << ")" << endl;

		Post* currentPost = GetPostById(post);
		Comment* newComment = new Comment(CurrentUser , txt);
		currentPost->AddComment(newComment);
	}

	void ViewPost(char* post)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	ViewPost(" << post << ")" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;
		bool temp = false;
		Post* currentPost = GetPostById(post);
		currentPost->Print(temp);
	}

	void ViewMemory(Users* currentUser , Date CurrentDate)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	SeeYourMemory()" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		currentUser->SeeMemory(CurrentDate);
	}

	void ShareMemory(Users* currentUSer, char* originalPostId, char* txt, Date currentDate)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	ShareMemory(" << originalPostId << "," << "\"" << txt << "\")" << endl;

		Post* originalPost = GetPostById(originalPostId);
		Memory* newPostPtr = new Memory(originalPost, txt, currentUSer , currentDate);
		currentUSer->AddPostToTimeline(newPostPtr);
	}

	void ViewPage(char* pageName)
	{
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "Command	ViewPage(" << pageName << ")" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;

		Pages* currentPage = GetPageFromId(pageName);
		currentPage->PrintForHome();
		cout << endl;
		currentPage->ViewTimeline();
	}

	void Load()
	{
		LoadPages("pages.txt");
		LoadUsers("users.txt");
		LoadPosts("posts.txt");
		LoadComments("comments.txt");
	}

	void Run(char* str)
	{
		Load();
		Users* currentUser = GetUserFromId(str);
		Date::CurrentDate.SetData(15 , 11, 2017);

		PrintUser(str);
		ViewFriendList(currentUser);
		ViewLikedPages(currentUser);

//  ALHAMDULLILAH -----------------------------------------------------------PHASE 1---------------------------------------------------------------
//  INSHA ALLAH -------------------------------------------------------------PHASE 2---------------------------------------------------------------

		ViewHome(currentUser , Date::CurrentDate);
		ViewTimeline(currentUser);
		ViewLikedList("post5");

		//command LikePost(Post5)

		LikePost(currentUser , "post5");
		ViewLikedList("post5");


		//command add comment
		ViewPost("post4");
		AddComment(currentUser , "post4" , "My Best Wishes.");
		ViewPost("post4");

		ViewPost("post8");
		AddComment(currentUser , "post8" , "Thanks for the wishes.");
		ViewPost("post8");

		//View memory
		ViewMemory(currentUser , Date::CurrentDate);

		ShareMemory(currentUser , "post10" , "Never thought I will be specialist in this field…" , Date::CurrentDate);
		ViewTimeline(currentUser);

		ViewPage("p1");

//Alhamdulillah ----------------------------------------------Phase 2 completed-----------------------------------------------------------------------------------------------
	}
};

char* Object::GetID() {
	return Id;
}
void Object::SetID(char* ptr) {
	Id = ptr;
}
void Post::ReadDataFromFile(ifstream& inp)
{
	int activityId = 0;
	inp >> activityId;
	char temp[100];
	inp >> temp;
	Helper::GetStringFromBuffer(temp, Id);
	sharedDate.ReadDataFromFile(inp);
	inp.ignore();
	inp.getline(temp, 100, '\n');
	Helper::GetStringFromBuffer(temp, text);
	if (activityId == 2)
	{
		activity = new Activity;
		activity->ReadDataFromFile(inp);
	}
	TotalPosts++;


}
void Post::Print(bool& flag)
{
	
		sharedBy->PrintForHome();
		cout << " ";
		if (activity != 0)
		{
			activity->Print();
		}
		cout << endl;
		cout << "\"" << text << "\"";
		cout << " (" ;
		sharedDate.Print();
		cout  << ") " << endl << "\t";
		for (int i = 0; i < totalComment; i++)
		{
			comments[i]->Print();
			cout << "\t";
		}
		cout << endl;
	
}
void Post::Print()
{
		sharedBy->PrintForHome();
		cout << " ";
		if (activity != 0)
		{
			activity->Print();
		}
		cout << endl;
		cout << "\"" << text << "\"";
		cout << " (" ;
		cout  << ") " << endl << "\t";
		for (int i = 0; i < totalComment; i++)
		{
			comments[i]->Print();
			cout << "\t";
		}
		cout << endl;
}
void Post::ViewLikedList()
{
	if(LikedBy != 0)
	{
		cout << "-----------------------------------------------------------------------------------------" << endl;
		for(int i=0 ; i<totalLikedBy ; i++)
		{
			LikedBy[i]->Print();
			cout << endl;
		}
	}
}

int FaceBook::totalPages = 0;
int FaceBook::totalUsers = 0;
int FaceBook::totalPosts = 0;
int FaceBook::totalComments = 0;

void main()
{
	FaceBook obj;
	obj.Run("u7");

	system("pause");
}