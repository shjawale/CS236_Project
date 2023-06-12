#include <iostream>

using namespace std;

#define MAX_BUFFER_SIZE 1024

int main (int argc, char* argv[]) {

	if (argc != 2) {
		cout << "Need to put input file during compilation\n";
		return 1;
	}

	tSize readByte = 0;
	char buffer[MAX_BUFFER_SIZE];
	memset(buffer, '\0', MAX_BUFFER_SIZE);

	hdfsFS fs = hdfsConnect("localhost", 9000);
	if(!fs) {
		cout << "failed to connect to HDFS\n";
		return 1;
	}

	hdfsFile readFile = hdfsOpenFile(fs, argv[1], O_RDONLY, 0, 0, 0);
	if (!readFile) {
		cout << "failed to open HDFS file: " << argv[1] << endl;
		return 1;
	}

	readByte = hdfsRead(fs, readFile, (void*)buffer, MAX_BUFFER_SIZE);
	while(readByte > 0) {
		cout << buffer;
		memset(buffer, '\0', MAX_BUFFER_SIZE);
		readByte = hdfsRead(fs, readFile, (void*)buffer, MAX_BUFFER_SIZE);
	}
	cout << endl;

	hdfsCloseFile(fs, readFile);
	hdfsDisconnect(fs);
	
	return 0;
}
