#define DEBUG_MODE //Hehehe

#include "RunManager.hh"
#include "G4UImanager.hh"

#include "Randomize.hh"

#include "DetectorConstruction.hh"

#include "SteppingVerbose.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "QGSP_BERT_HP.hh"
#include "PhysicsList.hh"
#include "G4StepLimiterPhysics.hh"

#include "G4EmLowEPPhysics.hh"
#include "G4VModularPhysicsList.hh"
#include "G4SteppingManager.hh"
#include "G4HadronicProcessStore.hh"

#include <sstream>
#include <fstream>
#include <string>
#include "time.h"

#include "Options.hh"
#include "OutputManager.hh"

#include "UserAction.hh"
#include "PhysicsList.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
	time_t curTime;
	time(&curTime);
	cout << "Current time: " << std::put_time(std::localtime(&curTime), "%Y-%m-%d %X") << endl;
	DefOutMan = new OutputManager();
	//Parse the command line first
	//All the parsing is in the options.cc (using TCLAP)
	if(!DefOpt.parseCmd(argc, argv)) {
		cout  << "TCLAP ERROR" << endl;
		return 1;
	}
	DefOutMan->filename = DefOpt.ofile;

	//Reroute the error log
	ostringstream ename;
	ename << "errorLogs/" << std::put_time(std::localtime(&curTime), "%Y-%m-%d_%X") << ".txt";
	cout << "Errorlog filename: " << ename.str() << endl;
	fstream ferr(ename.str(), std::fstream::out);
	std::streambuf *const cerrBuf = cerr.rdbuf();
	cerr.rdbuf(ferr.rdbuf());
	cerr << "Error log for " << std::put_time(std::localtime(&curTime), "%Y-%m-%d %X") << endl;
	
	//Set the seed
	G4long seed;
	if(DefOpt.setseed != 0) {
	  cout << "Selected seed: " << DefOpt.setseed << endl;	
	  seed = DefOpt.setseed;
	}
	else {
	  cout << "Selected seed: " << "current time (" << G4long(curTime) << ")" << endl;
	  seed = G4long(curTime);
	}

	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	G4Random::setTheSeed(seed, 2);

	G4VSteppingVerbose::SetInstance(new SteppingVerbose);
	RunManager * runManager = new RunManager;
	  
	cout << "Selected number of threads: " << DefOpt.threadNum << endl;
	runManager->SetNumberOfThreads(DefOpt.threadNum);

	if(DefOpt.noHadronic) {cout << "\n\nWARNING: Hadronic processes OFF\n\n" << endl;}
	else {cout << "\nHadronic processes are ON\n" << endl;}


	if(DefOpt.useSliced) {cout << "Using a sliced detector" << endl;}
	else {cout << "Using a \"big chunk\" detector" << endl;}
	DetectorConstruction* detector;
	detector = new DetectorConstruction();
	  

	runManager->SetUserInitialization(detector);
	//
	cout << "=== Building the physics list ===" << endl;
	G4VModularPhysicsList* physList;
	if(DefOpt.useOldPL) {
	  cout << "\n\nWARNING: Using QGSP_BERT_HP!\nThis is a legacy feature and is NOT recommended.\n" << endl;
	  physList = new QGSP_BERT_HP(0);
	} else {
	  physList = new PhysicsList(0);
	}
	runManager->SetUserInitialization(physList);
	G4HadronicProcessStore::Instance()->SetVerbose(0);
	cout << "=== Finished ===" << endl;

	// Set user action classes
	//
	runManager->SetUserInitialization(new UserActionInitialization());
	//
	  
	// Initialize G4 kernel
	runManager->Initialize();
	 
	#ifdef G4VIS_USE
	// Initialize visualization
	G4VisManager* visManager = new G4VisExecutive("Quiet");
	visManager->Initialize();
	#endif

	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	if (DefOpt.mfile!="")   //Run the macros
	{
		G4String command = "/control/execute ";
		G4String fileName = DefOpt.mfile;
		UImanager->ApplyCommand(command+fileName);
	} else {
		#ifdef G4UI_USE
			G4UIExecutive* ui = new G4UIExecutive(1, &argv[0]);
			#ifdef G4VIS_USE
				if(DefOpt.vis) {UImanager->ApplyCommand("/control/execute ../source/macros/newvis.mac");}
			#endif
			ui->SessionStart();
			delete ui;
		#endif
	}
	
	// Job termination
	#ifdef G4VIS_USE
		delete visManager;
	#endif
	delete runManager;
	cout << "Ending!" << endl;
	cerr.rdbuf(cerrBuf);
	ferr.close();
	return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
