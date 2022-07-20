#include "Pythia8/Pythia.h"
#include "TRandom.h"
using namespace Pythia8;

void initialization_pythia(Pythia* pythia, TRandom* rndm){

  int pythiaSeed = rndm->Integer(1000000);
  char processLine[80];
  sprintf(processLine, "Random:Seed = %d",pythiaSeed);

  pythia->readString("Random:setSeed = on");
  pythia->readString(processLine); 

  //Set process type and collision energy
  pythia->readString("Charmonium:all  = on");
  pythia->readString("Beams:eCM = 13000.");

  // Switch off all J/psi decays but J/psi -> e+ e-
  pythia->readString("443:onMode = off");
  pythia->readString("443:onIfAny = 11 -11");

  // Switch off all chi_c2 decays but chi_c2 -> J/psi gamma
  pythia->readString("445:onMode = off");
  pythia->readString("445:onIfAny = 443 22");

  // Switch off all chi_c0 decays but chi_c0 -> J/psi gamma
  pythia->readString("10441:onMode = off");
  pythia->readString("10441:onIfAny = 443 22");

  // Switch off all chi_c1 decays but chi_c1 -> J/psi gamma
  pythia->readString("20443:onMode = off");
  pythia->readString("20443:onIfAny = 443 22");

  pythia->init();

  cout << "Pythia was successfully initialized!" << endl;

  return;
}
