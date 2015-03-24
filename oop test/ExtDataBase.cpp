#include "ExtDataBase.h"


ExtDataBase::ExtDataBase() {
	ifstream ifs;
	ofstream ofs;
	ifs.open("DirectoryStorage.txt");

	if (ifs.is_open()) {
		getline(ifs, _currentLocation);
	}
	else {
		ofs.open("DirectoryStorage.txt");
		ofs << DEFAULT_SAVE_LOCATION;
		_currentLocation = DEFAULT_SAVE_LOCATION;
	}
	ifs.close();
	ofs.close();
}

ExtDataBase::~ExtDataBase()
{
}

string ExtDataBase::getLocation() {
	return _currentLocation;
}

string ExtDataBase::setLocation(Storage& _storage, string newDirectory) {

	newDirectory = newDirectory.substr(0, newDirectory.size() - 2);
	ofstream ofs;
	ofs.open(newDirectory);
	bool isOpen = false;
	isOpen = ofs.is_open();
	if (isOpen) {
		ofstream out;
		out.open("DirectoryStorage.txt");
		out << newDirectory;
		out.close();
		ofs.close();
		int ensure = remove(_currentLocation.c_str()); 
		assert(ensure == 0);
		_currentLocation = newDirectory;
		autoSave(_storage);
		return MESSAGE_DIRECTORY_CHANGED;
	}
	else{
		ofs.close();
		return MESSAGE_DIRECTORY_NOT_CHANGED;
	}
}

void ExtDataBase::autoSave(Storage& _storage) {
	
	ofstream ofs;
	size_t _size = _storage.getSize();
	list<StickyNote>::iterator iter;
	iter = _storage.getIter();

	ofs.open(_currentLocation);
	assert(ofs.is_open() == true);
	for (size_t i = 0; i < _size; i++, iter++){
		ofs << _storage.oneTaskInfoTypeTwo(iter);
	}
	ofs.close();
	return;
}

vector<string>* ExtDataBase::getContent() {

	vector<string>* vec = new vector<string> ;
	ifstream ifs(_currentLocation);
	string line;

	if (ifs.is_open()) {
		while (ifs) {
			if (!ifs) {
				break;
			}
			getline(ifs, line);

			line = "add " + line;
			vec->push_back(line);
		}
	}
	if (vec->size() > 0) {
		vec->pop_back(); // gets rid of unwanted last empty input from ifs.
	}

	return vec;
}

void ExtDataBase::archive(string done) {

	ofstream ofs;
	ofs.open("../archive.txt", ios::app);
	if (ofs.is_open()) {
		ofs << done << endl;
	}
	ofs.close();
	return;
}
