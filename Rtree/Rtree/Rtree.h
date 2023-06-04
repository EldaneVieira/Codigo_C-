#pragma once
class Rtree
{

private:
	FILE *handle;
	struct Header {
		unsigned int pageCount;
		unsigned int rootPage;
		unsigned int pageSize;
		unsigned int height;
	} header;



	struct Entry {
		int previous, successor;//o nó será folha se previous e sucessor forem -1
		vector <char> info;
	} entry;

	struct Page {
		vector <struct Entry> elements;
	}page;

public:
	Rtree(char *filename, int pageSize);
	~Rtree();

	static const int maxElementPerPage = 1;

	int GetPageCount();
	int GetHeight();
	void WritePage(int position, vector<char> buffer);
	void ReadPage(int position);
	void UpdateRootPage(int newValue);
	void UpdateHeight(int newValue);
	void SearchInsertionPosition();
	void ManageCreationPage(vector<char> info);
	void CreatePage();
	void CreateRootPage();
	


};

