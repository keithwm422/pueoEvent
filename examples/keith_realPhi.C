//# Dataset Example 
//This assumes you have the environmental PUEO_ROOT_DATA pointing at some simulated output

// load libPueoEvent
R__LOAD_LIBRARY(libpueoEvent) 

void keith_realPhi(int run = 1001, int entry_in  = 0) 
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
  //TH2D * gr = new TH2D("L2 masked b/c rate high","L2 Masked (rate too high); pol;phi",2,-0.5,1.5,24,0.5,24.5);
  TH2D* h_masked = new TH2D("h_masked", "L2 Masked Counts;phi ID;Pol ID", 24, 0.5, 24.5, 2, -0.5, 1.5);
  TH2D* h_total  = new TH2D("h_total",  "Total Entries;phi ID;Pol ID", 24, 0.5, 24.5, 2, -0.5, 1.5);
  // Turn off automatic error calculation issues during division
  h_masked->Sumw2();
  h_total->Sumw2();

  while(entry < totalevents){
    d.nextEvent();
    entry = d.current();
    d.header();
    d.daqh();
    //if((int) (d.gimmeL2Mask())!=0){
    //    cout << "found one: " << (int) d.gimmeL2Mask() << endl;
    //}
    for(int phi=1; phi<25;phi++){
      for(int pol=0;pol<2;pol++){
        h_total->Fill(phi, pol);
        if(d.IsThisPhiPolExcluded(phi,pol)) {
          //cout << phi <<"," << pol<<  " for readout time " << d.gimmeL2ReadoutTime() << endl;
          //timetostop=true;
          //gr->Fill(pol,phi);
          h_masked->Fill(phi, pol);
        }
      }
    }
    entry++;
    if(entry%10000==0){
      cout << entry << " at " << d.gimmeL2ReadoutTime() << endl;
    }
  }
  //auto cc = new TCanvas("cc","", 800, 800);
  //gr->Draw("colz");
  //gPad->SetLogz();
  //cc->Update();
  //cc->Modified();
    h_masked->Divide(h_masked, h_total, 1.0, 1.0, "B"); // "B" uses Binomial errors for fractions

    // 4. Drawing and Cosmetics
    TCanvas* cc = new TCanvas("c1", "Mask Map", 800, 400);
    gStyle->SetOptStat(0);       // Hide the statistical box
    gStyle->SetPalette(kBird); // e.g., kViridis or kBird look great for fractions
    
    h_masked->SetTitle("Fraction of Entries Masked per Channel/Bank");
    h_masked->GetZaxis()->SetRangeUser(0.0, 1.0); // Force colorbar from 0% to 100%
    
    // "COLZ" draws it as a heatmap with a colorbar axis
    h_masked->Draw("COLZ");

  cc->SaveAs("test.pdf");
  cout << "done" << endl;
}

