#include "ExtDataBase.h"


ExtDataBase::ExtDataBase() {
	getLocation();
}

ExtDataBase::~ExtDataBase()
{
}

//@author A0108375A
string ExtDataBase::getLocation() {
	ifstream ifs;
	ofstream ofs;
	ifs.open("../DirectoryStorage.txt");

	if (ifs.is_open()) {
		getline(ifs, _currentLocation);
	}
	else {
		ofs.open("../DirectoryStorage.txt");
		ofs << DEFAULT_SAVE_LOCATION;
		_currentLocation = DEFAULT_SAVE_LOCATION;
	}

	ifs.close();
	ofs.close();

	return _currentLocation;
}

//@author A0108375A
string ExtDataBase::setLocation(Storage& _storage, string newDirectory, bool& successful) {
	ofstream ofs;
	ofs.open(newDirectory);

	bool isOpen = false;
	isOpen = ofs.is_open();
	
	try{
		if (isOpen) {
			ofstream out;

			getLocation();
			int ensure = remove(_currentLocation.c_str());
			assert(ensure == 0);

			out.open("../DirectoryStorage.txt");
			out.clear();
			out << newDirectory;
			out.close();
			ofs.close();
			getLocation();
			successful = true;
			return MESSAGE_DIRECTORY_CHANGED;
		}
		else{
			ofs.close();
			successful = false;
			throw MESSAGE_DIRECTORY_NOT_CHANGED;
		}
	}
	catch (string e){
		return e;
	}
}

//@author A0110748J
void ExtDataBase::autoSave(Storage& _storage) {
	ofstream ofs;
	size_t _size = _storage.getSize();
	list<StickyNote>::iterator iter;

	iter = _storage.getIter();
	getLocation();
	ofs.open(_currentLocation);
	assert(ofs.is_open() == true);

	for (size_t i = 0; i < _size; i++, iter++){
		if (iter->getStatus() != "cleared"){
			ofs << _storage.oneTaskInfoTypeTwo(iter);
		}
	}

	ofs.close();

	return;
}

//@author A0108341R
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

//@author A0093863U
void ExtDataBase::archive(string done) {
	ofstream ofs;
	ofs.open("../archive.txt", ios::app);
	if (ofs.is_open()) {
		ofs << done << endl;
	}
	ofs.close();

	return;
}
