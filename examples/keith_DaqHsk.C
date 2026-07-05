//# Dataset Example 
//This assumes you have the environmental PUEO_ROOT_DATA pointing at some simulated output

// load libPueoEvent
R__LOAD_LIBRARY(libpueoEvent) 

void keith_DaqHsk(int run = 1201, int entry_in  = 0, int whichbit_in=0) 
{

  // create a dataset using MC data
  pueo::Dataset d(run);
  //d.getEntry(entry);
  int totalevents = d.N();
  d.header();
  d.daqh();
  cout << "hey" << endl;
  //int thisentry=entry;
  bool timetostop =false;
  int entry=entry_in;
  int whichbit = whichbit_in;
  TH2D * gr = new TH2D("L2tiggermap","DAQ HSK L2 Masked Bits to phi pol map; pol;phi",2,-0.5,1.5,24,0.5,24.5);
  //  TH2D* h_masked = new TH2D("h_masked", "L2 Masked Counts;phi ID;Pol ID", 24, 0.5, 24.5, 2, -0.5, 1.5);
  UInt_t thistest =0x00;
  thistest |= (1U << whichbit);;
  TString new_title = Form("L2 tigger to phi pol map Bit %d;pol;phi", whichbit);
  gr->SetTitle(new_title);

  while(entry < totalevents){
    d.nextEvent();
    entry = d.current();
    d.header();
    d.daqh();
    //if((int) (d.gimmeHeaderL2())!=0){
     //   cout << "found one: " << (int) d.gimmeHeaderL2() << endl;
    //}
    for(int phi=1; phi<25;phi++){
      for(int pol=0;pol<2;pol++){
        if(d.IsThisPhiPolExcluded(phi,pol,true,thistest)) {
          //cout << phi <<"," << pol<<  " for readout time " << d.gimmeL2ReadoutTime() << endl;
          //timetostop=true;
          gr->Fill(pol,phi);
        }
        
      }
    }
    entry++;
    if(entry%10000==0){
      cout << entry << " at " << d.gimmeHeaderL2() << endl;
    }
  }
  auto cc = new TCanvas("cc","", 800, 800);
  gr->Draw("colz");
  //gPad->SetLogz();
  //cc->Update();
  //cc->Modified();
  TString file_name = Form("DAQHSK_bit_map_check_%d.png", whichbit);
  cc->SaveAs(file_name);
  //cc->SaveAs("test.pdf");
  cout << "done" << endl;
}
