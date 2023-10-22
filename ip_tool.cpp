#include <iostream>
#include <cstdio>
#include <string.h>
#include <cstdlib>


using namespace std;

char gateAddress[14];
int num=0;

void filterGateAdress(char lineGateAdress[128]){
	int i=12;
	for (int k=0; k<14; k++) {
		if(lineGateAdress[i] != ' ')
			gateAddress[k] = lineGateAdress[i];
		else{
			for(int j=k; j<14; j++)
				gateAddress[j] = ' ';
			k=14;
		}

		i++;
	}
}

int partGateAdress(){
	int num;
	for(num = 0; gateAddress[num + 2] != ' '; num++);
	return num;
}

bool isConnected(char pingBuffer[2]){
	return pingBuffer[0] != 'X';
}

int visibility =0;

void openSettings() {

	cout<<"type 0 to keep the default settings"<<endl;
	cout<<"type 1 to view all scaning data"<<endl;
	cout<<"type 2 to enter debug mode"<<endl;
	cin>>visibility;
	system("clear");
	cout<<"----ipsearcher(1.0)----"<<endl<<endl;
}



int main(){
	system("clear");

	int ping_number=10;

	cout<<"----ipsearcher(v1.0)----"<<endl;


	cout<<endl;

	int hostsConnected=0;

	openSettings();

	int timeout=0;

	cout<<"enter scanning timeout limit(ms): ";
	cin>>timeout;
	cout<<endl;

	cout<<"select the number of ports to be scanned: ";
	cin>>num;

	cout<<endl;
	cout<<"scanning "<<num<<"ports..."<<endl;
	cout<<endl;

	const char* getGateAdress = "ip r | grep default";
	string pingLine="sh -c \"A=\\`fping -c1 -t" + to_string(timeout) + " ";

	FILE* pipe = popen(getGateAdress, "r");

	char pingBuffer[16];


	char bashBuffer[128];
	char lineGateAdress[128];

	while(fgets(bashBuffer, sizeof(bashBuffer), pipe) != NULL){
		for(int i = 0; i < 128; i++)
			lineGateAdress[i] = bashBuffer[i];
		if(visibility==2)
			cout<<bashBuffer<<endl;
		
	}

	filterGateAdress(lineGateAdress);

	
	string prefix = "";
	int gateAddrLen = partGateAdress() + 1;
	for(int i=0; i < gateAddrLen; i++) {
		pingLine += gateAddress[i];
		prefix += gateAddress[i];
	}

	string pingLineDyn=pingLine;
	
	for(int i=1; i<num; i++) {
		pingLineDyn = pingLine+to_string(i) + "\\` 2>/dev/null && echo -n \\$A | grep -oP ', \\K[0-9]+.[0-9]+' | tr -d '\\n' || echo -n X\"";
		FILE*papa = popen(pingLineDyn.c_str(), "r");
		if(fgets(pingBuffer, sizeof(pingBuffer), papa) !=NULL){
			if(visibility==2)
				cout<< "pingbuf: " << pingBuffer<<endl;
			if(isConnected(pingBuffer)) {
				cout<<"connected host: "<<prefix<<to_string(i)<< " ping: " << pingBuffer << "ms " << endl;
				hostsConnected++;
			}
			else if(visibility==1||visibility==2)
					cout<<"host unreachable: "<<prefix<<to_string(i)<<endl;


		}
		fclose(papa);
	}
	cout<<endl;
	cout<<"Found: "<<hostsConnected<<" connected devices";
	cout<<endl;

	return 0;
}

