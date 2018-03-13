#include <iostream>
#include <signal.h>
#include "TCPClient.h"
#include <algorithm>

TCPClient tcp;

void sig_exit(int s)
{
	tcp.exit();
	exit(0);
}


void sendandprint2(string desc, string code){
		tcp.Send(code);		
		cout << "sent " << code << endl;
		int recv = 0;
		string s2 = "ELM320";
		string s3 = "OK";
		string s4 = ">";
		string rec ="";
		while(recv ==0){
			rec = tcp.receive();
			remove(rec.begin(), rec.end(),' ');
			cout <<"--- "<< rec.length() << endl;
			if(rec!=""){
				if (rec.find(s2) != std::string::npos) {
					cout << " receive 2 " << rec << endl;
					recv = 1;
				}
				else if (rec.find(s3) != std::string::npos) {
					cout << " receive 3 " << rec << endl;				
					recv = 1;
				}
				else if (rec.find(s4) != std::string::npos) {
					cout << " receive 4 " << rec << endl;				
					recv = 1;
				}
				else{
					cout << "wait " << rec << endl;				
				}
			}
		}
		cout << "loop finished for " <<desc << ", value = " << rec << endl;
}

void sendandprintOBD(string desc, string code){
		tcp.Send(code);		
		cout << "sent " << code << endl;
		int recv = 0;
		string back = tcp.receive();
		cout << desc <<" = " << back << endl;
		// sleep(10);			
		for(int i =0;i<3;i++){
			sleep(1);
			back = tcp.receive();
			cout << back << endl;
			if (back.find(">") != std::string::npos){
				break;
			}
		}
}
int main(int argc, char *argv[])
{
	signal(SIGINT, sig_exit);
	// tcp.setup("192.168.0.10",35000);
	tcp.setup("localhost",35000);	
	int recv = 0;
	string s2 = "ELM320";	
	string s4 = ">";	
	cout << "try to connect" <<endl;

	// warm up 
	sendandprint2("Handshake","ATZ\r");	
	sendandprint2("Handshake","ATE0\r");
	sendandprint2("Handshake","ATH0\r");
	sendandprint2("Handshake","0100\r");
	sendandprint2("Handshake","0101\r");
	while(1)
	{
		srand(time(NULL));
		sendandprintOBD(" fuel status","0103\r");
		sendandprintOBD(" air pressure","010f\r");
		sendandprintOBD(" dist","0121\r");
		sendandprintOBD(" runtime","011f\r");
	}
	return 0;
}
