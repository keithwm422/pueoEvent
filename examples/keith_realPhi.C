//# Dataset Example 
//This assumes you have the environmental PUEO_ROOT_DATA pointing at some simulated output

// load libPueoEvent
R__LOAD_LIBRARY(libpueoEvent) 

void keith_realPhi(int run = 1201, int entry_in  = 0) 
{

  // create a dataset using MC data
  pueo::Dataset d(run);
  //d.getEntry(entry);
  int totalevents = d.N();
  d.header();
  d.daqh();
  cout << "hey" << endl;
  cout << d.gimmeL2ReadoutTime() << endl;
  //int thisentry=entry;
  bool timetostop =false;
  int entry=entry_in;
  TH2D * gr = new TH2D("L2 masked b/c rate high","L2 Masked (rate too high); pol;phi",2,-0.5,1.5,24,-0.5,23.5);
  while(entry < totalevents){
    d.nextEvent();
    entry = d.current();
    d.header();
    d.daqh();
    //if((int) (d.gimmeL2Mask())!=0){
    //    cout << "found one: " << (int) d.gimmeL2Mask() << endl;
    //}
    for(int phi=0; phi<24;phi++){
      for(int pol=0;pol<2;pol++){
        if(d.IsThisPhiPolExcluded(phi,pol)) {
          //cout << phi <<"," << pol<<  " for readout time " << d.gimmeL2ReadoutTime() << endl;
          //timetostop=true;
          gr->Fill(pol,phi);
        }
      }
    }
    entry++;
    if(entry%10000==0){
      cout << entry << " at " << d.gimmeL2ReadoutTime() << endl;
    }
  }
  auto cc = new TCanvas("cc","", 800, 800);
  gr->Draw("colz");
  //gPad->SetLogz();
  //cc->Update();
  //cc->Modified();
  cc->SaveAs("test.pdf");
  cout << "done" << endl;
}

